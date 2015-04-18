#include "all.h"
#include "qmcoder.h"

int main()
{
	std::vector <unsigned char> audio_org, text_org, binary_org, image_org;
	std::vector <unsigned char> binary_block2, image_block2;
	std::vector <unsigned char> binary_block4, image_block4;
	std::vector < std::vector <float> > transition;
	
	transition.resize(46);
	for (int i = 0; i < 46; i++)
	{
		transition[i].resize(5);
	}
	read_transition(transition);

	audio_org = fileread("audio.dat");
	Qmcoder(audio_org, transition, "audio_Qm.dat");

	cabac(audio_org, 1, "audio_cabac_1.dat");
	cabac(audio_org, 2, "audio_cabac_2.dat");
	cabac(audio_org, 3, "audio_cabac_3.dat");

	text_org = fileread("text.dat");
	Qmcoder(text_org, transition, "text_Qm.dat");

	cabac(text_org, 1, "text_cabac_1.dat");
	cabac(text_org, 2, "text_cabac_2.dat");
	cabac(text_org, 3, "text_cabac_3.dat");

	binary_org = fileread("binary.dat");
	block(binary_org, binary_block2, 2);
	block(binary_org, binary_block4, 4);
	Qmcoder(binary_org, transition, "binary_Qm.dat");

	cabac(binary_org, 1, "binary_cabac_1.dat");
	cabac(binary_org, 2, "binary_cabac_2.dat");
	cabac(binary_org, 3, "binary_cabac_3.dat");

	cabac(binary_block2, 1, "binary_cabac_1_block2.dat");
	cabac(binary_block2, 2, "binary_cabac_2_block2.dat");
	cabac(binary_block2, 3, "binary_cabac_3_block2.dat");

	cabac(binary_block4, 1, "binary_cabac_1_block4.dat");
	cabac(binary_block4, 2, "binary_cabac_2_block4.dat");
	cabac(binary_block4, 3, "binary_cabac_3_block4.dat");


	image_org = fileread("image.dat");
	block(image_org, image_block2, 2);
	block(image_org, image_block4, 4);
	Qmcoder(image_org, transition, "image_Qm.dat");

	cabac(image_org, 1, "image_cabac_1.dat");
	cabac(image_org, 2, "image_cabac_2.dat");
	cabac(image_org, 3, "image_cabac_3.dat");

	cabac(image_block2, 1, "image_cabac_1_block2.dat");
	cabac(image_block2, 2, "image_cabac_2_block2.dat");
	cabac(image_block2, 3, "image_cabac_3_block2.dat");

	cabac(image_block4, 1, "image_cabac_1_block4.dat");
	cabac(image_block4, 2, "image_cabac_2_block4.dat");
	cabac(image_block4, 3, "image_cabac_3_block4.dat");

	return 0;
}