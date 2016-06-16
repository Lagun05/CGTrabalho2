#ifndef CAIXAPARALELA_H
#define CAIXAPARALELA_H

#include <Qt>
#include "Objeto_3d.h"
#include "PlanoX.h"
#include "PlanoY.h"
#include "PlanoZ.h"

#define PROXIMO(a,b) ((a-b<ZERO)&&(a-b>-ZERO))

//* classe CaixaParalela #CaixaParalela#
  //* A CaixaParalela tem 6 planos, contidos dois a dois nos planos:xy, xz, yz.
class CaixaParalela : public Objeto_3D {
  private:
    Vetor_3D extremo_inferior, extremo_superior; //pontos que limitam a caixa
    PlanoX *px1, *px2;
    PlanoY *py1, *py2;
    PlanoZ *pz1, *pz2;

    void configura(const Vetor_3D & _extremo_inferior, const Vetor_3D & _extremo_superior );

  public:

 //* Construtor e Destrutor

    CaixaParalela( int _indice_textura,const Vetor_3D& _extremo_inferior,
                   const Vetor_3D& _extremo_superior );

    CaixaParalela() : Objeto_3D(-1) { px1 = px2 = NULL;
                                      py1 = py2 = NULL;
                                      pz1 = pz2 = NULL;}

    CaixaParalela( const CaixaParalela &cx) : Objeto_3D(cx) { *this = cx; }

    ~CaixaParalela();
 //* interseção e Normal
    Intersection Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold);
    Vetor_3D normal( const Ponto_3D& ponto ) const { ponto.X(); return Vetor_3D(0.0,0.0,0.0); }

    const Vetor_3D& getExtremo_inferior(void) const {return extremo_inferior; }
    const Vetor_3D& getExtremo_superior(void) const {return extremo_superior; }

    CaixaParalela& operator=(const CaixaParalela &cx);
};

#endif // CAIXAPARALELA_H
