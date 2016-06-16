#ifndef PLANOZ_H
#define PLANOZ_H

#include "Plano.h"

//* classe PlanoZ #PlanoZ#
  //* Este plano é perpendicular ao eixo Z
class PlanoZ : public Plano {
  public:
 //* Construtor e Destrutor
    PlanoZ( float _z, float _xmin, float _xmax, float _ymin, float _ymax, int ind ) :
        Plano(  _z,  _xmin,  _xmax,  _ymin,  _ymax, ind ) {}
    ~PlanoZ() {}
 //* interseção
    //float Intercepta( Raio r_vis )const;
    Intersection Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold) ;
    Vetor_3D normal( const Ponto_3D& ponto ) const { ponto.X(); return Vetor_3D(0,0,1); }
    TexturePoint pontoTextura(const Ponto_3D& ponto) const;
};

#endif // PLANOZ_H
