#ifndef AGP3_SEARCH_INCLUDED
#define AGP3_SEARCH_INCLUDED

#include "topology.hpp"
#include "evaluation.hpp"
#include "character.hpp"
#include <functional>
#include <string>

// Includes simple random generator. and will include a complex analysis tree.

/*
   == Intented to handle multiple searching functions:
      x = Random generative topologies
      x = Genetically fit topologies [Genetic algorithm to select the best topology]
      x = Statiscaly procedural fit topologies
   Since the last commit to this file, random generative topology search method is the only one implemented.
*/

/// @brief Generates a random topology. 
void shuffle_topology(topology_t& top, std::vector<character_t>& characters);

/// @brief Applying the rules of the genetic algorithm to determine and select the fittest topology.
/// @param primitives The primal population of each topological entity.
/// @param primitive_topology The primitive topology that roots all other children entities.
/// @param rounds The number of generations to simulate.
/// @returns The fittest topology found after n generations consisting of the same primitive population.
topology_t genetic_topology(std::vector<character_t>& primitives, topology_t& primitive_topology, int rounds);

#endif