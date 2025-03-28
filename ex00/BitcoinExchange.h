#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <iostream>
#include <algorithm>
#include <cctype>

class Bitcoin {
    public:
        Bitcoin();
        Bitcoin(const std::string&);
        Bitcoin &operator=(const Bitcoin&);
        Bitcoin(const Bitcoin&);
        ~Bitcoin();

        double getExchangeRate(const std::string&) const;
    private:
        std::map<std::string, double> _rates;

        bool isValidDate(const std::string&) const;
        bool isValidValue(const std::string&) const;
        void loadfile(const std::string&);
};