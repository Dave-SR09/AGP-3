#include "topology.hpp"
#include <vector>
#include <functional>
#include <string>

topology_t::topology_t (std::vector<character_t>& ref, const int& width, const int& depth)
   : universal(&ref), swidth(width), sdepth(depth) {}


void topology_t::set_topology(const std::string& constructor){
    int index = 0; 
    const int size = constructor.size();
    int square = 0; 
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

        selected->set_column((square) % sdepth);
        selected->set_row(((square) / sdepth)%swidth);

        index++;
        square++; 
    }
}

void topology_t::set_width(const int& nwidth){
   swidth = nwidth;
}

void topology_t::set_score(const float& score){
    topology_score = score;
}

float topology_t::get_score() const{
    return topology_score;
}

void topology_t::set_depth(const int& ndepth){
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

character_t topology_t::get_character(const int& index) const {
    return (*universal).at(index);
}