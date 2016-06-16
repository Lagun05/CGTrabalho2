# #####################################################################
# raytrace qmake
# #####################################################################
QT += core
QT += widgets

# app indica ao qmake que estamos montando uma aplicacão
TEMPLATE = app

# Diretórios onde estarão outros arquivos do projeto
DEPENDPATH += src
INCLUDEPATH += .
INCLUDEPATH += src

# Pasta onde os arquivos temporarios de compilacao ficaram armazenados
OBJECTS_DIR = tmp
MOC_DIR = tmp
RCC_DIR = tmp

# Diretorio onde os arquivos executaveis serao gerados
DESTDIR = bin

# Indica ao qmake que vamos utilizar a biblioteca qt
# com os modulos core e gui (que sao os que utilizaremos)
CONFIG += qt

# Indica se deve criar um makefile com suporte aos simbolos de debug ou nao
CONFIG += debug

# CONFIG += release
# #DEFINES += QT_NO_DEBUG_OUTPUT
# #DEFINES += QT_NO_WARNING_OUTPUT
# Habilitando os warnings do compilador no makefile.
CONFIG += warn_on

# Se estivermos em uma plataforma Windows
win32 { 
    # Se estiver em modo debug, incluimos as bibliotecas de console para podermos
    # utilizar funcoes de debug como a qDebug():
    # http://doc.qtsoftware.com/4.5/qtglobal.html#qDebug
    debug:CONFIG += console
    
    # Então configura de acordo.
    CONFIG += windows
}

# # Windows common build here
# Se estivermos em ambiente unix
unix:CONFIG += x11

# Nome do executavel criado
TARGET = raytrace

# # ADICIONEM OS ARQUIVOS AQUI ##
# Arquivos .h
HEADERS += src/camara.h \
    src/CaixaParalela.h \
    src/PlanoX.h \
    src/PlanoY.h \
    src/PlanoZ.h \
    src/Raio.h \
    src/Vetor_3d.h \
    src/Cor_rgb.h \
    src/Objeto_3d.h \
    src/Esfera.h \
    src/Triangulo.h \
    src/Plano.h \
    src/cenario.h \
    src/io.h \
    src/material.h \
    src/Trab3FT.h \
    src/PlyParser.h \
    src/MainWindow.h \
    src/RenderPanel.h \
    src/Render.h \
    src/CommandQueue.h \
    src/TriangleMesh.h \
    src/Ponto_3D.h \
    src/TexturePoint.h \
    src/intersection.h \
    src/Luz.h

# Arquivos .cpp
SOURCES += src/camara.cpp \
    src/CaixaParalela.cpp \
    src/PlanoX.cpp \
    src/PlanoY.cpp \
    src/PlanoZ.cpp \
    src/Raio.cpp \
    src/Vetor_3d.cpp \
    src/Cor_rgb.cpp \
    src/Esfera.cpp \
    src/Triangulo.cpp \
    src/cenario.cpp \
    src/io.cpp \
    src/material.cpp \
    src/Trab3FT.cpp \
    src/PlyParser.cpp \
    src/MainWindow.cpp \
    src/RenderPanel.cpp \
    src/Render.cpp \
    src/CommandQueue.cpp \
    src/TriangleMesh.cpp \
    src/TexturePoint.cpp \
    src/intersection.cpp \
    src/Objeto_3d.cpp \
    src/Plano.cpp \
    src/Luz.cpp

# Arquivos dos resources (imagens por exemplo)
RESOURCES += raytrace.qrc
