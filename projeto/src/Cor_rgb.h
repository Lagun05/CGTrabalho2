#ifndef COR_RGB_H
#define COR_RGB_H

#include <QColor>

//--------------------
//* classe Cor_rgb #Cor_rgb#
  //* Contem r g b em três unsigned char e faz operações sobre cor.
class Cor_rgb{
  private:
    unsigned char r,g,b;
 //* Função _Private_ que trunca para x ficar entre 0 e 255
    unsigned char Acerta(int x);
  public:

 //* Construtores e Destrutor
    Cor_rgb() : r(0), g(0), b(0) {}
    Cor_rgb(int _r, int _g, int _b);
    Cor_rgb(const Cor_rgb& c) { r = c.R(); g = c.G(); b = c.B(); }
    Cor_rgb(const QRgb& q) { r = qRed(q); g = qGreen(q); b = qBlue(q); }
    ~Cor_rgb() {}

 //* Operações sobre cor
    void Multiplica(float ind);
    void Indexa(Cor_rgb indice);
    void Soma(Cor_rgb outra);
 //* Funções inline que retornam as cores
    inline unsigned char R() const {  return(r); }
    inline unsigned char G() const {  return(g); }
    inline unsigned char B() const {  return(b); }

    const Cor_rgb& operator =(const Cor_rgb& c1) {r = c1.R(); g = c1.G(); b = c1.B(); return *this;}

};

#endif // COR_RGB_H
