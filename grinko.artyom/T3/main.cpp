#include <cstdint>
#include <cstdlib>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <utility>
#include <vector>

#include "command.h"
#include "geometry.h"

int32_t main(int32_t argc, char **argv) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    std::ifstream file{argv[1]};
    if (!file) {
        return EXIT_FAILURE;
    }

    std::vector<Polygon> polygons{};

    while (!file.eof()) {
        std::copy(std::istream_iterator<Polygon>{file},
                  std::istream_iterator<Polygon>{},
                  std::back_inserter(polygons));

        if (!file) {
            file.clear();
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    while (!std::cin.eof()) {
        std::unique_ptr<Command> command{};
        std::cin >> command;

        if (!std::cin) {
            if (!std::cin.eof()) {
                std::cerr << "<INVALID COMMAND>" << std::endl;
            } else {
                continue;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (command != nullptr) {
            std::cout << (*command)(polygons) << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
