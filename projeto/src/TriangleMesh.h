#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

//#include "CaixaParalela.h"
#include "Objeto_3d.h"
#include "Triangulo.h"
#include "Vetor_3d.h"
#include "PlyParser.h"
#include <QVector>

class TriangleMesh : public Objeto_3D
{
private:
    QVector<Triangulo*> mesh;

    void calculaCoordenadasTextura(void);
public:
    TriangleMesh(PlyParser::iterator_st bit, PlyParser::iterator_st eit, int ind, float param[9]);

    Vetor_3D normal( const Ponto_3D& ponto) const { ponto.X(); return Vetor_3D(); }
    Intersection Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold) ;
};

#endif // TRIANGLEMESH_H
