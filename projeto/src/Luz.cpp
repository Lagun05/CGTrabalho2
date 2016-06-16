#include "Luz.h"

Luz::Luz( const Ponto_3D& _posicao, Cor_rgb _intensidade) :
     posicao(_posicao), intensidade(_intensidade)
{

}
Luz::~Luz()
{

}
//* Funções inline que retornam informações da Luz
const Ponto_3D& Luz::Posicao()
{
    return(posicao);
}

const Cor_rgb&  Luz::Intensidade()
{
    return(intensidade);
}

float Luz::percDecaimento(float distancia)
{
    return 1.0/distancia*distancia;
}
