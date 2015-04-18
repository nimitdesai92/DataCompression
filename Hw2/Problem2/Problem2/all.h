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
void plothist(std::vector <float> hist, char *filename);
void calchist(std::vector <unsigned char> file_org, std::vector <float> &file_hist);
void calchist_float(std::vector <float> file_org, std::vector <float> &file_hist);
double calc_entropy(std::vector<float> &file_hist);
void calc_cdf(std::vector <float> &file_hist);
std::vector<float> sum_hist(std::vector <float> hist1, std::vector <float> hist2, std::vector <float> hist3);
void scalar_quantizer(std::vector<float> &code_book, std::vector<float> hist, std::vector<float> &rep_val);
void quantized(std::vector <unsigned char> file_org, std::vector <float> &file_quant, std::vector <float> code_book, std::vector <float> rep_val);
float calc_PSNR(float MSE, int max);
float calc_MSE(std::vector<float> &code_book, std::vector<float> hist, std::vector<float> &rep_val);
void block(std::vector<unsigned char> file_org, std::vector<unsigned char> &file_vector, int block_Size);
void filewrite(std::vector <unsigned char> file, char *filename);
void add_train(std::vector<unsigned char> one, std::vector<unsigned char> two, std::vector<unsigned char> three, std::vector<unsigned char> &final);