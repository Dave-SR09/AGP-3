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
void shuffle_topology(topology_t& top, int seedoff, std::vector<character_t>& characters);
/// @brief Mutates a topology depending on a mutation rate.
void mutate_topology(topology_t& top, int mutation_rate, int seedoff, std::vector<character_t>& characters);

typedef float (*Evalfunc_t)(topology_t&);
/// @brief Applying the rules of the genetic algorithm to determine and select the fittest topology.
/// @param primitives The primal population of each topological entity.
/// @param rounds The number of generations to simulate.
/// @param eval The evaluation method to be adopted. Note that a different method will generate other results.
/// @param mut_rate Mutation rate of the algorithm. A high mutation rate can destabilize quickly the algorithm, so be careful when picking it!
/// @param n_children The amount of children that is generated per generation. (Must be even).
/// @returns The fittest topology found after n generations consisting of the same primitive population.
topology_t genetic_topology(std::vector<character_t>& primitives, Evalfunc_t eval, int n_children, int rounds, int mut_rate, int width, int depth);

#endif