#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "Objeto_3d.h"
#include <QDebug>
#include "TexturePoint.h"

//* classe Triangulo #Triangulo#
class Triangulo : public Objeto_3D {
  private:
    Ponto_3D vert1, vert2, vert3;
    TexturePoint tx1, tx2, tx3;
    Vetor_3D aresta12, aresta23, aresta31;
    Vetor_3D vnormal;
    float area;

    Ponto_3D coordenadaBaricentrica(const Ponto_3D& ponto) const;
  public:
 //* Construtor e Destrutor

    Triangulo(const Triangulo& t);
    Triangulo( int _indice_textura, const Ponto_3D& v1, const Ponto_3D& v2, const Ponto_3D& v3 );
    ~Triangulo() {}
 //* interseção e Normal
    Intersection Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold) ;
    Vetor_3D normal( const Ponto_3D& ponto ) const { ponto.X(); return vnormal; }

    const Ponto_3D& getVertice1(void)const {return vert1; }
    const Ponto_3D& getVertice2(void)const {return vert2; }
    const Ponto_3D& getVertice3(void)const {return vert3; }

    void setVertice1(const Ponto_3D& vert) { vert1 = vert;}
    void setVertice2(const Ponto_3D& vert) { vert2 = vert;}
    void setVertice3(const Ponto_3D& vert) { vert3 = vert;}

    const TexturePoint& getTexturePoint1(void)const {return tx1; }
    const TexturePoint& getTexturePoint2(void)const {return tx2; }
    const TexturePoint& getTexturePoint3(void)const {return tx3; }

    void setTexturePoint1(const TexturePoint& tx) { tx1 = tx;}
    void setTexturePoint2(const TexturePoint& tx) { tx2 = tx;}
    void setTexturePoint3(const TexturePoint& tx) { tx3 = tx;}

    TexturePoint pontoTextura(const Ponto_3D& ponto) const;

    void refazArestas(void);

    Triangulo& operator=(const Triangulo& v);
};

#endif // TRIANGULO_H
