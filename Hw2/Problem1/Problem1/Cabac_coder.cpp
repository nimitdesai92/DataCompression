#include "all.h"
#include "qmcoder.h"

void cabac(std::vector<unsigned char> file_org,int context_bits, char* filename)
{
	FILE *name = NULL;
	name = fopen(filename,"wb");
	QM coder(name);

	switch (context_bits)
	{
	case 1:
	{
		unsigned char byte, bits = 0, context;
		int count = 0, sum = 0, plane = 7;

		coder.StartQM("encode");

		while (count < file_org.size())
		{
			sum = 0;
			for (int i = 0; i < file_org.size(); i++)
			{
				context = bits;
				byte = file_org[i];
				bits = (byte >> plane) & 1;
				coder.encode(bits, context);
				sum++;
			}
			count += sum / 8;
			plane--;
		}
		coder.Flush();
		break;
	}
	case 2:
	{
		unsigned char byte, bits = 0, context[2] = { 0 };
		int count = 0, sum = 0, plane = 7;

		coder.StartQM("encode");

		while (count < file_org.size())
		{
			sum = 0;
			for (int i = 0; i < file_org.size(); i++)
			{
				context[0] = context[1];
				context[1] = bits;
				byte = file_org[i];
				bits = (byte >> plane) & 1;
				coder.encode(bits, context[1]*2 + context[0]);
				sum++;
			}
			count += sum / 8;
			plane--;
		}
		coder.Flush();
		break;
	}
	case 3:
	{
		unsigned char byte, bits = 0, context[3] = { 0 };
		int count = 0, sum = 0, plane = 7;

		coder.StartQM("encode");

		while (count < file_org.size())
		{
			sum = 0;
			for (int i = 0; i < file_org.size(); i++)
			{
				context[0] = context[1];
				context[1] = context[2];
				context[2] = bits;
				byte = file_org[i];
				bits = (byte >> plane) & 1;
				coder.encode(bits, context[2]*4 + context[1]*2 + context[0]);
				sum++;
			}
			count += sum / 8;
			plane--;
		}
		coder.Flush();
		break;
	}

	default:
		std::cout << "Wrong input" << std::endl;
		break;
	}
}