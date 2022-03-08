//
//  MatchMaker.cpp
//  proj4
//
//  Created by Andy on 3/3/22.
//

#include "MatchMaker.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include "PersonProfile.h"
#include "utility.h"
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
{
    database = mdb;
    translator = at;
}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
    const PersonProfile* person  = database.GetMemberByEmail(email);
    std::set<AttValPair> totalPairs;//set so no duplicates 
    for(int i = 0;i<person->GetNumAttValPairs();i++)//gets all compatible pairs for that person
    {
        AttValPair attval;
        person->GetAttVal(i, attval);
        std::vector<AttValPair> compatiblePairs = translator.FindCompatibleAttValPairs(attval);
        for(int k = 0;k<compatiblePairs.size();k++)
        {
            //std::cout << compatiblePairs[k].attribute << "," << compatiblePairs[k].value << std::endl;
            totalPairs.insert(compatiblePairs[k]);
        }
    }
    
    
    
    std::map<std::string, int> emailToCount;
    std::map<std::string, int>:: iterator mapit;
    std::set<AttValPair>::iterator it;
    it = totalPairs.begin();
    while(it!=totalPairs.end())//gets map with all emails and number of matches
    {
        std::vector<std::string> matchingMembers = database.FindMatchingMembers(*it);
        for(int i = 0;i<matchingMembers.size();i++)
        {
            
            mapit = emailToCount.find(matchingMembers[i]);
            if(mapit!=emailToCount.end())
            {
                mapit->second += 1;
            }
            else
            {
                emailToCount.insert({matchingMembers[i], 1});
            }
        }
        it++;
    }
    
    std::vector<EmailCount> compatiblePeople;
    mapit = emailToCount.begin();
    while(mapit!=emailToCount.end())//creates the emailCount vector
    {
        if(mapit->second>=threshold)
        {
            EmailCount newPerson = EmailCount(mapit->first, mapit->second);
            compatiblePeople.push_back(newPerson);
        }
        mapit++;
    }
    
    std::sort(compatiblePeople.begin(), compatiblePeople.end());
    return compatiblePeople;
    
    
}
