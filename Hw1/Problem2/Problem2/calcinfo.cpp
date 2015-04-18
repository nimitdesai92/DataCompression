#include "all.h"

float sum(float filetype[])
{
	float sum = 0;
	for (int i = 0; i < 256; i++)
	{
		sum = sum + filetype[i];
	}
	cout << "Sum is: " << sum << "\n\n";
	return sum;
}

void probability(float filetype[], float probability_file[], float file_total)
{
	for (int i = 0; i < 256; i++)
	{
		probability_file[i] = filetype[i] / file_total;
	}
}

double calc_entropy(float probability_file[])
{
	double entropy = 0;
	for (int i = 0; i < 256; i++)
	{
		if (probability_file[i] != 0)
		{
			entropy = entropy - (probability_file[i] * log2f(probability_file[i]));
		}
	}
	return entropy;
}

void fillvector(float filetype[], std::vector<std::pair<unsigned char, float> > &newvector)
{
	std::pair<unsigned char, float> temp;
	for (int i = 0; i < 256; i++)
	{
		temp.first = (unsigned char)i;
		temp.second = filetype[i];
		newvector.push_back(temp);
	}
}

void sortvector(std::vector<std::pair<unsigned char, float> > &newvector)
{
	unsigned char temp_char;
	float temp_prob;

	for (int i = 0; i < (int)newvector.size(); i++)
	{
		for (int j = i; j < (int)newvector.size(); j++)
		{
			if (newvector[i].second < newvector[j].second)
			{
				temp_char = newvector[i].first;
				temp_prob = newvector[i].second;
				newvector[i] = newvector[j];
				newvector[j].first = temp_char;
				newvector[j].second = temp_prob;
			}
		}
	}
}

void erase(std::vector<std::pair<unsigned char, float> > &newvector)
{
	int point;
	point = newvector.size();
	for (int i = 0; i < newvector.size(); i++)
	{
		if (newvector[i].second == 0)
		{
			point = i;
			break;
		}
	}
	newvector.resize(point);
}