//
//  AttributeTranslator.cpp
//  proj4
//
//  Created by Andy on 3/3/22.
//

#include "AttributeTranslator.h"
#include <fstream>
AttributeTranslator::AttributeTranslator()
{
    
}

bool AttributeTranslator::Load(std::string filename)
{

    std::ifstream file(filename);
    if (file.fail() || !file)
    {
        return false;
    }
    std::string line;
    while(getline(file, line))
    {
        int i = 0;
        int track = 0;
        int comma = 0;
        std::string source;
        std::string compatible_attribute;
        while(line[i] != '\n')
        {
            if(line[i] == ',' && track == 1)//separator between source and compatible
            {
                source = line.substr(0, i);
                comma = i;
            }
            if(line[i] == ',' && track == 2)//separator between compatible value and compatible attribute
            {
                compatible_attribute = line.substr(comma+1, i-(comma+1));
                comma = i;
            }
            if(line[i]==',')
            {
                track++;
            }
            i++;
        }
        std::string compatible_value = line.substr(comma+1, i);
        std::vector<AttValPair>* temp = SourceMatch.search(source);
        AttValPair newPair = AttValPair(compatible_attribute, compatible_value);
        if(temp!=nullptr)
        {
            temp->push_back(newPair);
        }
        else
        {
            std::vector<AttValPair> newVector;
            newVector.push_back(newPair);
            SourceMatch.insert(source, newVector);
        }
    }
    return true;

}


std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const//Needs to check for duplicates
{
    std::string sourceString = source.attribute+","+source.value;
    std::vector<AttValPair>* temp = SourceMatch.search(sourceString);
    if(temp!=nullptr)
    {
        return *temp;
    }
    else
    {
        std::vector<AttValPair> newVector;
        return newVector;
    }
}

