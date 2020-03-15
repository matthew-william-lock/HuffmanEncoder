#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <iostream>
#include <fstream>
#include <queue>          // std::priority_queue
#include <bits/stdc++.h> 
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

    std::unordered_map<char,int> frequencyMap;
    std::priority_queue<LCKMAT002::HuffmanNode,std::vector<LCKMAT002::HuffmanNode>,myComparator> pQueue;
    std::unordered_map<char,std::string> codeTable;
    
    std::shared_ptr<LCKMAT002::HuffmanNode> root;    
    std::string bitString;   
    int bits;

    
    // Internal Calls
    void buildCodeTable(std::shared_ptr<LCKMAT002::HuffmanNode> node,std::string &code);
    bool buildBitString(const std::unordered_map<char,std::string> & bitmap,const std::string &fileName);
    void writeBitString();

    public:

    // Special Members ===========================================================================================================

    // Default Constructor
    HuffmanTree();

    // Constructor
    HuffmanTree(const std::unordered_map<char,int> & frequencyMap);

    // Move Constructor
    HuffmanTree(HuffmanTree&& other) noexcept;

    // Copy Constructor
    HuffmanTree(const HuffmanTree& other);

    // Assignment Operator
    void operator=(const HuffmanTree &M );

    // Move Assignment Operator
    HuffmanTree& operator=(HuffmanTree&& other) noexcept;

    // Destructor
    ~HuffmanTree();

    //=============================================================================================================================   

    // Getters
    std::unordered_map<char,int> getFrequencyMap() const;
    std::priority_queue<LCKMAT002::HuffmanNode,std::vector<LCKMAT002::HuffmanNode>,myComparator> getPQueue() const;
    std::unordered_map<char,std::string> getCodeTable() const;
    std::shared_ptr<LCKMAT002::HuffmanNode> getRoot() const;
    std::string getBitString() const;

    // Build Frequency map
    bool buildFrequencymap(std::string fileName);

    // Build Priority Queue
    bool buildPriorityQueue();

    // Build Tree
    bool buildTree();

    // Build Code Table
    bool buildCodeTable();

    // Build Bit String
    bool buildBitString(const std::string &fileName);

    // Write BitString
    bool writeBitString(const std::string &fileName);

    // Build BitStream
    bool buildBitstream(std::string fileName);

    // Print contents of Priority Queue
    void printPqueue();

    // Decode binary file using header
    bool decodeFile(std::string fileName);

    // Build decoded bitString
    bool buildDecodedBitString(std::string inputFileName);

    // Decode and write decoded bitString
    bool decodeBitString(std::string outputFileName);

    };  

}
#endif