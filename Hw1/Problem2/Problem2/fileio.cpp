#include "all.h"


std::vector <unsigned char> fileread(char *filename, float filetype[])
{
	std::vector <unsigned char> file;
	unsigned char symbol[1];
	FILE *filer = NULL;
	filer = fopen(filename, "rb");
	while (fread(symbol, sizeof(unsigned char), 1, filer) != 0)
	{
		file.push_back(symbol[0]);
		filetype[(int)symbol[0]]++;
	}
	fclose(filer);
	return file;
}

void filewrite(char *filename, std::vector<std::pair<unsigned char, string> > &newvector, std::vector <unsigned char> &orgvector)
{
	int ptr, char_ptr = 7;
	string temp;
	unsigned char byte, write_byte = 0;
	FILE *filew = NULL;
	filew = fopen(filename, "wb");
	for (int i = 0; i < orgvector.size(); i++)
	{
		ptr = 0;
		while (newvector[ptr].first != orgvector[i])
		{
			ptr++;
		}
		temp = newvector[ptr].second;
		for (int j = 0; j < temp.size(); j++)
		{
			byte = temp[j];
			if (byte == '0' && char_ptr >= 0)
			{
				char_ptr--;
			}
			else if (byte == '1' && char_ptr >= 0)
			{
				write_byte = write_byte | 1 << char_ptr;
				char_ptr--;
			}
			else
			{
				char_ptr = 7;
				fwrite(&write_byte, sizeof(unsigned char), 1, filew);
				write_byte = 0;
				if (byte == '0')
				{
					char_ptr--;
				}
				else
				{
					write_byte = write_byte | 1 << char_ptr;
					char_ptr--;
				}
			}
		}
	}
	fclose(filew);
}

void displayfile(float filetype[])
{
	for (int i = 0; i < 256; i++)
	{
		cout << filetype[i] << "\t";
	}
	cout << "\n\n";
}

void displayfile_vector(std::vector <unsigned char> filetype)
{
	for (int i = 0; i < (int)filetype.size(); i++)
	{
		std::cout << filetype[i];
	}
	std::cout << "\n\n";
}

void displayfile_pair(std::vector<std::pair<unsigned char, float> > filetype)
{
	for (int i = 0; i < (int)filetype.size(); i++)
	{
		std::cout << (int)filetype[i].first << " " << filetype[i].second << "\t";
	}
	std::cout << "\n\n";
}