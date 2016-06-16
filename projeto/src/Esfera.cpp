#include "Esfera.h"
#include <cmath>

Esfera::Esfera(int _indice_textura, float _raio, const Ponto_3D& _centro) : Objeto_3D ( _indice_textura )
{
  raio = _raio;
  centro =  _centro;
}


//Foley capítulo 15.10, fórmula 15.17
Intersection Esfera::Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold)
{
  float a, b, c, delta;
  Intersection intersection;

  // valores intermediários
  Vetor_3D K = Vetor_3D(r_vis.X0() - centro.X(),
                        r_vis.Y0() - centro.Y(),
                        r_vis.Z0() - centro.Z());


  // montando a equação do 2º grau at2 + bt + c = 0
  a = r_vis.Direcao().produtoEscalar(r_vis.Direcao());
  b = 2*(r_vis.Direcao().produtoEscalar( K ));
  c = K.produtoEscalar(K) - raio*raio;

  delta = b*b - 4*a*c;
  if (delta >= 0) {

      intersection = Intersection::nearest(
                  Intersection(this, (-b - sqrt(delta)) /(2*a)),
                  Intersection(this, (-b + sqrt(delta)) /(2*a)), threshold);
  }

  return intersection;
}

Vetor_3D Esfera::normal( const Ponto_3D& ponto ) const
{
    Vetor_3D tmp;

    tmp = ponto - centro;
    tmp.normaliza();

    return tmp;
}

TexturePoint Esfera::pontoTextura(const Ponto_3D& ponto) const
{
    float phi, theta;
    Vetor_3D tmp(ponto - centro);

    tmp.normaliza();

    phi  = acosf(tmp.Z());
    theta = acosf(tmp.X()/sin(phi));

    return TexturePoint((phi/M_PI), ((theta)/M_PI));
}
