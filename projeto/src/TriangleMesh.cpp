#include "TriangleMesh.h"
#include "Esfera.h"
#include <QDebug>

Intersection TriangleMesh::Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold)
{
    Intersection intersection;

    Esfera esfera(0, getRaio(), getCentro()/*centro da malha de triângulos*/);
    if(esfera.Intercepta(r_vis, mode, threshold ).hasPositiveIntersection(threshold))
    {
        for(int i = 0; i < mesh.size(); ++i)
        {
            if(mode == First && intersection.hasPositiveIntersection(threshold) )
                return intersection;
            intersection  = Intersection::nearest(intersection, mesh[i]->Intercepta(r_vis, mode, threshold),threshold);
        }
    }

    return intersection;
}

TriangleMesh::TriangleMesh(PlyParser::iterator_st bit, PlyParser::iterator_st eit, int ind, float para[9] ): Objeto_3D(ind)
{
    float x,y,z;
    QVector<Vetor_3D> pontos;

    Ponto_3D v1,v2,v3;

    Vetor_3D v;
    Vetor_3D center(0,0,0);

    Triangulo *t;
    Triangulo tmp(0, Ponto_3D(), Ponto_3D(), Ponto_3D());

    if(bit != eit)
    {
        tmp = Triangulo(bit.getTriangulo());

        x = tmp.getVertice1().X() * para[0] + para[3];
        y = tmp.getVertice1().Y() * para[1] + para[4];
        z = tmp.getVertice1().Z() * para[2] + para[5];

        v1 = Ponto_3D(x,y,z);
        v = Vetor_3D(x,y,z);
        center = center + v;
        pontos.append(v);

        x = tmp.getVertice2().X() * para[0] + para[3];
        y = tmp.getVertice2().Y() * para[1] + para[4];
        z = tmp.getVertice2().Z() * para[2] + para[5];

        v2 = Ponto_3D(x,y,z);
        v = Vetor_3D(x,y,z);
        center = center + v;
        pontos.append(v);

        x = tmp.getVertice3().X() * para[0] + para[3];
        y = tmp.getVertice3().Y() * para[1] + para[4];
        z = tmp.getVertice3().Z() * para[2] + para[5];

        v3 = Ponto_3D(x,y,z);
        v = Vetor_3D(x,y,z);
        center = center + v;
        pontos.append(v);

        t = new Triangulo(tmp.getIndiceMaterial(), v1, v2, v3);

        t->setIndiceTextura(ind);
        t->refazArestas();

        mesh.push_back(t);
    }

    for(++bit; bit != eit; ++bit)
    {
        tmp = Triangulo(bit.getTriangulo());

        x = tmp.getVertice1().X() * para[0] + para[3];
        y = tmp.getVertice1().Y() * para[1] + para[4];
        z = tmp.getVertice1().Z() * para[2] + para[5];

        v1 = Ponto_3D(x,y,z);
        v = Vetor_3D(x,y,z);
        center = center + v;
        pontos.append(v);

        x = tmp.getVertice2().X() * para[0] + para[3];
        y = tmp.getVertice2().Y() * para[1] + para[4];
        z = tmp.getVertice2().Z() * para[2] + para[5];

        v2 = Ponto_3D(x,y,z);
        v = Vetor_3D(x,y,z);
        center = center + v;
        pontos.append(v);

        x = tmp.getVertice3().X() * para[0] + para[3];
        y = tmp.getVertice3().Y() * para[1] + para[4];
        z = tmp.getVertice3().Z() * para[2] + para[5];

        v3 = Ponto_3D(x,y,z);
        v = Vetor_3D(x,y,z);
        center = center + v;
        pontos.append(v);

        t = new Triangulo(tmp.getIndiceMaterial(), v1, v2, v3);

        t->setIndiceTextura(ind);

        t->refazArestas();

        mesh.push_back(t);
    }

    setCentro( Ponto_3D(0,0,0) + center * (1.0/pontos.size()) );

    float raio = 0;
    for(int i = 0; i < pontos.size(); ++i)
    {
        float f = centro.distancia( Ponto_3D(pontos[i]) );
        raio = f > raio ? f : raio;
    }

    setRaio( raio );

    for(int i = 0; i < mesh.size(); ++i)
    {
        mesh[i]->setCentro(this->getCentro());
        mesh[i]->setRaio(this->getRaio());
    }

    calculaCoordenadasTextura();
}
void TriangleMesh::calculaCoordenadasTextura()
{
    float phi, theta;
    Vetor_3D proj;
    TexturePoint tx;

    for(int i=0; i < mesh.size(); ++i)
    {
        //V1
        proj = ( mesh[i]->getVertice1() - centro);

        proj.normaliza();
        phi  = acosf(proj.Z());
        theta = acosf(proj.X()/sin(phi));

        tx = TexturePoint((phi/M_PI), ((theta)/M_PI));
        mesh[i]->setTexturePoint1(tx);

        //V2
        proj = ( mesh[i]->getVertice2() - centro);

        proj.normaliza();
        phi  = acosf(proj.Z());
        theta = acosf(proj.X()/sin(phi));

        tx = TexturePoint((phi/M_PI), ((theta)/M_PI));
        mesh[i]->setTexturePoint2(tx);

        //V3
        proj = ( mesh[i]->getVertice3() - centro);

        proj.normaliza();
        phi  = acosf(proj.Z());
        theta = acosf(proj.X()/sin(phi));

        tx = TexturePoint((phi/M_PI), ((theta)/M_PI));
        mesh[i]->setTexturePoint3(tx);

    }
}
