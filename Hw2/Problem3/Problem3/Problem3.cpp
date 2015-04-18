#include "all.h"

int main()
{
	std::vector<std::vector <std::vector <int> > > Lena_Img;
	std::vector<std::vector <std::vector <float> > > block1, block2, block3, block4;
	std::vector<std::vector <std::vector <int> > > clock, clock1, clock2, clock3, clock4, clock5;
	std::vector<std::vector <std::vector <int> > > pepper, pepper1, pepper2, pepper3, pepper4, pepper5;
	std::vector<std::vector <std::vector <int> > > clock1_simple, clock2_simple, clock3_simple, clock4_simple, clock5_simple;
	std::vector<std::vector <std::vector <int> > > pepper1_simple, pepper2_simple, pepper3_simple, pepper4_simple, pepper5_simple;
	std::vector<std::vector <std::vector <int> > > clock1_paper, clock2_paper, clock3_paper, clock4_paper, clock5_paper;
	std::vector<std::vector <std::vector <int> > > pepper1_paper, pepper2_paper, pepper3_paper, pepper4_paper, pepper5_paper;
	std::vector<std::vector <std::vector <int> > > clock1_jpeg, clock2_jpeg, clock3_jpeg, clock4_jpeg, clock5_jpeg;
	std::vector<std::vector <std::vector <int> > > pepper1_jpeg, pepper2_jpeg, pepper3_jpeg, pepper4_jpeg, pepper5_jpeg;
	float PSNR_c1_org, PSNR_c2_org, PSNR_c3_org, PSNR_c4_org, PSNR_c5_org, PSNR_p1_org, PSNR_p2_org, PSNR_p3_org, PSNR_p4_org, PSNR_p5_org;
	float PSNR_c1_simple, PSNR_c2_simple, PSNR_c3_simple, PSNR_c4_simple, PSNR_c5_simple, PSNR_p1_simple, PSNR_p2_simple, PSNR_p3_simple, PSNR_p4_simple, PSNR_p5_simple;
	float PSNR_c1_paper, PSNR_c2_paper, PSNR_c3_paper, PSNR_c4_paper, PSNR_c5_paper, PSNR_p1_paper, PSNR_p2_paper, PSNR_p3_paper, PSNR_p4_paper, PSNR_p5_paper;
	float PSNR_c1_jpeg, PSNR_c2_jpeg, PSNR_c3_jpeg, PSNR_c4_jpeg, PSNR_c5_jpeg, PSNR_p1_jpeg, PSNR_p2_jpeg, PSNR_p3_jpeg, PSNR_p4_jpeg, PSNR_p5_jpeg;

	resize(block1); resize(block2); resize(block3); resize(block4);

	imread("lena.raw", 16, 16, 1, Lena_Img);
	adjust_range(Lena_Img);

	std::cout << "Dct coeff of block1 and its Q 50" << std::endl;
	Dct_coeff(0, 0, Lena_Img, block1, 50);
	std::cout << "Dct coeff of block2 and its Q 50" << std::endl;
	Dct_coeff(0, 8, Lena_Img, block2, 50);
	std::cout << "Dct coeff of block3 and its Q 50" << std::endl;
	Dct_coeff(8, 0, Lena_Img, block3, 50);
	std::cout << "Dct coeff of block4 and its Q 50" << std::endl;
	Dct_coeff(8, 8, Lena_Img, block4, 50);

	std::cout << "Dct coeff of block1 and its Q 10" << std::endl;
	Dct_coeff(0, 0, Lena_Img, block1, 10);
	std::cout << "Dct coeff of block2 and its Q 10" << std::endl;
	Dct_coeff(0, 8, Lena_Img, block2, 10);
	std::cout << "Dct coeff of block3 and its Q 10" << std::endl;
	Dct_coeff(8, 0, Lena_Img, block3, 10);
	std::cout << "Dct coeff of block4 and its Q 10" << std::endl;
	Dct_coeff(8, 8, Lena_Img, block4, 10);

	std::cout << "Dct coeff of block1 and its Q 90" << std::endl;
	Dct_coeff(0, 0, Lena_Img, block1, 90);
	std::cout << "Dct coeff of block2 and its Q 90" << std::endl;
	Dct_coeff(0, 8, Lena_Img, block2, 90);
	std::cout << "Dct coeff of block3 and its Q 90" << std::endl;
	Dct_coeff(8, 0, Lena_Img, block3, 90);
	std::cout << "Dct coeff of block4 and its Q 90" << std::endl;
	Dct_coeff(8, 8, Lena_Img, block4, 90);


	imread("clock.raw", 256, 256, 1, clock); imread("clock1.raw", 256, 256, 1, clock1); imread("clock2.raw", 256, 256, 1, clock2);
	imread("clock3.raw", 256, 256, 1, clock3); imread("clock4.raw", 256, 256, 1, clock4); imread("clock5.raw", 256, 256, 1, clock5);

	imread("pepper.raw", 256, 256, 3, pepper); imread("pepper1.raw", 256, 256, 3, pepper1); imread("pepper2.raw", 256, 256, 3, pepper2);
	imread("pepper3.raw", 256, 256, 3, pepper3); imread("pepper4.raw", 256, 256, 3, pepper4); imread("pepper5.raw", 256, 256, 3, pepper5);

	PSNR_c1_org = calc_PSNR(clock, clock1);
	std::cout << "PSNR value of Clock1 is: " << PSNR_c1_org << std::endl;
	PSNR_c2_org = calc_PSNR(clock, clock2);
	std::cout << "PSNR value of Clock2 is: " << PSNR_c2_org << std::endl;
	PSNR_c3_org = calc_PSNR(clock, clock3);
	std::cout << "PSNR value of Clock3 is: " << PSNR_c3_org << std::endl;
	PSNR_c4_org = calc_PSNR(clock, clock4);
	std::cout << "PSNR value of Clock4 is: " << PSNR_c4_org << std::endl;
	PSNR_c5_org = calc_PSNR(clock, clock5);
	std::cout << "PSNR value of Clock5 is: " << PSNR_c5_org << std::endl;

	PSNR_p1_org = calc_PSNR(pepper, pepper1);
	std::cout << "PSNR value of pepper1 is: " << PSNR_p1_org << std::endl;
	PSNR_p2_org = calc_PSNR(pepper, pepper2);
	std::cout << "PSNR value of pepper2 is: " << PSNR_p2_org << std::endl;
	PSNR_p3_org = calc_PSNR(pepper, pepper3);
	std::cout << "PSNR value of pepper3 is: " << PSNR_p3_org << std::endl;
	PSNR_p4_org = calc_PSNR(pepper, pepper4);
	std::cout << "PSNR value of pepper4 is: " << PSNR_p4_org << std::endl;
	PSNR_p5_org = calc_PSNR(pepper, pepper5);
	std::cout << "PSNR value of pepper5 is: " << PSNR_p5_org << std::endl;

	simple_deblock(clock1,clock1_simple);
	PSNR_c1_simple = calc_PSNR(clock, clock1_simple);
	std::cout << "PSNR value of Clock1 after simple De-blocking is: " << PSNR_c1_simple << std::endl;
	simple_deblock(clock2, clock2_simple);
	PSNR_c2_simple = calc_PSNR(clock, clock2_simple);
	std::cout << "PSNR value of Clock2 after simple De-blocking is: " << PSNR_c2_simple << std::endl;
	simple_deblock(clock3, clock3_simple);
	PSNR_c3_simple = calc_PSNR(clock, clock3_simple);
	std::cout << "PSNR value of Clock3 after simple De-blocking is: " << PSNR_c3_simple << std::endl;
	simple_deblock(clock4, clock4_simple);
	PSNR_c4_simple = calc_PSNR(clock, clock4_simple);
	std::cout << "PSNR value of Clock4 after simple De-blocking is: " << PSNR_c4_simple << std::endl;
	simple_deblock(clock5, clock5_simple);
	PSNR_c5_simple = calc_PSNR(clock, clock5_simple);
	std::cout << "PSNR value of Clock5 after simple De-blocking is: " << PSNR_c5_simple << std::endl;

	simple_deblock(pepper1, pepper1_simple);
	PSNR_p1_simple = calc_PSNR(pepper, pepper1_simple);
	std::cout << "PSNR value of Pepper1 after simple De-blocking is: " << PSNR_p1_simple << std::endl;
	simple_deblock(pepper2, pepper2_simple);
	PSNR_p2_simple = calc_PSNR(pepper, pepper2_simple);
	std::cout << "PSNR value of Pepper2 after simple De-blocking is: " << PSNR_p2_simple << std::endl;
	simple_deblock(pepper3, pepper3_simple);
	PSNR_p3_simple = calc_PSNR(pepper, pepper3_simple);
	std::cout << "PSNR value of Pepper3 after simple De-blocking is: " << PSNR_p3_simple << std::endl;
	simple_deblock(pepper4, pepper4_simple);
	PSNR_p4_simple = calc_PSNR(pepper, pepper4_simple);
	std::cout << "PSNR value of Pepper4 after simple De-blocking is: " << PSNR_p4_simple << std::endl;
	simple_deblock(pepper5, pepper5_simple);
	PSNR_p5_simple = calc_PSNR(pepper, pepper5_simple);
	std::cout << "PSNR value of Pepper5 after simple De-blocking is: " << PSNR_p5_simple << std::endl;

	paper_deblock(clock1, clock1_paper);
	PSNR_c1_paper = calc_PSNR(clock, clock1_paper);
	std::cout << "PSNR value of Clock1 after paper De-blocking is: " << PSNR_c1_paper << std::endl;
	imwrite("clock1_paper.raw", clock1_paper);
	paper_deblock(clock2, clock2_paper);
	PSNR_c2_paper = calc_PSNR(clock, clock2_paper);
	std::cout << "PSNR value of Clock2 after paper De-blocking is: " << PSNR_c2_paper << std::endl;
	imwrite("clock2_paper.raw", clock2_paper);
	paper_deblock(clock3, clock3_paper);
	PSNR_c3_paper = calc_PSNR(clock, clock3_paper);
	std::cout << "PSNR value of Clock3 after paper De-blocking is: " << PSNR_c3_paper << std::endl;
	imwrite("clock3_paper.raw", clock3_paper);
	paper_deblock(clock4, clock4_paper);
	PSNR_c4_paper = calc_PSNR(clock, clock4_paper);
	std::cout << "PSNR value of Clock4 after paper De-blocking is: " << PSNR_c4_paper << std::endl;
	imwrite("clock4_paper.raw", clock4_paper);
	paper_deblock(clock5, clock5_paper);
	PSNR_c5_paper = calc_PSNR(clock, clock5_paper);
	std::cout << "PSNR value of Clock5 after paper De-blocking is: " << PSNR_c5_paper << std::endl;
	imwrite("clock5_paper.raw", clock5_paper);

	paper_deblock(pepper1, pepper1_paper);
	PSNR_p1_paper = calc_PSNR(pepper, pepper1_paper);
	std::cout << "PSNR value of Pepper1 after paper De-blocking is: " << PSNR_p1_paper << std::endl;
	imwrite("pepper1_paper.raw", pepper1_paper);
	paper_deblock(pepper2, pepper2_paper);
	PSNR_p2_paper = calc_PSNR(pepper, pepper2_paper);
	std::cout << "PSNR value of Pepper2 after paper De-blocking is: " << PSNR_p2_paper << std::endl;
	imwrite("pepper2_paper.raw", pepper2_paper);
	paper_deblock(pepper3, pepper3_paper);
	PSNR_p3_paper = calc_PSNR(pepper, pepper3_paper);
	std::cout << "PSNR value of Pepper3 after paper De-blocking is: " << PSNR_p3_paper << std::endl;
	imwrite("pepper3_paper.raw", pepper3_paper);
	paper_deblock(pepper4, pepper4_paper);
	PSNR_p4_paper = calc_PSNR(pepper, pepper4_paper);
	std::cout << "PSNR value of Pepper4 after paper De-blocking is: " << PSNR_p4_paper << std::endl;
	imwrite("pepper4_paper.raw", pepper4_paper);
	paper_deblock(pepper5, pepper5_paper);
	PSNR_p5_paper = calc_PSNR(pepper, pepper5_paper);
	std::cout << "PSNR value of Pepper5 after paper De-blocking is: " << PSNR_p5_paper << std::endl;
	imwrite("pepper5_paper.raw", pepper5_paper);

	return 0;
}