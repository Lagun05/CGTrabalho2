#ifndef PONTO_3D_H
#define PONTO_3D_H

#include "Vetor_3d.h"

class Ponto_3D
{
private:
    float x, y, z;
public:
    Ponto_3D() : x(0), y(0), z(0) { }
    Ponto_3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
    Ponto_3D(const Ponto_3D& p) : x(p.X()), y(p.Y()), z(p.Z()) { }
    Ponto_3D(const Vetor_3D& v) : x(v.X()), y(v.Y()), z(v.Z()) {}

    float X() const { return x; }
    float Y() const { return y; }
    float Z() const { return z; }

    void X(float _x) { x = _x; }
    void Y(float _y) { y = _y; }
    void Z(float _z) { z = _z; }

    float distancia(const Ponto_3D& p) const { return sqrt(((x-p.X())*((x-p.X())))+((y-p.Y())*(y-p.Y()))+((z-p.Z())*(z-p.Z()))); }
    const Ponto_3D& operator=(const Ponto_3D& p) {x = p.X(); y = p.Y(); z = p.Z(); return *this; }
    Ponto_3D operator+(const Vetor_3D& v) { return Ponto_3D(x+v.X(), y+v.Y(), z+v.Z()); }
    const Ponto_3D& operator+=(const Vetor_3D& v) { x+=v.X(); y+=v.Y(); z+=v.Z(); return *this; }
    Vetor_3D operator-(const Ponto_3D& p)const{ return Vetor_3D(x-p.X(), y-p.Y(), z-p.Z()); }
    Ponto_3D operator-()const { return Ponto_3D(-x,-y,-z); }

};

#endif // PONTO_3D_H
