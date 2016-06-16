#ifndef PLANOX_H
#define PLANOX_H

#include "Plano.h"

//* classe PlanoX #PlanoX#
  //* Este plano é perpendicular ao eixo X
class PlanoX : public Plano {
  public:
 //* Construtor e Destrutor
    PlanoX( float _x, float _ymin, float _ymax, float _zmin, float _zmax, int ind ) :
        Plano( _x,  _ymin,  _ymax,  _zmin,  _zmax, ind ) {}
    ~PlanoX() {}
 //* interseção
    Intersection Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold) ;
    Vetor_3D normal( const Ponto_3D& ponto ) const;
    TexturePoint pontoTextura(const Ponto_3D& ponto) const;
};

#endif // PLANOX_H
