#include "all.h"

std::vector <unsigned char> ModifiedRLE(std::vector <unsigned char> filetype)
{
	std::vector < unsigned char > filetype_rle;
	unsigned char current_char, count;
	int i = 0;

	while (i < (int)filetype.size())
	{
		count = 1;
		current_char = filetype[i];

		while (i < filetype.size() - 1 && filetype[i + 1] == current_char && count<127)
		{
			count++;
			i++;
		}

		if (count > 1 || current_char >= 128)
		{
			count = count + 128;
			filetype_rle.push_back(count);
			filetype_rle.push_back(current_char);
		}
		else
			filetype_rle.push_back(current_char);

		i++;
	}
	return filetype_rle;
}

std::vector <unsigned char> modifiedRLE_decoder(std::vector <unsigned char> filetype)
{
	std::vector < unsigned char > filetype_decode;
	unsigned char current_char, count;
	int a;

	for (int i = 0; i < (int)filetype.size() - 1; i++)
	{
		a = 0;
		if (filetype[i] >= 128)
		{
			count = filetype[i];
			count = count - 128;
			current_char = filetype[i + 1];
			while (a < count || count == 0)
			{
				filetype_decode.push_back(current_char);
				a = a + 1;
			}
			i = i + 1;
		}
		else
		{
			current_char = filetype[i];
			filetype_decode.push_back(current_char);
		}
	}
	return filetype_decode;
}