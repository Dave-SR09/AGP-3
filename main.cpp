#include "character.hpp"
#include "evaluation.hpp"
#include "topology.hpp"
#include "interface.hpp"
#include "search.hpp"
#include <iostream>
#include <vector>
#include <cmath>

int main(int argc, char** argv){
    std::ifstream in("tst1.txt", std::ios_base::in);
    auto al = ex_chars(buffer_out(in));
    topology_t t1(al, 4, 2);

    for(auto chara : al){
        std::cout << chara.get_column() << " | " << chara.get_row() << " |\n";
    }

    std::cout << "Topology construction: " << t1.get_construction() << " |\nScore topology:" << t1.get_score() << "\n";

    in.close();
    return 0;
}