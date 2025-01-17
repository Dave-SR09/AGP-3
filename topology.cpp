#include "topology.hpp"
#include "evaluation.hpp"
#include <vector>
#include <functional>
#include <algorithm>
#include <string>

topology_t::topology_t (std::vector<character_t>& ref, const int& width, const int& depth)
   : universal(&ref), swidth(width), sdepth(depth) {
    topology_score = 0;
}


void topology_t::set_topology(const std::string& constructor){
    int index = 0; 
    const int size = constructor.size();
    int square = 0; 

    topology_construction = constructor;

    while(index < size){
        std::string smallname;
        while(constructor[index] != '-' && index < size){
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
    
    update_hash();
}

void topology_t::update_constructor(){
    std::vector<character_t> sorted = *universal;
    // Sorting the characters based on their placement on the board.
    std::sort(sorted.begin(), sorted.end(), [=](character_t& a, character_t& b) { 
        int sqr1 = a.get_column() + a.get_row() * sdepth;
        int sqr2 = b.get_column() + b.get_row() * sdepth;
        return sqr1 > sqr2;
    });

    // Set the topology constructor to null.
    topology_construction = "";
    
    for(auto& character : sorted){
        topology_construction += character.mininame();
        topology_construction += '-';
    }
    // This is to remove the last '-'.
    topology_construction.pop_back();
    // And finally, update the hash.
    update_hash();
}

int topology_t::availaible_characters() const{
    return (*universal).size();
}

void topology_t::update_hash(){
    std::hash<std::string> hash_fn;
    topology_key = hash_fn(topology_construction);
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
    return topology_key;
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

std::vector<social_branch>* topology_t::get_tree(){
    return social_tree;
}

void topology_t::set_tree(std::vector<social_branch>& c_tree){
    social_tree = &c_tree;
}
