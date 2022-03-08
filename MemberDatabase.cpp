//
//  MemberDatabase.cpp
//  proj4
//
//  Created by Andy on 3/3/22.
//

#include "MemberDatabase.h"
#include "PersonProfile.h"
#include <fstream>

MemberDatabase::MemberDatabase()
{
    
}

MemberDatabase::~MemberDatabase()
{
    //std::vector<PersonProfile*>::iterator it;
    //for(it = people.begin();it!=people.end();)
    //{
        
        //delete *it;
            //it = people.erase(it);
    //}
}

bool MemberDatabase::LoadDatabase(std::string filename)
{
    std::ifstream file(filename);
    if (file.fail())
    {
        return false;
    }
    std::string line;
    std::vector<std::string> member;
    while(getline(file, line))
    {
        member.push_back(line);
        if(line.empty())//end of one member
        {
            std::string name = member[0];
            std::string email = member[1];
            int numPairs = std::stoi(member[2]);
            PersonProfile* newPerson = new PersonProfile(name, email);
            people.push_back(newPerson);
            for(int i = 3;i<3+numPairs;i++)
            {
                std::string attributeValue = member[i];
                std::vector<std::string>* emails = pairToEmail.search(attributeValue);
                if(emails!=nullptr)
                {
                    emails->push_back(email);
                }
                else
                {
                    std::vector<std::string> newVector;
                    newVector.push_back(email);
                    pairToEmail.insert(attributeValue, newVector);
                }
                
                
                std::string att;
                std:: string val;
                for(int k = 0;k<member[i].size();k++)
                {
                    if(member[i][k]==',')
                    {
                        att = member[i].substr(0, k);
                        val = member[i].substr(k+1, member[i].size());
                    }
                }
                AttValPair newPair = AttValPair(att, val);
                newPerson->AddAttValPair(newPair);
                
            }
            emailtoPerson.insert(email, newPerson);
            member.clear();
        }
    }
    return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{//check for duplicates 
    std::string sourceString = input.attribute+","+input.value;
    std::vector<std::string>* temp = pairToEmail.search(sourceString);
    if(temp!=nullptr)
    {
        return *temp;
    }
    else
    {
        std::vector<std::string> newVector;
        return newVector;
    }
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
    PersonProfile** temp = emailtoPerson.search(email);
    if(temp!=nullptr)
    {
        return *temp;
    }
    return nullptr;
}

