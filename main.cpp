#include "character.hpp"
#include "topology.hpp"
#include <iostream>
#include <vector>

int main(){
    std::vector<character_t> cts;
    cts.push_back(character_t("John", "JHN", 0.15f));
    cts.push_back(character_t("Arthur", "ART", 0.35f));
    cts.push_back(character_t("Jason", "JSN", 0.27f));
    cts.push_back(character_t("Luke", "LKE", 0.53f));

    topology_t top1(cts, 2, 2);

    top1.set_topology("JHN-ART-JSN-LKE-");
    
    for(auto& c : cts){
        std::cout << c.get_row() << " | " << c.get_column() << " |\n";
    }

    return 0;
}