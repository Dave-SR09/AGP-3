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

float dynamic_evaluation(topology_t& top){
    auto social_tree = top.get_tree();
    float score = 0.0;
    for(auto& branch : *social_tree){
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

// log (a/b) = log(a) - log(b)

float total_evaluation(topology_t& top){
    // Get both values from both evaluation techniques.
    float static_ev = static_evaluation(top);
    float dynamic_ev = dynamic_evaluation(top);
    // Return the difference of logs. We can determine the total evaluation raw as e^10 * (static_eval/dynamic_eval)
    // Static evaluation is discrimanatory, meaning we are evaluating position efficiency.
    // while Dynamic evaluation evaluates the potential of all the characters in the social tree.
    // Thus, dynamic and static are opposites in context. That's why we return the difference.
    return static_ev - dynamic_ev;
}