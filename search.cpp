#include "search.hpp"
#include "topology.hpp"
#include "evaluation.hpp"
#include "character.hpp"

#include <functional>
#include <string>
#include <time.h>

void shuffle_topology(topology_t& top, std::vector<character_t>& characters){
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
        srand(time(0));
        character_t *c = &characters[i];

        int selected_column = rand() % top_depth;
        int selected_row = rand() % top_width;
        
        // If the selected column & row are already occupied, we must go another round !
        while(check_occupied({selected_column, selected_row})){
            srand(time(0));
            selected_column = rand() % top_depth;
            selected_row = rand()%top_width;
        }

        (*c).set_column(selected_column);
        (*c).set_row(selected_row);

        occupied_position.push_back({selected_column, selected_row});
    }

    top.update_constructor();
}