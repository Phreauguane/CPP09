#include "BitcoinExchange.h"


bool notSpace(char c){
    return !std::isspace(static_cast<unsigned char>(c));
}

std::string& trim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
    s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
    return s;
}

Bitcoin::Bitcoin() {}
Bitcoin::~Bitcoin() {}
Bitcoin::Bitcoin(const Bitcoin &src) {
    *this = src;
}
Bitcoin &Bitcoin::operator=(const Bitcoin&src) {
    if (this != &src)
        _rates = src._rates;
    return *this;
}
Bitcoin::Bitcoin(const std::string&file) {
    std::ifstream f(file.c_str());
	
    if (!f)
        throw std::runtime_error("Error: could not open file.");

    std::string line, date;
    double rate;

    if (std::getline(f, line))
    {
        if (line != "date,exchange_rate")
        {
            std::istringstream ss(line);

            if (std::getline(ss, date, ',') && (ss >> rate))
                _rates[date] = rate;
        }
    }
    
    while (std::getline(f, line))
    {
        std::stringstream ss(line);

        if (std::getline(ss, date, ',') && (ss >> rate))
            _rates[date] = rate;
    }
}