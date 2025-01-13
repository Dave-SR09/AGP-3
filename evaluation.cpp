#include "evaluation.hpp"
#include "character.hpp"
#include "topology.hpp"
#include <iostream>
#include <cmath>

float static_evaluation(topology_t& top){
    const int nSquares = top.get_width() * top.get_depth();
    float score = 0.0; 
    for(int i = 0; i < nSquares; i++){
        for(int j = 0; j < nSquares; j++){
            if(i == j)continue; 
            character_t alpha = top.get_character(i);
            character_t beta = top.get_character(j);
            float dist = 
                    powf(alpha.get_column() - beta.get_column(), 2)
                +   powf(alpha.get_row() - beta.get_row(), 2);
            
            float communication_potential = 
               (alpha.get_potential() * beta.get_potential())/dist; 

            score += alpha.get_potential() / communication_potential; 
        }
    }
    
    // Score is evaluated in Rabhis-Stokers (RbStk) a special value made to evaluate configuration.
    return log10(score)*10;
}

float dynamic_evaluation(const std::vector<social_branch>& social_tree){
    float score = 0.0;
    for(auto& branch : social_tree){
        character_t *alpha = branch.alpha, *beta = branch.beta; 
        float dist = 
              powf(alpha->get_column() - beta->get_column(), 2)
            + powf(alpha->get_row() - beta->get_row(), 2);

        try {
            if(dist == 0) throw std::runtime_error("Division by zero either by selecting the same character.\n");
        }catch (const std::exception& e){
            std::cout << e.what();
        };

        score += dist / branch.mutual_potential; 
    }

    return log10(score)*10;
}
