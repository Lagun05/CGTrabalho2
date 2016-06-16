//* Módulo : material.hpp
//
// _Desc_   : Declara classe Material.
// _Autor_: Rodrigo P. R. de Toledo

#ifndef __MATERIAL_HPP
#define __MATERIAL_HPP

#include "Cor_rgb.h"
#include "TexturePoint.h"
#include "Objeto_3d.h"
#include <QImage>
#include <QRgb>

class Material{
  private:
    Cor_rgb ambiente, cor_difusa, indice_especular;
    int n_especular;
    float coeficiente_reflexao, indice_refracao, indice_opacidade;
    QImage textura;
    bool temTextura;

  public:
  
    Material(const Cor_rgb& _ambiente, const Cor_rgb& _cor_difusa, const Cor_rgb& _indice_especular,
             int _n_especular, float _coeficiente_reflexao,
             float _indice_refracao, float _indice_opacidade, const QImage& img = QImage() , bool tt = false);
    virtual ~Material() {}
 
    const Cor_rgb& Ambiente() const;
    const Cor_rgb& Cor_difusa() const;
    const Cor_rgb& Indice_especular()const;
    bool hasTexture()const;
    Cor_rgb getCorFromTexture(TexturePoint tp) const;
    inline int N_especular() {return n_especular;}
    inline float Coeficiente_reflexao() {return coeficiente_reflexao;}
    inline float Indice_refracao() {return indice_refracao; }
    inline float Indice_Opacidade() { return indice_opacidade; }

};

#endif
