#include "area.h"

#include <cmath>
#include <cassert>

#include <sstream>
#include <ios>
#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>

#include "geometry.h"
#include "lib.h"

Area::Area(Type type, size_t numberOfVertices):
    type{type},
    numberOfVertices{numberOfVertices} {}

double_t Area::operator()(const std::vector<Polygon> &polygons) const {
    using namespace std::placeholders;

    std::vector<double_t> areas{};

    fn<void(fn<double_t(const Polygon &)>)> transformPolygons = std::bind(
        std::transform<
            std::vector<Polygon>::const_iterator,
            std::back_insert_iterator<std::vector<double_t>>,
            fn<double_t(const Polygon &)>
        >,
        std::begin(polygons),
        std::end(polygons),
        std::back_inserter(areas),
        _1
    );

    switch (this->type) {
    case Type::Even:
    case Type::Odd:
        transformPolygons([this](const Polygon &polygon) {
            if (polygon.points.size() % 2 == static_cast<size_t>(this->type)) {
                return shoelace(polygon);
            }

            return 0.0;
        });

        break;

    case Type::Mean:
        transformPolygons([this](const Polygon &polygon) {
            return shoelace(polygon);
        });

        break;

    case Type::NumberOfVertices:
        transformPolygons([this](const Polygon &polygon) {
            if (polygon.points.size() == this->numberOfVertices) {
                return shoelace(polygon);
            }

            return 0.0;
        });

        break;

    default:
        assert(false && "You're not supposed to get here.");

        break;
    }

    double_t result = std::accumulate(std::begin(areas), std::end(areas), 0.0);
    if (this->type == Type::Mean) {
        result /= polygons.size();
    }

    return result;
}

std::istream &operator>>(std::istream &stream, Area &area) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        Area input{Area::Type::Even, 0};
        std::string type{};
        stream >> type;

        if (type == "EVEN") {
            input.type = Area::Type::Even;
        } else if (type == "ODD") {
            input.type = Area::Type::Odd;
        } else if (type == "MEAN") {
            input.type = Area::Type::Mean;
        } else {
            if (!(std::stringstream{type} >> input.numberOfVertices)) {
                stream.setstate(std::ios::failbit);
            }

            input.type = Area::Type::NumberOfVertices;
        }

        if (stream) {
            area = std::move(input);
        }
    }

    return stream;
}
