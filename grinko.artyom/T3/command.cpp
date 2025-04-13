#include "command.h"

#include <new>
#include <ios>
#include <iostream>
#include <iomanip>
#include <string>
#include <memory>

#include "geometry.h"
#include "area.h"
#include "max.h"
#include "min.h"
#include "count.h"

std::istream &operator>>(std::istream &stream, std::unique_ptr<Command> &command) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        std::string input{};
        stream >> input;
        if (!stream) {
            return stream;
        }

        if (input == "AREA") {
            Area area{Area::Type::Even, 0};
            stream >> area;

            if (stream) {
                command = std::unique_ptr<Command>(new(std::nothrow) Area{area});
            }
        } else if (input == "MAX") {
            Max max{Max::Type::Area};
            stream >> max;

            if (stream) {
                command = std::unique_ptr<Command>(new(std::nothrow) Max{max});
            }
        } else if (input == "MIN") {
            Min min{Min::Type::Area};
            stream >> min;

            if (stream) {
                command = std::unique_ptr<Command>(new(std::nothrow) Min{min});
            }
        } else if (input == "COUNT") {
            Count count{Count::Type::Even, 0};
            stream >> count;

            if (stream) {
                command = std::unique_ptr<Command>(new(std::nothrow) Count{count});
            }
        } else {
            stream.setstate(std::ios::failbit);
        }
    }

    return stream;
}
