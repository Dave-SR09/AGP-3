#ifndef AGP3_INTERFACE_INCLUDED
#define AGP3_INTERFACE_INCLUDED

#include <string>
#include <vector>
#include <fstream>

#include "character.hpp"
#include "evaluation.hpp"

/// @brief Basically extracting the binary from the file into a real string.
std::string buffer_out(std::ifstream& infile);

/// @brief Extracts all the characters from the source string. (Avoiding any brackets notation)
/// Extract character from the source string. exc1 for extract 1.
std::vector<character_t> ex_chars(const std::string& src);

/// @brief Extracts all the branches from the same file or other file.
/// Extract second from the source string pulling out the social tree. Characters must be pulled out before.
std::vector<social_branch> ex_branches(const std::string& src, std::vector<character_t>& characters);

#endif