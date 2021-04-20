
#include "calculator.hpp"
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>
char findFirstCharDiff(std::string s1)
{
    std::string expected = "mod";
    int smallerLength = std::min(s1.length(), expected.length());
    for (int i = 0; i < smallerLength; i++)
    {
        if (expected.at(i) != s1.at(i))
        {
            return s1.at(i);
        }
    }
    return s1.at(smallerLength - 1);
}
// Scanner implementation

// You may have to modify this constructor, although it might not be neccessary.
Scanner::Scanner() : line(1),
                     value(0),
                     tokenSet(false),
                     currToken(T_EOF)
{
    // WRITEME
    // std::string junk;
    // std::cin >> std::setw(2) >> junk;
    // std::cout << "this is junk " << junk;
    std::cin.peek();
}

// You need to fill this method with the appropriate code for it to work as described in the project description.
Token Scanner::nextToken()
{
    if (this->tokenSet)
    {
        return this->currToken;
    }
    char c = (std::cin >> std::ws).peek();
    if (c == std::char_traits<char>::eof())
    {
        this->currToken = T_EOF;
        this->tokenSet = true;
        return T_EOF;
    }
    if (std::isdigit(c))
    {
        int n;
        std::cin >> n;
        this->value = n;
        this->currToken = T_NUMBER;
        this->tokenSet = true;
        return T_NUMBER;
    }

    if (c == '(')
    {
        char temp;
        std::cin >> std::setw(1) >> temp;
        this->currToken = T_OPENPAREN;
        this->tokenSet = true;
        return T_OPENPAREN;
    }
    if (c == ')')
    {
        char temp;
        std::cin >> std::setw(1) >> temp;
        this->currToken = T_CLOSEPAREN;
        this->tokenSet = true;
        return T_CLOSEPAREN;
    }
    if (c == '+')
    {
        char temp;
        std::cin >> std::setw(1) >> temp;
        this->currToken = T_PLUS;
        this->tokenSet = true;
        return T_PLUS;
    }
    if (c == '-')
    {
        char temp;
        std::cin >> std::setw(1) >> temp;
        this->currToken = T_MINUS;
        this->tokenSet = true;
        return T_MINUS;
    }
    if (c == '*')
    {
        char temp;
        std::cin >> std::setw(1) >> temp;
        this->currToken = T_MULTIPLY;
        this->tokenSet = true;
        return T_MULTIPLY;
    }
    if (c == '/')
    {
        char temp;
        std::cin >> std::setw(1) >> temp;
        this->currToken = T_DIVIDE;
        this->tokenSet = true;
        return T_DIVIDE;
    }
    if (c == ';')
    {
        char temp;
        std::cin >> std::setw(1) >> temp;
        this->currToken = T_SEMICOLON;
        this->tokenSet = true;
        return T_SEMICOLON;
    }
    if (c == '\n')
    {
        char temp;
        std::cin >> std::setw(1) >> temp;
        this->currToken = T_NEWLN;
        this->tokenSet = true;
        return T_NEWLN;
    }
    if (c == 'm')
    {
        std::string input;
        std::cin >> std::setw(3) >> input;
        if (input.compare("mod") != 0)
        {
            char result = findFirstCharDiff(input);
            scanError(this->line, result);
        }
        else
        {
            this->currToken = T_MODULO;
            this->tokenSet = true;
            return T_MODULO;
        }
    }
    scanError(this->line, c);
}

// You need to fill this method with the appropriate code for it to work as described in the project description.
void Scanner::eatToken(Token toConsume)
{
    if (this->currToken == toConsume)
    {
        this->tokenSet = false;
    }
    else
    {
        mismatchError(this->line, toConsume, this->currToken);
    }
}

int Scanner::lineNumber()
{
    return this->line;
}

int Scanner::getNumberValue()
{
    return this->value;
}

// Parser implementation

// You may need to modify this constructor and make it do stuff, although it might not be neccessary.
Parser::Parser(bool eval) : evaluate(eval)
{
    Scanner newScanner;
    this->scanner = newScanner;
}

void Parser::parse()
{
    start();
}

void Parser::start()
{
    // I am a placeholder. Implement a recursive descent parser starting from me. Add other methods for different recursive steps.
    // Depending on how you designed your grammar, how many levels of operator precedence you need, etc., you might end up with more
    // or less steps in the process.
    //
    L();
}

void Parser::match(Token token)
{
    if (this->scanner.nextToken() == token)
    {
        std::cout << "matched token " << tokenToString(token);
        this->scanner.eatToken(token);
    }
    else
    {
        // std::cout << "scanner token: " << tokenToString(this->scanner.nextToken());
        parseError(this->scanner.lineNumber(), token);
    }
}

void Parser::L()
{
    E();
    R();
}

void Parser::R()
{
    switch (this->scanner.nextToken())
    {
    case T_SEMICOLON:
        match(T_SEMICOLON);
        E();
        R();
        break;
    case T_EOF:
        this->scanner.eatToken(T_EOF);
        break;
    default:
        parseError(this->scanner.lineNumber(), this->scanner.nextToken());
    }
}

void Parser::E()
{
    T();
    EPrime();
}

void Parser::EPrime()
{
    switch (this->scanner.nextToken())
    {
    case T_PLUS:
        match(T_PLUS);
        T();
        EPrime();
        break;
    case T_MINUS:
        match(T_MINUS);
        T();
        EPrime();
        break;
    case T_EOF:
        this->scanner.eatToken(T_EOF);
        break;
    default:
        parseError(this->scanner.lineNumber(), this->scanner.nextToken());
    }
}

void Parser::T()
{
    F();
    TPrime();
}

void Parser::TPrime()
{
    switch (this->scanner.nextToken())
    {
    case T_MULTIPLY:
        match(T_MULTIPLY);
        F();
        TPrime();
        break;
    case T_DIVIDE:
        match(T_DIVIDE);
        F();
        TPrime();
        break;
    case T_MODULO:
        match(T_MODULO);
        F();
        TPrime();
        break;
    case T_EOF:
        this->scanner.eatToken(T_EOF);
        break;
    default:
        parseError(this->scanner.lineNumber(), this->scanner.nextToken());
    }
}

void Parser::F()
{
    switch (this->scanner.nextToken())
    {
    case T_NUMBER:
        match(T_NUMBER);
        break;
    case T_OPENPAREN:
        match(T_OPENPAREN);
        E();
        match(T_CLOSEPAREN);
        break;
    default:
        parseError(this->scanner.lineNumber(), this->scanner.nextToken());
    }
}