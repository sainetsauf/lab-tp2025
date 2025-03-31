#include "DataStruct.h"
#include <cassert>
#include <iterator>
#include <vector>
#include <algorithm>

int main()
{
    using nspace::DataStruct;

    std::vector< DataStruct > data;

    while (!std::cin.eof()) {
        std::copy(
            std::istream_iterator< DataStruct >(std::cin),
            std::istream_iterator< DataStruct >(),
            std::back_inserter(data)
        );
        if (std::cin.fail()) {
            std::cin.clear();
            char c = '\0';
            while (std::cin.get(c) && c != '\n') {}
        }
    }

    std::sort(data.begin(), data.end());

    std::cout << "Data:\n";
    std::copy(
        std::begin(data),
        std::end(data),
        std::ostream_iterator< DataStruct >(std::cout, "\n")
    );

    return 0;
}