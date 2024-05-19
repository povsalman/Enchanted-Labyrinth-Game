#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "UserInterface.h"

using namespace std;

class highscore {
    bool empty = 0, check = true;

public:
    string H = "high";
    string* names;
    string* score;
    int size = 0;

    highscore() {
        ifstream file("high.txt");
        if (file.peek() == ifstream::traits_type::eof()) {
            empty = true;
        }
        else {
            empty = false;
        }

        if (empty) {
            size = 0;
        }
        else {
            string line;
            while (getline(file, line) && line.empty() == false) {
                size++;
            }
        }

        names = nullptr;
        score = nullptr;
    }

    void adding(string n, string s) {
        ofstream writeFile;

        if (empty) {
            writeFile.open("high.txt", ios::app);
            writeFile << n << " " << s << endl;
            empty = false;
        }
        else {
            string* tempname = new string[size];
            string* tempscore = new string[size];

            ifstream file("high.txt");
            string line;

            for (int i = 0; getline(file, line) && i < size; i++) {
                size_t spacePos = line.find('    ');
                string name = line.substr(0, spacePos);
                string scorz = line.substr(spacePos + 1);

                tempname[i] = name;
                tempscore[i] = scorz;
            }

            for (int i = 0; i < size; i++) {
                if (tempname[i] == n) {
                    tempscore[i] = s;
                    check = false;
                }
            }

            if (check) {
                string* newNames = new string[size + 1];
                string* newScores = new string[size + 1];

                for (int i = 0; i < size; i++) {
                    newNames[i] = tempname[i];
                    newScores[i] = tempscore[i];
                }

                newNames[size] = n;
                newScores[size] = s;
                size++;

                delete[] names;
                delete[] score;

                names = newNames;
                score = newScores;
            }
            else {
                delete[] tempname;
                delete[] tempscore;
            }

            SortDescending(names, score, size);

            writeFile.clear();
            writeFile.open("high.txt", ios::trunc);

            for (int i = 0; i < size; i++) {
                writeFile << names[i] << "    " << score[i] << endl;
            }
        }
    }

    void SortDescending(string names[], string scores[], int s) {
        //for (int i = 0; i < s - 1; ++i) {
        //    for (int j = 0; j < s - i - 1; ++j) {
        //        // Convert scores to integers for comparison
        //        int score1 = stoi(scores[j]);
        //        int score2 = stoi(scores[j + 1]);

        //        if (score1 < score2) {
        //            swap(names[j], names[j + 1]);
        //            swap(scores[j], scores[j + 1]);
        //        }
        //    }
        //}
    }

    ~highscore() {
        delete[] names;
        delete[] score;
    }

};


