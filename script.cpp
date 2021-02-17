#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

#define SELECTION_WORDS 3

using namespace std;
using namespace cgicc;

bool isSeparator(char c);
string textWithoutSeparators(string text);
int findWords(string text, string textForFind);
int wordCounter(string userText);
void addWordsInArray(string userText, string words[]);
int checkWordsInText(int size, string words[], string documentText);
int plagiatDetector(int size, int coincidences);
int sumOfNotSelection();
double antiPlagiarism(string text, string fragment);
string getDB();

int main()
{
    Cgicc form;
    string name;

    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<title>Ggi Server</title>\n";
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<p>";

    name = form("value");
    if (!name.empty())
    {
        cout << antiPlagiarism(getDB(), name) << "\n";
    }
    else
    {
        cout << "Text is not provided!\n";
    }
    cout << "</p>\n";
    cout << "</body>\n";
    cout << "</html>\n";

    return 0;
}

string getDB()
{
    std::ifstream in("db.txt");

    string dbText = "", s1;
    while (getline(in, s1))
        dbText += s1;

    in.close();

    return dbText;
}

double antiPlagiarism(string text, string fragment)
{
    string documentText = textWithoutSeparators(text);
    string userText = textWithoutSeparators(fragment);

    const int arraySize = wordCounter(userText);
    string words[arraySize] = {};

    addWordsInArray(userText, words);

    int coincidences = checkWordsInText(arraySize, words, documentText);
    return 100.0 - (1.0 * plagiatDetector(arraySize, coincidences));
}

bool isSeparator(char c)
{
    char s[] = ",.!;?:-+\"`'/\\%#^@&$*()}{][|~=";
    for (int i = 0; s[i] != '\0'; i++)
        if (c == s[i])
            return true;

    return false;
}

string textWithoutSeparators(string text)
{
    string newText;
    for (int i = 0; i < text.size(); i++)
    {
        if (isSeparator(text[i]))
            continue;
        newText += tolower(text[i]);
    }
    return newText;
}

int findWords(string text, string textForFind)
{
    int j = 0;
    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] == textForFind[j])
            j++;
        else if (j == textForFind.size())
            return SELECTION_WORDS;
        else
            j = 0;
    }
    return 0;
}

int wordCounter(string userText)
{
    int counter = 0;

    for (int i = 0; i <= userText.size(); i++)
        if (userText[i] == ' ' or i == userText.size())
            counter++;

    return counter;
}

void addWordsInArray(string userText, string words[])
{
    string word = "";
    int wc = 0;
    for (int i = 0; i <= userText.size(); i++)
        if (userText[i] == ' ' or i == userText.size())
        {
            words[wc] = word;
            wc++;
            word = "";
        }
        else
        {
            word += userText[i];
        }
}

int checkWordsInText(int size, string words[], string documentText)
{
    string threeWordsForCheck = "";
    int counter = 0;
    int finish = SELECTION_WORDS - 1;

    for (int i = 0; i < size - finish; i++)
    {
        int wCount = 0;
        while (wCount < SELECTION_WORDS)
        {
            if (wCount == SELECTION_WORDS - 1)
                threeWordsForCheck += (words[i + wCount]);
            else
                threeWordsForCheck += (words[i + wCount] + " ");

            wCount++;
        }
        counter += findWords(documentText, threeWordsForCheck);
        threeWordsForCheck = "";
    }
    return counter;
}

int plagiatDetector(int size, int coincidences)
{
    int common = (size * SELECTION_WORDS) - (2 * sumOfNotSelection());
    return (coincidences * 100) / common;
}

int sumOfNotSelection()
{
    int sum = 0;
    for (int i = 0; i < SELECTION_WORDS; i++)
    {
        sum += i;
    }
    return sum;
}