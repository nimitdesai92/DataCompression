#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string.h>

#define PI 3.1416

void imread(char *filename, int x1, int y1, int z1, std::vector<std::vector<std::vector <int> > > &Img);
void imwrite(char *filename, std::vector<std::vector<std::vector<int> > > Img);
void display_block(std::vector<std::vector<std::vector <float> > > block);
void resize(std::vector<std::vector<std::vector<float> > > &block);
void adjust_range(std::vector<std::vector<std::vector<int> > > &Img);
std::vector<std::vector<float > > getq(int ratio);
void Dct_coeff(int start_x, int start_y, std::vector<std::vector<std::vector<int> > > Img, std::vector<std::vector<std::vector<float> > > &block, int ratio);
float calc_PSNR(std::vector<std::vector <std::vector <int> > > org, std::vector<std::vector <std::vector <int> > > compressed);
void simple_deblock(std::vector<std::vector <std::vector <int> > > input, std::vector<std::vector <std::vector <int> > > &output);
void paper_deblock(std::vector<std::vector <std::vector <int> > > input, std::vector<std::vector <std::vector <int> > > &output);
void findmin_max(std::vector<float> v, int &min, int & max);
void geta(std::vector<float> v, std::vector<float> &a);
int getF(std::vector<float> v);
float clip(std::vector<float> v, std::vector<float> a);
void smooth_mode(std::vector<float> &v);