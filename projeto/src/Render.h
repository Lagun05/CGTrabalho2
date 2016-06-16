#ifndef RENDER_H
#define RENDER_H

#include <QThread>
#include <QPainter>
#include <QDebug>
#include <CommandQueue.h>
#include "camara.h"
#include "cenario.h"


#define INCPOS      100
#define INCZ        0.5
#define MARGEM      0.05

class Render : public QThread
{
	Q_OBJECT

signals:
        void renderizado(const QImage &screen);

        
public slots:
    void updateScreen(int w, int y);
    void recebeArquivo(const QString &);

                
public:
        Render(int w, int y, CommandQueue *c);

    void run(void);

private:
        void atualizaScreen(void);
        void renderiza(void);
        void reiniciaBuffers(int w, int h);
        void umpixel();
        int selx,sely;
        Camara camara;    // cria uma câmera default
        Cenario cenario;  // cria o cenário
        QImage* screen;
        QImage* buffer;
        CommandQueue *cmdq;
        QPoint *ponto;
        QPoint *sel;
        int screenW;
        int screenH;
};

#endif
