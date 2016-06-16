#ifndef __cenario_HPP
#define __cenario_HPP

#include "Luz.h"
#include "Objeto_3d.h"
#include "Cor_rgb.h"
#include "material.h"

#define MAX_PROFUNDIDADE 6
#define MAXOBJ 5000
#define MAXLUZ 10
#define ZERO 0.0001
#define REFRAMBIENTE 1.0

class Cenario{
  private:
    int total, total_materiais, total_luzes;
    Objeto_3D *objetos[MAXOBJ];
    Cor_rgb cor_de_fundo;
    Material *materiais[MAXOBJ];
    Luz *luzes[MAXLUZ];

  public:

    Cenario();
    ~Cenario();
    void    Zera();

    bool     InsereObjeto( Objeto_3D *mais_um );
    bool     InsereMaterial( Material *mais_uma );
    bool     InsereLuz( Luz *mais_uma );

    void    RecebeFundo( Cor_rgb _cor_de_fundo );

    Cor_rgb Intercepta(Raio r_vis, int profundidade, bool* hit);

  private:
    Cor_rgb CorDoPonto( const Objeto_3D* obj, Ponto_3D ponto,
                        Raio r_vis, int profundidade);
};

#endif
