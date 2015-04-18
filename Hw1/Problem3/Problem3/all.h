#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

std::vector <unsigned char> fileread(char *filename);
void filewrite(char *filename, std::vector < unsigned char > filetype);
void displayfile(std::vector <unsigned char> filetype);

std::vector <unsigned char> BasicRLE(std::vector <unsigned char> filetype);
std::vector <unsigned char> BasicRLE_decoder(std::vector <unsigned char> filetype);

std::vector <unsigned char> ModifiedRLE(std::vector <unsigned char> filetype);
std::vector <unsigned char> modifiedRLE_decoder(std::vector <unsigned char> filetype);

std::vector <unsigned char> MTF(std::vector <unsigned char> filetype);
std::vector <unsigned char> MTFdecoder(std::vector <unsigned char> filetype);

struct adap_huffmannode;
adap_huffmannode* createnewnode(adap_huffmannode *NYT, unsigned char charac);
void swapnadd(adap_huffmannode* current);
string adaphuffman_code(adap_huffmannode* root, string code);
void adap_huffman(std::vector <unsigned char> filetype, char* filename);

