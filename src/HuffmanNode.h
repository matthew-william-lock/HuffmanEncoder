
#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H


#include <memory> // C++11
#include <iostream>

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

    // Special Members ===========================================================================================================

    // Default Constructor
    HuffmanNode();

    // Custom Constructor
    HuffmanNode(char c, int freq);

    ~HuffmanNode();

    // Move Constructor
    HuffmanNode(HuffmanNode&& other) noexcept;

    // Assignment Operator
    void operator=(const HuffmanNode &M );

    // Move Assignment Operator
    HuffmanNode& operator=(HuffmanNode&& other) noexcept;

    // Copy Constructor
    HuffmanNode(const HuffmanNode& other);

    //=============================================================================================================================      

    // Smaller than operator
    friend bool operator<(const HuffmanNode& l, const HuffmanNode& r);    

    // Getters
    char getC() const;
    int getFreq() const;
    std::shared_ptr<HuffmanNode> getLeftChild() const;
    std::shared_ptr<HuffmanNode> getRightChild() const;

    // Setters
    void setLeftChild(std::shared_ptr<HuffmanNode> left);
    void setRightChild(std::shared_ptr<HuffmanNode> right);

    };


    // Smaller than operator
    bool operator<(const HuffmanNode& lhs, const HuffmanNode& rhs); 

;
    
   
} // namespace LCKMAT002

#endif