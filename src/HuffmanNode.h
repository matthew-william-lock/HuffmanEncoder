
#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H


#include <memory> // C++11

namespace LCKMAT002
{
    class HuffmanNode
    {

    private:

    char c;
    int freq;

    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;


    public:


    HuffmanNode(char c, int freq);
    ~HuffmanNode();

    friend bool operator<(const HuffmanNode& l, const HuffmanNode& r);    

    // Char getter
    char getC() const;

    // Freq getter
    int getFreq() const;

    };

    bool operator<(const HuffmanNode& lhs, const HuffmanNode& rhs); 
    
   
} // namespace LCKMAT002

#endif