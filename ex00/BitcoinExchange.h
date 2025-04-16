#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <algorithm>
#include <cctype>

#define DEF "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define BOLD_RED "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_BLUE "\033[1;34m"
#define BOLD_PURPLE "\033[1;35m"
#define BOLD_CYAN "\033[1;36m"
#define BOLD_WHITE "\033[1;37m"

class Bitcoin {
    public:
        Bitcoin();
        Bitcoin(const std::string&);
        Bitcoin &operator=(const Bitcoin&);
        Bitcoin(const Bitcoin&);
        ~Bitcoin();

        double getExchangeRate(const std::string&) const;
        void loadfile(const std::string&);
    private:
        std::map<std::string, double> _rates;

        void error(const std::string&, const std::string&, size_t, size_t) const;
        double getRate(const std::string&date) const;
};