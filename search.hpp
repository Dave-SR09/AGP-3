#ifndef AGP3_SEARCH_INCLUDED
#define AGP3_SEARCH_INCLUDED

#include "topology.hpp"
#include "evaluation.hpp"
#include "character.hpp"
#include <functional>
#include <string>

// Includes simple random generator. and will include a complex analysis tree.

/// @brief Generates a random topology. 
void shuffle_topology(topology_t& top, std::vector<character_t>& characters);

#endif