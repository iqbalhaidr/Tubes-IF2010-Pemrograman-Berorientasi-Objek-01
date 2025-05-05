#include "Image.hpp"

void Image::display(const std::string& filename) {
    std::ifstream file("pacatur.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }
}