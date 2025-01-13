#include "interface.hpp"
#include "character.hpp"
#include "evaluation.hpp"

#include <string>
#include <vector>

/// @brief Extracts all the characters from the source string. (Avoiding any brackets notation)
/// Extract character from the source string. exc1 for extract 1.
std::vector<character_t> exc1(const std::string& src){
    // Kept a repository to handle pulling out.
    std::vector<character_t> pulled_out;
    int k = 0; 

    while(k < src.size()){
        // The first bracket of the character.
        if(src[k] == '{'){
            k++;
            // Identifier 1 ; Small name 1 ; Social potential.
            std::string id1, sm1, sp; 
            while(src[k] != ','){
                id1.push_back(src[k]);
                k++;
            }
            k++;
            while(src[k] != ','){
                sm1.push_back(src[k]);
                k++;
            }
            k++;
            while(src[k] != '}'){
                sp.push_back(src[k]);
                k++;
            }

            pulled_out.push_back(character_t(id1, sm1, std::stof(sp)));               
        }
        k++;
    }

    return pulled_out;
}

/// @brief Extracts all the branches from the same file or other file.
/// Extract second from the source string pulling out the social tree.
std::vector<social_branch> exc2(const std::string& src, std::vector<character_t>& characters){
    // Keep track of the social tree, the social tree is submitted on to change.
    std::vector<social_branch> social_tree;
    // Keep track of the index.
    int k = 0; 
    while(k < src.size()){
        if(src[k] == '['){
            // Stored abstracted tokens.
            std::string alpha, beta, mutpt; 
            // Token extraction from the tuple.
            while(src[k] != ','){
                alpha.push_back(src[k]);
                k++;
            }
            k++;
            while(src[k] != ','){
                beta.push_back(src[k]);
                k++;
            }
            k++;
            // Get over the end bracket to close and halt extraction.
            while(src[k] != ']'){
                mutpt.push_back(src[k]);
                k++;
            }
            // Pushes out the social branch into the social tree.
            social_tree.push_back({&characters[std::stoi(alpha)], &characters[std::stoi(beta)], std::stof(mutpt)});
        }
        k++;
    }
    return social_tree;
}