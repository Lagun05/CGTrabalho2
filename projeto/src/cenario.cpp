#include <math.h>
#include "cenario.h"
#include "Plano.h"
#include <QDebug>
#include <QtAlgorithms>

Cenario::Cenario()
{
  total = 0;
  total_materiais = 0;
  total_luzes = 0;
  cor_de_fundo = Cor_rgb(60,60,60);
}

Cenario::~Cenario()
{
  Zera();
}

void Cenario::Zera()
{
  int i;
  for (i=0;i<total;delete(objetos[i]),i++);
  for (i=0;i<total_luzes;delete(luzes[i]),i++);
  for (i=0;i<total_materiais;delete(materiais[i]),i++);
  total=total_luzes=total_materiais=0;
}

void Cenario::RecebeFundo( Cor_rgb _cor_de_fundo )
{
  cor_de_fundo = _cor_de_fundo;
}

bool Cenario::InsereObjeto( Objeto_3D *mais_um )
{
  if( total+1 == MAXOBJ )
    return false;
  
  objetos[total] = mais_um;

  total++;

  return true;
}

bool Cenario::InsereMaterial( Material *mais_uma )
{
  if( total_materiais+1 == MAXOBJ )
    return false;
  
  materiais[total_materiais] = mais_uma;

  total_materiais++;

  return true;
}

bool Cenario::InsereLuz( Luz *mais_uma )
{
  if( total_luzes+1 == MAXLUZ )
    return false;
  
  luzes[total_luzes] = mais_uma;

  total_luzes++;

  return true;
}

//------------------------------------------//
// Correspondente ao TRACE da transparencia //
//------------------------------------------//
Cor_rgb Cenario::Intercepta( Raio r_vis, int profundidade, bool* hit )
{
  Ponto_3D ponto;
  float t_min;
  //Verifico se eh o primeiro raio, se for soh me interessa o que
  //estiver depois da tela de projecao
  //(que tem valor 1 na funcao parametrica do raio).
  if ( profundidade == 0 )
    t_min = 1;
  else
    t_min = (float)ZERO;//0.0001 para nao iterceptar com a propria origem do raio

  Intersection inter;
  for(int i=0;i<total;i++)
  {
    inter = Intersection::nearest(inter, objetos[i]->Intercepta( r_vis, Objeto_3D::Nearest, t_min), t_min);
  }

  //Houve intersecao? (sem intersecao: obj_final == NULL)
  if ( inter.hasPositiveIntersection(t_min) )
  {
    ponto = r_vis.QualPonto(inter.getParametrizedDistance());
    if(hit != NULL)
        *hit = true;
    return( CorDoPonto( inter.getObject(), ponto, r_vis, profundidade) );
  }
  else
  {
      if(hit != NULL)
          *hit = false;
    return( cor_de_fundo );
  }

}

//------------------------------------------//
// Correspondente ao SHADE da transparencia //
//------------------------------------------//
Cor_rgb Cenario::CorDoPonto(const Objeto_3D* obj, Ponto_3D ponto, Raio r_vis, int profundidade)
{
  int i, j=0, bool_sombra, indMaterial;
  float nl, rv, coef_reflexao;
  Cor_rgb final, intermediaria, ilumina;
  Vetor_3D normal_ponto,  reflexao_luz, direcao_vista, direcao_luz;
  Raio sombra, reflexao, refracao;
  bool frontFace = true;

  indMaterial = obj->getIndiceMaterial();

  // calcula a direcao da vista normalizada para usar no calculo da difusa
  direcao_vista = r_vis.Origem() - r_vis.Destino();
  direcao_vista.normaliza();

  //== calculos iniciais ==//
  normal_ponto  =  obj->normal(ponto);
  normal_ponto.normaliza();

  if(normal_ponto.produtoEscalar(direcao_vista) < 0)
  {
      frontFace = false;
      normal_ponto = -normal_ponto;
  }

  Cor_rgb textureColor;
  if( materiais[indMaterial]->hasTexture() )
  {
      TexturePoint tp = obj->pontoTextura(ponto);
      textureColor = materiais[indMaterial]->getCorFromTexture(tp);
  }

  //== loop para todas as luzes (calculo da difusa e especular) ==/
  for(i=0;i<total_luzes;i++)
  {
    bool_sombra = 0;
    direcao_luz = luzes[i]->Posicao() - ponto;
    direcao_luz.normaliza();

    sombra = Raio(ponto + (normal_ponto*ZERO), luzes[i]->Posicao());
    Intersection inter;
    for(j=0;j<total;++j)
    {
        inter = objetos[j]->Intercepta(sombra, Objeto_3D::First, 0);
        if ( inter.hasIntersection() &&
             INSIDE(inter.getParametrizedDistance(),0,1) ) //para evitar sombra de objetos depois da luz
        {
            bool_sombra = 1;
            break;
        }
    }

    // Se nao houver sombra
//    /*
    if ( !bool_sombra )
    {
      //calcula a difusa
      nl = direcao_luz.produtoEscalar(normal_ponto);
      if(nl > 0)
      {
        intermediaria = luzes[i]->Intensidade();
        //intermediaria.Multiplica(luzes[i]->percDecaimento((luzes[i]->Posicao() - ponto).modulo()));
        intermediaria.Multiplica(nl);

        if( materiais[indMaterial]->hasTexture() )
            ilumina = textureColor;
        else
            ilumina = materiais[indMaterial]->Cor_difusa();

        ilumina.Indexa(intermediaria);
        final.Soma(ilumina);
      }
      
      //calcula a especular
      Vetor_3D incidenciaLuz(-direcao_luz);
      reflexao_luz = normal_ponto.reflect(incidenciaLuz);
      rv = reflexao_luz.produtoEscalar(direcao_vista);  //Foley 16.17
      if ( rv > 0.01 )
      {
        rv = (float)pow(rv,materiais[indMaterial]->N_especular());
        ilumina = materiais[indMaterial]->Indice_especular();
        ilumina.Multiplica(rv);
        final.Soma(ilumina);
      }
    }

  }

  if(materiais[indMaterial]->hasTexture() )
  {
      textureColor.Multiplica(0.2);
      final.Soma(textureColor);
  }else{
      final.Soma(materiais[indMaterial]->Ambiente());
  }

  coef_reflexao = materiais[indMaterial]->Coeficiente_reflexao();
  if ( coef_reflexao > 0  && profundidade < MAX_PROFUNDIDADE)
  {
     Vetor_3D vReflexao = normal_ponto.reflect(-direcao_vista);

     reflexao = Raio(ponto + vReflexao*ZERO ,ponto + vReflexao);
     bool hit = false;
     intermediaria = Intercepta( reflexao, profundidade + 1, &hit );
     if(hit)
     {
         intermediaria.Multiplica( coef_reflexao );
         final.Soma(intermediaria);
     }
  }

  float indice_refracao = materiais[indMaterial]->Indice_refracao();
  float indice_opacidade = materiais[indMaterial]->Indice_Opacidade();

  if ( indice_opacidade < 1  && profundidade < MAX_PROFUNDIDADE )
  {
     Vetor_3D at = normal_ponto*(direcao_vista.produtoEscalar(normal_ponto)) - direcao_vista;
     float sinTi = at.modulo();

     float sinTt;
     if(frontFace)
        sinTt = sinTi/indice_refracao;
     else
        sinTt = sinTi*indice_refracao;
     float cosTt = sqrt(1 - sinTt*sinTt);

     at.normaliza();
     Vetor_3D refracao_vista = at*sinTt - normal_ponto*cosTt;

     refracao = Raio( ponto + refracao_vista*ZERO, ponto + refracao_vista);
     bool hit = false;
     intermediaria = Intercepta( refracao, profundidade + 1, &hit);
     if(hit)
     {
         intermediaria.Multiplica( 1- indice_opacidade );
         final.Soma(intermediaria);
     }
  }

  return final;
}
