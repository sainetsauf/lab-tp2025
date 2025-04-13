#include "geometry.h"

#include <ios>
#include <iostream>
#include <iterator>
#include <utility>

struct Delimiter {
    char expected = '\0';
};

std::istream &operator>>(std::istream &stream, const Delimiter &&delimiter) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        char expected = '\0';
        stream >> expected;

        if (!stream || expected != delimiter.expected) {
            stream.setstate(std::ios::failbit);
        }
    }

    return stream;
}

std::istream &operator>>(std::istream &stream, Point &point) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        Point input{};
        stream >> Delimiter{'('}
               >> input.x
               >> Delimiter{';'}
               >> input.y
               >> Delimiter{')'};

        if (stream) {
            point = std::move(input);
        }
    }

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Point &point) {
    std::ostream::sentry sentry{stream};
    if (sentry) {
        stream << '(' << point.x << ';' << point.y << ')';
    }

    return stream;
}

std::istream &operator>>(std::istream &stream, Polygon &polygon) {
    std::istream::sentry sentry{stream};
    if (sentry) {
        Polygon input{};
        size_t size = 0;
        stream >> size;
        if (!stream || size < 3) {
            stream.setstate(std::ios::failbit);

            return stream;
        }

        do {
            Point inputPrime{};
            stream >> inputPrime;
            if (!stream) {
                break;
            }
            input.points.push_back(inputPrime);
            --size;
        } while (size != 0);

        if (stream) {
            polygon = std::move(input);
        }
    }

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Polygon &polygon) {
    std::ostream::sentry sentry{stream};
    if (sentry) {
        stream << polygon.points.size() << ' ';
        std::copy(
            std::begin(polygon.points),
            std::end(polygon.points),
            std::ostream_iterator<Point>{stream, " "}
        );
    }

    return stream;
}
