#include "HuffmanNode.h"

namespace LCKMAT002{

bool operator<(const HuffmanNode& lhs, const HuffmanNode& rhs)
{
    return lhs.freq<rhs.freq;
}

HuffmanNode::HuffmanNode(char c, int freq){
    this->c=c;
    this->freq=freq;
}

HuffmanNode::~HuffmanNode(){
}

// Char getter
char HuffmanNode::getC() const{
    return this->c;
}

// Freq getter
int HuffmanNode::getFreq() const{
    return this->freq;
}

}