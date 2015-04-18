#include "all.h"

void read_transition(std::vector<std::vector<float>> &transition)
{
	int number;
	float prob;
	char temp = 0;
	int count = 0;
	int i = 0, j = 0;
	FILE *filer = NULL;
	filer = fopen("QM_state_transition_table.txt", "r");

	while (i < 46)
	{
		if (count == 0)
		{ 
			fscanf(filer, "%c", &temp);
			while (temp != ' ')
			{
				fscanf(filer, "%c", &temp);
			}
			transition[i][0] = i;
			count++;
		}
		else if (count == 1)
		{
			fscanf(filer, "%x", &number);
			transition[i][1] = number;
			count++;
		}
		else if (count == 2)
		{
			fscanf(filer, "%f", &prob);
			transition[i][2] = prob;
			count++;
		}
		else if (count == 3)
		{
			fscanf(filer, "%c", &temp);
			if (temp != ' ')
			{
				transition[i][3] = temp - 48;
				count++;
			}
		}
		else if (count == 4)
		{
			fscanf(filer, "%c", &temp);
			if (temp != ' ')
			{
				transition[i][4] = temp - 48;
				count++;
			}
		}
		else if (count == 5)
		{
			fscanf(filer, "%c", &temp);
			count = 0;
			i++;
		}
	}
	fclose(filer);
}

void renormalize(std::string &out, bool &carry,unsigned int &A,unsigned int &C)
{
	if (carry == true)
	{
		out += '1';
		carry = false;
	}
	while (A < 0x8000)
	{
		A <<= 1;
		if (C & 0x8000)
		{
			out += '1';
		}
		else
			out += '0';
		
		C <<= 1;
		if (C > 65535)
		{
			C -= 65536;
		}
	}
}

void Qmcoder(std::vector<unsigned char> file_org, std::vector<std::vector<float>> transition, char* filename)
{
	std::string out;
	int MPS = 0;
	int LPS = 1;
	int temp;
	int current_state = 0;
	unsigned int A = 0x10000;
	unsigned int C = 0x0000;
	int Q_e = transition[0][1];
	bool carry = false;

	int byte;
	char bits;
	int count = 0, plane = 7;
	int sum = 0;

	while (count < file_org.size())
	{
		sum = 0;
		for (int i = 0; i < file_org.size(); i++)
		{
			byte = file_org[i];
			bits = (byte >> plane) & 1;
			if (bits == MPS)
			{
				A = A - Q_e;
				if (A < 0x8000)
				{
					if (A < Q_e)
					{
						if (C + A > 0xffff)
						{
							carry = true;
							C = C + A - 65536;
							A = Q_e;
						}
						else
						{ 
							C += A;
							A = Q_e;
						}
					}
					current_state += transition[current_state][3];
					Q_e = transition[current_state][1];
					renormalize(out, carry, A, C);
				}
			}
			else if (bits == LPS)
			{
				A = A - Q_e;
				if (A >= Q_e)
				{ 
					if (C + A > 0xffff)
					{
						carry = true;
						C = C + A - 65536;
						A = Q_e;
					}
					else
					{
						C += A;
						A = Q_e;
					}
				}
				if (current_state == 0)
				{
					temp = MPS;
					MPS = LPS;
					LPS = temp;
					Q_e = transition[current_state][1];
				}
				else
				{
					current_state -= transition[current_state][4];
					Q_e = transition[current_state][1];
				}
				renormalize(out, carry, A, C);
			}
			sum++;
		}
		count += sum / 8;
		plane--;
	}
	writefile(filename, out);
}

void writefile(char* filename, std::string out)
{
	int ptr, char_ptr = 7;
	unsigned char byte, write_byte = 0;
	FILE *filew = NULL;
	filew = fopen(filename, "wb");

	for (int j = 0; j < out.size(); j++)
	{
		byte = out[j];
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
	fclose(filew);
}