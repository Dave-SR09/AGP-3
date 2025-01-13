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
    auto al = exc1(buffer_out(in));
    auto tree = exc2(buffer_out(in), al);

    for(auto& b : tree){
        std::cout << b.alpha->get_id() << " === " << b.beta->get_id() << " <= " << b.mutual_potential << "\n";
    }
    in.close();
    return 0;
}