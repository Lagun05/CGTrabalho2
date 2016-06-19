#include "Cilindro.h"
#include <cmath>

Cilindro::Cilindro(int _indice_textura, float _raio, float _altura, const Ponto_3D& _centro) : Objeto_3D ( _indice_textura )
{
  raio = _raio;
  altura = _altura;
  centro =  _centro;
}


Intersection Cilindro::Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold)
{
  float a, b, c, delta;
  Intersection intersection;  

  // valores intermediários
  Vetor_3D K = Vetor_3D(r_vis.X0() - centro.X(),
                        r_vis.Y0() - centro.Y(),
                        r_vis.Z0() - centro.Z());


  // montando a equação do 2º grau at2 + bt + c = 0
  // equação para o cilindro:
  a = pow(r_vis.Direcao().X(), 2) + pow(r_vis.Direcao().Z(), 2);
  b = 2*((r_vis.Direcao().X() * K.X()) + (r_vis.Direcao().Z() * K.Z()));
  c = pow(K.X(), 2) + pow(K.Z(), 2) - raio*raio;

  delta = b*b - 4*a*c;
  if (delta >= 0) {

      float t_plus = (-b + sqrt(delta)) /(2*a);
      float t_minus = (-b - sqrt(delta)) /(2*a);

      Ponto_3D p_plus( r_vis.Origem().X() + r_vis.Direcao().X()*t_plus ,
                       r_vis.Origem().Y() + r_vis.Direcao().Y()*t_plus ,
                       r_vis.Origem().Z() + r_vis.Direcao().Z()*t_plus );

      Ponto_3D p_minus( r_vis.Origem().X() + r_vis.Direcao().X()*t_minus ,
                        r_vis.Origem().Y() + r_vis.Direcao().Y()*t_minus ,
                        r_vis.Origem().Z() + r_vis.Direcao().Z()*t_minus );

      bool p_plus_dentro_do_intervalo = false;
      bool p_minus_dentro_do_intervalo = false;

      if ((p_plus.Y() < (centro.Y() + altura/2.0)) && (p_minus.Y() > (centro.Y() - altura/2.0)))
          p_plus_dentro_do_intervalo = true;
      if ((p_minus.Y() < (centro.Y() + altura/2.0)) && (p_minus.Y() > (centro.Y() - altura/2.0)))
          p_minus_dentro_do_intervalo = true;

      if (p_plus_dentro_do_intervalo && p_minus_dentro_do_intervalo){
          intersection = Intersection::nearest(
                      Intersection(this, t_plus),
                      Intersection(this, t_minus), threshold);
      } else if (p_plus_dentro_do_intervalo){
          intersection.setValues(this, t_plus);
      } else if (p_minus_dentro_do_intervalo){
          intersection.setValues(this, t_minus);
      }
  }
  return intersection;
}

Vetor_3D Cilindro::normal( const Ponto_3D& ponto ) const
{
    Vetor_3D tmp;

    tmp.setX(ponto.X() - centro.X());
    tmp.setY(0);
    tmp.setZ(ponto.Z() - centro.Z());

    tmp.normaliza();

    return tmp;
}

TexturePoint Cilindro::pontoTextura(const Ponto_3D& ponto) const
{
    float phi, theta;
    Vetor_3D tmp;

    tmp.setX(ponto.X() - centro.X());
    tmp.setY(0);
    tmp.setZ(ponto.Z() - centro.Z());

    tmp.normaliza();

    phi  = acosf(tmp.Z());
    theta = acosf(tmp.X()/sin(phi));

    return TexturePoint((phi/M_PI), theta/M_PI);
}
