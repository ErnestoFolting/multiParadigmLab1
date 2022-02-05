#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    int stopWordsSize = 15;
    string* stopWords = new string[stopWordsSize];
    stopWords[0] = "in";
    stopWords[1] = "on";
    stopWords[2] = "up";
    stopWords[3] = "an";
    stopWords[4] = "a";
    stopWords[5] = "are";
    stopWords[6] = "is";
    stopWords[7] = "has";
    stopWords[8] = "so";
    stopWords[9] = "be";
    stopWords[10] = "were";
    stopWords[11] = "do";
    stopWords[12] = "did";
    stopWords[13] = "can";
    stopWords[14] = "for";

    ifstream inFile("input.txt");
    int maxNumberWords = 10;
    int currentNumberWords = 0;
    string* allWords = new string[maxNumberWords];
    int* allNumbers = new int[maxNumberWords];

    string temp = "";
wordFromFile:
    inFile >> temp;
    if (temp == "") {
        goto end;
    }
    else {
        temp += " ";
        int i = 0;
    normalization:
        if (temp[i] >= 65 && temp[i] <= 90)temp[i] += 32;
        i++;
        if (temp[i] != ' ') goto normalization;
        i = 0;
    checkStop:
        if (i < stopWordsSize) {
            if ((stopWords[i]+' ') == temp) {
                temp = "";
                goto wordFromFile;
            }
            i++;
            goto checkStop;
        }
        cout << temp << endl;
        goto wordFromFile;
    }
end:
    inFile.close();
}