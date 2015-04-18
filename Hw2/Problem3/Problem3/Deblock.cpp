#include "all.h"

#define c1 2.0
#define c2 5.0
#define c3 8.0

#define T1 2.0
#define T2 6.0

#define QP 20.0

float calc_PSNR(std::vector<std::vector <std::vector <int> > > org, std::vector<std::vector <std::vector <int> > > compressed)
{
	float MSE = 0, PSNR;

	for (int i = 0; i < org.size(); i++)
	{
		for (int j = 0; j < org[0].size(); j++)
		{
			for (int k = 0; k < org[0][0].size(); k++)
			{
				MSE += pow((org[i][j][k] - compressed[i][j][k]), 2);
			}
		}
	}
	MSE = MSE / (org.size()*org[0].size()*org[0][0].size());
	PSNR = 10 * log10f(pow(255,2)/MSE);
	return PSNR;
}

void simple_deblock(std::vector<std::vector <std::vector <int> > > input, std::vector<std::vector <std::vector <int> > > &output)
{
	output.resize(input.size(), std::vector<std::vector<int>>(input[0].size(), std::vector<int>(input[0][0].size(), 0)));

	for (int k = 0; k < input[0][0].size(); k++)
	{
		for (int i = 0; i < input.size(); i++)
		{
			for (int j = 0; j < input[0].size(); j++)
			{
				if ((i % 8) == 0 && i != 0)
				{
					output[i][j][k] = (round)((input[i - 1][j][k] + input[i][j][k]) / 2.0);
					output[i - 1][j][k] = output[i][j][k];
				}
				else
					output[i][j][k] = input[i][j][k];

				if ((j % 8) == 0 && j != 0)
				{
					output[i][j][k] = (round)((input[i][j - 1][k] + input[i][j][k]) / 2.0);
					output[i][j - 1][k] = output[i][j][k];
				}
				else
					output[i][j][k] = input[i][j][k];
			}
		}
	}
}

void findmin_max(std::vector<float> v, int &min, int & max)
{
	for (int x = 1; x < 9; x++)
	{
		if (v[x] < min)
		{
			min = v[x];
		}
		if (v[x] > max)
		{
			max = v[x];
		}
	}
}

void geta(std::vector<float> v, std::vector<float> &a)
{
	for (int x = 0; x < 3; x++)
	{
		a[x] = (c1 * v[2 * x + 1] - c2 * v[2 * x + 2] + c2 * v[2 * x + 3] - c1 * v[2 * x + 4]) / c3;
	}
}

int getvalF(std::vector<float> v)
{
	int F = 0;
	for (int x = 0; x < 9; x++)
	{
		if (abs(v[x] - v[x + 1]) <= T1)
		{
			F++;
		}
	}
	return F;
}

float clip(std::vector<float> v, std::vector<float> a, float a3)
{
	float temp;
	temp = (c2 / c3) * (a3 - a[1]);
	if (temp >= 0 && temp <= ((v[4] - v[5]) / 2.0))
	{
		return temp;
	}
	else
	{
		temp = ((v[4] - v[5]) / 2.0);
		return temp;
	}
}

void default_mode(std::vector<float> &v, std::vector<float> a)
{
	float a3, d, min = INFINITY;

	for (int x = 0; x < 3; x++)
	{
		if (abs(a[x]) < min){
			min = a[x];
		}
	}

	if (a[1] == 0)
	{
		a3 = 0;
	}
	else
	{
		a3 = a[1] * min/abs(a[1]);
	}
	d = clip(v, a, a3);
	v[4] = v[4] - d;
	v[5] = v[5] + d;
}

void smooth_mode(std::vector<float> &v)
{
	int sum = 0;
	std::vector<float> b {1,1,2,2,4,2,2,1,1};
	std::vector<float> p (10,0);
	for (int x = 0; x < 10; x++)
	{
		if (x == 0)
		{
			if (abs(v[1] - v[0]) < QP)
			{
				p[0] = v[0];
			}
			else
				p[0] = v[1];
		}
		if (x > 0 && x < 9)
		{
			p[x] = v[x];
		}
		if (x == 9)
		{
			if (abs(v[9] - v[8]) < QP)
			{
				p[9] = v[9];
			}
			else
				p[9] = v[8];
		}
	}

	for (int x = 1; x < 9; x++)
	{
		sum = 0;
		for (int y = -4; y <= 4; y++)
		{
			if (x + y < 1)
			{
				sum += b[y + 4] * p[0];
			}
			else if (x + y > 8)
			{
				sum += b[y + 4] * p[9];
			}
			else
			{
				sum += b[y + 4] * p[x + y];
			}
		}
		v[x] = (1 / 16.0)*sum;
	}
}

void paper_deblock(std::vector<std::vector <std::vector <int> > > input, std::vector<std::vector <std::vector <int> > > &output)
{
	std::vector<float> v(10, 0), a(3, 0);
	int index = 0, max = -1, min = 256;
	int F = 0;
	output.resize(input.size(), std::vector<std::vector<int>>(input[0].size(), std::vector<int>(input[0][0].size(), 0)));

	for (int k = 0; k < input[0][0].size(); k++)
	{
		for (int i = 0; i < input.size(); i++)
		{
			for (int j = 0; j < input[0].size(); j++)
			{
				if ((j % 8) == 0 && j != 0)
				{
					index = 0; min = 256; max = -1; F = 0;
					for (int x = j - 5; x <= j + 4; x++)
					{
						v[index] = input[i][x][k];
						index++;
					}
					findmin_max(v, min,max);
					geta(v, a);
					F = getvalF(v);
					if (F < T2)
					{
						if (a[1] < QP)
						{
							default_mode(v,a);
						}
					}
					else
					{
						if ((max - min) < 2 * QP)
						{
							smooth_mode(v);
						}
					}
					index = 0;
					for (int x = j - 5; x <= j + 4; x++)
					{
						output[i][x][k] = v[index];
						index++;
					}
				} //end if of Horizontal Block.
				else
				{
					output[i][j][k] = input[i][j][k];
				}
			} // end of Horizontal scan
		} // end of Vertical scan
	} // end of image depth

	for (int k = 0; k < input[0][0].size(); k++)
	{
		for (int i = 0; i < input.size(); i++)
		{
			for (int j = 0; j < input[0].size(); j++)
			{
				if ((i % 8) == 0 && i != 0)
				{
					index = 0; min = 256; max = -1; F = 0;
					for (int x = i - 5; x <= i + 4; x++)
					{
						v[index] = input[x][j][k];
						index++;
					}
					findmin_max(v, min, max);
					geta(v, a);
					F = getvalF(v);
					if (F < T2)
					{
						if (a[1] < QP)
						{
							default_mode(v, a);
						}
					}
					else
					{
						if (max - min < 2 * QP)
						{
							smooth_mode(v);
						}
					}
					index = 0;
					for (int x = i - 5; x <= i + 4; x++)
					{
						output[x][j][k] = v[index];
						index++;
					}
				} //end if of Vertical Block.
			}
		}
	}
} // end of function