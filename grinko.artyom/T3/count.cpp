#include "count.h"

#include <cmath>
#include <cassert>

#include <sstream>
#include <ios>
#include <iostream>
#include <algorithm>
#include <numeric>

#include "geometry.h"
#include "lib.h"

Count::Count(Type type, size_t numberOfVertices):
    type{type},
    numberOfVertices{numberOfVertices} {}

double_t Count::operator()(const std::vector<Polygon> &polygons) const {
    return std::count_if(
        std::begin(polygons),
        std::end(polygons),
        [this](const Polygon &polygon) {
            if (this->type == Type::NumberOfVertices) {
                return polygon.points.size() == this->numberOfVertices;
            }

            return polygon.points.size() % 2 == static_cast<size_t>(this->type);
       }
   );
}

std::istream &operator>>(std::istream &stream, Count &count) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        Count input{Count::Type::Even, 0};
        std::string type{};
        stream >> type;

        if (type == "EVEN") {
            input.type = Count::Type::Even;
        } else if (type == "ODD") {
            input.type = Count::Type::Odd;
        } else {
            if (!(std::stringstream{type} >> input.numberOfVertices)) {
                stream.setstate(std::ios::failbit);
            }
            
            input.type = Count::Type::NumberOfVertices;
        }

        if (stream) {
            count = std::move(input);
        }
    }

    return stream;
}
