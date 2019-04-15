// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
//#include <cuda_runtime.h>

#define RST	"\x1B[0m"
#define RED	"\x1B[31m"
#define GRN	"\x1B[32m"
#define YEL	"\x1B[33m"
#define BLU	"\x1B[34m"
#define CONS_COLOR(X) (no_color ? "" : X)

#define CURS_POS(X, Y) "\033["#Y";"#X"H"

using namespace std;

int main(int argc, char** argv)
{
	bool no_color = false;
	int nbDigits = 1000;
	int maxGen = 100;
	int popSize = 16;
	char imagePath[256] = "train_images.txt";
	char labelPath[256] = "train_labels.txt";
	
	{
		ArgsParser parser(7);

		Option color_onOpt{ "-n", "--no-color", "No color output (use this option if things like \"\\x1B[31m\" appear in the output)", 0, nullptr, &no_color };
		parser.add(color_onOpt);

		OptionArg* nbDigitsArgs = new OptionArg[1]; nbDigitsArgs[0].name = "nb"; nbDigitsArgs[0].type = intArg; nbDigitsArgs[0].min = 1; nbDigitsArgs[0].varPtr = &nbDigits;
		Option nbDigitsOpt{ "-d", "--nb-digits", "Use <nb> digits images for the training (default = 1000)", 1, nbDigitsArgs, nullptr };
		parser.add(nbDigitsOpt);

		OptionArg* maxGenArgs = new OptionArg[1]; maxGenArgs[0].name = "gen"; maxGenArgs[0].type = intArg; maxGenArgs[0].min = 0; maxGenArgs[0].varPtr = &maxGen;
		Option maxGenOpt{ "-m", "--max-gen", "Set the number of maximum generations to <gen> (use 0 for infinite) (default = 100)", 1, maxGenArgs, nullptr };
		parser.add(maxGenOpt);

		OptionArg* popSizeArgs = new OptionArg[1]; popSizeArgs[0].name = "size"; popSizeArgs[0].type = intArg; popSizeArgs[0].min = 1; popSizeArgs[0].varPtr = &popSize;
		Option popSizeOpt{ "-p", "--pop-size", "Set the population size to <size> (should be strictly positive) (default = 16)", 1, popSizeArgs, nullptr };
		parser.add(popSizeOpt);

		OptionArg* imagePathArgs = new OptionArg[1]; imagePathArgs[0].name = "file"; imagePathArgs[0].type = stringArg; imagePathArgs[0].varPtr = &imagePath;
		Option imagePathOpt{ "-i", "--images", "Path to the images file (default = \"train_images.txt\")", 1, imagePathArgs, nullptr };
		parser.add(imagePathOpt);

		OptionArg* labelPathArgs = new OptionArg[1]; labelPathArgs[0].name = "file"; labelPathArgs[0].type = stringArg; labelPathArgs[0].varPtr = &labelPath;
		Option labelPathOpt{ "-l", "--labels", "Path to the labels file (default = \"train_labels.txt\")", 1, labelPathArgs, nullptr };
		parser.add(labelPathOpt);

		bool help = false;
		Option helpOpt{ "-h", "--help", "Display this help and exit", 0, nullptr, &help };
		parser.add(helpOpt);


		try
		{
			parser.execute(argc, argv);
		}
		catch (exception const &e)
		{
			cout << CONS_COLOR(RED) << e.what() << CONS_COLOR(RST) << endl;
			exit(-1);
		}

		if (help)
		{
			char** text = new char*;
			int helpSize = parser.help(text);
			for (size_t i = 0; i < helpSize; i++)
			{
				cout << text[i] << endl;
			}

			exit(0);
		}

		delete nbDigitsArgs;
		delete maxGenArgs;
		delete popSizeArgs;
		delete imagePathArgs;
		delete labelPathArgs;
	}

	srand(static_cast<int>(time(NULL)));

	cout << "Loading " << nbDigits << " digits" << endl;
	ifstream labels_f;
	labels_f.open(labelPath);

	int *labels = new int[nbDigits];
	if (!labels_f.is_open())
	{
		labels_f.open("..\\ConsoleApplication1\\train_labels.txt");
		if (!labels_f.is_open())
		{
			labels_f.open("..\\..\\ConsoleApplication1\\train_labels.txt");
			if (!labels_f.is_open())
			{
				labels_f.open("..\\..\\train_labels.txt");
				if (!labels_f.is_open())
				{
					cout << "Wrong path" << endl;
					exit(-1);
				}
			}
		}
	}

	for (size_t i = 0; i < nbDigits; i++)
	{
		labels_f >> labels[i];
	}
	labels_f.close();


	ifstream images_f;
	images_f.open(imagePath);

	Digit *images = new Digit[nbDigits];
	if (!images_f.is_open())
	{
		images_f.open("..\\ConsoleApplication1\\train_images.txt");
		if (!images_f.is_open())
		{
			images_f.open("..\\..\\ConsoleApplication1\\train_images.txt");
			if (!images_f.is_open())
			{
				images_f.open("..\\train_images.txt");
				if (!images_f.is_open())
				{
					cout << "Wrong path" << endl;
					exit(-1);
				}
			}
		}
	}

	unsigned dots = 0;
	for (size_t i = 0; i < nbDigits; i++)
	{
		images[i].setLabel(labels[i]);
		double* numbers = images[i].getPixels();
		for (unsigned j = 0; j < 28; j++)
		{
			string line;
			getline(images_f, line);
			line = line.substr(2, 111);
			
			for (unsigned k = 0; k < 28; k++)
			{
				numbers[j * 28 + k] = stoi(line.substr(0, 3)) / 255.;
				if (k == 27)
					break;
				line = line.substr(4);
			}
		}
		while (i * 100 / nbDigits > dots)
		{
			cout << ".";
			dots++;
		}
		images[i].createmPixels();
	}
	cout << endl;
	images_f.close();
	delete labels;

	AG(popSize, (maxGen == 0 ? UINTMAX_MAX : maxGen), no_color).evolve(images, nbDigits);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
