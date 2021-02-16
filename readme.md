## [textAI.cpp](https://github.com/repinnick/antiplagiat/blob/main/textAI.cpp)

<b>textAI</b> is a program that compares the original text with a test fragment (a fragment of text entered by the user). The basis is taken such a system for determining plagiarism: 
<ul>
    <li>first, we select <code>1, 2, 3</code> words from a fragment of the text, the entered by user, and check if there is such a sequence of words in the original text;</li>
    <li>then select <code>2, 3, 4</code> words and again look for them in the text and etc.;</li>
    <li>after a complete analysis of the text we will calculate the percentage of matching selections and draw a conclusion about the uniqueness of the text.</li>
</ul>

```c++
#define SELECTION_WORDS 3

// sets the meaning of words in the selection;
// the value can be a positive integer no less than 2 (otherwise the selection is meaningless);
// default value is 3;
```

```c++
//into variables
string documentText;
string userText;
// formatted original text and user text are transmitted, respectively;
```
<hr>
Text formatting (removing punctuation marks and converting text to lowercase) performs the function:

```c++
string textWithoutSeparators(string text);
```

It calls the ```bool isSeparator(char c)``` function, which searches for punctuation marks in the original text and in the user's text. The output is a new formatted string.
<hr>

Then, using the function
```c++
int wordCounter(string userText);
```
the program counts the number of words in the user's text. Returns the number of words that we write to the variable ```int arraySize```. This variable will act as the size of the future array.
<hr>

```c++
void addWordsInArray(string userText, string words[]);
```

This function fills the static array ```string words[arraySize] = {};``` with words from the user's text.
<hr>

```c++
int checkWordsInText(int size, string words[], string documentText);
```
<b><i>The most important part of the program.</i></b> Here is the breakdown of the array into three elements, the concatenation of three words into a string and the check of the selected string with the function ```findWords()```.

```c++
int findWords(string text, string textForFind);
```
The function takes as input the original text and a fragment of text from the function ```int checkWordsInText()```, and checks for the coincidence of the fragment of text with the original text.
<hr>

```c++
int plagiatDetector(int size, int coincidences);
int sumOfNotSelection();
```
Final functions of the program, which allow to determine the uniqueness of the text. Selections are counted, and using the proportion method, the function calculates the percentage of plagiarism.
<hr>

<b>The project was made by:</b>
<ul>
    <li>
    <code>Mikalai Repin</code><br>
    <a href="mailto:mikalai.repin@gmail.com">mikalai.repin@gmail.com</a>
    </li>
    <li>
    <code>Artur Kutas</code><br>
    <a href="mailto:artur.kytas@gmail.com">artur.kytas@gmail.com</a>
    </li>
</ul>

<hr>