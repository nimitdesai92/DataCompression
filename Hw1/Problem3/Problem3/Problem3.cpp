#include "all.h"

int main()
{
	std::vector <unsigned char> audio , text , binaryImg , grayImg;
	std::vector <unsigned char> audio_basicRLE, text_basicRLE, binaryImg_basicRLE, grayImg_basicRLE;
	std::vector <unsigned char> audio_basicRLEDecode, text_basicRLEDecode, binaryImg_basicRLEDecode, grayImg_basicRLEDecode;
	std::vector <unsigned char> audio_modifiedRLE, text_modifiedRLE, binaryImg_modifiedRLE, grayImg_modifiedRLE;
	std::vector <unsigned char> audio_modifiedRLEDecode, text_modifiedRLEDecode, binaryImg_modifiedRLEDecode, grayImg_modifiedRLEDecode;
	std::vector <unsigned char> audio_MTF, text_MTF, binaryImg_MTF, grayImg_MTF;
	std::vector <unsigned char> audio_MTFDecode, text_MTFDecode, binaryImg_MTFDecode, grayImg_MTFDecode;

	std::cout << "Audio File Data" << std::endl << std::endl;
	audio = fileread("audio.dat");
	audio_basicRLE = BasicRLE(audio);
	filewrite("audio_basicRLE.dat", audio_basicRLE);
	audio_basicRLEDecode = BasicRLE_decoder(audio_basicRLE);
	filewrite("audio_basicRLEDecoded.dat", audio_basicRLEDecode);
	audio_modifiedRLE = ModifiedRLE(audio);
	filewrite("audio_modifiedRLE.dat", audio_modifiedRLE);
	audio_modifiedRLEDecode = modifiedRLE_decoder(audio_modifiedRLE);
	filewrite("audio_modifiedRLEDecoded.dat", audio_modifiedRLEDecode);
	audio_MTF = MTF(audio);
	filewrite("audio_MTF.dat", audio_MTF);
	adap_huffman(audio_MTF, "audio_adaptiveMTF.dat");
	audio_MTFDecode = MTFdecoder(audio_MTF);
	filewrite("audio_MTFDecoded.dat", audio_MTFDecode);


	std::cout << "Text File Data" << std::endl << std::endl;
	text = fileread("text.dat");
	text_basicRLE = BasicRLE(text);
	filewrite("text_basicRLE.dat", text_basicRLE);
	text_basicRLEDecode = BasicRLE_decoder(text_basicRLE);
	filewrite("text_basicRLEDecoded.dat", text_basicRLEDecode);
	text_modifiedRLE = ModifiedRLE(text);
	filewrite("text_modifiedRLE.dat", text_modifiedRLE);
	text_modifiedRLEDecode = modifiedRLE_decoder(text_modifiedRLE);
	filewrite("text_modifiedRLEDecoded.dat", text_modifiedRLEDecode);
	text_MTF = MTF(text);
	filewrite("text_MTF.dat", text_MTF);
	adap_huffman(text_MTF, "text_adaptiveMTF.dat");
	text_MTFDecode = MTFdecoder(text_MTF);
	filewrite("text_MTFDecoded.dat", text_MTFDecode);

	std::cout << "Binary Image File Data" << std::endl << std::endl;
	binaryImg = fileread("binary.dat.raw");
	binaryImg_basicRLE = BasicRLE(binaryImg);
	filewrite("binaryImg_basicRLE.dat.raw", binaryImg_basicRLE);
	binaryImg_basicRLEDecode = BasicRLE_decoder(binaryImg_basicRLE);
	filewrite("binaryImg_basicRLEDecoded.dat.raw", binaryImg_basicRLEDecode);
	binaryImg_modifiedRLE = ModifiedRLE(binaryImg);
	filewrite("binaryImg_modifiedRLE.dat.raw", binaryImg_modifiedRLE);
	binaryImg_modifiedRLEDecode = modifiedRLE_decoder(binaryImg_modifiedRLE);
	filewrite("binaryImg_modifiedRLEDecoded.dat.raw", binaryImg_modifiedRLEDecode);
	binaryImg_MTF = MTF(binaryImg);
	filewrite("binaryImg_MTF.dat.raw", binaryImg_MTF);
	adap_huffman(binaryImg_MTF, "binaryImg_adaptiveMTF.dat.raw");
	binaryImg_MTFDecode = MTFdecoder(binaryImg_MTF);
	filewrite("binaryImg_MTFDecoded.dat.raw", binaryImg_MTFDecode);


	std::cout << "Grayscale Image Data" << std::endl << std::endl;
	grayImg = fileread("image.dat.raw");
	grayImg_basicRLE = BasicRLE(grayImg);
	filewrite("image_basicRLE.dat.raw", grayImg_basicRLE);
	grayImg_basicRLEDecode = BasicRLE_decoder(grayImg_basicRLE);
	filewrite("image_basicRLEDecoded.dat.raw", grayImg_basicRLEDecode);
	grayImg_modifiedRLE = ModifiedRLE(grayImg);
	filewrite("image_modifiedRLE.dat.raw", grayImg_modifiedRLE);
	grayImg_modifiedRLEDecode = modifiedRLE_decoder(grayImg_modifiedRLE);
	filewrite("image_modifiedRLEDecoded.dat.raw", grayImg_modifiedRLEDecode);
	grayImg_MTF = MTF(grayImg);
	filewrite("grayImg_MTF.dat.raw", grayImg_MTF);
	adap_huffman(grayImg_MTF, "grayImg_adaptiveMTF.dat.raw");
	grayImg_MTFDecode = MTFdecoder(grayImg_MTF);
	filewrite("grayImg_MTFDecoded.dat.raw", grayImg_MTFDecode);

	return 0;
}