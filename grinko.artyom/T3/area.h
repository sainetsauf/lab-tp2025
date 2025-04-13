#ifndef AreaH
#define AreaH

#include <cmath>
#include <cstddef>

#include <iostream>
#include <vector>

#include "command.h"
#include "geometry.h"

struct Area: public Command {
    enum class Type {
        Even,
        Odd,
        Mean,
        NumberOfVertices,
    };

    Type type{};
    size_t numberOfVertices = 0;

    Area(Type, size_t);

    double_t operator()(const std::vector<Polygon> &) const final override;
};

std::istream &operator>>(std::istream &, Area &);

#endif
