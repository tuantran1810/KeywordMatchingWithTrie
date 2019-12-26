This source code implements keywords matching using Trie data structure with O(N) complexity (with N is the length of input string).
List of keywords is stored in ./data/keywordTable.txt -> this file can be changed for your purpose

How to build:
- This source code is written in C++11 standard, so please make sure that your compiler is suitable
- To build:
	cd ./build && make
- Executable binary should be generated in ./build with the name "keywordMatching"

How to use:
- Write an input file and store it somewhere. Let say you create a file at path: ~/blabla/input.txt
- Run the binary file with command: ./keywordMatching <path_to_input_file>. For example: ./keywordMatching ~/blabla/input.txt
