//
//  RadixTree.h
//  proj4
//
//  Created by Andy on 3/3/22.
//

#ifndef RadixTree_h
#define RadixTree_h
#include <map>
#include <string>

template <typename ValueType>
class RadixTree {
public:
     RadixTree()
    {
        um = new std::map<std::string, ValueType>;
        root = new Node;
        root->str = "";
        root->str = false;
        for(int i = 0;i<128;i++)
        {
            root->children[i] = nullptr;
        }
        
    }
    ~RadixTree()
    {
        //um->clear();
        //delete um;
    }
     void insert(std::string key, const ValueType& value)
    {
        um->insert({key, value});
        /*
        typename std::map<std::string, ValueType>:: iterator mapit;
        mapit = um->find(key);
        if ( mapit == um->end())//not in the radixtree yet
        {
            um->insert({key, value});
        }
        else
        {
            std::vector<ValueType> newvec;
            newvec.push_back(value[0]);
            um->insert({key, newvec});
        }
         */
        Node* n = root;
        
        if(n->children[int(key[0])] != nullptr)// if the prefix is already in the tree
        {
            n=n->children[int(key[0])];//if that key starts with a certain letter that we already have
            int i = 0;
            while(key[i]==n->str[i])
            {
                i++;
            }
            if(i<key.size() && i==n->str.size())//had slow, added slower
            {
                if(n->children[int(key[i])] == nullptr)
                {
                    createNode(n, key.substr(i, key.size()-i, value, key[i]));
                }
                else
                {
                    
                }
            }
        }
        else//create new node
        {
            createNode(n, key, value, key[0]);
        }

    }
     ValueType* search(std::string key) const
    {
        
        typename std::map<std::string, ValueType>:: iterator mapit;
        mapit = um->find(key);
        if ( mapit == um->end())
        {
            return nullptr;
        }
        return &(mapit->second);
         
        //findNode(key, root);
    }
    
    std::string size() const
    {
        typename std::map<std::string, ValueType>:: iterator mapit;
        mapit = um->begin();
        
        return mapit->first;
    }
private:
    struct Node
    {
        std::string str;
        ValueType value;
        bool endstr;
        Node* children[128];
    };
    Node* root;
    
    void deleteNodes(Node* root)
    {
        if(root==nullptr)
        {
            return;
        }
        Node* p = root->children.begin();
        while(p!=root->children.end())
        {
            deleteNodes(p);
        }
        delete root;
    }
    
    void createNode(Node* prevNode, std::string key, ValueType value, char startOfStr)
    {
        Node* n = new Node;
        prevNode->children[int(startOfStr)] = n;
        n-> str = key;
        n->endstr = true;
        n->value = value;
        for(int i = 0;i<128;i++)
        {
            n->children = nullptr;
        }
    }
    ValueType* findNode(std::string key, Node* n)//find the matching node to the key
    {

        if((n->str == key || n->str=="") && n->endstr == true)
        {
            return &(n->value);
        }
        if(n->children[int(key[0])] == nullptr)
        {
            return nullptr;
        }
        else
        {
            n=n->children[int(key[0])];
            int i = 0;
            while(key[i]==n->str[i])
            {
                i++;
            }
            search(key.substr(i, key.size()-i), n);
        }
        
    }
    
    void insertNode(std::string key, ValueType value, Node* n)
    {
        if(n->children[int(key[0])] != nullptr)// if the prefix is already in the tree
        {
            n=n->children[int(key[0])];//if that key starts with a certain letter that we already have
            int i = 0;
            while(key[i]==n->str[i])
            {
                i++;
            }
            if(i<key.size() && i==n->str.size())//had slow, added slower
            {
                if(n->children[int(key[i])] == nullptr)
                {
                    createNode(n, key.substr(i, key.size()-i, value, key[i]));
                }
                else
                {
                    insertNode(key.substr(i, key.size()-i), value, n);
                }
            }
            
            if(i==key.size() && i<n->str.size())//had slower, added slow
            {
                n->endstr = true;
                createNode(n, n->str.substr(i, n->str.size()-i), value, n->str[i]);
                return;
            }
            
            if(i<key.size() && i<n->str.size())//had water, added waste
            {
                //check if the first letter is in a subnode,
                insertNode(key.substr(i, key.size()-i), value, n);
            }
            
        }
        else//create new node
        {
            createNode(n, key, value, key[0]);
            return;
        }
    }
    std::map <std::string, ValueType>* um;//CHANGE TO RADIXTREE LATER
};

#endif /* RadixTree_h */
