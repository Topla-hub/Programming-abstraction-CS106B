/**********************************************************
 * File: HuffmanEncoding.cpp
 *
 * Implementation of the functions from HuffmanEncoding.h.
 * Most (if not all) of the code that you write for this
 * assignment will go into this file.
 */

#include "HuffmanEncoding.h"

/* Function: getFrequencyTable
 * Usage: Map<ext_char, int> freq = getFrequencyTable(file);
 * --------------------------------------------------------
 * Given an input stream containing text, calculates the
 * frequencies of each character within that text and stores
 * the result as a Map from ext_chars to the number of times
 * that the character appears.
 *
 * This function will also set the frequency of the PSEUDO_EOF
 * character to be 1, which ensures that any future encoding
 * tree built from these frequencies will have an encoding for
 * the PSEUDO_EOF character.
 */
Map<ext_char, int> getFrequencyTable(istream& file) {
	Map<ext_char, int> result;
	char ch;
	while (file.get(ch)) {
		if (result.containsKey(ch)) {
			result[ch] += 1;
		}
		else {
			result.put(ch, 1);
		}
	}
	result[PSEUDO_EOF] = 1;
	return result;
}

/* Function: buildEncodingTree
 * Usage: Node* tree = buildEncodingTree(frequency);
 * --------------------------------------------------------
 * Given a map from extended characters to frequencies,
 * constructs a Huffman encoding tree from those frequencies
 * and returns a pointer to the root.
 *
 * This function can assume that there is always at least one
 * entry in the map, since the PSEUDO_EOF character will always
 * be present.
 */
Node* buildEncodingTree(Map<ext_char, int>& frequencies) {
	PriorityQueue<Node*> myqueue;
	for (ext_char c : frequencies) {//puts all nodes in queue
		Node* n = new Node();
		n->character = c;
		n->weight = frequencies[c];
		n->one = NULL;
		n->zero = NULL;
		myqueue.enqueue(n, n->weight);
	}
	while (myqueue.size() > 1) {//modifies queue acorrding given conditions 
		Node* min1 = myqueue.dequeue();
		Node* min2 = myqueue.dequeue();
		Node* combination = new Node();
		combination->zero = min1;
		combination->one = min2;
		combination->character = NOT_A_CHAR;
		combination->weight = min1->weight + min2->weight;
		myqueue.enqueue(combination, combination->weight);
	}
	return myqueue.dequeue();
}

/* Function: freeTree
 * Usage: freeTree(encodingTree);
 * --------------------------------------------------------
 * Deallocates all memory allocated for a given encoding
 * tree.
 */
void freeTree(Node* root) {
	if (root == NULL) return;
	freeTree(root->one);
	freeTree(root->zero);
	delete root;
}

/* Function: encodeFile
 * Usage: encodeFile(source, encodingTree, output);
 * --------------------------------------------------------
 * Encodes the given file using the encoding specified by the
 * given encoding tree, then writes the result one bit at a
 * time to the specified output file.
 *
 * This function can assume the following:
 *
 *   - The encoding tree was constructed from the given file,
 *     so every character appears somewhere in the encoding
 *     tree.
 *
 *   - The output file already has the encoding table written
 *     to it, and the file cursor is at the end of the file.
 *     This means that you should just start writing the bits
 *     without seeking the file anywhere.
 */ 
void encodeFile(istream& infile, Node* encodingTree, obstream& outfile) {
	ext_char ch;
	while (!infile.eof()) {//this loop reads file char by char
		ch = infile.get();
		string bitsstr = getBit(encodingTree, ch, "");//generates string of bits of char
		for (ext_char bit : bitsstr) {//writes in file
			if (bit == '1') {
				outfile.writeBit(1);
			}
			else {
				outfile.writeBit(0);
			}
		}
	}
	string ending = getBit(encodingTree, PSEUDO_EOF, "");//generates string of bits for efo (the end of file)
	for (ext_char c : ending) {//writes in file
		if (c == '1') {
			outfile.writeBit(1);
		}
		else {
			outfile.writeBit(0);
		}
	}
}
//This helper method generates string of bits of char by encodingtree
string getBit(Node* encodingTree, ext_char toFind,string res) {
	if (encodingTree->character == toFind) {  // base case
		return res;
	}
	if (encodingTree->zero!=NULL) {//go left
		string zeros = getBit(encodingTree->zero, toFind, res + '0');
		if (!zeros.empty()) {
			return zeros;
		}
	}
	if (encodingTree->one!=NULL) {//go right
		string ones = getBit(encodingTree->one, toFind, res + '1');
		if (!ones.empty()) {
			return ones;
		}
	}
	return "";//wrong leaf 
}

/* Function: decodeFile
 * Usage: decodeFile(encodedFile, encodingTree, resultFile);
 * --------------------------------------------------------
 * Decodes a file that has previously been encoded using the
 * encodeFile function.  You can assume the following:
 *
 *   - The encoding table has already been read from the input
 *     file, and the encoding tree parameter was constructed from
 *     this encoding table.
 *
 *   - The output file is open and ready for writing.
 */
void decodeFile(ibstream& infile, Node* encodingTree, ostream& file) {
	string bitsstr;
	while (!infile.eof()) {//this loop reads file bite by bite
		int oneBite = infile.readBit();
		if (oneBite == 1) {//generates string of bits for chr
			bitsstr += '1';
		}
		else {
			bitsstr += '0';
		}
		ext_char coverted = convert(encodingTree, bitsstr);//converts string of bits into char if posible
		if (coverted != NOT_A_CHAR) {
			if (coverted == PSEUDO_EOF) {
				break;// got end of file 
			}
			file.put(coverted);//write in file 
			bitsstr = "";//for new char 
		}
	}
}
//This helper metjod convert string of bits into character
ext_char convert(Node* encodingTree,  string bitsstr) {
	Node* current = encodingTree;//root
	for (ext_char bit : bitsstr) {//follow path from string
		if (bit == '0') {
			if (current->zero) {//left
				current = current->zero;
			}
			else {
				return NOT_A_CHAR;//string was not correct for generating char
			}
		}
		else {
			if (current->one) {//right
				current = current->one;
			}
			else {
				return NOT_A_CHAR;//string was not correct for generating char
			}
		}
	}
	return current->character;//answer in the end of path
}

/* Function: writeFileHeader
 * Usage: writeFileHeader(output, frequencies);
 * --------------------------------------------------------
 * Writes a table to the front of the specified output file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to decompress input files once they've been
 * compressed.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * readFileHeader function defined below this one so that it
 * can properly read the data back.
 */
void writeFileHeader(obstream& outfile, Map<ext_char, int>& frequencies) {
	/* The format we will use is the following:
	 *
	 * First number: Total number of characters whose frequency is being
	 *               encoded.
	 * An appropriate number of pairs of the form [char][frequency][space],
	 * encoding the number of occurrences.
	 *
	 * No information about PSEUDO_EOF is written, since the frequency is
	 * always 1.
	 */
	 
	/* Verify that we have PSEUDO_EOF somewhere in this mapping. */
	if (!frequencies.containsKey(PSEUDO_EOF)) {
		error("No PSEUDO_EOF defined.");
	}
	
	/* Write how many encodings we're going to have.  Note the space after
	 * this number to ensure that we can read it back correctly.
	 */
	outfile << frequencies.size() - 1 << ' ';
	
	/* Now, write the letter/frequency pairs. */
	foreach (ext_char ch in frequencies) {
		/* Skip PSEUDO_EOF if we see it. */
		if (ch == PSEUDO_EOF) continue;
		
		/* Write out the letter and its frequency. */
		outfile << char(ch) << frequencies[ch] << ' ';
	}
}

/* Function: readFileHeader
 * Usage: Map<ext_char, int> freq = writeFileHeader(input);
 * --------------------------------------------------------
 * Reads a table to the front of the specified input file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to reconstruct the encoding tree for that file.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * writeFileHeader function defined before this one so that it
 * can properly write the data.
 */
Map<ext_char, int> readFileHeader(ibstream& infile) {
	/* This function inverts the mapping we wrote out in the
	 * writeFileHeader function before.  If you make any
	 * changes to that function, be sure to change this one
	 * too!
	 */
	Map<ext_char, int> result;
	
	/* Read how many values we're going to read in. */
	int numValues;
	infile >> numValues;
	
	/* Skip trailing whitespace. */
	infile.get();
	
	/* Read those values in. */
	for (int i = 0; i < numValues; i++) {
		/* Get the character we're going to read. */
		ext_char ch = infile.get();
		
		/* Get the frequency. */
		int frequency;
		infile >> frequency;
		
		/* Skip the space character. */
		infile.get();
		
		/* Add this to the encoding table. */
		result[ch] = frequency;
	}
	
	/* Add in 1 for PSEUDO_EOF. */
	result[PSEUDO_EOF] = 1;
	return result;
}

/* Function: compress
 * Usage: compress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman compressor.  Compresses
 * the file whose contents are specified by the input
 * ibstream, then writes the result to outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void compress(ibstream& infile, obstream& outfile) {
	Map<ext_char, int> table = getFrequencyTable(infile);//build table
	Node* encodingtree = buildEncodingTree(table);//build tree according to table 
	writeFileHeader(outfile, table);//write header
	infile.rewind();//go back to the bigining
	encodeFile(infile, encodingtree, outfile);
	freeTree(encodingtree);//free up memory 
	
}

/* Function: decompress
 * Usage: decompress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman decompressor.
 * Decompresses the file whose contents are specified by the
 * input ibstream, then writes the decompressed version of
 * the file to the stream specified by outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void decompress(ibstream& infile, ostream& outfile) {
	Map<ext_char, int> table = readFileHeader(infile);//build table according to header
	Node* encodingtree = buildEncodingTree(table);//build tree according to table
	decodeFile(infile, encodingtree, outfile);
	freeTree(encodingtree);//free up memory 
}

