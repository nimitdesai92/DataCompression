#include "all.h"


std::vector <unsigned char> fileread(char *filename)
{
	std::vector < unsigned char > filetype;
	unsigned char symbol[1];
	FILE *filer = NULL;
	filer = fopen(filename, "rb");
	while (fread(symbol, sizeof(unsigned char), 1, filer) != 0)
	{
		filetype.push_back(symbol[0]);
	}
	fclose(filer);
	return filetype;
}

void filewrite(char *filename, std::vector < unsigned char > filetype)
{
	FILE *filew = NULL;
	filew = fopen(filename, "wb");
	fwrite(&filetype[0], sizeof(unsigned char), (int)filetype.size(), filew);
	fclose(filew);
}

void displayfile(std::vector <unsigned char> filetype)
{
	for (int i = 0; i < (int)filetype.size(); i++)
	{
		std::cout << filetype[i];
	}
	std::cout << "\n\n";
}