//Klasa obs�uguj�ca obliczanie problemu komiwoja�era za pomoc� brute-force
#include "pch.h"
#include "Solutions.h"
using namespace std;

//Destruktor
Solutions::~Solutions()
{
	if (exists) delete[] tab;
}

//Rekurencyjne przeszukiwanie drzewa
void Solutions::rectree(int line, vector<bool> visited, int  distance, int layer)
{
	visited[line] = true;
	if (layer != (ext-1))
	{
		for (int i = 1; i < ext; i++)
		{
			if(!visited[i]) rectree(i, visited, (distance + tab[line][i]), (layer + 1));
		}
	}
	else if ((distance + tab[line][0]) < max || max == -1)
	{
		max = distance + tab[line][0];
	}
	return;
}

//Rekurencyjne przeszukiwanie drzewa z dodatkow� optymalizacj�
void Solutions::rectree_opt(int line, vector<bool> visited, int  distance, int layer)
{
	visited[line] = true;
	if (distance > max && max != -1) return;
	if (layer != (ext - 1))
	{
		for (int i = 1; i < ext; i++)
		{
			if (!visited[i]) rectree_opt(i, visited, (distance + tab[line][i]), (layer + 1));
		}
	}
	else if ((distance + tab[line][0]) < max || max == -1)
	{
		max = distance + tab[line][0];
	}
	return;
}

//Funkcja przeszukuj�ca drzewo w poszukiwaniu najlepszych rozwi�za�
void Solutions::searchtree()
{
	max = -1;
	vector<bool> visited(ext);
	visited[0] = true;
	for (int i = 1; i < ext; i++) visited[i] = false;
	for (int i = 0; i < (ext - 1); i++)
	{
		rectree((i + 1), visited, tab[0][i + 1], 1);
	}
}
void Solutions::seacrhtree_opt()
{
	max = -1;
	vector<bool> visited(ext);
	visited[0] = true;
	for (int i = 1; i < ext; i++) visited[i] = false;
	for (int i = 0; i < (ext - 1); i++)
	{
		rectree_opt((i + 1), visited, tab[0][i + 1], 1);
	}
}

//Pocz�tek Branch & Bound
void Solutions::BiBbegin()
{
	max = -1;
	Node *first = new Node(tab, ext, (ext - 1));
	nlist.push_back(first);
	first->weight = minimize(first->data);
	vector<Node*> nodes;
	for (int i = 0; i < (ext - 1); i++)
	{
		nodes.push_back(new Node(first->data, ext, (first->rem - 1)));
		nodes[i]->parent = first;
		nodes[i]->weight = calculatecost(nodes[i], 0, (i + 1));
		nlist.push_back(nodes[i]);
	}

	/*for (int z = 0; z < (ext - 1); z++)
	{
		system("cls");
		cout << nodes.size();
		_getche();
		for (int i = 0; i < ext; i++)
		{
			cout << " ";
			for (int j = 0; j < ext; j++)
			{
				cout << nodes[z]->data[i][j] << " ";
			}
			cout << endl;
		}
		cout << nodes[z]->weight;
		_getche();
	}*/
}

//G��wna p�tla dla Branch & Bound
void Solutions::BiBcalc(vector<Node*> nodes)
{

}

//Funkcja obliczaj�ca kost nast�pnego poziomu
int Solutions::calculatecost(Node *node, int from, int to)
{
	int result = node->data[from][to] + node->parent->weight;
	for (int i = 0; i < ext; i++)
	{
		node->data[from][i] = -1;
		node->data[i][to] = -1;
	}
	node->data[to][from] = -1;
	result = result + minimize(node->data);
	return result;
}

//Funkcja minimalizuj�ca macierz
int Solutions::minimize(int **data)
{
	int result = 0;
	for (int i = 0; i < ext; i++)
	{
		int small = data[i][0];
		if (small == -1) small = data[i][1];
		for (int j = 0; j < ext; j++)
		{
			if (data[i][j] < small && data[i][j] != -1) small = data[i][j];
		}
		if (small != 0)
		{
			for (int j = 0; j < ext; j++)
			{
				if (data[i][j] != -1) data[i][j] = data[i][j] - small;
			}
			result = result + small;
		}
	}
	for (int i = 0; i < ext; i++)
	{
		int small = data[0][i];
		if (small == -1) small = data[1][i];
		for (int j = 0; j < ext; j++)
		{
			if (data[j][i] < small && data[j][i] != -1) small = data[j][i];
		}
		if (small != 0)
		{
			for (int j = 0; j < ext; j++)
			{
				if (data[j][i] != -1)data[j][i] = data[j][i] - small;
			}
			result = result + small;
		}
	}
	return result;
}

//Gettery i Settery
int Solutions::getDistance() { return max; }