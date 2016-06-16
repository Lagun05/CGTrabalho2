#include "PlanoY.h"

Intersection PlanoY::Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold)
{
  float x,z;

  float t = (a - r_vis.Y0()) / r_vis.Dy();

  Intersection lastIntersection;
  if ( t <0)
    return lastIntersection;

  x = r_vis.X0() +  t * r_vis.Dx();
  if (INSIDE(x,bmin,bmax))
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

TexturePoint PlanoY::pontoTextura(const Ponto_3D& ponto) const
{
    return TexturePoint( (ponto.X() - bmin)/(bmax-bmin) ,
                         (ponto.Z() - cmin)/(cmax-cmin) );
}
