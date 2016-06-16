
#include <QString>
#include <QFile>
#include <QTextStream>

#include "material.h"
#include "camara.h"
#include "cenario.h"
#include "Luz.h"
#include "io.h"
#include "Esfera.h"
#include "Triangulo.h"
#include "CaixaParalela.h"
#include "PlyParser.h"
#include "TriangleMesh.h"

bool LeArquivo( Cenario * hcenario, Camara * hcamara, int hlinhas, int hcolunas, const QString& filename)
{
  QFile arqdat(filename);
  tok  tag;
  QString linha;
  QChar it;


  arqdat.open(QIODevice::ReadOnly);
  QTextStream stream(&arqdat);

  linha = stream.readLine();

  if(linha != "RT 1.0")
  {
    return false;
  }
  linha = stream.readLine();

  //Loop para leitura das linhas do arquivo
  tag = tok_DESCONHECIDO;
  while(!linha.isEmpty())
  {
      QTextStream s(&linha, QIODevice::ReadOnly);
      QString tmp;

      it = linha.at(0);
      if ( it == '#')
      {
          s >> tmp;
        tag = Token(tmp);  //ja dispenso a #
      }
      else if (it !=';' && it != '!')
        LeInfo( tag, hcenario, hcamara, hlinhas, hcolunas, s);

      linha = stream.readLine();
  }
 
  arqdat.close();
  return true;
}

//Reconhece o token
tok Token(const QString& linha)
{
    if(linha == "#BACKGROUND") return tok_BACKGROUND;

    if(linha == "#POSITION") return tok_POSITION;

    if(linha == "#TRIANGLE") return tok_TRIANGLE;

    if(linha == "#SURFACE") return tok_SURFACE;

    if(linha == "#SPHERE") return tok_SPHERE;

    if(linha == "#LIGHT") return tok_LIGHT;

    if(linha == "#SIZE") return tok_SIZE;

    if(linha == "#BOX") return tok_BOX;

    if(linha == "#FILM") return tok_FILM;

    if(linha == "#GRID") return tok_GRID;

    if(linha == "#LENS") return tok_LENS;

    if(linha == "#PLY") return tok_PLY;

  return tok_DESCONHECIDO;
}

void LeInfo( tok tag, Cenario *hcenario, Camara *hcamara, int hlinhas, int hcolunas, QTextStream& linha )
{
  int a,b,c;
  float e, f, g;
  float pa[9];
  bool tt;

  QImage tx;
  char p;
  QString nome;
  Cor_rgb cor1,cor2,cor3;
  Vetor_3D vet1, vet2, vet3;
  Ponto_3D p1, p2, p3;
  Material *mat1;
  Luz *luz1;
  Esfera *esf1;
  CaixaParalela *cxp1;
  Triangulo *tri1;

  int temp1,temp2;
  switch(tag)
  {
    case tok_SIZE:
      linha >> temp1 >> temp2;

      return;
    case tok_BACKGROUND:
      cor1 = LeCor(linha);
      hcenario->RecebeFundo(cor1);
      return;
    case tok_SURFACE:
      linha >> nome;

      cor1 = LeCor(linha); //Cor da iluminação ambiente

      cor2 = LeCor(linha); //Cor da difusa

      cor3 = LeCor(linha); //Cor da especular

      tt = false;
      if(nome != "0")
      {
          tx = QImage(nome);
          tt = true;
      }

      linha >> a >> p >> e >> f >> g;
      mat1 = new Material( cor1, cor2, cor3, a, e, f, g, tx, tt);
      hcenario->InsereMaterial( mat1 );
      return;
    case tok_LIGHT:
      p1 = LePonto(linha);   //Posição
      linha >> a >> p >> b >> p >> c >> p;
      cor1 = Cor_rgb(a, b, c);           //Cor
      luz1 = new Luz( p1, cor1);
      hcenario->InsereLuz( luz1 );
      return;
    case tok_SPHERE:
      linha >> a >> p;
      linha >> e;      //Raio
      p1 = LePonto(linha); //Centro
      esf1 = new Esfera( a, e, p1 );
      hcenario->InsereObjeto( esf1 );
      return;
    case tok_BOX:
      linha >> a;
      vet1 = LeVetor(linha); //canto inferior esquerdo
      vet2 = LeVetor(linha); //canto superior direito
      cxp1 = new CaixaParalela( a, vet1, vet2 );
      hcenario->InsereObjeto( cxp1 );
      return; 
    case tok_TRIANGLE:
      linha >> a >> p;
      p1 = LePonto(linha);//primeiro vértice

      p2 = LePonto(linha);//segundo vértice

      p3 = LePonto(linha);//terceiro vértice
      tri1 = new Triangulo( a, p1, p2, p3);
      hcenario->InsereObjeto( tri1 );
      return;
    case tok_POSITION:
      p1 = LePonto(linha);       //eye

      p2 = LePonto(linha);   //ref

      vet3 = LeVetor(linha);   //up
      hcamara->Atribui( p1, p2, vet3, hlinhas, hcolunas );
      return;
    case tok_FILM:
      linha >> e >> f;
      return;
    case tok_GRID:
      linha >> a >> b;
      return;
    case tok_LENS:
      linha >> e;
      return;
    case tok_DESCONHECIDO:
      return;
    case tok_PLY:
      linha >> a;
      linha >> nome;

      PlyParser ply(nome);

      if(ply.parse() == 1)
      {

        linha >> pa[0] >> pa[1] >> pa[2];
        //tm->scala(e,f,g);
        linha >> pa[3] >> pa[4] >> pa[5];
        //tm->translada(e,f,g);
        linha >> pa[6] >> pa[7] >> pa[8];
        //tm->rotaciona(e,f,g);
        TriangleMesh *tm = new TriangleMesh(ply.begin(),ply.end(),a, pa);
        hcenario->InsereObjeto(tm);
      }else
      {
          linha >> e >> f >> g;
          linha >> e >> f >> g;
          linha >> e >> f >> g;
      }
      return;
  }
}

//As duas funcoes abaixo são apenas facilitadoras na leitura
Cor_rgb LeCor(QTextStream &linha)
{
  Cor_rgb cor;
  int a,b,c;
  char p;

  linha >> a >> p >> b >> p >> c >> p;
  cor = Cor_rgb(a,b,c);
  return cor;

}

Vetor_3D LeVetor(QTextStream &linha)
{
  float a,b,c;
  linha >> a ; linha >> b; linha >> c;
  return Vetor_3D(a,b,c);
}

Ponto_3D LePonto(QTextStream& linha)
{
  float a,b,c;
  linha >> a ; linha >> b; linha >> c;
  return Ponto_3D(a,b,c);
}
