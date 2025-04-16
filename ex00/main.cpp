#include "BitcoinExchange.h"

int main(int ac, char **av) {
    try {
        if (ac != 2)
            throw std::runtime_error(" Bad arguments");
        Bitcoin btc("data.csv");
        btc.loadfile(std::string(av[1]));
    } catch (const std::exception&e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}