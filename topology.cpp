#include "topology.hpp"
#include <vector>
#include <functional>
#include <string>

topology_t::topology_t (std::vector<character_t>& ref, const int& width, const int& depth)
   : universal(&ref), swidth(width), sdepth(depth) {}


void topology_t::set_topology(const std::string& constructor){
    int index = 0; 
    const int size = constructor.size();

    while(index < size){
        std::string smallname;
        while(constructor[index] != '-'){
            smallname.push_back(constructor[index]);
            index++;
        }
        
        character_t *selected;
        for(auto& character : *universal){
            if(character.mininame() == smallname){
                selected = &character;
                break;
            }
        }
        if(selected == nullptr)return;

        selected->set_column(index % sdepth);
        selected->set_row((index / sdepth) % swidth);

        index++; 
    }
}

int topology_t::set_width(const int& nwidth){
   swidth = nwidth;
}

int topology_t::set_depth(const int& ndepth){
   sdepth = ndepth;
}

std::string topology_t::get_construction() const{
   return topology_construction;
}

size_t topology_t::get_key() const{
    std::hash<std::string> hash_fn;
    return hash_fn(topology_construction);
}

int topology_t::get_width() const{
    return swidth;
}

int topology_t::get_depth() const{
    return sdepth;
}