#include "all.h"

//Huffmann Algorithm

struct huffmannode
{
	int index;
	float sym_probability;
	huffmannode* parent;
	huffmannode* left;
	huffmannode* right;
};

huffmannode* createleafnode(int index, float sym_probablity)
{
	huffmannode* newnode = new huffmannode();
	newnode->index = index;
	newnode->sym_probability = sym_probablity;
	newnode->parent = NULL;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

huffmannode* createrootnode(huffmannode* left, huffmannode* right)
{
	huffmannode* newnode = new huffmannode();
	newnode->index = 0;
	newnode->sym_probability = left->sym_probability + right->sym_probability;
	newnode->parent = NULL;
	newnode->left = left;
	newnode->right = right;
	left->parent = newnode;
	right->parent = newnode;
	return newnode;
}

void huffman(vector<huffmannode*> leaf)
{
	huffmannode* newroot, *temp;

	if (leaf.size() < 1)
	{
		return;
	}
	while (leaf.size() != 1)
	{
		newroot = createrootnode(leaf[leaf.size() - 1], leaf[leaf.size() - 2]);
		leaf.pop_back();
		leaf.pop_back();
		leaf.push_back(newroot);
		for (int i = 0; i < (int)leaf.size(); i++)
		{
			for (int j = i; j < (int)leaf.size(); j++)
			{
				if (leaf[i]->sym_probability < leaf[j]->sym_probability)
				{
					temp = leaf[i];
					leaf[i] = leaf[j];
					leaf[j] = temp;
				}
			}
		}
	}
	return;
}

string huffman_code(huffmannode* root, string code)
{
	huffmannode* temp1;
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
		return huffman_code(temp1, code);
	}
	else if (root == temp1->right)
	{
		code += '1';
		return huffman_code(temp1, code);
	}
}

void huff_insert(std::vector<std::pair<unsigned char, string> > &newvector, std::vector<huffmannode*> twovector)
{
	std::pair<unsigned char, string> temp;
	string temp_2;
	for (int i = 0; i < twovector.size(); i++)
	{
		temp.second = "";
		temp.first = twovector[i]->index;
		temp_2 = huffman_code(twovector[i], "");
		for (string::reverse_iterator rit = temp_2.rbegin(); rit != temp_2.rend(); ++rit)
		{
			temp.second += *rit;
		}
		newvector.push_back(temp);
	}
}