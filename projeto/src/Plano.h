#ifndef PLANO_H
#define PLANO_H

#include "Raio.h"
#include "Objeto_3d.h"

#define INSIDE(a,b,c) (((b>a)&&(a>c))||((b<a)&&(a<c)))

//* classe Plano #Plano#
  //* Define um plano. Esta classe é mãe das classes PlanoX, PlanoY e PlanoZ.
class Plano : public Objeto_3D{
  protected:
    float a, bmin, bmax, cmin, cmax;

  public:
 //* Construtor e Destrutor
    Plano( float _a, float _bmin, float _bmax, float _cmin, float _cmax, int ind);
    Plano( const Plano& p);
    ~Plano();
 //* interseção. Função pura virtual para ser implementada pelos herdeiros
    virtual Intersection Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold) = 0;
    virtual Vetor_3D normal( const Ponto_3D& ponto ) const  = 0;
    
    float getA(void) const;
    float getBmin(void) const;
    float getBmax(void) const;
    float getCmin(void) const;
    float getCmax(void) const;
};

#endif // PLANO_H
