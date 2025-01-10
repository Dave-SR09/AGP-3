#include "evaluation.hpp"
#include "character.hpp"
#include "topology.hpp"
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
    top.set_score(log10(score) * 10);
    return log10(score)*10;
}

float dynamic_evaluation(topology_t& top, const std::vector<social_branch>& social_tree){
    float score = 0.0;
    for(auto& branch : social_tree){
        character_t *alpha = branch.alpha, *beta = branch.beta; 
        float dist = 
              powf(alpha->get_column() - beta->get_column(), 2)
            + powf(alpha->get_row() - beta->get_row(), 2);

        score += dist / branch.mutual_potential; 
    }
    top.set_score(log10(score)*10);
    return log10(score)*10;
}
