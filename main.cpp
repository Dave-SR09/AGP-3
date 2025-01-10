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

    topology_t top1(cts, 2, 2);

    top1.set_topology("JHN-JSN-ART-LKE-");
    static_evaluation(top1);
    
    for(auto& c : cts){
        std::cout << c.get_id() << ": " << c.get_row() << " | " << c.get_column() << " |\n";
    }
    
    std::cout << "Topology score: " << top1.get_score() << " Rbs.\n"; 

    return 0;
}