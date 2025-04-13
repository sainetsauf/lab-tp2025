#ifndef MinH
#define MinH

#include <cmath>

#include <iostream>
#include <vector>

#include "command.h"
#include "geometry.h"

struct Min: public Command {
    enum class Type {
        Area,
        Vertices
    };

    Type type{};

    Min(Type type);

    double_t operator()(const std::vector<Polygon> &) const final override;
};

std::istream &operator>>(std::istream &, Min &);

#endif
