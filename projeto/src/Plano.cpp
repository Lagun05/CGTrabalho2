#include "Plano.h"

Plano::Plano( float _a, float _bmin, float _bmax, float _cmin, float _cmax, int ind)
    : Objeto_3D(ind), a(_a), bmin(_bmin), bmax(_bmax), cmin(_cmin), cmax(_cmax)
{
}

Plano::Plano( const Plano& p)
    : Objeto_3D(p), a(p.a), bmin(p.bmin), bmax(p.bmax), cmin(p.cmin), cmax(p.cmax)
{
}

Plano::~Plano()
{

}

float Plano::getA(void) const
{
    return a;
}
float Plano::getBmin(void) const
{
    return bmin;
}
float Plano::getBmax(void) const
{
    return bmax;
}
float Plano::getCmin(void) const
{
    return cmin;
}
float Plano::getCmax(void) const
{
    return cmax;
}
