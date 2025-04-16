#include "BitcoinExchange.h"

bool notSpace(char c){
    return !std::isspace(static_cast<unsigned char>(c));
}

void trim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
    s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
}

Bitcoin::Bitcoin() {}
Bitcoin::~Bitcoin() {}
Bitcoin::Bitcoin(const Bitcoin &src): _rates(src._rates) {}

Bitcoin &Bitcoin::operator=(const Bitcoin&src) {
    if (this != &src)
        _rates = src._rates;
    return *this;
}

Bitcoin::Bitcoin(const std::string&file) {
    std::ifstream f(file.c_str());
	
    if (!f)
        throw std::runtime_error("Error: invalid file " + file);

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

void Bitcoin::error(const std::string&line, const std::string&err, size_t l, size_t c) const{
    std::stringstream ss;
    std::cout << BOLD_RED "[ERROR] " RED << l + 1 << ":" << c << " " << err << " :  " << line << std::endl;

    ss << "XXXXXXXX" << l + 1 << "X" << c << "X" << err << "XXX";
    for (size_t i = 0; i < ss.str().size(); i++) {
        std::cout << " ";
    }
    
    std::cout << BOLD_RED ;

    for (size_t i = 0; i < line.size() + 2 || i <= c; i++) {
        if (i == c + 1) {
            std::cout << "⌃"; i++;
        }
        else
            std::cout << "~";
    }
    std::cout << "~" << DEF << std::endl;
}

void Bitcoin::loadfile(const std::string&file) {
    std::ifstream f(file.c_str());

    if (!f)
        throw std::runtime_error("Error: invalid file " + file);

    std::string line, date, value;
    // double val;

    for (size_t i = 0; getline(f, line); i++) {
        trim(line);

        if (i == 0 && line == "date | value")
            continue;
        
        // basic synthax check
        bool valid = true;

        for (size_t j = 0; j < line.size() && valid; j++) {
            if (j < 4 || j == 5 || j == 6 || j == 8 || j == 9) {    // digits
                if (!std::isdigit(line[j])) {
                    valid = false;
                    error(line, "Invalid date", i, j);
                }
            } else if (j == 4 || j == 7) {                          // dashes
                if (line[j] != '-') {
                    valid = false;
                    error(line, "Invalid format", i, j);
                }
            } else if (j == 10 || j == 12) {                        // spaces
                if (!std::isspace(line[j])) {
                    valid = false;
                    error(line, "Invalid format", i, j);
                }
            } else if (j == 11) {                                   // separator
                if (line[j] != '|') {
                    valid = false;
                    error(line, "Invalid format", i, j);
                }
            } else if (j > 12) {                          // value format
                if ((!std::isdigit(line[j])) && (line[j] != '.')) {
                    valid = false;
                    error(line, "Invalid value", i, j);
                }
            }
        }
        if (valid && line.size() < 14) {
            valid = false;
            error(line, "Missing data", i, line.size());
        }

        if (!valid)
            continue;
        
        // get date and value
        date = line.substr(0, 10);
        double value;

        ssize_t year = std::atoi(date.substr(0, 4).c_str()), month = std::atoi(date.substr(5, 2).c_str()), day = std::atoi(date.substr(8, 2).c_str());

        // 31 - 1 3 5 7 8 10 12
        // 30 - 4 6 9 11

        if (month > 12 || month == 0) {
            valid = false;
            error(line, "Invalid month", i, 5);
        } else if (day == 0 || day > 31 || (month == 2 && day > (28 + (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 1 : 0)))) {
            valid = false;
            error(line, "Invalid day", i, 8);
        } else if (day == 31 && ((month < 8 && !(month % 2)) || (month > 7 && month % 2))) {
            valid = false;
            error(line, "Invalid day", i, 8);
        } 
        
        else {
            char *tmp;
            value = std::strtod(line.substr(13).c_str(), &tmp);

            if (value > 1000) {
                valid = false;
                error(line, "Invalid value", i, 13);
            }
        }

        if (!valid)
            continue;

        double rate = getRate(date);

        std::cout << GREEN << date << BOLD_CYAN " ƒ(" BOLD_BLUE << value << BOLD_CYAN ") = " BOLD_BLUE << rate * value << std::endl;
    }
}

double Bitcoin::getRate(const std::string&date) const {
    std::map<std::string, double>::const_iterator it = _rates.lower_bound(date);
    
    if (it == _rates.end() || it->first != date)
    {
        if (it == _rates.begin())
            return 0;
        --it;
    }
    return it->second;
}

// XXXX-XX-XX | XXXX