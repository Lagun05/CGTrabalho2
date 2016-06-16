#include <stdio.h>
#include "material.h"

Material::Material(const Cor_rgb& _ambiente,const Cor_rgb& _cor_difusa,
                   const Cor_rgb& _indice_especular, int _n_especular, float _coeficiente_reflexao,
                   float _indice_refracao, float _indice_opacidade , const QImage& tx, bool tt) :
ambiente(_ambiente), cor_difusa(_cor_difusa), indice_especular(_indice_especular), n_especular(_n_especular),
coeficiente_reflexao(_coeficiente_reflexao), indice_refracao(_indice_refracao), indice_opacidade(_indice_opacidade),
textura(tx), temTextura(tt) { }

const Cor_rgb& Material::Ambiente() const
{
    return ambiente;
}

bool Material::hasTexture()const
{
    return temTextura;
}

const Cor_rgb& Material::Cor_difusa()const
{
    return cor_difusa;
}

const Cor_rgb& Material::Indice_especular()const
{
    return indice_especular;
}

Cor_rgb Material::getCorFromTexture(TexturePoint tp)const
{
        int x,y;

        x = qRound(tp.U() * textura.width());
        y = qRound(tp.V() * textura.height());

        if(x >= textura.width())
            x = textura.width()-1;
        if(y >= textura.height())
            y = textura.height()-1;

        return textura.pixel(x, y);
}
