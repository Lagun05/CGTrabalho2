#include "Objeto_3d.h"

Objeto_3D::Objeto_3D(int _indice_textura) :
    indice_textura( _indice_textura )
{

}

Objeto_3D::Objeto_3D(const Objeto_3D& obj) :
    indice_textura( obj.getIndiceMaterial() ), centro(obj.getCentro()), raio(obj.getRaio())
{

}

Objeto_3D::~Objeto_3D(){

}

Vetor_3D Objeto_3D::normal( const Ponto_3D& ponto, const Vetor_3D & d_vis) const
{
    Vetor_3D n(normal(ponto));
    if(n.produtoEscalar(d_vis) >= 0)
        return n;
    else
        return -n;
}

int Objeto_3D::getIndiceMaterial() const{
    return indice_textura;
}

float Objeto_3D::getRaio() const
{
    return raio;
}

const Ponto_3D& Objeto_3D::getCentro() const
{
    return centro;
}

void Objeto_3D::setCentro(const Ponto_3D& _centro)
{
    centro = _centro;
}

void Objeto_3D::setIndiceTextura(int indice)
{
    indice_textura = indice;
}

void Objeto_3D::setRaio(float _raio)
{
    raio = _raio;
}

TexturePoint Objeto_3D::pontoTextura(const Ponto_3D& ponto) const
{
    return TexturePoint(0,0);
}
