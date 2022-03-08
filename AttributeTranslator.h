//
//  AttributeTranslator.hpp
//  proj4
//
//  Created by Andy on 3/3/22.
//

#ifndef AttributeTranslator_h
#define AttributeTranslator_h
#include <string>
#include <vector>
#include "provided.h"
#include "RadixTree.h"

class AttributeTranslator
{
public:
    AttributeTranslator();
    bool Load(std::string filename);//load into radix tree
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;//iterate through radix tree
private:
    RadixTree<std::vector<AttValPair>> SourceMatch;
};

#endif /* AttributeTranslator_h */
