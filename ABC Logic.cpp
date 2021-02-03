// ABC Logic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Header.h"

std::string Edges[4] = Puz3;

PuzzleBoard Puzzle(Edges);

std::ofstream myfile;

int Tot = 0;

int main() {
    
    myfile.open("example.txt");
    myfile << "ABC Logic \n\n";
    std::cout << "ABC Logic \n\n";
    PrintBoard(Puzzle, std::cout);
    PrintBoard(Puzzle, myfile);

    ProcessPuzzle();

    PrintBoard(Puzzle, std::cout);

    LoseDsBoard(Puzzle);

    PrintBoard(Puzzle, std::cout);
    PrintCentreBoard(Puzzle, std::cout);
    PrintCentreBoard(Puzzle, myfile);

    std::cout << Tot << "\n\n";
    myfile.close();
}

int ProcessPuzzle() {
    int f, i, j;
    Tot++;
    for (f = 0; f < 25; f++) if (Puzzle((f / 5) + 1, (f % 5) + 1) == ' ') break;
    if (f == 25) return true;
    i = (f / 5) + 1;
    j = (f % 5) + 1;
//    std::cout << i << ", " << j << "\n";
    
    for (int ii = 'A'; ii <= 'D'; ii++) {
        if (TestEntryLegal(ii, i, j)) {
            Puzzle(i, j) = ii;
//            std::cout << ii << "\n";
            if (ProcessPuzzle()) return true;;
            Puzzle(i, j) = ' ';
        }
    }
    return false;
}

int TestEntryLegal(int c, int i, int j) {
    int t, tt;

// Count Ds in row
    tt = 0;
    for (t = 1; t < 6; t++) if (Puzzle(i, t) == 'D') tt++;
    if ((tt >= 2 && c == 'D')) return false;

// Count Ds in column
    tt = 0;
    for (t = 1; t < 6; t++) if (Puzzle(t, j) == 'D') tt++;
    if ((tt >= 2 && c == 'D')) return false;

 // D is now OK
    if (c == 'D') return true;

 // Check for multiple As, Bs or Cs in row or column
    for (int ii = 1; ii < 6; ii++)
        if (Puzzle(i, ii) == c or Puzzle(ii, j) == c) return false;

 // Check that there is space for legal letter at end of row and column
    if ((c == Puzzle(i, 6) && j < 3) or (c == Puzzle(6, j) && i < 3)) return false;

// Check Row
    if (c != Puzzle(i, 0) && Puzzle(i,0) != '-') {  // Check not an illegal first letter in row
        for (t = 1; t < j; t++)
            if (Puzzle(i, t) != 'D') break;
        if (t == j) return false;
    }

    if (c != Puzzle(i, 6) && Puzzle(i,6) != '-') {  // Check not an illegal last letter in row
        for (t = j+1; t < 6; t++)
            if (Puzzle(i, t) != 'D') break;
        if (t == 6) return false;
    }

    if (c != Puzzle(i, 6) && Puzzle(i, 6) != '-') {  // Check not blocking the legal last letter in row
        for (t = 1; t < j; t++)
            if (Puzzle(i, t) == Puzzle(i, 6)) break;
        if (t < j) return false;
    }


//Check Column
    if (c != Puzzle(0,j) && Puzzle(0, j) != '-') {
        for (t = 1; t < i; t++)
            if (Puzzle(t, j) != 'D') break;
        if (t == i) return false;
    }

    if (c != Puzzle(6, j) && Puzzle(6, j) != '-') {
        for (t = i + 1; t < 6; t++)
            if (Puzzle(t, j) != 'D') break;
        if (t == 6) return false;
    }

    if (c != Puzzle(6, j) && Puzzle(6, j) != '-') {
        for (t = 1; t < i; t++)
            if (Puzzle(t, j) == Puzzle(6,j)) break;
        if (t < i) return false;
    }

//    PrintBoard(Puzzle, std::cout);
    return true;
}
void PrintBoard(PuzzleBoard PzB, std::ostream& Stream) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            Stream << " " << PzB(i, j);
        }
        Stream << "\n";
    }
    Stream << "\n\n";
}
void PrintCentreBoard(PuzzleBoard PzB, std::ostream& Stream) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <5; j++) {
            Stream << " " << PzB(i + 1, j + 1);
        }
        Stream << "\n";
    }
    Stream << "\n\n";
}

void LoseDsBoard(PuzzleBoard &PzB) {
    for (int i = 0; i < 49; i++) if (PzB(i / 7, i % 7) == 'D') PzB(i / 7, i % 7) = '-';
}
