#ifndef GeometryH
#define GeometryH

#include <cstdint>

#include <iostream>
#include <vector>

struct Point {
    int32_t x = 0, y = 0;
};

struct Polygon {
    std::vector<Point> points{};
};

std::istream &operator>>(std::istream &, Polygon &);
std::ostream &operator<<(std::ostream &, const Polygon &);

#endif
