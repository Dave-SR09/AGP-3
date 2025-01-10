#include "character.hpp"
#include "evaluation.hpp"
#include "topology.hpp"
#include <iostream>
#include <vector>
#include <cmath>

int main(){
    std::vector<character_t> cts;
    cts.push_back(character_t("John", "JHN", 1.15f));
    cts.push_back(character_t("Arthur", "ART", 0.35f));
    cts.push_back(character_t("Jason", "JSN", 0.27f));
    cts.push_back(character_t("Luke", "LKE", 0.53f));
    cts.push_back(character_t("Georges", "GRG", 0.53f));
    cts.push_back(character_t("Wilock", "WLK", 0.23f));
    cts.push_back(character_t("Dell", "DLL", 0.79f));
    cts.push_back(character_t("Dylan", "DYN", 0.25f));
    cts.push_back(character_t("Zack", "ZCK", 0.39f));

    std::vector<social_branch> s_tree;
    s_tree.push_back({&cts[0], &cts[1], 10.16f});
    s_tree.push_back({&cts[0], &cts[5], 3.75f});

    topology_t top1 = topology_t(cts, 3, 3);
    top1.set_topology("JHN-JSN-LKE-GRG-WLK-DLL-ZCK-DYN-ART");

    dynamic_evaluation(top1, s_tree);

    for(auto& c : cts){
        std::cout << c.get_id() << ": " << c.get_row() << " | " << c.get_column() << " |\n";
    }
    
    std::cout << "Topology configuration: " << top1.get_construction() << ".\n";
    std::cout << "Topology key: " << std::hex << top1.get_key() << ".\n";
    std::cout << "Topology score: " << top1.get_score() << " Rbs.\n"; 

    return 0;
}