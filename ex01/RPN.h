#pragma once

#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <exception>
#include <algorithm>
#include <cctype>

class RPN {
public:
    RPN();
    RPN(const std::string&);
    RPN(const RPN&);
    RPN &operator=(const RPN&);
    ~RPN();

    ssize_t evaluate();
private:
    std::stack<char> _stack;
    ssize_t _val;

    char pop();
    void push(char);
};