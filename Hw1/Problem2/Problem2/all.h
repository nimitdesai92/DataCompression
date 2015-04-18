#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

std::vector <unsigned char> fileread(char *filename, float filetype[]);
void filewrite(char *filename, std::vector<std::pair<unsigned char, string> > &newvector, std::vector <unsigned char> &orgvector);
void displayfile(float filetype[]);
void displayfile_vector(std::vector <unsigned char> filetype);
void displayfile_pair(std::vector<std::pair<unsigned char, float> > filetype);

float sum(float filetype[]);
void probability(float filetype[], float probability_file[], float file_total);
double calc_entropy(float probability_file[]);
void fillvector(float filetype[], std::vector<std::pair<unsigned char, float> > &newvector);
void sortvector(std::vector<std::pair<unsigned char, float> > &newvector);
void erase(std::vector<std::pair<unsigned char, float> > &newvector);

struct shannonode;
shannonode* createshannonode(int first, int last);
shannonode* insert(shannonode *root, int first, int last);
void shannon(std::vector<std::pair<unsigned char, float> > newvector, shannonode* root, int first, int last); 
string shannon_code(shannonode* root, int index, string code);
void erase_tree(shannonode *leaf);
void insert(shannonode* root, std::vector<std::pair<unsigned char, string> > &newvector, std::vector<std::pair<unsigned char, float> > twovector);
void displaysymbol(std::vector<std::pair<unsigned char, string> > newvector);

struct huffmannode;
huffmannode* createleafnode(int index, float sym_probablity);
huffmannode* createrootnode(huffmannode* left, huffmannode* right);
void huffman(vector<huffmannode*> leaf);
string huffman_code(huffmannode* root, string code);
void huff_insert(std::vector<std::pair<unsigned char, string> > &newvector, std::vector<huffmannode*> twovector);

struct adap_huffmannode;
adap_huffmannode* createnewnode(adap_huffmannode *NYT, unsigned char charac);
void swapnadd(adap_huffmannode* current);
string adaphuffman_code(adap_huffmannode* root, string code);
void adap_huffman(std::vector <unsigned char> filetype, char* filename);