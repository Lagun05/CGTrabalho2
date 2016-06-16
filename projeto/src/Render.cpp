#include <Render.h>
#include <QPaintDevice>
#include <PlyParser.h>
#include <QRgb>
#include "io.h"
#include "Luz.h"
#include "material.h"
#include "Cor_rgb.h"
#include <cstdio>
#include <ctime>
#include <QtAlgorithms>

Render::Render(int w, int h, CommandQueue *c) {

    screenW = w;
    screenH = h;
    cmdq = c;

    sel = NULL;
    buffer = NULL;
    screen = NULL;

    qsrand(time(NULL));

    screen = new QImage(w, h, QImage::Format_RGB32);
    reiniciaBuffers(w,h);
    ponto = new QPoint(0,0);
}

void Render::run(void) {
    ExCom ex;
    
    do {
        ex = cmdq->consome();
        if(buffer == NULL)
        {
             msleep(100);
             continue;
        }
        switch(ex.cmd)
        {
            case NENHUM:
                msleep(100);
                continue;
            case RENDER:
                renderiza();
                break;
            case SELECT:
                umpixel();
                selx = ex.x;
                sely = ex.y;
                break;
            default:
                msleep(100);
                continue;
        }
        atualizaScreen();
    } while (true);
}

void Render::updateScreen(int w, int h)
{
    screenW = w;
    screenH = h;

    if(buffer->width() < w || buffer->height() < h)
    {
        reiniciaBuffers(screenW , screenH );

    }

    if(ponto->x() + w > buffer->width())
        ponto->setX(buffer->width() - w);
    if(ponto->y() + h > buffer->height())
        ponto->setY(buffer->height() - h);

    atualizaScreen();
}

void Render::recebeArquivo(const QString &filename)
{

  cenario.Zera();

  if(!LeArquivo( &cenario, &camara, screenH, screenW, filename))
          return;

  cmdq->produz(RENDER);
}
 
void Render::atualizaScreen(void)
{
    QPainter p;

    if(screen != NULL)
        delete screen;

    screen = new QImage(screenW, screenH, QImage::Format_RGB32);
    p.begin(screen);
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.drawImage(0,0, buffer->copy(ponto->x(),ponto->y(),screenW, screenH));
    p.end();
    emit renderizado(*screen);
}

void Render::renderiza(void)
{
    Raio raio;
    Cor_rgb cor1;

// /*
    raio = camara.PrimeiroRaio();


    for(int i=0;i<screenH;i++)
    {
        for(int j=0;j<screenW;j++)
        {
            cor1 = cenario.Intercepta( raio, 0, NULL );
            buffer->setPixel(j,screenH-1-i, qRgb(cor1.R(), cor1.G(), cor1.B()));
            raio = camara.ProximoRaio();
        }
        atualizaScreen();
    }

//*/
/*
 *  Cor_rgb cor2, cor3;
    QRgb cor4;

    int r,g,b;
    raio = camara.PrimeiroRaio();

    for(int i=0;i<screenH;i++)
    {
        for(int j=0;j<screenW;j++)
        {
            raio = camara.SubRaio();
            cor1 = cenario.Intercepta( raio, 0 );
            raio = camara.SubRaio();
            cor2 = cenario.Intercepta( raio, 0 );
            raio = camara.SubRaio();
            cor3 = cenario.Intercepta( raio, 0 );
            cor4 = buffer->pixel(j, screenH-1-i);
            r = cor1.R();
            r+= cor2.R();
            r+= cor3.R();
            r+= qRed(cor4);
            r/=4;
            g = cor1.G();
            g+= cor2.G();
            g+= cor3.G();
            g+= qGreen(cor4);
            g/=4;
            b = cor1.B();
            b+= cor2.B();
            b+= cor3.B();
            b+= qBlue(cor4);
            b/=4;
            buffer->setPixel(j,screenH-1-i, qRgb(r, g, b));
            raio = camara.ProximoRaio();
        }
        atualizaScreen();
        qDebug() << "percentagem: " << i/(float)screenH;
    }
    //*/
}

void Render::reiniciaBuffers(int w, int h)
{
    if(buffer != NULL)
        delete buffer;

    buffer = new QImage(w, h, QImage::Format_RGB32);

    QPainter p;
    p.begin(buffer);
    p.fillRect(buffer->rect(), Qt::white);
    p.end();

}

void Render::umpixel()
{
    int i,j;
    Raio raio;

    raio = camara.PrimeiroRaio();
    for(i = 0; i < sely; ++i)
        for(j = 0; j < screenW; ++j)
            camara.ProximoRaio();

    for(j = 0; j < selx; j++)
        camara.ProximoRaio();

    cenario.Intercepta(raio , 0, NULL);
}
