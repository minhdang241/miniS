#include <iostream>
#include <string>


int main() {
    auto command = std::string();
    while (true) {
        std::cout << "simple> ";
        if (std::getline(std::cin, command)) {
            if (command == ".exit") {
                exit(EXIT_SUCCESS);
            } else {
                std::cout << "Invalid command: " << command << std::endl;
            }
        };
    }
}
