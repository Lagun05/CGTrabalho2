#ifndef VETOR_3D_H
#define VETOR_3D_H

#include <cmath>
//#include "Ponto_3D.h"

class Ponto_3D;

//* classe Vetor_3D #Vetor_3D#
  //* Vetor tridimensional com valores x y z guardados em float
class Vetor_3D{
  private:
    float x, y, z;
  public:

 //* Construtores e Destrutor
    Vetor_3D() : x(0.0), y(0.0), z(0.0) {}
    Vetor_3D(const Vetor_3D& v) { x = v.X(); y = v.Y(); z = v.Z(); }
    Vetor_3D(const Ponto_3D& destino, const Ponto_3D& origem);
    Vetor_3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    ~Vetor_3D() {}

    Vetor_3D operator+(const Vetor_3D& v) const { return Vetor_3D(x+v.X(), y+v.Y(), z+v.Z()); }
    const Vetor_3D& operator+=(const Vetor_3D& v) { x+=v.X(); y+=v.Y(); z+=v.Z(); return *this; }
    Vetor_3D operator -(const Vetor_3D& v) const { return Vetor_3D(x-v.X(), y-v.Y(), z-v.Z()); }
    const Vetor_3D& operator-=(const Vetor_3D& v) { x-=v.X(); y-=v.Y(); z-=v.Z(); return *this; }
    Vetor_3D operator/(float f) const { return Vetor_3D(x/f, y/f, z/f); }
    const Vetor_3D& operator/=(float f) { x/=f; y/=f; z/=f; return *this; }
    Vetor_3D operator*(float f) const { return Vetor_3D(x*f, y*f, z*f); }
    const Vetor_3D& operator*=(float f) { x*=f; y*=f; z*=f; return *this; }
    void normaliza();
    inline float modulo(void) const { return sqrt(x*x + y*y + z*z); }
    float produtoEscalar(const Vetor_3D& outro)const;

    Vetor_3D operator*(const Vetor_3D& v)const { return Vetor_3D( y*v.Z() - z*v.Y(),  z*v.X() - x*v.Z(), x*v.Y() - y*v.X() );  }
 //* Funções inline que retornam os valores de x y z
    inline float X() const {  return(x); }
    inline float Y() const {  return(y); }
    inline float Z() const {  return(z); }
    void  setX(float _x) {  x = _x; }
    void  setY(float _y) {  y = _y; }
    void  setZ(float _z) {  z = _z; }
    Vetor_3D operator-()const { return Vetor_3D(-x, -y, -z); }
    const Vetor_3D& operator=(const Vetor_3D& e ) { x = e.X(); y = e.Y(); z = e.Z(); return *this; }

    Vetor_3D reflect(Vetor_3D incidet)const{
        return incidet - operator*(2*( produtoEscalar(incidet) ));
    }
};

#endif // VETOR_3D_H
