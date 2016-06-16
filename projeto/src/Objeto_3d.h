#ifndef OBJETO_3D_H
#define OBJETO_3D_H

#include "Raio.h"
#include "Vetor_3d.h"
#include "TexturePoint.h"
#include "intersection.h"
#include <cmath>
#include <QDebug>
#include <QtAlgorithms>

#define SQR(X) (X*X)
#define MINI(x,y) (x<y?x:y)
#define MAXI(x,y) (x>y?x:y)
#define ZERO 0.0001

//* classe Objeto_3D #Objeto_3D#
  //* Esta classe e mae das classes Esfera, CaixaParalela e Triangulo.
class Objeto_3D {
  protected:
    int indice_textura;
    Ponto_3D centro;
    float raio;
 public:
    enum IntersectionMode{
        Nearest,
        First
    };
 //* Construtor e Destrutor
    Objeto_3D(int _indice_textura);
    Objeto_3D(const Objeto_3D& obj);
    virtual ~Objeto_3D();

    Vetor_3D normal( const Ponto_3D& ponto, const Vetor_3D & d_vis) const;

 //* Funcoes puras virtuais para serem implementadas pelos herdeiros
    virtual Intersection Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold) = 0;
    virtual Vetor_3D normal( const Ponto_3D& ponto) const  = 0;

    //* Funcoes virtuais que podem ser reimplementadas pelos herdeiros
    virtual int getIndiceMaterial() const;
    virtual float getRaio() const;
    virtual const Ponto_3D& getCentro() const;
    virtual void setCentro(const Ponto_3D& _centro);
    virtual void setIndiceTextura(int indice);
    virtual void setRaio(float _raio);
    virtual TexturePoint pontoTextura(const Ponto_3D& ponto) const;
};

#endif // OBJETO_3D_H
