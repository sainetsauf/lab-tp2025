#ifndef LibH
#define LibH

#include <cmath>

#include <functional>

#include "geometry.h"

template<typename T>
using fn = std::function<T>;

double_t shoelace(const Polygon &);

#endif
