#include <string>

#ifndef CHARACTER_INCLUDED
#define CHARACTER_INCLUDED

class character_t {
    private:
       std::string character_id;
       std::string smininame; 
       size_t hash_key;
       int column;
       int row;

       float social_potential;
    public: 
       explicit character_t (const std::string& character1, const float& potential);
       explicit character_t (const std::string& character1, const std::string& mini1, const float& potential);

       int get_column() const;
       int get_row() const;
       float get_potential() const;
       std::string mininame() const;
       std::string get_id()const;
       size_t get_key()const;

       void set_column(const int& column);
       void set_row(const int& row);
       void set_miniman(const std::string& mn);
       void set_potential(const float& pot);
};

#endif 