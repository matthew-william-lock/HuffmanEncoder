#include "HuffmanTree.h"
#include <fstream>

// Special Members ===========================================================================================================

// Custom Constructor
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
    this->frequencyMap=M.frequencyMap;
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
      frequencyMap=std::move(other.frequencyMap);
    }
    other.frequencyMap=std::unordered_map<char,int> ();
    other.pQueue=std::priority_queue<LCKMAT002::HuffmanNode,std::vector<LCKMAT002::HuffmanNode>,myComparator>();
    other.codeTable=std::unordered_map<char,std::string>();
    other.root=nullptr;
    other.bitString=std::string();
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

//=============================================================================================================================  

// Build Frequency Table
bool LCKMAT002::HuffmanTree:: buildFrequencymap(std::string fileName){
    using namespace std;
    ifstream inputFile;
    inputFile.open (fileName);
    if (inputFile.is_open())
    {
        char c;        
        while (inputFile.get(c))
        {
            auto iterator = frequencyMap.find(c);
            if (iterator!=frequencyMap.end()) iterator -> second++;
            else frequencyMap[c]=1;                
        }
        inputFile.close(); 

        //Print Result
        std::cout<<"Number of characters:"<<frequencyMap.size()<<std::endl;
        auto it = frequencyMap.begin();
        while (it!=frequencyMap.end())
        {
            cout<<it->first<<":"<<it->second<<endl;
            it++;
        }
    }
    else
    {
        cout << "Unable to open input file"; 
        return false;
    }
    return true; 
}

// Build Priority Queue
bool LCKMAT002::HuffmanTree:: buildPriorityQueue(){
    using namespace std;
    if (frequencyMap.size()>1)
    {
        auto it = frequencyMap.begin();
        while (it!=frequencyMap.end())
        {
            HuffmanNode newNode(it->first,it->second);
            pQueue.push(newNode);
            it++;
        }
        cout<<"COMPLETE"<<endl; 
    }
    else
    {
        cout<<"EMPTY FREQUENCY TABLE"<<endl;
        return false;
    }
    return true;  
}

// Build Tree
bool LCKMAT002::HuffmanTree:: buildTree(){
    using namespace std;
    if (pQueue.size()>1)
    {
        int i =1;
        while (pQueue.size()>1) // Create Tree
        {            
            std::shared_ptr<HuffmanNode> leftChild = std::make_shared<HuffmanNode>(pQueue.top()); 
            pQueue.pop();                                                                         

            std::shared_ptr<HuffmanNode> rightChild = std::make_shared<HuffmanNode>(pQueue.top());
            pQueue.pop(); 

            HuffmanNode newNode('0',leftChild->getFreq() +rightChild->getFreq()); // Create new internal node
            std::cout<<leftChild->getC() <<":"<<leftChild->getFreq() <<+" + "<< rightChild->getC() <<":"<< rightChild->getFreq()<<" = 0:"<<leftChild->getFreq()+rightChild->getFreq()<<endl ;
            newNode.setLeftChild(leftChild); // Set left and right child of internal node
            newNode.setRightChild(rightChild);
            pQueue.push(newNode); //Push new node
            i++;
        }        
        root = std::make_shared<HuffmanNode>(pQueue.top()); // Make shared pointer to new node object
        cout<<"Pop left "<<root->getRightChild()->getC() <<":"<<root->getRightChild()->getFreq()<<endl;
        pQueue.pop();                                       // Pop the node
        std::cout<<"Queue node sum:"<<root->getFreq()<<std::endl;
        std::cout<<"Leaf nodes:"<<i<<std::endl;
        cout<<"COMPLETE"<<endl; 
    }
    else
    {
        cout<<"EMPTY PRIORITY QUEUE"<<endl;
        return false;
    }
    return true;  
}

void LCKMAT002::HuffmanTree::buildCodeTable(std::shared_ptr<LCKMAT002::HuffmanNode> node,std::string &code){
    if (node->getLeftChild()==nullptr&&node->getLeftChild()==nullptr)
    {
        codeTable[node->getC()]=code;
        std::cout<<node->getC()<<":"<<code<<std::endl;
        return;
    }
    auto tempLeft=code+"0";
    buildCodeTable(node->getLeftChild(),tempLeft); 
    auto tempRight=code+"1";
    buildCodeTable(node->getRightChild(),tempRight);
}

// Build Code Table
bool LCKMAT002::HuffmanTree::buildCodeTable(){
    std::string code;
    buildCodeTable(root,code);
    if (codeTable.size()<1) {
        std::cout<<"ERROR BUILDING CODE TABLE"<<std::endl;
        return false;
    }
    std::cout<<"COMPLETE"<<std::endl;
    return true; 
}

bool LCKMAT002::HuffmanTree::buildBitString(const std::string &fileName){
    bool success = buildBitString(codeTable,fileName);
    if (!success) std::cout<<"Something went wrong creating the bitstring"<<std::endl;
    return success;
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
            if (iterator!=bitmap.end()) bitString=bitString+iterator->second;
            else return false;
               
        }
        if (bitString.length()<1)return false;
        inputFile.close();
        std::cout<<"Final bitstring:"<<std::endl<<bitString<<std::endl;
        return true;
    }
    std::cout << "Unable to open input file"; 
    return false;
}

bool LCKMAT002::HuffmanTree::writeBitString(const std::string &fileName)
{
    // Write bitstring
    std::string file="../bin/"+fileName;
    std::ofstream outputFile;
    outputFile.open (file);
    if (outputFile.is_open()){
        for (size_t i = 0; i < bitString.length(); i++){
            outputFile<<bitString.c_str()[i];
        }
    outputFile.close();
    } 
    else {
        std::cout<<"Something went wrong while writing the bitstream"<<std::endl;
        return false;
    }

    // Write headerfile
    file="../bin/"+fileName+".hdr";
    outputFile.open(file);
    if (outputFile.is_open()){
        outputFile<<codeTable.size()<<std::endl;
        for (auto it =  codeTable.begin(); it !=codeTable.end(); it++){
            outputFile<<it->first<<","<<it->second<<std::endl;
        }
    outputFile.close();
    std::cout<<"COMPLETED"<<std::endl;
    return true;
        
    } else std::cout<<"Something went wrong while writing the bitstream"<<std::endl;
    return false;

}

// Build BitStream
bool LCKMAT002::HuffmanTree::buildBitstream(std::string fileName){
    using namespace std;

    // Determine number of bytes
    int N = (bitString.length()/8) + (bitString.length()%8 ? 1 : 0);
    std::cout<<"N:"<<N<<std::endl;

    // Create bitsream
    unsigned char bitStream[N];
    for (size_t i = 0; i < N-1; i++)
    {
        string code = bitString.substr(i*8,8);
        std::bitset<8> byte(code);
        unsigned char c = byte.to_ullong();
        bitStream[i]=c;
        cout<<code<<" "<<bitStream[i]<<endl;
    }
    
    // Create last character of bitstream
    {
        string code = bitString.substr((N-1)*8,8);
        // Determine how to fill last char of byte array
        for (size_t i = 0; i < bitString.length()-(N-1)*8; i++){
            code = code + "0";
        }        
        std::bitset<8> byte(code);
        unsigned char c = byte.to_ullong();
        bitStream[N]=c;
        cout<<code<<" "<<bitStream[N]<<endl;
    }

    // Write binary File
    ofstream binaryFile ("../bin/"+fileName+".raw", ios::out | ios::binary);

    // Write int header
    int length = bitString.length();
    binaryFile.write(reinterpret_cast<const char *>(&length), sizeof(length));

    if(!binaryFile)
    {
        cout<<"Failed to generate output file, check that bin file exists."<<endl;
        return false;
    }

    for (size_t i = 0; i < N; i++)
    {
        binaryFile.write((char*)&bitStream[i], sizeof (bitStream[i]));
    }
    binaryFile.close();  
    return true;
}

std::unordered_map<char,int> LCKMAT002::HuffmanTree::getFrequencyMap()const{
    return frequencyMap;
}

std::priority_queue<LCKMAT002::HuffmanNode,std::vector<LCKMAT002::HuffmanNode>,LCKMAT002::myComparator> LCKMAT002::HuffmanTree::getPQueue() const{
    return pQueue;
};

std::unordered_map<char,std::string> LCKMAT002::HuffmanTree::getCodeTable() const{
    return codeTable;
}

std::shared_ptr<LCKMAT002::HuffmanNode> LCKMAT002::HuffmanTree::getRoot() const{
    return root;
}

std::string LCKMAT002::HuffmanTree::getBitString() const{
    return bitString;
}

