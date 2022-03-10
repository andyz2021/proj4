//
//  RadixTree.h
//  proj4
//
//  Created by Andy on 3/3/22.
//

#ifndef RadixTree_h
#define RadixTree_h
#include <string>

template <typename ValueType>
class RadixTree {
public:
     RadixTree()
    {
        root = new Node;
        root->str = "";
        root->endstr = false;
        root->parent = nullptr;
        for(int i = 0;i<128;i++)
        {
            root->children[i] = nullptr;
        }
        
    }
    ~RadixTree()
    {
        deleteNodes(root);
    }
     void insert(std::string key, const ValueType& value)
    {
        insertNode(key, value, root);
    }
     ValueType* search(std::string key) const
    {
        return findNode(key, root);
    }
    
private:
    struct Node
    {
        std::string str;
        ValueType value;
        bool endstr;
        Node* children[128];
        Node* parent;
    };
    Node* root;
    
    void deleteNodes(Node* root)
    {
        if(root==nullptr)
        {
            return;
        }
        for(int i = 0;i<128;i++)
        {
            if(root->children[i]!=nullptr)
            {
                deleteNodes(root->children[i]);
            }
        }
        delete root;
    }
    
    void createNode(Node* prevNode, std::string key, ValueType value, char startOfStr)
    {
        Node* n = new Node;
        prevNode->children[int(startOfStr)] = n;
        n->str = key;
        n->endstr = true;
        n->value = value;
        for(int i = 0;i<128;i++)
        {
            n->children[i] = nullptr;
        }
        n->parent = prevNode;
    }
    
    Node* createNonLeafNode(Node* prevNode, std::string key, char startOfStr)
    {
        Node* n = new Node;
        prevNode->children[int(startOfStr)] = n;
        n->str = key;
        n->endstr = false;
        for(int i = 0;i<128;i++)
        {
            n->children[i] = nullptr;
        }
        n->parent = prevNode;
        return n;
    }
    ValueType* findNode(std::string key, Node* n) const//find the matching node to the key
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
            while(key[i]==n->str[i] && i<key.size() && i<n->str.size())
            {
                i++;
            }
            if(i==key.size() && n->endstr == true)
            {
                return &(n->value);
            }
            else
            {
                return findNode(key.substr(i, key.size()), n);
            }
        }
        
    }
    
    void insertNode(std::string key, ValueType value, Node* n)
    {
        if(n->children[int(key[0])] != nullptr)// if the prefix is already in the tree
        {
            n=n->children[int(key[0])];//if that key starts with a certain letter that we already have
            int i = 0;
            while(key[i]==n->str[i]  && i<key.size() && i<n->str.size())
            {
                i++;
            }
            if(i<key.size() && i==n->str.size())//had slow, added slower
            {
                if(n->children[int(key[i])] == nullptr)
                {
                    createNode(n, key.substr(i, key.size()), value, key[i]);
                    return;
                }
                else//had slow and slowest, added slower, so rerun the insert
                {
                    insertNode(key.substr(i, key.size()), value, n);
                }
            }
            
            if(i==key.size() && i<n->str.size())//had slower, added slow
            {
                n->endstr = true;
                createNode(n, n->str.substr(i, n->str.size()), n->value, n->str[i]);//create new node with er with original value
                n->value = value;
                n->str = n->str.substr(0, i);
                return;
            }
            
            if(i<key.size() && i<n->str.size())//had water, added waste
            {
                    Node* p = createNonLeafNode(n->parent, key.substr(0, i), key[0]);//create wa node
                    
                    p->children[int(n->str[i])] = n;//link wa node to water
                    n->parent = p;
                    n->str = n->str.substr(i, n->str.size());//change water to ter
                    
                    createNode(p, key.substr(i, key.size()), value, key[i]);//create ste node
                    return;

            }
            
            if(i==key.size() && i==n->str.size())//found the word
            {
                n->value = value;
                n->endstr = true;
                return;
            }
            
        }
        else//create new node ex: we have slow, insert water
        {
            createNode(n, key, value, key[0]);
            return;
        }
    }
};

#endif /* RadixTree_h */
