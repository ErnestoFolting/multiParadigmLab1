#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    int expectedWordsToShow;
    cout << "How many words you want to show?\n";
    cin >> expectedWordsToShow;

    int stopWordsSize = 18;
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
    stopWords[15] = "to";
    stopWords[16] = "and";
    stopWords[17] = "the";

    ifstream inFile("input.txt");
    int maxNumberWords = 10;
    int currentNumberWords = 0;
    string* allWords = new string[maxNumberWords];
    int* allNumbers = new int[maxNumberWords];
    int numberOfWordsToDisplay = 25;

    string temp = "";
wordFromFile:
    inFile >> temp;
    if (temp == "") {
        goto wordsReadingEnd;
    }
    else {
        temp += " ";
        int i = 0;
    normalization:
        if (temp[i] >= 65 && temp[i] <= 90)temp[i] += 32;
        i++;
        if (temp[i] != ' ') goto normalization;
        i = 0;
        string buffer = "";
        bool afterChar = false;
    deleteSigns:
        if (temp[i] >= 97 && temp[i] <= 122 || (temp[i] == '-' || temp[i] == '\'' || temp[i] == '`') && (temp[i + 1] >= 97 && temp[i + 1] <= 122) && afterChar) {
            buffer += temp[i];
            afterChar = true;
        }
        i++;
        if (temp[i] != ' ') goto deleteSigns;
        if (buffer == "") {
            temp = "";
            goto wordFromFile;
        }
        temp = buffer + " ";
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
        i = 0;
    countDuplication:
        if (i < currentNumberWords) {
            if (allWords[i] == temp) {
                allNumbers[i] += 1;
                temp = "";
                goto wordFromFile;
            }
            i++;
            goto countDuplication;
        }
        allWords[currentNumberWords] = temp;
        allNumbers[currentNumberWords] = 1;
        currentNumberWords++;
        temp = "";
        if (currentNumberWords + 1 == maxNumberWords) {
            maxNumberWords += 5; //expand to 5 extra words 
            //initialize new arrays
            string* tempWords = new string[maxNumberWords];
            int* tempNumbers = new int[maxNumberWords];
            i = 0;
        newArrays:
            if (i < currentNumberWords) {
                tempWords[i] = allWords[i];
                tempNumbers[i] = allNumbers[i];
                i++;
                goto newArrays;
            }
            delete[] allWords;
            delete[] allNumbers;
            allWords = tempWords;
            allNumbers = tempNumbers;
        }
        goto wordFromFile;
    }
wordsReadingEnd:
    inFile.close();
    //bubble sort
    int i = 0;
    externalCycle:
    if (i < currentNumberWords - 1) {
        int j = 0;
    internalCycle:
        if (j < currentNumberWords - i - 1) {
            if (allNumbers[j] < allNumbers[j + 1]) {
                int tempNumber = allNumbers[j];
                allNumbers[j] = allNumbers[j + 1];
                allNumbers[j + 1] = tempNumber;
                string tempWord = allWords[j];
                allWords[j] = allWords[j + 1];
                allWords[j + 1] = tempWord;
            }
            j++;
            goto internalCycle;
        }
        i++;
        goto externalCycle;
    }
    int wordsToShow;
    if (expectedWordsToShow > currentNumberWords) {
        wordsToShow = currentNumberWords;
    }
    else {
        wordsToShow = expectedWordsToShow;
    }
    i = 0;
    ofstream outFile("output.txt");
output:
    if (i < wordsToShow) {
        cout << allWords[i] << " - " << allNumbers[i] << endl;
        outFile << allWords[i] << " - " << allNumbers[i] << endl;
        i++;
        goto output;
    }
    outFile.close();
    delete[] allWords;
    delete[] allNumbers;
}