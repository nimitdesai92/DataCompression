#include "all.h"

int main()
{
	std::vector <unsigned char> chem_org, house_org, moon_org, f16_org, couple_org, elaine_org;
	std::vector <float> chem_hist(256, 0), house_hist(256, 0), moon_hist(256, 0), 
						f16_hist(256, 0), couple_hist(256, 0), elaine_hist(256, 0), training_hist(256,0);
	std::vector <float> chem_hist3(256, 0), house_hist3(256, 0), moon_hist3(256, 0),
						f16_hist3(256, 0), couple_hist3(256, 0), elaine_hist3(256, 0);
	std::vector <float> chem_hist5(256, 0), house_hist5(256, 0), moon_hist5(256, 0),
						f16_hist5(256, 0), couple_hist5(256, 0), elaine_hist5(256, 0);
	std::vector <float> quantizer_3(8, 0), quantizer_5(32, 0),rep_val3,rep_val5;
	double chem_entropy3, house_entropy3, moon_entropy3, f16_entropy3, couple_entropy3, elaine_entropy3;
	double chem_entropy5, house_entropy5, moon_entropy5, f16_entropy5, couple_entropy5, elaine_entropy5;
	std::vector <float> chem_quant3, house_quant3, moon_quant3, f16_quant3, couple_quant3, elaine_quant3;
	std::vector <float> chem_quant5, house_quant5, moon_quant5, f16_quant5, couple_quant5, elaine_quant5;

	std::vector <unsigned char> chem_vector2, house_vector2, moon_vector2, f16_vector2, couple_vector2, elaine_vector2;
	std::vector <unsigned char> chem_vector4, house_vector4, moon_vector4, f16_vector4, couple_vector4, elaine_vector4;
	std::vector <unsigned char> chem_vector8, house_vector8, moon_vector8, f16_vector8, couple_vector8, elaine_vector8;

	std::vector <unsigned char> train_vector2, train_vector4, train_vector8;

	// Training Set Calculation
	chem_org = fileread("chem.256");
	calchist(chem_org, chem_hist);
	plothist(chem_hist,"chem.256_hist.txt");
	calc_cdf(chem_hist);

	house_org = fileread("house.256");
	calchist(house_org, house_hist);
	plothist(house_hist, "house.256_hist.txt");
	calc_cdf(house_hist);

	moon_org = fileread("moon.256");
	calchist(moon_org, moon_hist);
	plothist(moon_hist, "moon.256_hist.txt");
	calc_cdf(moon_hist);

	// Constructing the Code Book
	training_hist = sum_hist(chem_hist, house_hist, moon_hist);
	scalar_quantizer(quantizer_3, training_hist, rep_val3);
	scalar_quantizer(quantizer_5, training_hist, rep_val5);

	// Testing Set Calculation
	f16_org = fileread("f16.256");
	calchist(f16_org, f16_hist);
	plothist(f16_hist, "f16.256_hist.txt");

	couple_org = fileread("couple.256");
	calchist(couple_org, couple_hist);
	plothist(couple_hist, "couple.256_hist.txt");

	elaine_org = fileread("elaine.256");
	calchist(elaine_org, elaine_hist);
	plothist(elaine_hist, "elaine.256_hist.txt");

	// Compression Stage
	quantized(chem_org, chem_quant3, quantizer_3, rep_val3);
	quantized(chem_org, chem_quant5, quantizer_5, rep_val5);

	quantized(house_org, house_quant3, quantizer_3, rep_val3);
	quantized(house_org, house_quant5, quantizer_5, rep_val5);

	quantized(moon_org, moon_quant3, quantizer_3, rep_val3);
	quantized(moon_org, moon_quant5, quantizer_5, rep_val5);

	quantized(f16_org, f16_quant3, quantizer_3, rep_val3);
	quantized(f16_org, f16_quant5, quantizer_5, rep_val5);

	quantized(couple_org, couple_quant3, quantizer_3, rep_val3);
	quantized(couple_org, couple_quant5, quantizer_5, rep_val5);

	quantized(elaine_org, elaine_quant3, quantizer_3, rep_val3);
	quantized(elaine_org, elaine_quant5, quantizer_5, rep_val5);

	// Output Histogram from 3 bit and 5 bit Compressed files.
	calchist_float(chem_quant3, chem_hist3);
	plothist(chem_hist3, "chem.256_hist3.txt");
	chem_entropy3 = calc_entropy(chem_hist3);
	std::cout << "Entropy for 3 bit quantized Chem: " << chem_entropy3 << std::endl;

	calchist_float(chem_quant5, chem_hist5);
	plothist(chem_hist5, "chem.256_hist5.txt");
	chem_entropy5 = calc_entropy(chem_hist5);
	std::cout << "Entropy for 5 bit quantized Chem: " << chem_entropy5 << std::endl;


	calchist_float(house_quant3, house_hist3);
	plothist(house_hist3, "house.256_hist3.txt");
	house_entropy3 = calc_entropy(house_hist3);
	std::cout << "Entropy for 3 bit quantized house: " << house_entropy3 << std::endl;

	calchist_float(house_quant5, house_hist5);
	plothist(house_hist5, "house.256_hist5.txt");
	house_entropy5 = calc_entropy(house_hist5);
	std::cout << "Entropy for 5 bit quantized house: " << house_entropy5 << std::endl;


	calchist_float(moon_quant3, moon_hist3);
	plothist(moon_hist3, "moon.256_hist3.txt");
	moon_entropy3 = calc_entropy(moon_hist3);
	std::cout << "Entropy for 3 bit quantized moon: " << moon_entropy3 << std::endl;

	calchist_float(moon_quant5, moon_hist5);
	plothist(moon_hist5, "moon.256_hist5.txt");
	moon_entropy5 = calc_entropy(moon_hist5);
	std::cout << "Entropy for 5 bit quantized moon: " << moon_entropy5 << std::endl;


	calchist_float(f16_quant3, f16_hist3);
	plothist(f16_hist3, "f16.256_hist3.txt");
	f16_entropy3 = calc_entropy(f16_hist3);
	std::cout << "Entropy for 3 bit quantized f16: " << f16_entropy3 << std::endl;

	calchist_float(f16_quant5, f16_hist5);
	plothist(f16_hist5, "f16.256_hist5.txt");
	f16_entropy5 = calc_entropy(f16_hist5);
	std::cout << "Entropy for 5 bit quantized f16: " << f16_entropy5 << std::endl;


	calchist_float(couple_quant3, couple_hist3);
	plothist(couple_hist3, "couple.256_hist3.txt");
	couple_entropy3 = calc_entropy(couple_hist3);
	std::cout << "Entropy for 3 bit quantized couple: " << couple_entropy3 << std::endl;

	calchist_float(couple_quant5, couple_hist5);
	plothist(couple_hist5, "couple.256_hist5.txt");
	couple_entropy5 = calc_entropy(couple_hist5);
	std::cout << "Entropy for 5 bit quantized couple: " << couple_entropy5 << std::endl;


	calchist_float(elaine_quant3, elaine_hist3);
	plothist(elaine_hist3, "elaine.256_hist3.txt");
	elaine_entropy3 = calc_entropy(elaine_hist3);
	std::cout << "Entropy for 3 bit quantized elaine: " << elaine_entropy3 << std::endl;

	calchist_float(elaine_quant5, elaine_hist5);
	plothist(elaine_hist5, "elaine.256_hist5.txt");
	elaine_entropy5 = calc_entropy(elaine_hist5);
	std::cout << "Entropy for 5 bit quantized elaine: " << elaine_entropy5 << std::endl;

	//Block of Vectors
	block(chem_org, chem_vector2, 2);
	filewrite(chem_vector2, "chem_vector2.256");
	block(chem_org, chem_vector4, 4);
	filewrite(chem_vector4, "chem_vector4.256");
	block(chem_org, chem_vector8, 8);
	filewrite(chem_vector8, "chem_vector8.256");

	block(house_org, house_vector2, 2);
	filewrite(house_vector2, "house_vector2.256");
	block(house_org, house_vector4, 4);
	filewrite(house_vector4, "house_vector4.256");
	block(house_org, house_vector8, 8);
	filewrite(house_vector8, "house_vector8.256");

	block(moon_org, moon_vector2, 2);
	filewrite(moon_vector2, "moon_vector2.256");
	block(moon_org, moon_vector4, 4);
	filewrite(moon_vector4, "moon_vector4.256");
	block(moon_org, moon_vector8, 8);
	filewrite(moon_vector8, "moon_vector8.256");

	add_train(chem_vector2, house_vector2, moon_vector2, train_vector2);
	filewrite(train_vector2, "train_vector2");
	add_train(chem_vector4, house_vector4, moon_vector4, train_vector4);
	filewrite(train_vector4, "train_vector4");
	add_train(chem_vector8, house_vector8, moon_vector8, train_vector8);
	filewrite(train_vector8, "train_vector8");

	return 0;
}