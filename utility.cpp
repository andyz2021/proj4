//
//  utility.cpp
//  proj4
//
//  Created by Andy on 3/3/22.
//

#include "utility.h"
#include "provided.h"

bool operator<(const EmailCount& a, const EmailCount& b)
{
    if(a.count!=b.count)
    {
        return a.count>b.count;
    }
    else
    {
        return a.email<b.email;
    }
}

bool operator<(const AttValPair& a, const AttValPair& b)
{
    if(a.attribute!=b.attribute)
    {
        return a.attribute<b.attribute;
    }
    else
    {
        return a.value<b.value;
    }
}
