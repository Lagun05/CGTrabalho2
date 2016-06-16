//* Módulo : luz.hpp                                                         
//
// _Descrição_   : Declara classe Luz.
// _Autor_: Rodrigo P. R. de Toledo

#ifndef __LUZ_HPP
#define __LUZ_HPP

#include "Ponto_3D.h"
#include "Cor_rgb.h"

//* classe Luz #Luz#
  //* Esta classe guarda informações quanto a posição e intensidade de uma luz.
  //* Atenção! Não foi necessário um arquivo .cpp para este módulo.
class Luz{
  private:
    Ponto_3D posicao;
    Cor_rgb  intensidade;
  public:
 //* Construtor e Destrutor
    Luz( const Ponto_3D& _posicao, Cor_rgb _intensidade);
    ~Luz();
 //* Funções inline que retornam informações da Luz
    const Ponto_3D& Posicao();
    const Cor_rgb&  Intensidade();
    float percDecaimento(float distancia);
};

#endif
