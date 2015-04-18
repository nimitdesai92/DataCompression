#include "all.h"

std::vector <unsigned char> fileread(char *filename)
{
	std::vector <unsigned char> file;
	unsigned char symbol;
	FILE *filer = NULL;
	filer = fopen(filename, "rb");
	while (fread(&symbol, sizeof(unsigned char), 1, filer) != 0)
	{
		file.push_back(symbol);
	}
	fclose(filer);
	return file;
}

void displayfile_vector(std::vector <unsigned char> filetype)
{
	for (int i = 0; i < (int)filetype.size(); i++)
	{
		std::cout << filetype[i];
	}
	std::cout << "\n\n";
}

void block(std::vector<unsigned char> file_org, std::vector<unsigned char> &file_vector, int block_Size)
{
	int image_size, count_row = 0, count_col;
	image_size = (file_org.size() / sqrt(file_org.size()));

	while (count_row < image_size - (block_Size / 2))
	{
		count_col = 0;
		while (count_col < image_size - (block_Size / 2))
		{
			for (int i = count_row; i < count_row + block_Size; i++)
			{
				for (int j = count_col; j < count_col + block_Size; j++)
				{
					file_vector.push_back(file_org[i*image_size + j]);
				}
			}
			count_col = count_col + block_Size;
		}
		count_row = count_row + block_Size;
	}
}