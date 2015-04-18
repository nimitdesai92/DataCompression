#include "all.h"


//Adaptive Huffmann Algorithm

struct adap_huffmannode
{
	int character;
	int freq;
	int weight;

	adap_huffmannode* parent;
	adap_huffmannode* left;
	adap_huffmannode* right;
};

adap_huffmannode* locate[512] = { NULL };

adap_huffmannode* createnewnode(adap_huffmannode *NYT, unsigned char charac)
{
	adap_huffmannode* newnode = new adap_huffmannode();
	adap_huffmannode* newNYT = new adap_huffmannode();

	NYT->right = newnode;
	NYT->left = newNYT;
	NYT->freq = 1;
	NYT->character = -2;

	newnode->character = charac;
	newNYT->character = -1;

	newnode->parent = NYT;
	newNYT->parent = NYT;

	newnode->freq = 1;
	newNYT->freq = 0;

	newnode->left = NULL;
	newnode->right = NULL;

	newNYT->left = NULL;
	newNYT->right = NULL;

	newnode->weight = NYT->weight - 1;
	newNYT->weight = NYT->weight - 2;

	locate[newnode->weight] = newnode;
	locate[newNYT->weight] = newNYT;

	return newNYT;
}

void swapnadd(adap_huffmannode* current)
{
	int locate_pos, temp_weight, count, flag;
	adap_huffmannode* temp = new adap_huffmannode;
	adap_huffmannode* temp2 = new adap_huffmannode;
	adap_huffmannode* tempchild = new adap_huffmannode;
	locate_pos = current->weight;

	for (int i = locate_pos; i < 511; i++)
	{
		count = 0;
		flag = 0;
		for (int j = i + 1; j < 511; j++)
		{
			count = 1;
			temp = locate[j];
			if (temp->freq < locate[i]->freq)
			{
				if (i % 2 == 0 && locate[j] != locate[i]->parent)
				{
					flag = 1;
					temp2 = locate[j]->parent;
					if (j % 2 == 0)
					{
						tempchild = temp2->right;
						locate[j]->parent->right = locate[i]->parent->right;
						locate[i]->parent->right = tempchild;
					}
					else
					{
						tempchild = temp2->left;
						locate[j]->parent->left = locate[i]->parent->right;
						locate[i]->parent->right = tempchild;
					}
					locate[j]->parent = locate[i]->parent;
					locate[i]->parent = temp2;

					temp2 = locate[j];
					locate[j] = locate[i];
					locate[i] = temp;

					temp_weight = locate[j]->weight;
					locate[j]->weight = locate[i]->weight;
					locate[i]->weight = temp_weight;
					temp = locate[j]->parent;
					temp->freq = temp->left->freq + temp->right->freq;
					break;
				}
				else if (i % 2 == 1 && locate[j] != locate[i]->parent)
				{
					flag = 1;
					temp2 = locate[j]->parent;
					if (j % 2 == 0)
					{
						tempchild = temp2->right;
						locate[j]->parent->right = locate[i]->parent->left;
						locate[i]->parent->left = tempchild;
					}
					else
					{
						tempchild = temp2->left;
						locate[j]->parent->left = locate[i]->parent->left;
						locate[i]->parent->left = tempchild;
					}
					locate[j]->parent = locate[i]->parent;
					locate[i]->parent = temp2;

					temp2 = locate[j];
					locate[j] = locate[i];
					locate[i] = temp;

					temp_weight = locate[j]->weight;
					locate[j]->weight = locate[i]->weight;
					locate[i]->weight = temp_weight;
					temp = locate[j]->parent;
					temp->freq = temp->left->freq + temp->right->freq;
					break;
				}
			}
		}
		if ((count == 0 || flag == 0) && locate[i]->parent != NULL)
		{
			temp = locate[i]->parent;
			temp->freq = temp->left->freq + temp->right->freq;
		}
	}
}

string adaphuffman_code(adap_huffmannode* root, string code)
{
	adap_huffmannode* temp1;
	int low, high;

	if (root == NULL)
	{
		code = "";
		return code;
	}
	temp1 = root->parent;
	if (temp1 == NULL)
	{
		return code;
	}
	if (root == temp1->left)
	{
		code += '0';
		return adaphuffman_code(temp1, code);
	}
	else if (root == temp1->right)
	{
		code += '1';
		return adaphuffman_code(temp1, code);
	}
}

void adap_huffman(std::vector <unsigned char> filetype, char* filename)
{
	int ptr, char_ptr = 7;
	unsigned char byte, write_byte = 0;
	unsigned char temp;
	int symbol_occ[256] = { 0 };
	int i = 0, j = 0;
	string code, temp_2;

	adap_huffmannode* root = new adap_huffmannode;
	adap_huffmannode* NYT = new adap_huffmannode;
	adap_huffmannode* up = new adap_huffmannode;
	adap_huffmannode* temp_node = new adap_huffmannode;
	root->freq = 0;
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;
	root->weight = 511;
	locate[511] = root;
	NYT = root;

	FILE *filew = NULL;
	filew = fopen(filename, "wb");

	while (i < filetype.size())
	{
		j = 511;
		temp_2 = "";
		temp = filetype[i];
		if (symbol_occ[(int)temp] == 0)
		{
			up = NYT;
			NYT = createnewnode(NYT, temp);
			symbol_occ[(int)temp] = NYT->weight + 1;
			for (int z = 511; z >= 0; z--)
			{
				if (temp == locate[z]->character)
				{
					temp_node = locate[z];
					break;
				}
			}
			swapnadd(temp_node);
		}
		else
		{
			for (int z = 511; z >= 0; z--)
			{
				if (temp == locate[z]->character)
				{
					temp_node = locate[z];
					break;
				}
			}
			temp_node->freq = temp_node->freq + 1;
			swapnadd(temp_node);
		}
		while (locate[j]->character != temp)
		{
			j--;
		}
		code = adaphuffman_code(locate[j], "");
		for (string::reverse_iterator rit = code.rbegin(); rit != code.rend(); ++rit)
		{
			temp_2 += *rit;
		}

		for (int k = 0; k < temp_2.size(); k++)
		{
			byte = temp_2[k];
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
		i++;
	}
}