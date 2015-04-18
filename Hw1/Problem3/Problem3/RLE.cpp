#include "all.h"

std::vector <unsigned char> BasicRLE(std::vector <unsigned char> filetype)
{
	std::vector < unsigned char > filetype_rle;
	unsigned char current_char, count;
	int i = 0;

	while (i < (int)filetype.size())
	{
		count = 1;
		current_char = filetype[i];

		while (i < filetype.size() - 1 && filetype[i + 1] == current_char && count<255)
		{
			count++;
			i++;
		}
		filetype_rle.push_back(count);
		filetype_rle.push_back(current_char);
		i++;
	}
	return filetype_rle;
}

std::vector <unsigned char> BasicRLE_decoder(std::vector <unsigned char> filetype)
{
	std::vector < unsigned char > filetype_decode;
	unsigned char current_char, count;
	int a;

	for (int i = 0; i < (int)filetype.size() - 1; i++)
	{
		a = 0;
		count = filetype[i];
		current_char = filetype[i + 1];
		while (a < count)
		{
			filetype_decode.push_back(current_char);
			a = a + 1;
		}
		i = i + 1;
	}
	return filetype_decode;
}