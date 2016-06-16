#include "Triangulo.h"

Triangulo::Triangulo(const Triangulo& t) : Objeto_3D(t.getIndiceMaterial())
{
    vert1 = t.getVertice1();
    vert2 = t.getVertice2();
    vert3 = t.getVertice3();

    refazArestas();
}

Triangulo& Triangulo::operator=(const Triangulo& v)
{
    vert1 = v.getVertice1();
    vert2 = v.getVertice2();
    vert3 = v.getVertice3();
    indice_textura = v.getIndiceMaterial();

    refazArestas();

    return *this;
}

Triangulo::Triangulo( int _indice_textura, const Ponto_3D& v1, const Ponto_3D& v2, const Ponto_3D& v3 ): Objeto_3D( _indice_textura )
{
    vert1 = v1;
    vert2 = v2;
    vert3 = v3;

    refazArestas();
}

void Triangulo::refazArestas(void)
{
  aresta12 = Vetor_3D(vert2,vert1);
  aresta23 = Vetor_3D(vert3,vert2);
  aresta31 = Vetor_3D(vert1,vert3);

  Vetor_3D temp(vert3, vert1);
  vnormal = aresta12 * temp;
  area = vnormal.modulo();
  vnormal.normaliza();
}

Intersection Triangulo::Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold)
{
  Ponto_3D temp;
  Vetor_3D temp2;
  float t;
  Intersection lastIntersection;

  //Cálculo da ponto em que o raio intercepta o plano
  //Foley, Appendix, A.3.5.
  {
    t = (vert1 - r_vis.Origem()).produtoEscalar(vnormal);
    temp2 =  vnormal - Vetor_3D();
    t/= vnormal.produtoEscalar( r_vis.Direcao() );

    if (t<0)
    {
        return lastIntersection;
    }
    temp = r_vis.QualPonto(t);
  }

  //Verificação se o ponto pertence ao triângulo
  {
    float v1,v2,v3;
    Vetor_3D d1, d2, d3;

    //Produto vetorial entre a aresta e a reta que sai do vértice até o ponto

    d1 = aresta12*(temp-vert1);
    d2 = aresta23*(temp-vert2);
    d3 = aresta31*(temp-vert3);

    //Produto Escalar apenas para verificar o sinal (+-)
    v1 = d1.produtoEscalar( d2 );
    v2 = d1.produtoEscalar( d3 );
    v3 = d2.produtoEscalar( d3 );

    //Se todos os vetores resultantes estiverem para o mesmo lado...
    if ( ( v1>0 && v2>0 && v3>0 ) || ( v1<0 && v2<0 && v3<0 ) )
    {
        lastIntersection.setValues(this, t);
      return lastIntersection;
    }else
    {
      return lastIntersection;
    }
  }
}

TexturePoint Triangulo::pontoTextura(const Ponto_3D& ponto) const
{
    
    Ponto_3D coord = coordenadaBaricentrica(ponto);

    return TexturePoint(tx1.U()*coord.X() + tx2.U()*coord.Y() + tx3.U()*coord.Z(),
                        tx1.V()*coord.X() + tx2.V()*coord.Y() + tx3.V()*coord.Z());
}

Ponto_3D Triangulo::coordenadaBaricentrica(const Ponto_3D& p) const
{
    Vetor_3D d1, d2, d3;

    //Produto vetorial entre a aresta e a reta que sai do vértice até o ponto

    d1 = aresta12*(p-vert1);
    d2 = aresta23*(p-vert2);
    d3 = aresta31*(p-vert3);

    float l1 = d1.modulo()/area;
    float l2 = d2.modulo()/area;
    float l3 = d3.modulo()/area;

    return Ponto_3D(l2,l3,l1);
}
