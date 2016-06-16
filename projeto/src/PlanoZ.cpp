#include "PlanoZ.h"

Intersection PlanoZ::Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold)
{
  float x,y;

  float t = (a - r_vis.Z0()) / r_vis.Dz();

  Intersection lastIntersection;
  if (t<0)
     return lastIntersection;

  x = r_vis.X0() + t * r_vis.Dx();
  if (INSIDE(x,bmin,bmax))
  {
    y = r_vis.Y0() + t*r_vis.Dy();
    if (INSIDE(y,cmin,cmax))
    {
        lastIntersection.setValues(this, t);
        return lastIntersection;
    }
  }

  return lastIntersection;
}

TexturePoint PlanoZ::pontoTextura(const Ponto_3D& ponto) const
{
    return TexturePoint( (ponto.X() - bmin)/(bmax-bmin) ,
                         (ponto.Y() - cmin)/(cmax-cmin) );
}
