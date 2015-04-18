#include "all.h"

struct shannonode
{
	int first;
	int last;
	shannonode *left;
	shannonode *right;
};

shannonode* createshannonode(int first, int last)
{
	shannonode* newnode = new shannonode();
	newnode->first = first;
	newnode->last = last;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

shannonode* insert(shannonode *root, int first, int last)
{
	if (root == NULL)
	{
		root = createshannonode(first, last);
	}
	else if (first == root->first)
	{
		root->left = insert(root->left, first, last);
		root = root->left;
	}
	else if (last == root->last)
	{
		root->right = insert(root->right, first, last);
		root = root->right;
	}
	return root;
}

void shannon(std::vector<std::pair<unsigned char, float> > newvector, shannonode* root, int first, int last)
{
	int ptr;
	float left_val = 0, right_val = 0;
	shannonode* rootl, *rootr;
	float current, previous;
	current = 1;
	ptr = first;
	if (first >= last)
	{
		return;
	}
	if (first == last - 1)
	{
		rootl = insert(root, first, first);
		rootr = insert(root, last, last);
		return;
	}
	else
	{
		do
		{
			left_val = 0;
			right_val = 0;
			previous = current;
			for (int i = first; i <= ptr; i++)
			{
				left_val += newvector[i].second;
			}
			for (int i = ptr + 1; i <= last; i++)
			{
				right_val += newvector[i].second;
			}
			current = left_val - right_val;
			ptr++;
		} while (fabs(previous) > fabs(current) && ptr < last);
		rootl = insert(root, first, ptr - 2);
		rootr = insert(root, ptr - 1, last);
	}
	shannon(newvector, rootl, first, ptr - 2);
	shannon(newvector, rootr, ptr - 1, last);
}

string shannon_code(shannonode* root, int index, string code)
{
	shannonode* temp1, *temp2;
	int low, high;

	if (root == NULL)
	{
		code = "";
		return code;
	}

	temp1 = root->left;
	temp2 = root->right;
	if (temp1 == NULL && temp2 == NULL)
	{
		return code;
	}
	low = temp1->last;
	high = temp2->first;
	if (index <= low && index != high)
	{
		code += '0';
		return shannon_code(root->left, index, code);
	}
	else if (index >= high && index != low)
	{
		code += '1';
		return shannon_code(root->right, index, code);
	}
	else if (index == low && index == high)
	{
		return code;
	}
}

void erase_tree(shannonode *leaf)
{
	if (leaf != NULL)
	{
		erase_tree(leaf->left);
		erase_tree(leaf->right);
		delete leaf;
	}
}

void insert(shannonode* root, std::vector<std::pair<unsigned char, string> > &newvector, std::vector<std::pair<unsigned char, float> > twovector)
{
	std::pair<unsigned char, string> temp;
	for (int i = 0; i < twovector.size(); i++)
	{
		temp.first = twovector[i].first;
		temp.second = shannon_code(root, i, "");
		newvector.push_back(temp);
	}
}

void displaysymbol(std::vector<std::pair<unsigned char, string> > newvector)
{
	for (int i = 0; i < newvector.size(); i++)
	{
		cout << (int)newvector[i].first << "\t" << newvector[i].second << endl;
	}
}