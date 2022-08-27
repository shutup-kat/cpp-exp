//	katelynn (kat) hernandez 
//		葵花
//
//	
#include <iostream>
#include <fstream>
#include <vector>
#include "ArgumentManager.h"
using namespace std;

void lemme_see(int d[], int cris, int source, int end, ofstream & OUTF)
{
	for(int c=1; c<cris+1; c++)
		{
			if(c == end)
				{
					cout << d[c];
					OUTF << d[c] << endl;
				}
		}
}


int min_dist(int dist[], bool trace[], int size)
{
	int min = 999999, min_index;
	for(int v=1; v<size+1; v++)
		{
			if(trace[v] == false && dist[v] <= min)
				{
					min = dist[v];
					min_index = v;
				}
		}
	return min_index;
}

void dijkastra(int g [10][10], int source, int size, int d, ofstream& OUTF)
{
	int dist[size];
	bool trace[size];
	
	for(int k=0; k<size; k++)
		{//for loop initilaizes both arrays so not empty.
			dist[k] = 999999;
			trace[k] = false;
		}
	dist[source] = 0; // source->starting index, distance from self = 0
	
	for(int a=1; a <size+1; a++)
		{
			int amor = min_dist(dist, trace, size);
			trace[amor] = true;
			for(int t=1; t<size+1; t++)
				{
					if(!trace[t] && g[amor][t] && dist[amor] != 999999)
						{
							if(dist[amor] + g[amor][t] < dist[t])
								{ dist[t] = dist[amor] + g[amor][t];  }
						}
				}
		}
	//print statment
	lemme_see(dist, size, source, d, OUTF);
}


int main(int argc, char * argv[]) {
/*
	string infilename = "input3.txt", outfilename;
	ifstream INF(infilename);
	ofstream OUTF;
*/
	
	ArgumentManager am(argc, argv);
	string infile = am.get("input"), outfile = am.get("output");
	ifstream INF (infile);
	ofstream OUTF (outfile);
	
	
	int ver_total=0, edg_total=0, source=0, desti=0;
	int one, two, weight;
	int test =0;
	
	int adjmatrix[10][10];
	for(int col=0; col<10; col++)
		{
			for(int row=0; row<10; row++)
				{ adjmatrix[col][row] = 0;  }
		}
	
	
	INF >> ver_total; //total num of verticies
	INF >> edg_total; //total num of edges
	INF >> source; //start 
	INF >> desti; //destination
	
	while(!INF.eof())
		{
			INF >> one;
			INF >> two;
			INF >> weight;
			cout << "ONE: " << one << " TWO: " << two << " WEIGHT: " << weight << endl;
			if(adjmatrix[one][two] == 0 && adjmatrix[two][one] == 0)
				{ //undirected graph
					adjmatrix[one][two] = weight;
					adjmatrix[two][one] = weight;
					test +=1;
				}
			
		}
	
	
	dijkastra(adjmatrix, source, ver_total, desti, OUTF);
	
	
	cout << "\n\n你好，世界！\n";
}