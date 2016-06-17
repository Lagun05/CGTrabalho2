//* Módulo : io.hpp                                                         
//
// _Descrição_  _.
// Responsável pelo *parsing* de leitura do arquivo de entrada.
// Responsável pela gravação do arquivo de saída (.ppm).
// _Autor_: Rodrigo P. R. de Toledo

#include "camara.h"
#include "cenario.h"
#include "Luz.h"
#include <QString>
#include <QTextStream>

//--------------------
//* enumerados #Enumerados#
  //* O _tok_ enumera as opções de token do arquivo de entrada.
typedef enum {
  tok_DESCONHECIDO = 0,
  tok_SIZE,
  tok_BACKGROUND,
  tok_SURFACE,
  tok_LIGHT,
  tok_SPHERE,
  tok_CYLINDER,
  tok_BOX,
  tok_TRIANGLE,
  tok_POSITION,
  tok_FILM,
  tok_GRID,
  tok_LENS,
  tok_PLY
}tok;

//* LEITURA
  //* Estas funções são usadas para a leitura do arquivo de entrada. 
//A leitura é feita linha a linha isoladamente.
//Existe sempre um token corrente que será trocado ao se encontrar outro
//(um dos tokens é "desconhecido")_. 
//OBS: Não é possível dividir os números de um único elemento em duas linhas
//e nem colocar informação na mesma linha do token.

 //* LeArquivo
  //* Esta função é a única que interage diretamente com o arquivo de entrada! 
//Cada linha é lida para uma string e as demais funções
//passam a interagir com essa string. 
//Esta função descobre se a linha é um início de um novo conjunto
//de elementos (#token) ou se é uma linha com as informações a serem lidas.
bool LeArquivo(Cenario * todos, Camara * cam, int lines, int cols, const QString&);

 //* Token
  //* Reconhece qual é o token.
tok Token(const QString &);

 //* LeInfo
  //* Lê as informações que estão na string de acordo com o token corrente
void LeInfo(tok i, Cenario *hcenario, Camara *hcamara, int hh, int hw, QTextStream&);

 //* Funções para agrupar a leitura de (x y z) e de (r g b).
Vetor_3D LeVetor(QTextStream&);
Ponto_3D LePonto(QTextStream&);
Cor_rgb LeCor(QTextStream&);


