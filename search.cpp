#include "search.hpp"
#include "topology.hpp"
#include "evaluation.hpp"
#include "character.hpp"

#include <functional>
#include <algorithm>
#include <string>
#include <time.h>

void shuffle_topology(topology_t& top, int seedoff, std::vector<character_t>& characters){
    // Get the constants to save some time.
    const int top_depth = top.get_depth();
    const int top_width = top.get_width();
    const int availaible = characters.size();

    std::vector<std::pair<int, int>> occupied_position; 

    auto check_occupied = [&](const std::pair<int, int>& p){
        for(auto& pair_alpha : occupied_position){
            if(pair_alpha.first == p.first && pair_alpha.second == p.second)return true;
        }
        return false;
    };
    
    for(int i = 0; i < availaible; i++){
        srand(time(0)+seedoff);
        character_t *c = &characters[i];

        int selected_column = rand() % top_depth;
        int selected_row = rand() % top_width;
        
        // If the selected column & row are already occupied, we must go another round !
        int k = 0;
        while(check_occupied({selected_column, selected_row})){
            srand(time(0)+k+seedoff);
            selected_column = rand() % top_depth;
            selected_row = rand()%top_width;
            k++;
        }

        (*c).set_column(selected_column);
        (*c).set_row(selected_row);

        occupied_position.push_back({selected_column, selected_row});
    }

    top.update_constructor();
}

// Mutates a topology.
void mutate_topology(topology_t& top, int mutation_rate, int seedoff, std::vector<character_t>& characters){
    // Mutation sequence.
    for(int mut_seq = 0; mut_seq < mutation_rate; mut_seq++){
        srand(time(0) + mut_seq + seedoff);
        int iter_seq = 0; 
        int select_index1 = rand() % characters.size();
        int select_index2 = rand() % characters.size();

        while(select_index1 == select_index2){
            srand(time(0) + mut_seq + seedoff + iter_seq++);
            select_index2 = rand() % characters.size();
        }

        int temp_col = characters[select_index1].get_column();
        int temp_dep = characters[select_index1].get_row();

        characters[select_index1].set_column(characters[select_index2].get_column());
        characters[select_index1].set_row(characters[select_index2].get_row());

        characters[select_index2].set_column(temp_col);
        characters[select_index2].set_row(temp_dep);
    }

    top.update_constructor();
}

// Genetic algorithm search algorithm.
topology_t genetic_topology(std::vector<character_t>& primitives, Evalfunc_t eval, int n_children, int rounds, int mut_rate, int width, int depth){
    /*
        Note: the algorithm will adopt binary reproducation as in unisexual reproduction.
        Therefore, topologies won't crossover but compete against eachother.
        Each topology will multiply into its children and will compete against the others,
        where the fittest are selected to progress to the next round with added mutation.    
    */

    // The number of children must be even.
    if(n_children % 2 != 0)return;
    
    auto check_existance = [&](const std::vector<topology_t>& list, topology_t& t){
        for(auto& top : list){
            if(top.get_key() == t.get_key())return true;
        }
        return false;
    };

    std::vector<topology_t> population; 
    // Generate primitive population with children.
    for(int nch = 0; nch < n_children; nch++){
        int iter_seed = 0; // This is used in case of a random generation error.
        topology_t t1(primitives, width, depth);
        shuffle_topology(t1, 0, primitives);           
        while(check_existance(population, t1)){
            shuffle_topology(t1, iter_seed++, primitives);
        }
        population.push_back(t1);
    }
    
    
    for(int n_generation = 0; n_generation < rounds; n_generation++){
        // Evaluate all topologies.
        float avg_eval = 0; 
        for(auto& topo : population){
            float eval_value = eval(topo);
            avg_eval += eval_value;
            topo.set_score(eval_value);
        }
        // The average topology score used to select the fittest topologies.
        avg_eval /= population.size();
        std::vector<topology_t> fittest_population; 

        for(auto& member : population){
            if(member.get_score() >= avg_eval)fittest_population.push_back(member);
        }
        
        // Clear out the rest of the population, as the fittest elements are saved in another vector.
        // As precised, the algorithm picks and selects the fittest. Implying that the topologies 'compete'.
        population.clear();

        for(auto& fittest : fittest_population){
            topology_t child1 (fittest), child2 (fittest);
            // Mutate the parent topology twice but differently.
            mutate_topology(child1, mut_rate, 2, primitives);
            mutate_topology(child2, mut_rate, 4, primitives);
            int iter_seq = 0; 
            while(child2.get_key() == child1.get_key()){
                mutate_topology(child2, mut_rate, 4+iter_seq, primitives);
            }

            population.push_back(child1);
            population.push_back(child2);
        }
    }
    
    // Sort the last generation of topologies.
    std::sort(population.begin(), population.end(), [&](const topology_t& a, const topology_t& b){
        return a.get_score() > b.get_score();
    });
    // And pick the best (fittest) topology from the last generation.
    return population[population.size()-1];
}