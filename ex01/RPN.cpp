#include "RPN.h"

RPN::RPN(): _val(0) {}
RPN::RPN(const RPN&src): _stack(src._stack), _val(0) {}
RPN::~RPN() {}
RPN &RPN::operator=(const RPN&src) {
    _stack = src._stack;
    _val = src._val;
    return *this;
}

RPN::RPN(const std::string&src): _val(0) {
    if (src.empty())
        throw std::runtime_error("Error: no inputs");
    
    for (size_t i = 0; i < src.size(); i++) {
        if (isspace(src[src.size() - 1]))
            throw std::runtime_error("Error");

        if (isspace(src[i]) && (i % 2 == 0))
            throw std::runtime_error("Error: space on even char");

        if (isspace(src[i]))
            continue;
        
        if (!isdigit(src[i]) && src[i] != '+' && src[i] != '-' && src[i] != '*' && src[i] != '/')
            throw std::runtime_error("Error");

        _stack.push(src[i]);
    }

    if (_stack.size() == 0)
        throw std::runtime_error("Error");
}

ssize_t RPN::evaluate() {
    if (_stack.empty()) {
        throw std::runtime_error("Error");
    }

    char token = pop();

    if (std::isdigit(token))
        return token - '0';

    ssize_t right = evaluate();
    ssize_t left = evaluate();

    switch (token) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': 
            if (right == 0) throw std::runtime_error("Error: division by zero");
            return left / right;
        default:
            throw std::runtime_error("Error: invalid operator");
    }
}

char RPN::pop() {
    char c = _stack.top();
    _stack.pop();
    return c;
}
