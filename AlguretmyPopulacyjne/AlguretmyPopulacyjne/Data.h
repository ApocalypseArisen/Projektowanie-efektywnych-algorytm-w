#pragma once
#ifndef Data_hpp
#define Data_hpp

#include "Counter.h"

using namespace std;

//Klasa przechowująca i obługująca wygenerowane dane
class Data
{
protected:
	//Atrybuty
	Counter count;
	bool exists = false;
	int **tab;
	int ext;
	const static int limit = 1000;
	int limits;
	double **results = nullptr;
public:
	//Metody
	string load(string filename);
	void randomify(int size, bool mirror);
	void manual(int size, bool mirror);
	void display();
	//Testowanie
	void dispaly_results(bool pop[], bool sizes[], int size);
	void save(bool pop[], bool sizes[], int size, string filename);
protected:
	int counttarget();
};

#endif