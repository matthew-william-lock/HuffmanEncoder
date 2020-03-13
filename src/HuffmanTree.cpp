#include "HuffmanTree.h"
#include <fstream>

// Default Constructor
LCKMAT002::HuffmanTree::HuffmanTree() {
    this->bitString="";
    this->root=nullptr;
    this->codeTable =std::unordered_map<char,std::string>();
    this->pQueue=std::priority_queue<LCKMAT002::HuffmanNode,std::vector<LCKMAT002::HuffmanNode>,myComparator>();
}

// Constructor
LCKMAT002::HuffmanTree::HuffmanTree(const std::unordered_map<char,int> & frequencyMap)
{
    using namespace std;

    std::cout<<"Number of characters:"<<frequencyMap.size()<<std::endl;
    auto it = frequencyMap.begin();
    while (it!=frequencyMap.end())
    {

        // cout<<"Point1"<<endl;
        HuffmanNode newNode(it->first,it->second);

        // cout<<"Point2"<<endl;
        cout<<it->first<<":"<<it->second<<endl;

        // cout<<"Point3"<<endl;
        pQueue.push(newNode);
        
        // cout<<"Point4"<<endl<<endl;
        it++;
    }    
    // printPqueue();
    int i =0;

    std::cout<<"Check point"<<std::endl;

    while (pQueue.size()>1) // Create Tree
    {
        auto poppedNode= pQueue.top(); // Get smallest node
        pQueue.pop();                  // Pop the node
        std::shared_ptr<HuffmanNode> leftChild = std::make_shared<HuffmanNode>(poppedNode.getC(),poppedNode.getFreq()); // Make shared pointer to new node object
        // std::shared_ptr<HuffmanNode> leftChild = std::make_shared<HuffmanNode>(poppedNode); // Make shared pointer to new node object
        leftChild->setLeftChild(poppedNode.getLeftChild());
        leftChild->setRightChild(poppedNode.getRightChild());

        poppedNode= pQueue.top(); // Get second smallest node
        pQueue.pop(); // Pop the node
        std::shared_ptr<HuffmanNode> rightChild = std::make_shared<HuffmanNode>(poppedNode.getC(),poppedNode.getFreq()); // Make shared pointer to new node object      
        // std::shared_ptr<HuffmanNode> rightChild = std::make_shared<HuffmanNode>(poppedNode); // Make shared pointer to new node object

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

// Assignment Operator
void LCKMAT002::HuffmanTree::operator=(const HuffmanTree &M ){
    this->pQueue=M.pQueue;
    this->root=M.root;
    this->codeTable=M.codeTable;
    this->bitString=M.bitString;
}

// Move Constructor
LCKMAT002::HuffmanTree::HuffmanTree(HuffmanTree&& other) noexcept{
    *this = std::move(other);  // invoke move assignment operator
}

// Copy Constructor
LCKMAT002::HuffmanTree::HuffmanTree(const HuffmanTree& other){
    *this = other;
}

// Move Assignment
LCKMAT002::HuffmanTree& LCKMAT002::HuffmanTree::operator=(HuffmanTree&& other) noexcept{
    if (this != &other) {
      pQueue = std::move(other.pQueue);
      root = std::move(other.root);
      codeTable=std::move(other.codeTable);
      bitString=std::move(other.bitString);
    }
    return *this;
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

void LCKMAT002::HuffmanTree::buildBitString(const std::string &fileName){
    bool success = buildBitString(codeTable,fileName);
}

bool LCKMAT002::HuffmanTree::buildBitString(const std::unordered_map<char,std::string> & bitmap,const std::string &fileName){

    std::ifstream inputFile;
    inputFile.open (fileName);

    if (inputFile.is_open())
    {
        char c;
        while (inputFile.get(c))
        {
            auto iterator = bitmap.find(c);
            if (iterator!=bitmap.end())
            {
                bitString=bitString+iterator->second;
                // std::cout<<c<<" "<<iterator->second<<std::endl;
                // std::cout<<"bitstring:"<<std::endl<<bitString<<std::endl<<std::endl;

            }
            else 
            {
                std::cout<<"Something went wrong creating the bitstring"<<std::endl;
                return false;
            }                
        }
        inputFile.close();
        std::cout<<"Final bitstring:"<<std::endl<<bitString<<std::endl;
        return true;
    }
    std::cout << "Unable to open input file"; 
    return false;
}

void LCKMAT002::HuffmanTree::writeBitString(const std::string &fileName)
{
    std::string file="../bin/"+fileName;

    std::ofstream outputFile;
    outputFile.open (file);

    if (outputFile.is_open())
    {
        for (size_t i = 0; i < bitString.length(); i++)
        {
            outputFile<<bitString.c_str()[i];
        }
        
    } else std::cout<<"Something went wrong while writing the bitstream"<<std::endl;

}