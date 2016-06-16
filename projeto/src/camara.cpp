#include <math.h>
#include "camara.h"
#include <QtAlgorithms>
#include <cstdlib>

Camara::Camara()
{
  linhas = 300;
  colunas = 300;
  olho = Ponto_3D();
  direcao = Ponto_3D(0.0,0.0, -1.0);
  vup = Vetor_3D(0 , 1, 0);

  PreparaRaios();
}

void Camara::Atribui( const Ponto_3D& _olho, const Ponto_3D& _direcao, const Vetor_3D& _vup, int _linhas, int _colunas )
{
  linhas = _linhas;
  colunas = _colunas;
  olho = _olho;
  direcao = _direcao;
  vup = _vup;

  PreparaRaios();
}

void Camara::setSize(int l, int c)
{
    linhas = l;
    colunas = c;

    PreparaRaios();
}

void Camara::PreparaRaios( void )
{
  // Determina xe, ye, ze

  ze = Vetor_3D(olho, direcao);
  ze.normaliza();
  xe = vup*ze;
  xe.normaliza();
  ye =  ze*xe;
  
  // Acha PU
  P0 = olho;
  P0+=-ze;
  P0+=-ye;
  P0+=-xe;
  
  // dx/2 e dy/2
  dx = xe;
  dx/=(float)colunas;
  dy = ye;
  dy/=(float)linhas;

  // Acha P0
  P0+=dx;
  P0+=dy;

  // Acha dx e dy
  dx/=0.5;
  dy/=0.5;

  P_atual = P0;
  P_linha = P0;
  l_atual = c_atual = 0;
}

Camara::~Camara()
{}

Raio Camara::PrimeiroRaio()
{
  Raio retorno( olho, P0 );
  l_atual = c_atual = 0;
  return (retorno);
}

Raio Camara::SubRaio()
{
    double ddy;
    double ddx;

    Ponto_3D ponto;
    Vetor_3D vDy;
    Vetor_3D vDx;

    ddy = (double)qrand()/(double)RAND_MAX;
    ddy/=2.0;
    ddx = (double)qrand()/(double)RAND_MAX;
    ddx/=2.0;

    if(qrand()%2 == 0)
        ddy = -ddy;
    if(qrand()%2 == 0)
        ddx = -ddx;

    vDx = dx;
    vDx*=ddx;

    vDy = dy;
    vDy*=ddy;

    ponto = P_atual;
    ponto+=vDx;
    ponto+=vDy;

    return Raio(olho, ponto);
}

Raio Camara::ProximoRaio()
{
  //Raio retorno;
  c_atual++;

  //Anda na linha
  if ( c_atual < colunas )
    P_atual+=dx;
  //Anda na coluna  
  else
  {
    c_atual = 0;
    l_atual++;
    if ( l_atual < linhas )
    {
      P_linha+=dy;
      P_atual = P_linha;
    }
    else
    //Se chegou no fim, entao recomeca
    {
      l_atual = 0;
      P_linha = P0;
      P_atual = P0;
    }
  }

  return Raio(olho, P_atual);
}
