#ifndef ESFERA_H
#define ESFERA_H

#include "Objeto_3d.h"

//* classe Esfera #Esfera#
class Esfera : public Objeto_3D {

  public:
 //* Construtor e Destrutor
    Esfera( int _indice_textura, float _raio,const Ponto_3D& _centro );
    ~Esfera() {}
 //* interseção e Normal
    Intersection Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold) ;
    Vetor_3D normal( const Ponto_3D& ponto ) const ;
    TexturePoint pontoTextura(const Ponto_3D& ponto) const;
};
#endif // ESFERA_H
