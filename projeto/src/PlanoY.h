#ifndef PLANOY_H
#define PLANOY_H

#include "Plano.h"

//* classe PlanoY #PlanoY#
  //* Este plano é perpendicular ao eixo Y
class PlanoY : public Plano {
  public:
 //* Construtor e Destrutor
    PlanoY( float _y, float _xmin, float _xmax, float _zmin, float _zmax, int ind ) :
        Plano(  _y,  _xmin,  _xmax,  _zmin,  _zmax, ind ) {}
    ~PlanoY() {}
 //* interseção
    //float Intercepta( Raio r_vis )const;
    Intersection Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold) ;
    Vetor_3D normal( const Ponto_3D& ponto ) const { ponto.X(); return Vetor_3D(0,1,0); }
    TexturePoint pontoTextura(const Ponto_3D& ponto) const;
};

#endif // PLANOY_H
