#ifndef CountH
#define CountH

#include <cmath>
#include <cstddef>

#include <iostream>
#include <vector>

#include "command.h"
#include "geometry.h"

struct Count: public Command {
    enum class Type {
        Even,
        Odd,
        NumberOfVertices,
    };

    Type type{};
    size_t numberOfVertices = 0;

    Count(Type, size_t);
    
    double_t operator()(const std::vector<Polygon> &) const final override;
};

std::istream &operator>>(std::istream &, Count &);

#endif
