#pragma once
#ifndef BruteForce_hpp
#define BruteForce_hpp

#include "Data.h"

//Klasa obsługująca obliczanie problemu komiwojażera za pomocą brute-force
class BruteForce : public Data
{
private:
	//zmienne
	int max;
public:
	//metody
	~BruteForce();
	void searchtree();
	void rectree(int line, vector<bool> visted, int distance, int layer);
	//Gettery i settery
	int getDistance();
};

#endif
