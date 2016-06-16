#include "Raio.h"

// implementação do Raio
Raio::Raio()
{}

Raio::Raio(const Ponto_3D& _origem,const Ponto_3D& _destino) : origem(_origem), destino(_destino), direcao(_destino,_origem)
{

}

//Retorna o ponto para este t aplicado na função paramétrica
Ponto_3D Raio::QualPonto(float t) const
{
  return Ponto_3D( origem.X() + t*direcao.X(),
                   origem.Y() + t*direcao.Y(),
                   origem.Z() + t*direcao.Z() );
}
