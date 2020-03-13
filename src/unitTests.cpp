#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "HuffmanNode.h"

namespace LCKMAT002{

TEST_CASE("Default Constructor","[HuffmanNode]") {
	HuffmanNode node = HuffmanNode();
	REQUIRE(node.getC()==char());
	REQUIRE(node.getFreq()==0);
}

TEST_CASE("Custom Constructor","[HuffmanNode]") {
	HuffmanNode node = HuffmanNode('a',1);
	REQUIRE(node.getC()==char('a'));
	REQUIRE(node.getFreq()==1);
}

TEST_CASE("Move Constructor","[HuffmanNode]") {
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

TEST_CASE("Copy Constructor","[HuffmanNode]") {
	HuffmanNode node = HuffmanNode('a',2);
	auto node2 = HuffmanNode(node);
	REQUIRE(node2.getC()=='a');
	REQUIRE(node2.getFreq()==2);

}

TEST_CASE("Assignment Operator","[HuffmanNode]") {
	HuffmanNode node1 = HuffmanNode('a',10);
	HuffmanNode node2 = node1;
	REQUIRE(node1.getC()==node2.getC());
	REQUIRE(node1.getFreq()==node2.getFreq());
  
}

TEST_CASE("Move Assignment Operator","[HuffmanNode]") {
	HuffmanNode node = std::move(HuffmanNode('a',20));
	REQUIRE(node.getC()=='a');
	REQUIRE(node.getFreq()==20);  
}

TEST_CASE("< Operator","[HuffmanNode]") {
	HuffmanNode node1 = HuffmanNode('a',10);
	HuffmanNode node2 = HuffmanNode('a',20);
	REQUIRE(node1<node2);
	REQUIRE(!(node2<node1));    
}


}