#ifndef AGP3_EVALUATOR_INCLUDED
#define AGP3_EVALUATOR_INCLUDED

#include "evaluation.hpp"
#include "character.hpp"
#include "topology.hpp"
#include <vector>
#include <functional>
#include <string>

// To obtain the real evaluation is the static evaluation - dynamic evaluation.
// As static evaluation is reciprocal whilst dynamic is simply potential measure.
// Knowing as potential increases the fitness of the topology lowers.

/// @brief A fundamental composite of a social tree.
struct social_branch {
    character_t *alpha; 
    character_t *beta;
    // The shared potential between both members of the social branch.
    float mutual_potential; 
};

/// @brief An evaluation method that doesn't involve any social tree except simple social potential measure.
/// @brief Currently a slow method of evaluation, but it is crucial!
float static_evaluation(topology_t& top);

/// @brief Involves simply social tree evaluation excludes the overall static evaluation.
/// @brief Generally, it doesn't involve the topology itself, as the tree is independant from the topology.
float dynamic_evaluation(const std::vector<social_branch>& social_tree);

#endif