//
//  PersonProfile.cpp
//  proj4
//
//  Created by Andy on 3/3/22.
//

#include "PersonProfile.h"



PersonProfile::PersonProfile(std::string name, std::string email)
{
    n_name = name;
    n_email = email;
}


std::string PersonProfile::GetName() const
{
    return n_name;
}


std::string PersonProfile::GetEmail() const
{
    return n_email;
}


void PersonProfile::AddAttValPair(const AttValPair& attval)//Still needs to check for duplicates 
{
    std::set<std::string>* temp = AttValMap.search(attval.attribute);
    if(temp!=nullptr)
    {
        temp->insert(attval.value);
        pairs.push_back(attval);
    }
    else
    {
        std::set<std::string> newset;
        newset.insert(attval.value);
        AttValMap.insert(attval.attribute, newset);
        pairs.push_back(attval);
    }
     
}

int PersonProfile::GetNumAttValPairs() const
{
    return pairs.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
    if(attribute_num<pairs.size() && attribute_num>=0)
    {
        attval = pairs[attribute_num];
        return true;
    }
    return false;
}
