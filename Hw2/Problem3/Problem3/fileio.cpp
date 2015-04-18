# include "all.h"

void imread(char *filename, int x1, int y1, int z1, std::vector<std::vector<std:: vector <int> > > &Img)
{
	Img.resize(x1, std::vector<std::vector<int>>(y1, std::vector<int>(z1,0)));

	FILE *filer = NULL;
	filer = fopen(filename, "rb");

	for (int i = 0; i <= x1 - 1; i++)
	{
		for (int j = 0; j <= y1 - 1; j++)
		{
			for (int k = 0; k <= z1 - 1; k++)
			{
				Img[i][j][k] = (double)fgetc(filer);
			}
		}
	}
	fclose(filer);
}

void imwrite(char *filename, std::vector<std::vector<std::vector<int> > > Img)
{
	FILE *filew = NULL;
	filew = fopen(filename, "wb");

	for (int i = 0; i <= Img.size() - 1; i++)
	{
		for (int j = 0; j <= Img[0].size() - 1; j++)
		{
			for (int k = 0; k <= Img[0][0].size() - 1; k++)
			{
				fputc(Img[i][j][k], filew);
			}
		}
	}
	fclose(filew);
}

void display_block(std::vector<std::vector<std:: vector <float> > > block)
{
	for (int i = 0; i <= block.size() - 1; i++)
	{
		for (int j = 0; j <= block[0].size() - 1; j++)
		{
			for (int k = 0; k <= block[0][0].size() - 1; k++)
			{
				std::cout << block[i][j][k] << "\t";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}