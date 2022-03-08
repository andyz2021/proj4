//
//  PersonProfile.hpp
//  proj4
//
//  Created by Andy on 3/3/22.
//

#ifndef PersonProfile_h
#define PersonProfile_h
#include <string>
#include "provided.h"
#include "RadixTree.h"
#include <vector>
#include <set>

class PersonProfile
{
public:
    PersonProfile(std::string name, std::string email);
    
    std::string GetName() const;
    std::string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
    
private:
    std::string n_name;
    std::string n_email;
    RadixTree<std::set<std::string>> AttValMap;
    std::vector<AttValPair> pairs;
};

#endif /* PersonProfile_h */
