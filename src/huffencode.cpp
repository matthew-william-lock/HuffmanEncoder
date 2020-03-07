#include "HuffmanTree.h"

#include <fstream>

int main(int argc, char* argv[])
{
    using namespace std;

     if (argc<2)
     {
        cout<<"usage: huffencode <inputFile><output file> "<<endl; 
        cout<<"usage: huffencode: error: too few arguments"<<endl;
        return 1;
     }
     else if (argc>2)
     {
         cout<<"usage: huffencode <inputFile><output file> "<<endl; 
        cout<<"usage: huffencode: error: too many arguments"<<endl;
        return 1;
     }

    ifstream inputFile;
    inputFile.open (argv[1]);
    if (inputFile.is_open())
    {
        std::unordered_map<char,int> frequencyMap;
        char c;
        
        while (inputFile.get(c))
        {
            auto iterator = frequencyMap.find(c);
            if (iterator!=frequencyMap.end()) iterator -> second++;
            else frequencyMap[c]=1;                
        }
        inputFile.close();  

        LCKMAT002::HuffmanTree tree(frequencyMap);
        tree.printPqueue();

    }
    else
    {
         cout << "Unable to open input file"; 
         return 1;
    } 


    return 0;
}