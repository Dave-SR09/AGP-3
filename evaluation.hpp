#ifndef AGP3_EVALUATOR_INCLUDED
#define AGP3_EVALUATOR_INCLUDED

#include "evaluation.hpp"
#include "character.hpp"
#include "topology.hpp"

/// @brief An evaluation method that doesn't involve any social tree except simple social potential measure.
/// @brief Currently a slow method of evaluation, but it is crucial!
void static_evaluation(topology_t& top);

#endif