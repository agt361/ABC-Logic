#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
using namespace std::chrono;

#define Puz1   { "BCA--", "BCBCA", "AB--B", "---AB" }
#define Puz2   { "B-C-B", "ABA-C", "BCCA-", "-B-B-" }
#define Puz3   { "-A---", "C-ABB", "-ACA-", "BCB-A" }

struct PuzzleBoard {
	std::string Shape;
	PuzzleBoard(std::string init1) {
		Shape = init1;
	}
	PuzzleBoard() : Shape( 49, ' ' ) {}

	PuzzleBoard(std::string Edges[4]) : PuzzleBoard() {
		for (int i = 0; i < 5; i++) {
			at(0, i + 1) = Edges[0][i];
			at(i + 1, 0) = Edges[1][i];
			at(i + 1, 6) = Edges[2][i];
			at(6, i + 1) = Edges[3][i];
		}
	}

	char& operator()(int i, int j) {
		return Shape[i * 7 + j];
	}
	char& at(int i, int j) {
		return Shape[i * 7 + j];
	}
};

int ProcessPuzzle();
void PrintBoard(PuzzleBoard PzB, std::ostream& Stream);
void PrintCentreBoard(PuzzleBoard PzB, std::ostream& Stream);
void LoseDsBoard(PuzzleBoard &PzB);
int TestEntryLegal(int c, int i, int j);
