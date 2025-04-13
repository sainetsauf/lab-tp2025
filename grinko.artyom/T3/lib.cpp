#include "lib.h"

#include <cmath>

#include "geometry.h"

double_t shoelace(const Polygon &polygon, size_t index) {
    if (index == polygon.points.size() - 1) {
        return 0;
    }
    
    return
        (polygon.points[index].x * polygon.points[index + 1].y
            - polygon.points[index + 1].x * polygon.points[index].y)
         + shoelace(polygon, index + 1);
}

double_t shoelace(const Polygon &polygon) {
    return std::abs(shoelace(polygon, 0)) / 2;
}
