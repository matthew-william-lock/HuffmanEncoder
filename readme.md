# Huffman Encoding
This program implements the Huffman encoding algorithm to perform file compression. This program is primarily meant for the purposes of compressing text files, and produces a compressed binary output file, along with standard ASCII header file, and ASCII file containing the plain bitstring. Functionality includes:
- File compression
- File decompression

## Source files
**huffencode.cpp:** : Implement functionality of program

**unitTests.cpp**: Implements unit testing for program

**HuffmanTree.cpp:** : Implements functionality of HuffmanTree class. Methods implemented are used to build a frequency map, build the HuffmanTree structure using the HuffmanNode class, as well as methods to build a code table, build a bitsting and bitstream, and write these to an output file.

**HuffmanTree.h**: Defines the HuffmanTree class

**HuffmanNode.cpp**: Implements functionality of the HuffmanNode. This is the building block of the HuffmanTree class. This class includes special members, as well as methods for getting and setting the children and values of the HuffmanNode.

**HuffmanNode.h**: Defines the HuffmanNode class

## Installation
**Step 1:** Compile huffencode
```
cd src
make
```

**Step 2:** Run huffencode
```
cd src
./huffencode <inputFile> <output file> [-d]
```

## Usage
The program can be used to encode files or decode existing compressed files. Encoding will be assumed unless specified otherwise when running the program.
*Note: input file is assumed to be in src while the ASCII and binary output files are placed in the bin directory*

Required arguments 
```
<inputFile>           file to be compressed
<output file>         output file of compression
```

Optional arguments:
| Parameter                 | Description   |	
| :------------------------ | :-------------|
| -d | Enable file decompression where the file to be decompressed is <b>inputFile</b> and the output file is <b>output file</b>

## Unit Testing
The provided unit tests are exhaustive and test all various implemented member functions, as well as all functions (exlcuding those merely used to print to console and files) undergo a unit test. 

**Step 1:** Compile unit tests
```
cd src
make tests
```

**Step 2:** Run unit tests
```
cd src
make test
```