
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
Scanner::Scanner() : line(0),
                     value(0),
                     tokenSet(false),
                     currToken(T_EOF)
{
    // WRITEME
    std::string dummy;
    std::cin >> dummy;
    std::cout << "this is dummy:" << dummy << "---" << std::endl;
}

// You need to fill this method with the appropriate code for it to work as described in the project description.
Token Scanner::nextToken()
{
    if (this->tokenSet)
    {
        std::cout << "token set " << std::endl;
        return this->currToken;
    }

    char c = std::cin.peek();
    std::string actual;
    std::cin >> actual;
    std::cout << "this is actual:" << actual << "---" << std::endl;
    std::cout << "this is what I peeked: " << c << std::endl;
    if (c == EOF)
    {
        std::cout << "token set " << std::endl;
        this->currToken = T_EOF;
        this->tokenSet = true;
        return T_EOF;
    }
    if (std::isdigit(c))
    {
        std::cout << "token set " << std::endl;
        int n;
        std::cin >> n;
        this->value = n;
        this->currToken = T_NUMBER;
        this->tokenSet = true;
        return T_NUMBER;
    }

    if (c == '(')
    {
        std::cout << "token set " << std::endl;
        this->currToken = T_OPENPAREN;
        this->tokenSet = true;
        return T_OPENPAREN;
    }
    if (c == ')')
    {
        std::cout << "token set " << std::endl;
        this->currToken = T_CLOSEPAREN;
        this->tokenSet = true;
        return T_CLOSEPAREN;
    }
    if (c == '+')
    {
        std::cout << "token set " << std::endl;
        this->currToken = T_PLUS;
        this->tokenSet = true;
        return T_PLUS;
    }
    if (c == '-')
    {
        std::cout << "token set " << std::endl;
        this->currToken = T_MINUS;
        this->tokenSet = true;
        return T_MINUS;
    }
    if (c == '*')
    {
        std::cout << "token set " << std::endl;
        this->currToken = T_MULTIPLY;
        this->tokenSet = true;
        return T_MULTIPLY;
    }
    if (c == '/')
    {
        std::cout << "token set " << std::endl;
        this->currToken = T_DIVIDE;
        this->tokenSet = true;
        return T_DIVIDE;
    }
    if (c == ';')
    {
        std::cout << "token set " << std::endl;
        this->currToken = T_SEMICOLON;
        this->tokenSet = true;
        return T_SEMICOLON;
    }
    if (c == '\n')
    {
        this->currToken = T_NEWLN;
        this->tokenSet = true;
        return T_NEWLN;
    }
    if (c == 'm')
    {
        std::cout << "token set " << std::endl;
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
    std::cout << "token not set " << std::endl;
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

Token Scanner::getCurrToken()
{
    return this->currToken;
}

// Parser implementation

// You may need to modify this constructor and make it do stuff, although it might not be neccessary.
Parser::Parser(bool eval) : evaluate(eval)
{
    // WRITEME
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
    // WRITEME
}

// You will need to add more methods for this to work. Don't forget to also define them in calculator.hpp!
// WRITEME
