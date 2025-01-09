#include "character.hpp"
#include <string>
#include <functional>

character_t::character_t (const std::string& character1, const float& potential) : character_id(character1), social_potential(potential) {
    std::hash<std::string> hash_fn;
    hash_key = hash_fn(character1);
}

int character_t::get_column() const{
    return column;
}

int character_t::get_row() const{
    return row;
}

float character_t::get_potential() const {
    return social_potential;
}

size_t character_t::get_key()const{
    return this->hash_key;
}

std::string character_t::mininame() const {
    return smininame;
}

void character_t::set_column(const int& column){
    this->column=column;
}

void character_t::set_miniman(const std::string& mn){
    smininame = mn;
}

void character_t::set_row(const int& row){
    this->row=row;
}

void character_t::set_potential(const float& pot){
    social_potential = pot;
}