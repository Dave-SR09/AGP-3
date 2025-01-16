#include "interface.hpp"
#include "character.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

std::string buffer_out(std::ifstream& infile){
    std::string buffout; 
    while(!infile.eof())buffout.push_back(infile.get());
    return buffout;
}

/// @brief Extracts all the characters from the source string. (Avoiding any brackets notation)
/// Extract character from the source string. ex_chars for extract 1.
std::vector<character_t> ex_chars(const std::string& src){
    // Kept a repository to handle pulling out.
    std::vector<character_t> pulled_out;
    int k = 0; 

    while(k < src.size()){
        // The first bracket of the character.
        if(src[k] == '{'){
            k++;
            // Identifier 1 ; Small name 1 ; Social potential.
            std::string id1, t_sm1, sp; 
            while(src[k] != ','){
                id1.push_back(src[k]);
                k++;
            }
            k++;
            while(src[k] != ','){
                t_sm1.push_back(src[k]);
                k++;
            }
            k++;

            std::string sm1;
            for(auto& ch : t_sm1){
                if(ch == ' ')continue;
                sm1.push_back(ch);
            }

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
std::vector<social_branch> ex_branches(const std::string& src, std::vector<character_t>& characters){
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

            std::cout << alpha << " | " << beta << " | " << mutpt << " |\n";
            // Pushes out the social branch into the social tree.
            social_tree.push_back({&characters[std::stoi(alpha)],&characters[std::stoi(beta)],std::stof(mutpt)});
        }
        k++;
    }
    return social_tree;
}