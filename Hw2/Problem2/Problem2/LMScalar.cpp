#include "all.h"

void calchist(std::vector <unsigned char> file_org, std::vector <float> &file_hist)
{
	unsigned int i = 0;
	while (i < file_org.size())
	{
		file_hist[file_org[i]]++;
		i++;
	}
	i = 0;
	while (i < file_hist.size())
	{
		file_hist[i] = file_hist[i] / file_org.size();
		i++;
	}
}

void calchist_float(std::vector <float> file_org, std::vector <float> &file_hist)
{
	unsigned int i = 0;
	while (i < file_org.size())
	{
		file_hist[file_org[i]]++;
		i++;
	}
	i = 0;
	while (i < file_hist.size())
	{
		file_hist[i] = file_hist[i] / file_org.size();
		i++;
	}
}

double calc_entropy(std::vector<float> &file_hist)
{
	double entropy = 0;

	for (int i = 0; i < 256; i++)
	{
		if (file_hist[i] != 0)
		{
			entropy = entropy - (file_hist[i] * log2f(file_hist[i]));
		}
	}
	return entropy;
}

void calc_cdf(std::vector <float> &file_hist)
{
	unsigned int i = 1;
	while (i < file_hist.size())
	{
		file_hist[i] += file_hist[i - 1];
		i++;
	}
}

std::vector<float> sum_hist(std::vector <float> hist1, std::vector <float> hist2, std::vector <float> hist3)
{
	std::vector<float> sum(256, 0);
	
	for (int i = 0; i <= 255; i++)
	{
		sum[i] = (hist1[i] + hist2[i] + hist3[i]) / 3;
	}
	return sum;
}

float calc_MSE(std::vector<float> &code_book, std::vector<float> hist, std::vector<float> &rep_val)
{
	float MSE = 0;
	for (int i = 0; i < code_book.size(); i++)
	{
		if (i == 0)
		{
			MSE = pow((0 - rep_val[i]), 2)*(hist[0]);
			for (int j = 1; j < code_book[0]; j++)
			{
				MSE += pow((j - rep_val[i]), 2)*(hist[j] - hist[j - 1]);
			}
		}
		else
		{
			for (int j = code_book[i - 1]; j < code_book[i]; j++)
			{
				MSE += pow((j - rep_val[i]), 2)*(hist[j] - hist[j - 1]);
			}
		}
	}
	return MSE;
}

float calc_PSNR(float MSE, int max)
{
	return (10 * log10(pow(max, 2) / MSE));
}

void scalar_quantizer(std::vector<float> &code_book, std::vector<float> hist, std::vector<float> &rep_val)
{
	int no_interval = code_book.size(), count = 1, count_2;
	float MSE = 100, prev_MSE = 200, PSNR;

	for (unsigned int i = 0; i < hist.size(); i++)
	{
		if (hist[i] >= (float) count / no_interval && count <= no_interval)
		{
			code_book[count - 1] = i;
			count++;
		}
	}

	count = 1;
	while (abs((prev_MSE - MSE) / MSE) > 0.001)
	{
		prev_MSE = MSE;
		rep_val.clear();
		rep_val.resize(code_book.size(), 0);
		
		for (unsigned int i = 0; i < code_book.size(); i++)
		{
			if (i == 0)
			{
				for (int j = 1; j <= code_book[0]; j++)
				{
					rep_val[i] += (j * (hist[j] - hist[j-1])) / hist[code_book[i]];
				}
			}
			else
			{
				for (int j = code_book[i - 1] + 1; j <= code_book[i]; j++)
				{
					rep_val[i] += (j * (hist[j] - hist[j - 1])) / (hist[code_book[i]] - hist[code_book[i - 1]]);
				}
			}
		}
		
		MSE = calc_MSE(code_book,hist,rep_val);
		PSNR = calc_PSNR(MSE, 255);
		std::cout << "PSNR at stage " << count << " is " << PSNR << std::endl;
		count++;
		
		for (int i = 0; i < code_book.size() - 1; i++)
		{
			code_book[i] = (rep_val[i] + rep_val[i + 1]) / 2.0;
		}
		for (int i = 0; i < code_book.size() - 1; i++)
		{
			count_2 = 0;
			for (int j = code_book[i] + 1; j < code_book[i + 1] - 1; j++)
			{
				if (hist[j] - hist[j - 1] != 0)
				{
					count_2++;
				}
			}
			if (count_2 == 0)
			{
				code_book[i] = (code_book[i] + code_book[i + 1]) / 2.0;
			}
		}
	}
}

void quantized(std::vector <unsigned char> file_org, std::vector <float> &file_quant, std::vector <float> code_book, std::vector <float> rep_val)
{
	unsigned char value;

	for (int i = 0; i < file_org.size(); i++)
	{
		value = file_org[i];
		for (int j = 0; j < code_book.size(); j++)
		{
			if (value <= code_book[j])
			{
				file_quant.push_back(rep_val[j]);
				break;
			}
		}
	}
}