#include "Automaton.h"

Automaton::Automaton() {
	number = 0;
	start = 0;
	numEndStates = 0;
	endStates = new int[0];
}
Automaton::Automaton(int num, int st, int mx[100][26], int*end, int n) {
	number = num;
	start = st;
	numEndStates = n;
	endStates = new int[numEndStates];
	for (int i = 0; i < numEndStates; i++) {
		endStates[i] = end[i];
	}
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < 26; j++) {
			matrix[i][j] = mx[i][j];
		}
	}
}
Automaton::Automaton(const Automaton& other) {
	number = other.number;
	start = other.start;
	numEndStates = other.numEndStates;
	endStates = new int[numEndStates];
	for (int i = 0; i < numEndStates; i++) {
		endStates[i] = other.endStates[i];
	}
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < 26; j++) {
			matrix[i][j] = other.matrix[i][j];
		}
	}
}

Automaton&::Automaton:: operator=(const Automaton& other) {
	if (this != &other) {
		delete[]endStates;
		number = other.number;
		start = other.start;
		numEndStates = other.numEndStates;
		endStates = new int[numEndStates];
		for (int i = 0; i < numEndStates; i++) {
			endStates[i] = other.endStates[i];
		}
		for (int i = 0; i < number; i++) {
			for (int j = 0; j < 26; j++) {
				matrix[i][j] = other.matrix[i][j];
			}
		}
	}
	return *this;
}
void Automaton::saveAutomaton(std::ofstream& out)const {
	out << number << std::endl; //put number of the states
	out << start << std::endl; //put the start state
	out << numEndStates << std::endl; //put number of end states
	out << "[";
	for (int i = 0; i < numEndStates; i++) {
		out << endStates[i]; // put end states
		if (i != numEndStates - 1) {
			out << ",";
		}
	}
	out << "]" << std::endl;
	// put the whole matrix
	out << "[-](";
	for (int i = 0; i < 26; i++) {
		out << char(97 + i);
		if (i != 25) {
			out << ",";
		}
	}
	out << ")" << std::endl;
	for (int i = 0; i < number; i++) {
		out << "(" << i << ")";
		out << "[";
		for (int j = 0; j < 26; j++) {
			out << matrix[i][j];
			if (j != 25) {
				out << ",";
			}
		}
		out << "]" << std::endl;
	}
	std::cout << "Successfully writen..!" << std::endl;
	out.close();
}

void Automaton::readAutomaton(std::ifstream& in) {
	in >> number; // get the number of states
	in >> start; // get the start state
	in >> numEndStates; // get the number of end states
	char tempChar;
	in >> tempChar;
	int index = 0;
	endStates = new int[numEndStates];
	while (tempChar != ']') {
		in >> endStates[index];
		index++;
		in >> tempChar;
	}
	while (tempChar != ')') {
		in >> tempChar;
	}
	int j = 0;
	int tempInt;
	for (int i = 0; i < number; i++) {
		in >> tempChar;
		in >> tempInt;
		in >> tempChar;
		in >> tempChar;
		while (tempChar != ']') {
			in >> matrix[i][j];
			j++;
			in >> tempChar;
		}
		j = 0;
	}
	std::cout << "Successfully read..!" << std::endl;
	in.close();
}
void Automaton::print() const {

	for (int i = 0; i < number; i++) {
		for (int j = 0; j < 26; j++) {
			std::cout << matrix[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}
bool Automaton::checkWord(char*word, std::ofstream& out) {
	bool canContinue = false;
	int get = 0;
	int index = 0;
	int tempState = start;
	out << "digraph{" << std::endl;
	while (get != (strlen(word) + 1)) {
		if (get == strlen(word)) {
			for (int i = 0; i < numEndStates; i++) {
				if (tempState == endStates[i]) {
					std::cout << "F";
					std::cout << std::endl;
					std::cout << "The word: " << word << " is accepted by the automaton..!" << std::endl;
					out << "}";
					out.close();
					return true;
				}
			}
			std::cout << "Could not accept the word.." << std::endl;
			out << "}";
			out.close();
			return false;
		}
		std::cout << tempState << "->";

		out << tempState << "->";
		for (int i = 0; i < 26; i++) {
			//std::cout << 97+i << " " <<int(word[index]) << "----" << std::endl;
			if ((97 + i) == int(word[index])) {
				if (matrix[tempState][i] != -1) {
					out << matrix[tempState][i] << ";" << std::endl;
					std::cout << matrix[tempState][i] << "->";
					tempState = matrix[tempState][i];
					index++;
					canContinue = true;
					get++;
					break;
				}
			}
		}
		if (!canContinue) {
			return false;
		}
		canContinue = false;
	}
}

Automaton::~Automaton() {
	delete[]endStates;
}