CC=g++
LIBS= -std=c++11

huffencode: huffencode.o HuffmanTree.o HuffmanNode.o
	$(CC) -o huffencode huffencode.o HuffmanTree.o HuffmanNode.o $(LIBS)

huffencode.o: huffencode.cpp
	$(CC) -c -o huffencode.o huffencode.cpp  $(LIBS)

HuffmanTree.o: HuffmanTree.cpp HuffmanTree.h
	$(CC) -c -o HuffmanTree.o HuffmanTree.cpp  $(LIBS)

HuffmanNode.o: HuffmanNode.cpp HuffmanNode.h
	$(CC) -c -o HuffmanNode.o HuffmanNode.cpp  $(LIBS)
	

clean:
	rm -f ./*.o
	rm huffencode

run:
	./huffencode