#pragma once

namespace kx
{

struct Texel
{
    int x; // x-coordinate of texel's top-left corner
    int y; // y-coordinate of texel's top-left corner

    Texel ()
        : x(0), y(0) {}

    Texel (int x, int y)
        : x(x), y(y) {}
};

} // namespace kx
