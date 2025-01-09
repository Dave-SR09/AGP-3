#ifndef AGP3_TOPOLOGY_INCLUDED
#define AGP3_TOPOLOGY_INCLUDED

#include "character.hpp"
#include <vector>
#include <functional>
#include <string>

/// @brief The base of AGP3 (The topology in the name)
class topology_t {
    private:
       std::vector<character_t>* universal; // Reference to the universal set of students.
       // Topology differentiation parameters.
       std::string topology_construction;
       size_t topology_key;
       // Configuratory topology where width represents rows, and depth, columns.
       int swidth; int sdepth;
    public:
       explicit topology_t (std::vector<character_t>& ref, const int& width, const int& depth);
       void set_topology(const std::string& constructor); // Set the topology to the provided construction blueprint.
       int set_width(const int& nwidth);
       int set_depth(const int& ndepth); 

       std::string get_construction() const;
       size_t get_key() const;
       int get_width() const;
       int get_depth() const;
};

#endif 