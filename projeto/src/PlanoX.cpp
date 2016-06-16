#include "PlanoX.h"

Intersection PlanoX::Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold)
{
  float y,z;

  //calcula-se o t da interseção do raio com o plano
  float t = (a - r_vis.X0()) / r_vis.Dx();

  Intersection lastIntersection;
  if (t<0)
      return lastIntersection;

  //se o t for maior que zero, verifica-se o ponto de interseção está
  //entre os limites que definem o segmento de plano
  y = r_vis.Y0() + t * r_vis.Dy();
  if (INSIDE(y,bmin,bmax))
  {
    z = r_vis.Z0() + t *r_vis.Dz();
    if (INSIDE(z,cmin,cmax))
    {
        lastIntersection.setValues(this, t);
      return lastIntersection;
    }
  }
  return lastIntersection;
}

Vetor_3D PlanoX::normal( const Ponto_3D& ponto) const {
    ponto.X();
    return Vetor_3D(1,0,0);
}

TexturePoint PlanoX::pontoTextura(const Ponto_3D& ponto) const
{
    return TexturePoint( (ponto.Y() - bmin)/(bmax-bmin) ,
                         (ponto.Z() - cmin)/(cmax-cmin) );
}
