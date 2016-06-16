#include "CaixaParalela.h"
#include "cenario.h"
#include <QDebug>

void CaixaParalela::configura(const Vetor_3D &_extremo_inferior, const Vetor_3D &_extremo_superior )
{
    float xmin, ymin, zmin, xmax, ymax, zmax;

    if(px1 != NULL) delete( px1 );
    if(px2 != NULL) delete( px2 );
    if(py1 != NULL) delete( py1 );
    if(py2 != NULL) delete( py2 );
    if(pz1 != NULL) delete( pz1 );
    if(pz2 != NULL) delete( pz2 );


    extremo_inferior = _extremo_inferior; // = _extremo_inferior);
    extremo_superior = _extremo_superior;
    xmin = extremo_inferior.X();
    ymin = extremo_inferior.Y();
    zmin = extremo_inferior.Z();
    xmax = extremo_superior.X();
    ymax = extremo_superior.Y();
    zmax = extremo_superior.Z();

    setCentro(Ponto_3D((xmin+xmax)/2, (ymin+ymax)/2, (zmin+zmax)/2));
    setRaio( centro.distancia(Ponto_3D(xmin,ymin,zmin)));

    px1 = new PlanoX( xmin,   ymin, ymax, zmin, zmax , indice_textura);
    px2 = new PlanoX( xmax,   ymin, ymax, zmin, zmax , indice_textura);

    py1 = new PlanoY( ymin,   xmin, xmax, zmin, zmax , indice_textura);
    py2 = new PlanoY( ymax,   xmin, xmax, zmin, zmax , indice_textura);

    pz1 = new PlanoZ( zmin,   xmin, xmax, ymin, ymax , indice_textura);
    pz2 = new PlanoZ( zmax,   xmin, xmax, ymin, ymax , indice_textura);
}

CaixaParalela::CaixaParalela( int _indice_textura,const Vetor_3D& _extremo_inferior,
                              const Vetor_3D& _extremo_superior ) : Objeto_3D ( _indice_textura )
{

    px1 = px2 = NULL;
    py1 = py2 = NULL;
    pz1 = pz2 = NULL;

    configura(_extremo_inferior, _extremo_superior);

}

CaixaParalela& CaixaParalela::operator=(const CaixaParalela &cx)
{
    this->setIndiceTextura(cx.getIndiceMaterial());

    px1 = px2 = NULL;
    py1 = py2 = NULL;
    pz1 = pz2 = NULL;

    configura(cx.getExtremo_inferior(), cx.getExtremo_superior());

    return *this;
}

CaixaParalela::~CaixaParalela()
{
    if(px1 != NULL) delete( px1 );
    if(px2 != NULL) delete( px2 );
    if(py1 != NULL) delete( py1 );
    if(py2 != NULL) delete( py2 );
    if(pz1 != NULL) delete( pz1 );
    if(pz2 != NULL) delete( pz2 );
}

// Chama a funcao Intercepta de cada um dos seis planos.
// Pega o menor t (maior que zero) entre todos.
Intersection CaixaParalela::Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold)
{
  Intersection time;
  Intersection lastIntersection;

  lastIntersection = px1->Intercepta( r_vis,mode,threshold);
  if(lastIntersection.hasPositiveIntersection(threshold) && mode == Objeto_3D::First)
  {
      return lastIntersection;
  }

  time = px2->Intercepta( r_vis,mode,threshold);
  if(time.hasPositiveIntersection(threshold) && mode == Objeto_3D::First)
  {
      lastIntersection = time;
      return lastIntersection;
  }
  else
  {
      lastIntersection = Intersection::nearest(lastIntersection, time, threshold);
  }

  time = py1->Intercepta( r_vis,mode,threshold);
  if(time.hasPositiveIntersection(threshold) && mode == Objeto_3D::First)
  {
      lastIntersection = time;
      return lastIntersection;
  }
  else
  {
      lastIntersection = Intersection::nearest(lastIntersection, time, threshold);
  }

  time = py2->Intercepta( r_vis,mode,threshold);
  if(time.hasPositiveIntersection(threshold) && mode == Objeto_3D::First)
  {
      lastIntersection = time;
      return lastIntersection;
  }
  else
  {
      lastIntersection = Intersection::nearest(lastIntersection, time, threshold);
  }

  time = pz1->Intercepta( r_vis,mode,threshold);
  if(time.hasPositiveIntersection(threshold) && mode == Objeto_3D::First)
  {
      lastIntersection = time;
      return lastIntersection;
  }else{
      lastIntersection = Intersection::nearest(lastIntersection, time, threshold);
  }

  time = pz2->Intercepta( r_vis,mode,threshold);
  if(time.hasPositiveIntersection(threshold) && mode == Objeto_3D::First)
  {
      lastIntersection = time;
      return lastIntersection;
  }else
  {
      lastIntersection = Intersection::nearest(lastIntersection, time, threshold);
  }

  return lastIntersection;

}
