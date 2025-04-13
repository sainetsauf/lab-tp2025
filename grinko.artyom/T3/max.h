#ifndef MaxH
#define MaxH

#include <cmath>

#include <iostream>
#include <vector>

#include "command.h"
#include "geometry.h"

struct Max: public Command {
    enum class Type {
        Area,
        Vertices
    };

    Type type{};

    Max(Type type);

    double_t operator()(const std::vector<Polygon> &) const final override;
};

std::istream &operator>>(std::istream &, Max &);

#endif
