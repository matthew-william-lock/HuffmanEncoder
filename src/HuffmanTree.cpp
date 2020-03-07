#include "HuffmanTree.h"

// Default Constructor
LCKMAT002::HuffmanTree::HuffmanTree(const std::unordered_map<char,int> & frequencyMap)
{
    using namespace std;

    std::cout<<"Number of characters:"<<frequencyMap.size()<<std::endl;
    auto it = frequencyMap.begin();
    while (it!=frequencyMap.end())
    {
        // std::shared_ptr<HuffmanNode> newNode = std::make_shared<HuffmanNode>(it->first,it->second);
        HuffmanNode newNode(it->first,it->second);
        cout<<it->first<<":"<<it->second<<endl;
        pQueue.push(newNode);
        it++;
    }    
    // printPqueue();
    int i =0;

    while (pQueue.size()>1) // Create Tree
    {
        auto poppedNode= pQueue.top(); // Get smallest node
        pQueue.pop();                  // Pop the node
        std::shared_ptr<HuffmanNode> leftChild = std::make_shared<HuffmanNode>(poppedNode.getC(),poppedNode.getFreq()); // Make shared pointer to new node object
        //std::shared_ptr<HuffmanNode> leftChild = std::make_shared<HuffmanNode>(poppedNode); // Make shared pointer to new node object
        leftChild->setLeftChild(poppedNode.getLeftChild());
        leftChild->setRightChild(poppedNode.getRightChild());

        poppedNode= pQueue.top(); // Get second smallest node
        pQueue.pop(); // Pop the node
        std::shared_ptr<HuffmanNode> rightChild = std::make_shared<HuffmanNode>(poppedNode.getC(),poppedNode.getFreq()); // Make shared pointer to new node object      
        //std::shared_ptr<HuffmanNode> rightChild = std::make_shared<HuffmanNode>(poppedNode); // Make shared pointer to new node object

        rightChild->setLeftChild(poppedNode.getLeftChild());
        rightChild->setRightChild(poppedNode.getRightChild());

        HuffmanNode newNode('0',leftChild->getFreq() +rightChild->getFreq()); // Create new internal node
        std::cout<<leftChild->getFreq() +rightChild->getFreq()<<" ";
        newNode.setLeftChild(leftChild); // Set left and right child of internal node
        newNode.setRightChild(rightChild);
        pQueue.push(newNode); //Push new node
        i++;
    }

    auto poppedNode= pQueue.top();
    std::cout<<std::endl<<"Queue node sum:"<<poppedNode.getFreq()<<std::endl;
    std::cout<<"Iterations:"<<i<<std::endl;

    pQueue.pop();                  // Pop the node
    root = std::make_shared<HuffmanNode>(poppedNode.getC(),poppedNode.getFreq()); // Make shared pointer to new node object
    root->setLeftChild(poppedNode.getLeftChild());
    root->setRightChild(poppedNode.getRightChild());

    std::cout<<"Size of PQueue:"<<pQueue.size()<<std::endl;;
}

// Move Constructor
LCKMAT002::HuffmanTree::HuffmanTree(HuffmanTree&& other) noexcept{
    // *this = std::move(other);  // invoke move assignment operator
}

// Destructort
LCKMAT002::HuffmanTree::~HuffmanTree(){root=nullptr;}

void LCKMAT002::HuffmanTree::printPqueue(){
    using namespace std;
    int sum=0;
    while (pQueue.size()>0)
    {
        auto node = pQueue.top();
        cout<<"c:\""<< node.getC()<<"\" Freq:"<< node.getFreq()<<endl;
        sum+=node.getFreq();
        pQueue.pop();

    }
    cout<<"Sum:"<<sum<<endl;
    
};

/* Given a binary tree, print its nodes in inorder*/
void LCKMAT002::HuffmanTree:: printInorder(std::shared_ptr<LCKMAT002::HuffmanNode> node,int &i,std::string &code) 
{ 
    using namespace std;

    if (node->getLeftChild()==nullptr&&node->getLeftChild()==nullptr)
    {
        cout << "LEAF("<<node->getC()<<":"<<node->getFreq() << " code:"<<code<<") "<<endl; 
        i++;
        return;
    }
    

    // if (node == nullptr) 
    //     return; 
  
    /* first recur on left child */
    auto tempLeft=code+"0";
    printInorder(node->getLeftChild(),i,tempLeft); 
  
    /* then print the data of node */
    // cout << node->getC()<<":"<<node->getFreq() << " "; 
  
    /* now recur on right child */
    auto tempRight=code+"1";
    printInorder(node->getRightChild(),i,tempRight); 
} 

/* Given a binary tree, print its nodes in inorder*/
void LCKMAT002::HuffmanTree:: printInorder()
{ 
    int i =0;
    std::string code;
    printInorder(root,i,code);
    std::cout<<std::endl<<"Number of chars:"<<i<<std::endl; 
} 

void LCKMAT002::HuffmanTree::buildCodeTable(std::shared_ptr<LCKMAT002::HuffmanNode> node,std::string &code){

    if (node->getLeftChild()==nullptr&&node->getLeftChild()==nullptr)
    {
        codeTable[node->getC()]=code;
        return;
    }

    auto tempLeft=code+"0";
    buildCodeTable(node->getLeftChild(),tempLeft); 

    auto tempRight=code+"1";
    buildCodeTable(node->getRightChild(),tempRight);

}

void LCKMAT002::HuffmanTree::buildCodeTable(){
    std::string code;
    buildCodeTable(root,code);    
}


