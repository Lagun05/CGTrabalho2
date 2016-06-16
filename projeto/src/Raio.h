#ifndef RAIO_H
#define RAIO_H

#include "Ponto_3D.h"
#include "Vetor_3d.h"

//* classe Raio #Raio#
  //* Contem 3 vetores tridimensionais
class Raio{
  private:
    Ponto_3D origem, destino;
    Vetor_3D direcao;
  public:
 //* Construtores e Destrutor
    Raio();
    Raio(const Ponto_3D& _origem,const Ponto_3D& _destino);
    Raio(const Raio& r) { origem = r.Origem(); destino = r.Destino(); direcao = Vetor_3D(destino,origem); }
    ~Raio() {}
 //* Funções inline que retornam informações do Raio
    const Ponto_3D& Origem() const {return origem;}
    const Ponto_3D& Destino() const {return destino;}
    const Vetor_3D& Direcao() const {return direcao;}
    inline float    Dx()  const    {return direcao.X();}
    inline float    Dy()  const    {return direcao.Y();}
    inline float    Dz()  const    {return direcao.Z();}
    inline float    X0()  const    {return origem.X();}
    inline float    Y0()  const    {return origem.Y();}
    inline float    Z0()  const    {return origem.Z();}
 //* QualPonto retorna o ponto x y z para um t da função paramétrica
    Ponto_3D QualPonto(float t) const;
};

#endif // RAIO_H
