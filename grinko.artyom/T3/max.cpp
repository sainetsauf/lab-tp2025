#include "max.h"

#include <cmath>
#include <cassert>

#include <algorithm>
#include <functional>
#include <ios>
#include <iostream>
#include <string>
#include <utility>

#include "geometry.h"
#include "lib.h"

Max::Max(Type type): type{type} {}

double_t Max::operator()(const std::vector<Polygon> &polygons) const {
    using namespace std::placeholders;

    std::vector<double_t> matched{};

    fn<void(fn<double_t(const Polygon &)>)> transformPolygons = std::bind(
        std::transform<
            std::vector<Polygon>::const_iterator,
            std::back_insert_iterator<std::vector<double_t>>,
            fn<double_t(const Polygon &)>
        >,
        std::begin(polygons),
        std::end(polygons),
        std::back_inserter(matched),
        _1
    );

    switch (this->type) {
    case Type::Area:
        transformPolygons([this](const Polygon &polygon) {
            return shoelace(polygon);
        });

        break;

    case Type::Vertices:
        transformPolygons([](const Polygon &polygon) {
            return static_cast<double_t>(polygon.points.size());
        });

        break;

    default:
        assert(false && "You're not supposed to get here.");

        break;
    }

    return *std::max_element(std::begin(matched), std::end(matched));
}

std::istream &operator>>(std::istream &stream, Max &max) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        Max input{Max::Type::Area};
        std::string type{};
        stream >> type;

        if (type == "AREA") {
            input.type = Max::Type::Area;
        } else if (type == "VERTICES") {
            input.type = Max::Type::Vertices;
        } else {
            stream.setstate(std::ios::failbit);
        }

        if (stream) {
            max = std::move(input);
        }
    }

    return stream;
}
