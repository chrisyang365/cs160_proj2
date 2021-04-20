#pragma once

#include "helpers.hpp"

#include <climits>

// SCANNER DEFINITION

// You can freely add member fields and functions to this class.
class Scanner
{
    int line;
    int value;
    bool tokenSet;
    Token currToken;

public:
    // You really need to implement these four methods for the scanner to work.
    Token nextToken();
    void eatToken(Token);
    int lineNumber();
    int getNumberValue();

    Scanner();
};

// PARSER DEFINITION

// You can freely add member fields and functions to this class.
class Parser
{
    Scanner scanner;
    Token lookahead;

    bool evaluate;
    void start();
    void match(Token token);
    void L();
    void E();
    void R();
    void EPrime();
    void T();
    void TPrime();
    void F();
    void FPrime();
    void evalProgram();
    int arithmetic(int x, int y, Token opToken);
    bool hasPrecedence(Token opToken1, Token opToken2);

public:
    void parse();

    Parser(bool);
};
