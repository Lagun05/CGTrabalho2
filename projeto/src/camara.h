//* Modulo : camara.hpp                                                         
//
// _Descricao_   : Declara classe Camara.
// _Autor_: Rodrigo P. R. de Toledo

#ifndef __CAMERA_HPP
#define __CAMERA_HPP

#include "Raio.h"
#include "Vetor_3d.h"
#include "Ponto_3D.h"

//* classe Camara #Camara#
//Esta classe guarda informacoes quanto posicao da camera, a tela
//de projecao. A classe tambem e responsavel por retornar os raios para cada pixel da tela.
class Camara{
  private:
    Vetor_3D  dx, dy,
              vup, xe, ye, ze;
    Ponto_3D P0, olho, direcao,  P_atual, P_linha;
    int linhas, colunas, l_atual, c_atual;

  public:
 //* Construtor e Destrutor
	  Camara();
	  ~Camara();
 //* Atribuicao
    void Atribui( const Ponto_3D& olho, const Ponto_3D& _direcao, const Vetor_3D& _vup, int _linhas, int _colunas );
 //* Pegando os Raios
    void setSize(int l, int c);
    Raio PrimeiroRaio();
    Raio ProximoRaio();
    Raio SubRaio();

    //calcula xe, ye, ze, dx, dy e tambem inicializa P0, P_atual e P_linha
    void PreparaRaios( );
};

#endif
