#include "TexturePoint.h"

TexturePoint::TexturePoint() : u(0), v(0)
{
}
TexturePoint::TexturePoint(float _u, float _v) : u(_u), v(_v)
{
    if(_u < 0.0 )
        u = 0.0;
    else if(_u > 1.0)
        u = 1.0;
    else
        u = _u;

    if(_v < 0.0 )
        v = 0.0;
    else if(_v > 1.0)
        v = 1.0;
    else
        v = _v;

}
TexturePoint::TexturePoint(const TexturePoint& p) : u(p.u), v(p.v)
{
}

float TexturePoint::U() const
{
    return u;
}

float TexturePoint::V() const
{
    return v;
}

void TexturePoint::U(float _u)
{
    if(_u < 0.0 )
        u = 0.0;
    else if(_u > 1.0)
        u = 1.0;
    else
        u = _u;
}

void TexturePoint::V(float _v)
{
    if(_v < 0.0 )
        v = 0.0;
    else if(_v > 1.0)
        v = 1.0;
    else
        v = _v;
}

const TexturePoint& TexturePoint::operator=(const TexturePoint& p)
{
    u = p.u;
    v = p.v;
    return *this;
}
