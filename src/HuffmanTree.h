#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <iostream>
#include <queue>          // std::priority_queue
#include <memory>
#include <unordered_map>
#include <functional>
#include <vector>
#include <bits/stdc++.h> 
#include <boost/shared_ptr.hpp> // C++03
#include <memory> // C++11


#include "HuffmanNode.h"


namespace LCKMAT002
{

    class myComparator 
    { 
    public: 
    int operator() (const HuffmanNode& p1, const HuffmanNode& p2) 
    { 
        return p2<p1; 
    } 
    };

    class HuffmanTree
    {

    private:

    std::shared_ptr<LCKMAT002::HuffmanNode> root;        
    std::priority_queue<LCKMAT002::HuffmanNode,std::vector<LCKMAT002::HuffmanNode>,myComparator> pQueue;


    public:

    // Special Members ===========================================================================================================

    // Default Constructor
    HuffmanTree(const std::unordered_map<char,int> & frequencyMap);

    // Move Constructor
    HuffmanTree(HuffmanTree&& other) noexcept;

    // Copy Constructor
    HuffmanTree(const HuffmanTree& other);

    // Assignment Operator
    void operator=(const HuffmanTree &M );

    // Move Assignment Operator
    HuffmanTree& operator=(HuffmanTree&& other) noexcept;

    // Print contents of Priority Queue
    void printPqueue();


    // Destructor
    ~HuffmanTree();

    //=============================================================================================================================   
    
    bool compare(const HuffmanNode& a, const HuffmanNode& b);



    };  
 
    
    
    

}
#endif