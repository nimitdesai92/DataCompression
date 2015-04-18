#include "all.h"


std::vector <unsigned char> MTF(std::vector <unsigned char> filetype)
{
	std::vector <unsigned char> filetype_mtf;
	std::vector <unsigned char> encode_dict(256);
	int j = 0, k, temp;

	for (int i = 0; i < 256; i++)
	{
		encode_dict[i] = (unsigned char)i;
	}
	
	while (j < (int)filetype.size())
	{
		k = 0;
		while (encode_dict[k] != filetype[j])
		{
			k++;
		}
		
		filetype_mtf.push_back(k);

		if (k != 0)
		{ 
			temp = encode_dict[0];
			encode_dict[0] = encode_dict[k];
			for (int i = k; i > 1; i--)
			{
				encode_dict[i] = encode_dict[i - 1];
			}
			encode_dict[1] = temp;
		}
		j++;
	}

	return filetype_mtf;
}


std::vector <unsigned char> MTFdecoder(std::vector <unsigned char> filetype)
{
	std::vector <unsigned char> filetype_mtf;
	std::vector <unsigned char> encode_dict(256);
	int j = 0, k, temp;

	for (int i = 0; i < 256; i++)
	{
		encode_dict[i] = (unsigned char)i;
	}

	while (j < (int)filetype.size())
	{
		k = filetype[j];
		filetype_mtf.push_back(encode_dict[k]);

		if (k != 0)
		{
			temp = encode_dict[0];
			encode_dict[0] = encode_dict[k];
			for (int i = k; i > 1; i--)
			{
				encode_dict[i] = encode_dict[i - 1];
			}
			encode_dict[1] = temp;
		}
		j++;
	}

	return filetype_mtf;
}