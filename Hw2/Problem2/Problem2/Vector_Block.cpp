#include "all.h"

void block(std::vector<unsigned char> file_org, std::vector<unsigned char> &file_vector, int block_Size)
{
	int image_size, count_row = 0, count_col;
	image_size = (file_org.size() / sqrt(file_org.size()));
	
	while (count_row < image_size - (block_Size/2))
	{
		count_col = 0;
		while (count_col < image_size - (block_Size/2))
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

void add_train(std::vector<unsigned char> one, std::vector<unsigned char> two, std::vector<unsigned char> three, std::vector<unsigned char> &final)
{
	for (int i = 0; i < one.size(); i++)
	{
		final.push_back(one[i]);
	}
	for (int i = 0; i < two.size(); i++)
	{
		final.push_back(two[i]);
	}
	for (int i = 0; i < three.size(); i++)
	{
		final.push_back(three[i]);
	}
}