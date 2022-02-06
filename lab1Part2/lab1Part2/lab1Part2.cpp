#include <iostream>
#include <fstream>

using namespace std;
int main()
{
	string fileName;
	cout << "Input the file name to index\n";
	cin >> fileName;
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

    ifstream inFile(fileName);
    int maxNumberWords = 10;
    int currentNumberWords = 0;
    string* allWords = new string[maxNumberWords];
    string* allPages = new string[maxNumberWords];
    int* numberOfPages = new int[maxNumberWords];
    bool* wasOnThisPage = new bool[maxNumberWords];
    int lineNumber = 0;
    int pageNumber = 0;

wordFromFile:
    if (inFile.peek() == '\n') {
        lineNumber++;
        inFile.get();
        goto wordFromFile;
    }
    if (lineNumber / 45 != pageNumber) {  //if the new page
        pageNumber++;
        int i = 0;
    newPage:
        wasOnThisPage[i] = false;
        i++;
        if (i < maxNumberWords)goto newPage;
    }
    string temp = "";
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
            if ((stopWords[i] + ' ') == temp) {
                temp = "";
                goto wordFromFile;
            }
            i++;
            goto checkStop;
        }
        i = 0;
    countDuplication:
        string tempStr = "";
        if (temp == allWords[i]) {
            numberOfPages[i]++;
            if (!wasOnThisPage[i]) {
                int tempPageNumber = pageNumber + 1; //logical page number
            toString:
                if (tempPageNumber != 0) {
                    int number = tempPageNumber % 10;
                    tempStr = char(number + 48) + tempStr; //ASCII code of number 
                    tempPageNumber /= 10;
                    goto toString;
                }
                allPages[i] += ", " + tempStr;                
            }
            wasOnThisPage[i] = true;
            temp = "";
            goto wordFromFile;
        }
        i++;
        if (i < currentNumberWords)goto countDuplication;
        tempStr = "";
        wasOnThisPage[currentNumberWords] = true;
        allWords[currentNumberWords] = temp;
        numberOfPages[currentNumberWords] = 1;
        int tempPageNumber = pageNumber + 1;
    toString2:
        if (tempPageNumber != 0) {
            int number = tempPageNumber % 10;
            tempStr = char(number + 48) + tempStr; //ASCII code of number 
            tempPageNumber /= 10;
            goto toString2;
        }
        allPages[currentNumberWords] += tempStr;
        currentNumberWords++ ;
        if (currentNumberWords == maxNumberWords) {
            maxNumberWords += 5; //expand to 5 extra words 
            //initialize new arrays
            string* tempWords = new string[maxNumberWords];
            string* tempPages = new string[maxNumberWords];
            int* tempNumbers = new int[maxNumberWords];
            bool* tempWas = new bool[maxNumberWords];
            int i = 0;
        copyToNewArrays:
            if (i < currentNumberWords) {
                tempWords[i] = allWords[i];
                tempPages[i] = allPages[i];
                tempNumbers[i] = numberOfPages[i];
                tempWas[i] = wasOnThisPage[i];
                i++;
                goto copyToNewArrays;
            }
            delete[] allWords;
            delete[] allPages;
            delete[] numberOfPages;
            delete[] wasOnThisPage;
            allWords = tempWords;
            allPages = tempPages;
            numberOfPages = tempNumbers;
            wasOnThisPage = tempWas;
        }
        temp = "";
        goto wordFromFile;
    }
wordsReadingEnd:
    inFile.close();
    ofstream outFile("output.txt");
    //bubble sort
    int i = 0;
externalCycle:
    if (i < currentNumberWords) {
        int j = i + 1;
    internalCycle:
        if (j < currentNumberWords) {
            bool swap = 0;
            int k = 0;
        checkSwap:
            if (allWords[i][k] != ' ' && allWords[j][k] != ' ') {
                if (allWords[i][k] == allWords[j][k]) {
                    k++;
                    goto checkSwap;
                }
                else {
                    if (allWords[i][k] > allWords[j][k]) swap = 1;
                }
            }
            else {
                if (allWords[i][k] != ' ') swap = 1;
            }
            if (swap) {
                string tempWord = allWords[i];
                allWords[i] = allWords[j];
                allWords[j] = tempWord;
                string tempPages = allPages[i];
                allPages[i] = allPages[j];
                allPages[j] = tempPages;
                int tempNumber = numberOfPages[i];
                numberOfPages[i] = numberOfPages[j];
                numberOfPages[j] = tempNumber;
            }
            j++;
            goto internalCycle;
        }
        i++;
        goto externalCycle;
    }
    i = 0;
output:
    if (numberOfPages[i] <= 100) {
        cout << allWords[i] << " - " << allPages[i] << endl;
        outFile << allWords[i] << " - " << allPages[i] << endl;
    }
    i++;
    if (i < currentNumberWords) goto output;
    delete[] allWords;
    delete[] allPages;
    delete[] numberOfPages;
    delete[] wasOnThisPage;
    outFile.close();
}