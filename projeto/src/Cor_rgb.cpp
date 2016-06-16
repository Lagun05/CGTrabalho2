#include "Cor_rgb.h"

Cor_rgb::Cor_rgb(int _r, int _g, int _b)
{
  r= Acerta(_r);
  g= Acerta(_g);
  b= Acerta(_b);
}

unsigned char Cor_rgb::Acerta(int x)
{
  if ( x<0 )
    return (unsigned char)0;
  if ( x>255 )
    return (unsigned char)255;
  return (unsigned char)x;
}

void Cor_rgb::Multiplica(float ind)
{
  r = Acerta( (int) ( (float) r * ind ) );
  g = Acerta( (int) ( (float) g * ind ) );
  b = Acerta( (int) ( (float) b * ind ) );
}

void Cor_rgb::Indexa(Cor_rgb indice)
{
    r = Acerta( (int) ( (float) r * ( (float) indice.R() / 255 ) ) );
    g = Acerta( (int) ( (float) g * ( (float) indice.G() / 255 ) ) );
    b = Acerta( (int) ( (float) b * ( (float) indice.B() / 255 ) ) );
}

void Cor_rgb::Soma(Cor_rgb outra)
{
    int t;
    t = outra.R() + (int)r;
    r = Acerta( t );
    t = outra.G() + (int)g;
    g = Acerta( t );
    t = outra.B() + (int)b;
    b = Acerta( t );
}
