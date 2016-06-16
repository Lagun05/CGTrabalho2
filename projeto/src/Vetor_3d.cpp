#include "Vetor_3d.h"
#include "Ponto_3D.h"

#include <cmath>

Vetor_3D::Vetor_3D(const Ponto_3D& destino, const Ponto_3D& origem)
{
    x = destino.X() - origem.X();
    y = destino.Y() - origem.Y();
    z = destino.Z() - origem.Z();
}

//divide cada componente pelo comprimento.
void Vetor_3D::normaliza()
{
  float aux;
  aux = modulo();
  x = x/aux;
  y = y/aux;
  z = z/aux;
}

//valor retornado em radianos.
float Vetor_3D::produtoEscalar(const Vetor_3D& outro)const
{
  return ( x*outro.X() +  y*outro.Y() + z*outro.Z() );
}
