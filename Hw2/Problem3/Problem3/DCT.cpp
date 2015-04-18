#include "all.h"

void resize(std::vector<std::vector<std::vector<float> > > &block)
{
	block.resize(8, std::vector<std::vector<float> >(8, std::vector<float>(1, 0)));
}

void adjust_range(std::vector<std::vector<std::vector<int> > > &Img)
{
	for (int i = 0; i <= Img.size() - 1; i++)
	{
		for (int j = 0; j <= Img[0].size() - 1; j++)
		{
			for (int k = 0; k <= Img[0][0].size() - 1; k++)
			{
				Img[i][j][k] = Img[i][j][k] - 128;
			}
		}
	}
}

std::vector<std::vector<float > > getq(int ratio)
{
	std::vector<std::vector<float> > Q = { { 16, 11, 10, 16, 24, 40, 51, 61 },
	{ 12, 12, 14, 19, 26, 58, 60, 55 },
	{ 14, 13, 16, 24, 40, 57, 69, 56 },
	{ 14, 17, 22, 29, 51, 87, 80, 62 },
	{ 18, 22, 37, 56, 68, 109, 103, 77 },
	{ 24, 35, 55, 64, 81, 104, 113, 92 },
	{ 49, 64, 78, 87, 103, 121, 120, 101 },
	{ 72, 92, 95, 98, 112, 100, 103, 99 } };

	if (ratio == 50)
	{
		//display_block(Q);
		return Q;
	}

	else if (ratio < 50)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Q[i][j] = (50.0 / ratio) * Q[i][j];
			}
		}
		//display_block(Q);
		return Q;
	}

	else
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Q[i][j] = ((100 - ratio) / 50.0) * Q[i][j];
			}
		}
		//display_block(Q);
		return Q;
	}
}

void Dct_coeff(int start_x, int start_y, std::vector<std::vector<std::vector<int> > > Img, std::vector<std::vector<std::vector<float> > > &block, int ratio)
{
	int x, y;
	float C;
	std::vector<std::vector <float> > Q;

	Q = getq(ratio);

	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (i == 0 && j == 0)
				C = 0.5;
			else if (i == 0 || j == 0)
				C = 1 / sqrt(2);
			else
				C = 1;
			x = 0;
			while (x < 8)
			{
				y = 0;
				while (y < 8)
				{
					block[i][j][0] += Img[start_x + x][start_y + y][0] * cos((((2 * x + 1)*i *PI / 16.0))) * cos((((2 * y + 1)*j * PI / 16.0)));
					y++;
				}
				x++;
			}
			block[i][j][0] = (1 / 4.0) * C * block[i][j][0];
		}
	}

	for (int i = 0; i <= block.size() - 1; i++)
	{
		for (int j = 0; j <= block[0].size() - 1; j++)
		{
			block[i][j][0] = (round)(block[i][j][0] / Q[i][j]);
			if (block[i][j][0] == -0)
			{
				block[i][j][0] = 0;
			}
		}
	}
	display_block(block);
}