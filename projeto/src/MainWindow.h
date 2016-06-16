#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <RenderPanel.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
   
public slots:
    void update(void);
    void clicou(QAction* a);

public:
    MainWindow();
    
private:
   CommandQueue *fila;
   RenderPanel* centralpanel;
   QFileDialog *fdo;
   QFileDialog *fds;
   QToolBar * tb;
   QAction *open;
   QAction *save;

};


#endif
