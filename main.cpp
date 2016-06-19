#include<iostream>

#include"Automaton.h"

using namespace std;

int main() { 
	//-1 if not found
	int matrix[4][26] = { { -1,3,0,1,2,3,-1,1,1,2,-1,1,3,0,-1,2,0,-1,3,2,0,-1,-1,-1,3,-1 }
						 ,{ -1,-1,0,-1,-1,-1,2,-1,-1,0,1,1,3,-1,-1,1,-1,-1,-1,0,1,3,-1,0,3,-1 }
						 ,{ 1,3,1,-1,-1,-1,0,-1,-1,0,2,-1,-1,-1,0,-1,3,-1,0,-1,0,-1,3,-1,-1,-1 }
						 ,{ -1,1,0,-1,1,-1,-1,1,2,-1,2,-1,-1,3,2,-1,-1,-1,-1,3,-1,2,-1,0,-1,-1 } };
	int end[2] = { 1,2 };
	Automaton aut(4, 0, matrix, end, 2);
	ofstream file("Automaton.txt");
	aut.saveAutomaton(file);
//	aut.print();
	Automaton readAut;
	ifstream file2("Automaton.txt");
	readAut.readAutomaton(file2);
//	readAut.print();
	ofstream file3("Automaton2.txt");
	readAut.saveAutomaton(file3);

	ofstream file4("Graph.dot");
	aut.checkWord("jacjacjacjacj",file4); // works fine
	system("pause");
	return 0;
}