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

void plothist(std::vector <float> hist, char *filename)
{
	FILE *filew = NULL;
	filew = fopen(filename, "w");
	for (int i = 0; i < hist.size(); i++)
	{
		fprintf(filew, "%d%c%f", i, ',', hist[i]);
		fprintf(filew, "%c", '\n');
	}
	fclose(filew);
}

void filewrite(std::vector <unsigned char> file, char *filename)
{
	FILE *filew = NULL;
	filew = fopen(filename, "wb");
	for (int i = 0; i < file.size(); i++)
	{
		fputc(file[i], filew);
	}
	fclose(filew);
}