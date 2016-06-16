#include <Trab3FT.h>
#include <MainWindow.h>

int Trab3FT::run(int argc, char* argv[])
{
    QApplication trab3FT(argc, argv);
    MainWindow *mwT2 = new MainWindow();

    mwT2->show();

    return trab3FT.exec();
}

int main(int argc, char* argv[])
{
    Trab3FT* t2 = new Trab3FT();
    return t2->run(argc, argv);
}
