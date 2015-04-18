#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string.h>

std::vector <unsigned char> fileread(char *filename);
void displayfile_vector(std::vector <unsigned char> filetype);
void block(std::vector<unsigned char> file_org, std::vector<unsigned char> &file_vector, int block_Size);
void read_transition(std::vector<std::vector<float>> &transition);
void Qmcoder(std::vector<unsigned char> file_org, std::vector<std::vector<float>> transition, char* filename);
void renormalize(std::string &out, bool &carry,unsigned int &A,unsigned int &C);
void writefile(char* filename, std::string out);
void cabac(std::vector<unsigned char> file_org, int context_bits, char* filename);
