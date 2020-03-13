#include "HuffmanNode.h"

namespace LCKMAT002{

    // Default Constructor
LCKMAT002::HuffmanNode::HuffmanNode(): c(), freq(0) {
};

// Smaller than operator
bool operator<(const HuffmanNode& lhs, const HuffmanNode& rhs)
{
    return lhs.freq<rhs.freq;
}

HuffmanNode::HuffmanNode(char c, int freq){
    this->c=c;
    this->freq=freq;
    this->left=nullptr;
    this->right=nullptr;
}

HuffmanNode::~HuffmanNode(){
}

// Move Constructor
HuffmanNode::HuffmanNode(HuffmanNode&& other) noexcept{
    *this = std::move(other);  // invoke move assignment operator
    other.c=0;
    other.freq=0;
    other.right=nullptr;
    other.left=nullptr;
    // std::cout<<"MOVE"<<std::endl;
}

// // Assignment Operator
void HuffmanNode::operator=(const HuffmanNode &M ){
    this->c=M.c;
    this->freq=M.freq;
    this->left=M.left;
    this->right=M.right;
    // std::cout<<"Called"<<std::endl;;
    // // std::cout<<"Assign"<<std::endl;
}

// Copy Constructor
HuffmanNode::HuffmanNode(const HuffmanNode& other){
    *this = other;
    // std::cout<<"Copy";
}

// Move Assignment
HuffmanNode& HuffmanNode::operator=(HuffmanNode&& other) noexcept{
    if (this != &other) {
      this->left=other.right;
      this->right=other.right;
      this->c=other.c;
      this->freq=other.freq;
    }
    return *this;
}


// Char getter
char HuffmanNode::getC() const{
    return this->c;
}

// Freq getter
int HuffmanNode::getFreq() const{
    return this->freq;
}

std::shared_ptr<HuffmanNode> HuffmanNode::getLeftChild(){
    return left;
}

std::shared_ptr<HuffmanNode> HuffmanNode::getRightChild(){
    return right;
}



void HuffmanNode::setLeftChild(std::shared_ptr<HuffmanNode> left)
{
    this->left = left;
}

void HuffmanNode::setRightChild(std::shared_ptr<HuffmanNode> right)
{
    this->right=right;
}

}