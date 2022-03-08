//
//  MatchMaker.hpp
//  proj4
//
//  Created by Andy on 3/3/22.
//

#ifndef MatchMaker_h
#define MatchMaker_h
#include "provided.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"

class MatchMaker
{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
    MemberDatabase database;
    AttributeTranslator translator;
};

#endif /* MatchMaker_h */
