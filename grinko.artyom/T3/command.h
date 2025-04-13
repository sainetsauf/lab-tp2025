#ifndef CommandH
#define CommandH

#include <cmath>

#include <iostream>
#include <memory>
#include <vector>

#include "geometry.h"

struct Command {
    virtual double_t operator()(const std::vector<Polygon> &) const = 0;

    virtual ~Command() {}
};

std::istream &operator>>(std::istream &, std::unique_ptr<Command> &);

#endif
