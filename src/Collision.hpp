#pragma once
#include <SDL3/SDL.h>
#include "Vector2.hpp"
#include <algorithm>
#include <cmath>

inline bool checkAABB(const SDL_FRect &a, const SDL_FRect &b)
{
    return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}

inline bool checkCircle(const Vector2 &centerA, float radiusA, const Vector2 &centerB, float radiusB)
{
    // dists from each other
    float dx = centerA.x - centerB.x;
    float dy = centerA.y - centerB.y;
    float distanceSquared = (dx * dx) + (dy * dy);
    float radiusSums = radiusA + radiusB;

    // sqrt = $$$, squared dist = $
    return distanceSquared < (radiusSums * radiusSums);
}

inline bool checkAABBCicle(const SDL_FRect &rect, const Vector2 &circleCenter, float circleRadius)
{
    float closestX = std::max(rect.x, std::min(circleCenter.x, rect.x + rect.w));
    float closestY = std::max(rect.y, std::min(circleCenter.y, rect.y + rect.h));

    // dist form closest point to center of circle
    float dx = circleCenter.x - closestX;
    float dy = circleCenter.y - closestY;
    float distanceSquared = (dx * dx) + (dy * dy);

    return distanceSquared < (circleRadius * circleRadius);
}