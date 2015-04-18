#include "all.h"

int main()
{
	std::vector <unsigned char> audio_org, text_org, binaryImg_org, grayImg_org;
	float audio[256] = { 0 }, text[256] = { 0 }, binaryImg[256] = { 0 }, grayImg[256] = { 0 };
	float audio_total, text_total, binaryImg_total, grayImg_total;
	float audio_probability[256] = { 0 }, text_probability[256] = { 0 }, binaryImg_probability[256] = { 0 }, grayImg_probability[256] = { 0 };
	double audio_entropy, text_entropy, binaryImg_entropy, grayImg_entropy;
	std::vector<std::pair<unsigned char, float> > audio_2, text_2, binaryImg_2, grayImg_2;
	std::vector<std::pair<unsigned char, string> > shannon_audio, shannon_text, shannon_binaryImg, shannon_grayImg;
	std::vector<std::pair<unsigned char, string> > huffman_audio, huffman_text, huffman_binaryImg, huffman_grayImg;

	/* Data Processing and Compression................................. 
	
	...................................................for Audio File*/

	cout << "Audio File Data" << endl << endl;
	audio_org = fileread("audio.dat", audio);
	audio_total = sum(audio);
	probability(audio, audio_probability, audio_total);
	fillvector(audio_probability, audio_2);
	sortvector(audio_2);
	erase(audio_2);
	//displayfile_pair(audio_2);
	cout << "# of unique character: " << audio_2.size() << endl << endl;
	audio_entropy = calc_entropy(audio_probability);
	cout << "Entropy for Audio File: " << audio_entropy << endl << endl;
	shannonode *root_audio = NULL;
	root_audio = insert(root_audio, 0, (int)audio_2.size() - 1);
	shannon(audio_2, root_audio, 0, (int)audio_2.size()-1);
	insert(root_audio, shannon_audio, audio_2);
	//displaysymbol(shannon_audio);
	erase_tree(root_audio);
	filewrite("audio_Shannonencode.dat", shannon_audio, audio_org);
	vector<huffmannode*> audio_leaf;
	for (int i = 0; i < audio_2.size(); i++)
	{
		audio_leaf.push_back(createleafnode(audio_2[i].first, audio_2[i].second));
	}
	huffman(audio_leaf);
	huff_insert(huffman_audio, audio_leaf);
	//displaysymbol(huffman_audio);
	filewrite("audio_Huffmancode.dat", huffman_audio, audio_org);
	adap_huffman(audio_org, "audio_adaptivehuffman.dat");

	/* Data Processing and Compression............................
	
	...............................................for Text File*/

	cout << "Text File Data" << endl << endl;
	text_org = fileread("text.dat", text);
	text_total = sum(text);
	probability(text, text_probability, text_total);
	fillvector(text_probability, text_2);
	sortvector(text_2);
	erase(text_2);
	//displayfile_pair(text_2);
	cout << "# of unique character: " << text_2.size() << endl << endl;
	text_entropy = calc_entropy(text_probability);
	cout << "Entropy for Text File: " << text_entropy << endl << endl;
	shannonode *root_text = NULL;
	root_text = insert(root_text, 0, (int)text_2.size() - 1);
	shannon(text_2, root_text, 0, (int)text_2.size() - 1);
	insert(root_text, shannon_text, text_2);
	//displaysymbol(shannon_text);
	erase_tree(root_text);
	filewrite("text_Shannonencode.dat", shannon_text, text_org);
	vector<huffmannode*> text_leaf;
	for (int i = 0; i < text_2.size(); i++)
	{
		text_leaf.push_back(createleafnode(text_2[i].first, text_2[i].second));
	}
	huffman(text_leaf);
	huff_insert(huffman_text, text_leaf);
	//displaysymbol(huffman_audio);
	filewrite("text_Huffmancode.dat", huffman_text, text_org);
	adap_huffman(text_org, "text_adaptivehuffman.dat");

	/* Data Processing and Compression...............................

	...........................................for BinaryImage File*/

	cout << "Binary Image File Data" << endl << endl;
	binaryImg_org = fileread("binary.dat.raw", binaryImg);
	binaryImg_total = sum(binaryImg);
	probability(binaryImg, binaryImg_probability, binaryImg_total);
	fillvector(binaryImg_probability, binaryImg_2);
	sortvector(binaryImg_2);
	erase(binaryImg_2);
	//displayfile_pair(binaryImg_2);
	cout << "# of unique character: " << binaryImg_2.size() << endl << endl;
	binaryImg_entropy = calc_entropy(binaryImg_probability);
	cout << "Entropy for Binary Image File: " << binaryImg_entropy << endl << endl;
	shannonode *root_binaryImg = NULL;
	root_binaryImg = insert(root_binaryImg, 0, (int)binaryImg_2.size() - 1);
	shannon(binaryImg_2, root_binaryImg, 0, (int)binaryImg_2.size() - 1);
	insert(root_binaryImg, shannon_binaryImg, binaryImg_2);
	//displaysymbol(shannon_binaryImg);
	erase_tree(root_binaryImg);
	filewrite("binaryImg_Shannonencode.dat.raw", shannon_binaryImg, binaryImg_org);
	vector<huffmannode*> binaryImg_leaf;
	for (int i = 0; i < binaryImg_2.size(); i++)
	{
		binaryImg_leaf.push_back(createleafnode(binaryImg_2[i].first, binaryImg_2[i].second));
	}
	huffman(binaryImg_leaf);
	huff_insert(huffman_binaryImg, binaryImg_leaf);
	//displaysymbol(huffman_audio);
	filewrite("binaryImg_Huffmancode.dat.raw", huffman_binaryImg, binaryImg_org);
	adap_huffman(binaryImg_org, "binaryImg_adaptivehuffman.dat.raw");

	/* Data Processing and Compression....................................

	.............................................for Grayscale Image File*/

	cout << "Grayscale Image Data" << endl << endl;
	grayImg_org = fileread("image.dat.raw", grayImg);
	grayImg_total = sum(grayImg);
	probability(grayImg, grayImg_probability, grayImg_total);
	fillvector(grayImg_probability, grayImg_2);
	sortvector(grayImg_2);
	erase(grayImg_2);
	//displayfile_pair(grayImg_2);
	cout << "# of unique character: " << grayImg_2.size() << endl << endl;
	grayImg_entropy = calc_entropy(grayImg_probability);
	cout << "Entropy for Grayscale Image File: " << grayImg_entropy << endl << endl;
	shannonode *root_grayImg = NULL;
	root_grayImg = insert(root_grayImg, 0, (int)grayImg_2.size() - 1);
	shannon(grayImg_2, root_grayImg, 0, (int)grayImg_2.size() - 1);
	insert(root_grayImg, shannon_grayImg, grayImg_2);
	//displaysymbol(shannon_grayImg);
	erase_tree(root_grayImg);
	filewrite("image_Shannonencode.dat.raw", shannon_grayImg, grayImg_org);
	vector<huffmannode*> grayImg_leaf;
	for (int i = 0; i < grayImg_2.size(); i++)
	{
		grayImg_leaf.push_back(createleafnode(grayImg_2[i].first, grayImg_2[i].second));
	}
	huffman(grayImg_leaf);
	huff_insert(huffman_grayImg, grayImg_leaf);
	//displaysymbol(huffman_audio);
	filewrite("image_Huffmancode.dat.raw", huffman_grayImg, grayImg_org);
	adap_huffman(grayImg_org, "image_adaptivehuffman.dat.raw");


	return 0;
}