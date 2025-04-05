// front.cpp - A lexical analyzer for simple arithmetic expressions

#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

// Character classes
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

// Token codes
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

// Global variables
int charClass;
string lexeme;
char nextChar;
int nextToken;
ifstream inFile;

// Function declarations
void addChar();
void getChar();
void getNonBlank();
int lookup(char ch);
int lex();

// Add character to lexeme
void addChar() {
    lexeme += nextChar;
}

// Read next character and classify it
void getChar() {
    if (inFile.get(nextChar)) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else {
        charClass = EOF;
    }
}

// Skip whitespace
void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

// Lookup operators and parentheses
int lookup(char ch) {
    switch (ch) {
    case '(': addChar(); return LEFT_PAREN;
    case ')': addChar(); return RIGHT_PAREN;
    case '+': addChar(); return ADD_OP;
    case '-': addChar(); return SUB_OP;
    case '*': addChar(); return MULT_OP;
    case '/': addChar(); return DIV_OP;
    default:  addChar(); return EOF;
    }
}

// Lexical analyzer function
int lex() {
    lexeme = "";
    getNonBlank();

    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;

    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;

    case UNKNOWN:
        nextToken = lookup(nextChar);
        getChar();
        break;

    case EOF:
        nextToken = EOF;
        lexeme = "EOF";
        break;
    }

    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}

// Main function
int main() {
    inFile.open("front.in");

    if (!inFile) {
        cout << "ERROR - cannot open front.in" << endl;
        return 1;
    }

    getChar();
    do {
        lex();
    } while (nextToken != EOF);

    inFile.close();
    return 0;
}

