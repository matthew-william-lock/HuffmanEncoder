#include "HuffmanTree.h"

// Default Constructor
LCKMAT002::HuffmanTree::HuffmanTree(const std::unordered_map<char,int> & frequencyMap)
{
    auto it = frequencyMap.begin();
    while (it!=frequencyMap.end())
    {
        std::shared_ptr<HuffmanNode> newNode = std::make_shared<HuffmanNode>(it->first,it->second);
        // HuffmanNode newNode(it->first,it->second);
        pQueue.push(*newNode);
        it++;
    }    

}

// Move Constructor
LCKMAT002::HuffmanTree::HuffmanTree(HuffmanTree&& other) noexcept{
    // *this = std::move(other);  // invoke move assignment operator
}

// Destructort
LCKMAT002::HuffmanTree::~HuffmanTree(){root=nullptr;}

void LCKMAT002::HuffmanTree::printPqueue(){
    using namespace std;
    while (pQueue.size()>0)
    {
        HuffmanNode node = pQueue.top();
        cout<<"c:\""<< node.getC()<<"\" Freq:"<< node.getFreq()<<endl;
        pQueue.pop();

    }
    
};


