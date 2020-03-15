#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "HuffmanNode.h"
#include "HuffmanTree.h"

// FIX MOVE CONSTRUCTOR VS ASSIGNMENT

/* 

	Unit testing is quite exhaustive

	Tests for HuffmanNode:
	- Inlcude all special member functions
	- Include any public function

	Tests for HuffmanTree:
	- Done using golden measure input with known results
	- Inlcude all special member functions
	- Include any public function (excluding those used for printing to files)


*/

namespace LCKMAT002{

// UNIT TESTS FOR HUFFMANN NODE =================================================================================================================

TEST_CASE("Default Constructor","[HuffmanNodeDefaultConstructor]") {
	HuffmanNode node = HuffmanNode();
	REQUIRE(node.getC()==char());
	REQUIRE(node.getFreq()==0);
}

TEST_CASE("Custom Constructor","[HuffmanNodeCustomConstructor]") {
	HuffmanNode node = HuffmanNode('a',1);
	REQUIRE(node.getC()==char('a'));
	REQUIRE(node.getFreq()==1);
}

TEST_CASE("Move Constructor","[HuffmanNodeMoveConstructor]") {
	HuffmanNode node = HuffmanNode('a',2);
	SECTION("Pre-call") {
		REQUIRE(node.getC()=='a');
		REQUIRE(node.getFreq()==2);
		
	}
	SECTION("Post-call") {
		auto node2 = std::move(node);
		REQUIRE(node2.getC()=='a');
		REQUIRE(node2.getFreq()==2);
		REQUIRE(node.getC()==char());
		REQUIRE(node.getFreq()==0);
	}
}

TEST_CASE("Copy Constructor","[HuffmanNodeCopyConstructor]") {
	HuffmanNode node = HuffmanNode('a',2);
	auto node2 = HuffmanNode(node);
	REQUIRE(node2.getC()=='a');
	REQUIRE(node2.getFreq()==2);

}

TEST_CASE("Assignment Operator","[HuffmanNodeAssignmentOperator]") {
	HuffmanNode node1 = HuffmanNode('a',10);
	HuffmanNode node2 = node1;
	REQUIRE(node1.getC()==node2.getC());
	REQUIRE(node1.getFreq()==node2.getFreq());
  
}

TEST_CASE("Move Assignment Operator","[HuffmanNodeMoveAssignmentOperator]") {
	HuffmanNode node = std::move(HuffmanNode('a',20));
	REQUIRE(node.getC()=='a');
	REQUIRE(node.getFreq()==20);  
}

TEST_CASE("< Operator","[HuffmanNode<Operator]") {
	HuffmanNode node1 = HuffmanNode('a',10);
	HuffmanNode node2 = HuffmanNode('a',20);
	REQUIRE(node1<node2);
	REQUIRE(!(node2<node1));    
}

TEST_CASE("Get Character","[HuffmanNodeGetC]") {
	HuffmanNode node = HuffmanNode('z',10);
	REQUIRE(node.getC()=='z');
}

TEST_CASE("Get Frequency","[HuffmanNodeGetFreq]") {
	HuffmanNode node = HuffmanNode('z',10);
	REQUIRE(node.getFreq()==10);
}

TEST_CASE("Get Left Child","[HuffmanNodeGetLeftChild]") {
	HuffmanNode node = HuffmanNode('z',10);
	std::shared_ptr<HuffmanNode> leftChild = std::make_shared<HuffmanNode>(HuffmanNode('q',24));
	node.setLeftChild(leftChild);
	REQUIRE(node.getLeftChild()==leftChild);
}

TEST_CASE("Get Right Child","[HuffmanNodeGetRightChild]") {
	HuffmanNode node = HuffmanNode('e',12);
	std::shared_ptr<HuffmanNode> rightChild = std::make_shared<HuffmanNode>(HuffmanNode('q',24));
	node.setRightChild(rightChild);
	REQUIRE(node.getRightChild()==rightChild);
}

TEST_CASE("Set Left Child","[HuffmanNodeSetLeftChild]") {
	HuffmanNode node = HuffmanNode('z',10);
	std::shared_ptr<HuffmanNode> leftChild1 = std::make_shared<HuffmanNode>(HuffmanNode('q',24));
	std::shared_ptr<HuffmanNode> leftChild2 = std::make_shared<HuffmanNode>(HuffmanNode('b',20));
	node.setLeftChild(leftChild1);
	REQUIRE(node.getLeftChild()==leftChild1);
	node.setLeftChild(leftChild2);
	REQUIRE(node.getLeftChild()==leftChild2);
}

TEST_CASE("Set Right Child","[HuffmanNodeSetRightChild]") {
	HuffmanNode node = HuffmanNode('z',10);
	std::shared_ptr<HuffmanNode> rightChild1 = std::make_shared<HuffmanNode>(HuffmanNode('q',24));
	std::shared_ptr<HuffmanNode> rightChild2 = std::make_shared<HuffmanNode>(HuffmanNode('b',20));
	node.setRightChild(rightChild1);
	REQUIRE(node.getRightChild()==rightChild1);
	node.setRightChild(rightChild2);
	REQUIRE(node.getRightChild()==rightChild2);
}

// UNIT TESTS FOR HUFFMANN TREE ==================================================================================================================

/* 

	SIMPLE TEST CASE BEING USED FOR UNIT TESTS WHERE INPUT STRING:
	abAB12

	Number of characters:
	7

	Expected Order of Tree Build:
	:1 + a:1 = 0:2
	B:1 + 2:1 = 0:2
	b:1 + A:1 = 0:2
	1:1 + 0:2 = 0:3
	0:2 + 0:2 = 0:4
	0:3 + 0:4 = 0:7 (root node)

	Expected CodeTable:
	1:00
	\n:010
	a:011
	B:100
	2:101
	b:110
	A:111

	Expected BitString:
	01111011110000101010


*/

TEST_CASE("HuffmanTree Default Constructor","[HuffmanTreeDefaultConstructor]") {
	HuffmanTree tree = HuffmanTree();
	REQUIRE(tree.getBitString()=="");
	REQUIRE(tree.getCodeTable().size()==0);
	REQUIRE(tree.getFrequencyMap().size()==0);
	REQUIRE(tree.getPQueue().size()==0);
	REQUIRE(tree.getRoot()==nullptr);
}

TEST_CASE("HuffmanTree Move Constructor","[HuffmanTreeMoveConstructor]") {

	// Prevent functions called from streaming to cout
    std::streambuf* orig_buf = std::cout.rdbuf();
    std::cout.rdbuf(NULL);

	HuffmanTree tree = HuffmanTree();
	bool suc = tree.buildFrequencymap("../unitTesting/inputFile");
	suc =tree.buildPriorityQueue();
	suc =tree.buildTree();
	suc =tree.buildCodeTable();
	suc =tree.buildBitString("../unitTesting/inputFile");

	SECTION("Pre-call") {
		REQUIRE(tree.getFrequencyMap().size()==7); // Accounts for end of line char		
		REQUIRE(tree.getPQueue().size()==0);
		REQUIRE(tree.getRoot()->getFreq()==7);
		REQUIRE(tree.getCodeTable().size()==7);
		REQUIRE(tree.getBitString()=="01111011110000101010");
	}
	SECTION("Post-call") {
		auto tree2 = std::move(tree);

		REQUIRE(tree2.getFrequencyMap().size()==7); // Accounts for end of line char		
		REQUIRE(tree2.getPQueue().size()==0);
		REQUIRE(tree2.getRoot()->getFreq()==7);
		REQUIRE(tree2.getCodeTable().size()==7);
		REQUIRE(tree2.getBitString()=="01111011110000101010");

		REQUIRE(tree.getFrequencyMap().size()==0); // Accounts for end of line char		
		REQUIRE(tree.getPQueue().size()==0);
		REQUIRE(tree.getRoot()==nullptr);
		REQUIRE(tree.getCodeTable().size()==0);
		REQUIRE(tree.getBitString()==std::string());
	}
	// Renable
    std::cout.rdbuf(orig_buf);
}

TEST_CASE("HuffmanTree Copy Constructor","[HuffmanTreeCopyConstructor]") {
	// Prevent functions called from streaming to cout
    std::streambuf* orig_buf = std::cout.rdbuf();
    std::cout.rdbuf(NULL);

	HuffmanTree tree = HuffmanTree();
	bool suc = tree.buildFrequencymap("../unitTesting/inputFile");
	suc =tree.buildPriorityQueue();
	suc =tree.buildTree();
	suc =tree.buildCodeTable();
	suc =tree.buildBitString("../unitTesting/inputFile");

	HuffmanTree tree2= HuffmanTree(tree);

	SECTION("Original Tree") {
		REQUIRE(tree.getFrequencyMap().size()==7);		
		REQUIRE(tree.getPQueue().size()==0);
		REQUIRE(tree.getRoot()->getFreq()==7);
		REQUIRE(tree.getCodeTable().size()==7);
		REQUIRE(tree.getBitString()=="01111011110000101010");
	}

	SECTION("New Tree") {
		REQUIRE(tree2.getFrequencyMap().size()==7);		
		REQUIRE(tree2.getPQueue().size()==0);
		REQUIRE(tree2.getRoot()->getFreq()==7);
		REQUIRE(tree2.getCodeTable().size()==7);
		REQUIRE(tree2.getBitString()=="01111011110000101010");
	}
	std::cout.rdbuf(orig_buf);

}

TEST_CASE("HuffmanTree Assignment Operator","[HuffmanTreeAssignmentOperator]") {
	// Prevent functions called from streaming to cout
    std::streambuf* orig_buf = std::cout.rdbuf();
    std::cout.rdbuf(NULL);

	HuffmanTree tree = HuffmanTree();
	bool suc = tree.buildFrequencymap("../unitTesting/inputFile");
	suc =tree.buildPriorityQueue();
	suc =tree.buildTree();
	suc =tree.buildCodeTable();
	suc =tree.buildBitString("../unitTesting/inputFile");

	HuffmanTree tree2= tree;

	SECTION("Original Tree") {
		REQUIRE(tree.getFrequencyMap().size()==7);		
		REQUIRE(tree.getPQueue().size()==0);
		REQUIRE(tree.getRoot()->getFreq()==7);
		REQUIRE(tree.getCodeTable().size()==7);
		REQUIRE(tree.getBitString()=="01111011110000101010");
	}

	SECTION("New Tree") {
		REQUIRE(tree2.getFrequencyMap().size()==7);		
		REQUIRE(tree2.getPQueue().size()==0);
		REQUIRE(tree2.getRoot()->getFreq()==7);
		REQUIRE(tree2.getCodeTable().size()==7);
		REQUIRE(tree2.getBitString()=="01111011110000101010");
	}
	std::cout.rdbuf(orig_buf);
  
}

TEST_CASE("HuffmanTree Move Assignment Operator","[HuffmanTreeMoveAssignmentOperator]") {
	// Prevent functions called from streaming to cout
    std::streambuf* orig_buf = std::cout.rdbuf();
    std::cout.rdbuf(NULL);

	HuffmanTree tree = HuffmanTree();
	bool suc = tree.buildFrequencymap("../unitTesting/inputFile");
	suc =tree.buildPriorityQueue();
	suc =tree.buildTree();
	suc =tree.buildCodeTable();
	suc =tree.buildBitString("../unitTesting/inputFile");

	HuffmanTree tree2= HuffmanTree();
	tree2 = tree;

	SECTION("Original Tree") {
		REQUIRE(tree.getFrequencyMap().size()==7);		
		REQUIRE(tree.getPQueue().size()==0);
		REQUIRE(tree.getRoot()->getFreq()==7);
		REQUIRE(tree.getCodeTable().size()==7);
		REQUIRE(tree.getBitString()=="01111011110000101010");
	}

	SECTION("New Tree") {
		REQUIRE(tree2.getFrequencyMap().size()==7);		
		REQUIRE(tree2.getPQueue().size()==0);
		REQUIRE(tree2.getRoot()->getFreq()==7);
		REQUIRE(tree2.getCodeTable().size()==7);
		REQUIRE(tree2.getBitString()=="01111011110000101010");
	}
	std::cout.rdbuf(orig_buf);
}

TEST_CASE("HuffmanTree Destructor","[HuffmanTreeDestructor]") {
	// Prevent functions called from streaming to cout
    std::streambuf* orig_buf = std::cout.rdbuf();
    std::cout.rdbuf(NULL);

	HuffmanTree tree = HuffmanTree();
	bool suc = tree.buildFrequencymap("../unitTesting/inputFile");
	suc =tree.buildPriorityQueue();
	suc =tree.buildTree();
	suc =tree.buildCodeTable();
	suc =tree.buildBitString("../unitTesting/inputFile");	

	SECTION("Before Destructor") {		
		std::shared_ptr<HuffmanNode> newRoot = (tree.getRoot());
		REQUIRE(tree.getRoot().use_count()==3);	// Accounts for tempory RHS value being created
	}

	REQUIRE(tree.getRoot().use_count()==2);

	std::cout.rdbuf(orig_buf);
}

TEST_CASE("HuffmanTree Frequency Map","[HuffmanTreeFrequencyMap]") {
	// Prevent functions called from streaming to cout
    std::streambuf* orig_buf = std::cout.rdbuf();
    std::cout.rdbuf(NULL);

	HuffmanTree tree = HuffmanTree();
	bool suc = tree.buildFrequencymap("../unitTesting/inputFile");

	SECTION("Check that the map was built") {		
		REQUIRE(tree.getFrequencyMap().find('a')!=tree.getFrequencyMap().end());
		REQUIRE(tree.getFrequencyMap().find('b')!=tree.getFrequencyMap().end());
		REQUIRE(tree.getFrequencyMap().find('A')!=tree.getFrequencyMap().end());
		REQUIRE(tree.getFrequencyMap().find('B')!=tree.getFrequencyMap().end());
		REQUIRE(tree.getFrequencyMap().find('1')!=tree.getFrequencyMap().end());
		REQUIRE(tree.getFrequencyMap().find('2')!=tree.getFrequencyMap().end());
	}
	
	SECTION("Check that the map was built correctly") {		
		REQUIRE(tree.getFrequencyMap().find('a')->second==1);
		REQUIRE(tree.getFrequencyMap().find('b')->second==1);
		REQUIRE(tree.getFrequencyMap().find('A')->second==1);
		REQUIRE(tree.getFrequencyMap().find('B')->second==1);
		REQUIRE(tree.getFrequencyMap().find('1')->second==1);
		REQUIRE(tree.getFrequencyMap().find('2')->second==1);
	}	

	std::cout.rdbuf(orig_buf);
}

TEST_CASE("HuffmanTree Priority Queue","[HuffmanTreePriorityQueue]") {
	// Prevent functions called from streaming to cout
    std::streambuf* orig_buf = std::cout.rdbuf();
    std::cout.rdbuf(NULL);

	HuffmanTree tree = HuffmanTree();
	bool suc = tree.buildFrequencymap("../unitTesting/inputFile");
	suc = tree.buildPriorityQueue();

	REQUIRE(tree.getPQueue().top().getFreq()==1); // Frequency of 1
	REQUIRE(tree.getPQueue().top().getC()=='\n'); // Character expected to be top of priority queue

	std::cout.rdbuf(orig_buf);
}

TEST_CASE("HuffmanTree","[HuffmanTree]") {
	// Prevent functions called from streaming to cout
    std::streambuf* orig_buf = std::cout.rdbuf();
    std::cout.rdbuf(NULL);

	HuffmanTree tree = HuffmanTree();
	bool suc = tree.buildFrequencymap("../unitTesting/inputFile");
	suc = tree.buildPriorityQueue();
	suc = tree.buildTree();

	REQUIRE(tree.getRoot()->getC()=='0'); // Internal node expected as root
	REQUIRE(tree.getRoot()->getFreq()==7); // Character expected to be top of priority queue

	std::cout.rdbuf(orig_buf);
}

TEST_CASE("HuffmanTree CodeTable","[HuffmanTreeCodeTable]") {
	// Prevent functions called from streaming to cout
    std::streambuf* orig_buf = std::cout.rdbuf();
    std::cout.rdbuf(NULL);

	HuffmanTree tree = HuffmanTree();
	bool suc = tree.buildFrequencymap("../unitTesting/inputFile");
	suc = tree.buildPriorityQueue();
	suc = tree.buildTree();
	suc = tree.buildCodeTable();

	SECTION("Check that the code table was built correctly") {	
		REQUIRE(tree.getCodeTable().find('a')!=tree.getCodeTable().end()); 
		REQUIRE(tree.getCodeTable().find('b')!=tree.getCodeTable().end()); 
		REQUIRE(tree.getCodeTable().find('A')!=tree.getCodeTable().end());
		REQUIRE(tree.getCodeTable().find('B')!=tree.getCodeTable().end()); 
		REQUIRE(tree.getCodeTable().find('1')!=tree.getCodeTable().end()); 
		REQUIRE(tree.getCodeTable().find('2')!=tree.getCodeTable().end()); 
		REQUIRE(tree.getCodeTable().find('\n')!=tree.getCodeTable().end()); 
	}

	SECTION("Check that the code table was built correctly") {	
		REQUIRE(tree.getCodeTable().find('a')->second=="011"); 
		REQUIRE(tree.getCodeTable().find('b')->second=="110");
		REQUIRE(tree.getCodeTable().find('A')->second=="111");
		REQUIRE(tree.getCodeTable().find('B')->second=="100");
		REQUIRE(tree.getCodeTable().find('1')->second=="00");
		REQUIRE(tree.getCodeTable().find('2')->second=="101");
		REQUIRE(tree.getCodeTable().find('\n')->second=="010");
	}
	std::cout.rdbuf(orig_buf);
}

TEST_CASE("HuffmanTree BitString","[HuffmanTreeBitString]") {
	// Prevent functions called from streaming to cout
    std::streambuf* orig_buf = std::cout.rdbuf();
    std::cout.rdbuf(NULL);

	HuffmanTree tree = HuffmanTree();
	bool suc = tree.buildFrequencymap("../unitTesting/inputFile");
	suc = tree.buildPriorityQueue();
	suc = tree.buildTree();
	suc = tree.buildCodeTable();
	suc = tree.buildBitString("../unitTesting/inputFile");

	REQUIRE(tree.getBitString()=="01111011110000101010");

	std::cout.rdbuf(orig_buf);
}

}