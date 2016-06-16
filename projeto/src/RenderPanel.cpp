#include <RenderPanel.h>

RenderPanel::RenderPanel(CommandQueue *c, int w, int h)
{  
    cmdq = c;
    fundolb = new QLabel(this);

    screenW = w;
    screenH = h;

    Render *r = new Render(screenW, screenH, c);
    connect(r, SIGNAL(renderizado(const QImage &)), this, SLOT(update(const QImage &)), Qt::QueuedConnection);
    connect(this, SIGNAL(atualizaTamanho(int, int)), r, SLOT(updateScreen(int, int)), Qt::QueuedConnection);
    connect(this, SIGNAL(enviaArquivo(const QString &)), r, SLOT(recebeArquivo(const QString &)), Qt::QueuedConnection);
    
    QImage tmp(screenW, screenH,QImage::Format_RGB32);
    QPainter p;
    p.begin(&tmp);
    p.fillRect(tmp.rect(), Qt::white);
    p.end();
    fundolb->setPixmap(QPixmap::fromImage(tmp));
    fundolb->show();

    repaint();
    r->start();
}

void RenderPanel::setSize(int w,int h)
{
    screenW = w;
    screenH = h;
}

void RenderPanel::update(const QImage& screen)
{
    fundolb->setPixmap(QPixmap::fromImage(screen));
    fundolb->show();
    repaint();
    emit atualizaMain();
}

void RenderPanel::salvaArquivo(const QString &fn)
{
    QString fileFormat;
    int tam = fn.length();
     if(tam > 4)
         fileFormat = fn.right(4);

    QString filename;

    if(fileFormat == ".png" || fileFormat == ".PNG")
        filename = fn;
    else
        filename = fn + ".png";

    const QPixmap *p;
    p = fundolb->pixmap();

    p->save(filename, "png");
}

void RenderPanel::recebeArquivo(const QString &filename)
{
    emit enviaArquivo(filename);
}

void RenderPanel::mouseReleaseEvent(QMouseEvent *event)
{

    if(event->x() >= 0 && event->y() >=0 && event->x() < fundolb->width() && event->y() < fundolb->height())
    {
        cmdq->produz(SELECT,event->x(), event->y());
    }
}
