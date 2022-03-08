//
//  MemberDatabase.hpp
//  proj4
//
//  Created by Andy on 3/3/22.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h
#include <string>
#include <vector>
#include "provided.h"
#include "RadixTree.h"


class PersonProfile;

class MemberDatabase
{
public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);//load into radix tree
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
private:
    RadixTree<std::vector<std::string>> pairToEmail;
    RadixTree<PersonProfile*> emailtoPerson;
    std::vector<PersonProfile*> people;
};

#endif /* MemberDatabase_h */
