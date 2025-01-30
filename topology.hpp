#ifndef AGP3_TOPOLOGY_INCLUDED
#define AGP3_TOPOLOGY_INCLUDED

#include "evaluation.hpp"
#include "character.hpp"
#include <vector>
#include <functional>
#include <string>

/// @brief The base of AGP3 (The topology in the name)
/// @brief Set the foundation of all search and evaluation.
class topology_t {
    private:
      std::vector<character_t>* universal; // Reference to the universal set of students.
      std::vector<social_branch>* social_tree; // Reference to the universal set of students.
      // Topology differentiation parameters.
      std::string topology_construction;
      size_t topology_key;
      // Configuratory topology where width represents rows, and depth, columns.
      int swidth; int sdepth; // Width represents row, whilst depth represents columns.
      float topology_score;

    public:
      explicit topology_t (std::vector<character_t>& ref, const int& width, const int& depth);
      // Constructs the topology based on the provided constructor in the format '{small_name1}-{small_name2}...-{small_name n}-'
      void set_topology(const std::string& constructor); // Set the topology to the provided construction blueprint.
      void update_constructor(); // If a position is already entered, but the constructor doesn't follow.
      void set_width(const int& nwidth);
      void set_depth(const int& ndepth); 
      void set_tree(std::vector<social_branch>& c_tree);
      void update_hash();

      void set_score(const float& score); // Sets the fitness value of the topology.
      float get_score() const; 

      std::string get_construction() const;
      size_t get_key() const;
      int get_width() const;
      int availaible_characters() const;
      std::vector<social_branch>* get_tree();
      int get_depth() const;
      character_t get_character(const int& index) const;
};

#endif 