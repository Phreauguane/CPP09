#include "RPN.h"

int main(int ac, char **av) {
    try {
        if (ac != 2) throw std::runtime_error("Error");
        RPN rpn(av[1]);
        ssize_t value = rpn.evaluate();
        std::cout << value << std::endl;
    } catch (const std::exception&) {
        std::cout << "Error" << std::endl;
    }
    return 0;
}