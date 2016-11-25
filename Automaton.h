#pragma once
#include<fstream>
#include<iostream>
#include<string>

#ifndef AUTOMATON_H
#define AUTOMATON_H

class Automaton
{
private:
	int number;
	int start;
	int matrix[100][26];
	int *endStates;
	int numEndStates;
public:
	Automaton();
	Automaton(int, int, int[100][26], int*, int );
	Automaton(const Automaton& other);
	Automaton& operator=(const Automaton& other);
	void saveAutomaton(std::ofstream& out)const;
	void readAutomaton(std::ifstream& in);
	void print() const;
	bool checkWord(char*,std::ofstream& out);
	~Automaton();
};

#endif
