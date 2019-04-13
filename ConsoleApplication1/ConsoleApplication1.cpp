// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>


#define NB_DIGITS 10000

using namespace std;

int main()
{
	cout << "Loading " << NB_DIGITS << " digits" << endl;

	srand(time(NULL));
	ifstream labels_f;
	labels_f.open("train_labels.txt");

	int labels[NB_DIGITS];
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
					char a; cin >> a;
					exit(-1);
				}
			}
		}
	}

	for (unsigned i = 0; i < NB_DIGITS; i++)
	{
		labels_f >> labels[i];
	}
	labels_f.close();


	ifstream images_f;
	images_f.open("train_images.txt");

	Digit *images = new Digit[NB_DIGITS];
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
					exit(-1);
			}
		}
	}

	for (unsigned i = 0; i < NB_DIGITS; i++)
	{
		images[i].setLabel(labels[i]);
		double* numbers = images[i].getPixels();
		for (unsigned j = 0; j < 28; j++)
		{
			string line;
			getline(images_f, line);
			/*if (i == 785)
				cout << line << endl;*/
			line = line.substr(2, 111);
			//cout << line << endl;
			for (unsigned k = 0; k < 28; k++)
			{
				//cout << /*"'" << line.substr(0, 3) << "'=" <<*/ stoi(line.substr(0, 3));
				numbers[j * 28 + k] = stoi(line.substr(0, 3)) / 255.;
				//cout << "=" << numbers[j * 28 + k] << "  ";
				if (k == 27)
					break;
				line = line.substr(4);
			}
			//cout << endl;
		}
		images[i].createmPixels();
	}
	images_f.close();

	//cout << images[785].getLabel() << endl;
	//cout << images[785].getPixels()[77] << endl;
	AG(64, 100).evolve(images, NB_DIGITS);
	char a; cin >> a;

	/*Matrix m(4, 2);
	m.set(0, 0, 42);
	m.set(1, 0, 2);
	m.set(2, 0, 3);
	m.set(3, 0, 4);
	m.set(0, 1, 5);
	m.set(1, 1, 6);
	m.set(2, 1, 7);
	m.set(3, 1, 8);


	Matrix n(3, 4);
	n.set(0, 0, 1337);
	n.set(1, 0, 2);
	n.set(2, 0, 3);
	n.set(0, 1, 4);
	n.set(1, 1, 5);
	n.set(2, 1, 6);
	n.set(0, 2, 7);
	n.set(1, 2, 8);
	n.set(2, 2, 9);
	n.set(0, 3, 10);
	n.set(1, 3, 11);
	n.set(2, 3, 12);

	while (true)
	{
		m*n;
	}

	cout << n << endl;
	m = Matrix(n);

	cout << m << endl;// << n;// << endl << p;*/
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
