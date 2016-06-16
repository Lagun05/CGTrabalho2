#ifndef _PLYPARSER_H
#define	_PLYPARSER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QPointF>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include "Triangulo.h"

class PlyProperty
{
public:
    enum Propertype { LIST, SCALAR };

    PlyProperty(QString pn, Propertype t) : propertyName(pn), type(t) { }
    PlyProperty(Propertype t) : type(t) { }
    PlyProperty() {}
    QString getPropertyName(void)   const   { return propertyName; }
    Propertype getType(void)        const   { return type; }
    void setPropertyName(QString s)         { propertyName = s; }
    void setType(Propertype t)              { type = t; }

private:
    QString propertyName;
    Propertype type;

};

class PlyScalarProperty : public PlyProperty
{
private:
    QVector<float> data;
public:
    PlyScalarProperty(QString pn) : PlyProperty(pn, SCALAR) { }
    PlyScalarProperty() : PlyProperty(SCALAR) { }

    void addData(float t) { data.push_back(t); }
    int getdataSize(void) const { return data.size(); }
    float getData(int i) const { return data[i]; }

};

class PlyListProperty : public PlyProperty
{
private:
    QVector<QVector<int> >data;
public:
    PlyListProperty(QString pn) : PlyProperty(pn, LIST) {}
    PlyListProperty() : PlyProperty(LIST) {}

    void addData(QVector<int> t) { data.push_back(t); }
    int getdataSize(void)const { return data.size(); }
    int getData(int li, int di)const  { return data[li][di]; }
};

class PlyElement
{

private:
    QVector<PlyProperty*> propertyList;
    QString elementName;
    int nElements;

public:
    PlyElement() {}
    PlyElement(QString n, int qtd): elementName(n), nElements(qtd) { }
    PlyElement(const PlyElement &pe) { elementName = pe.getElementName(); nElements = pe.getNElements(); propertyList = pe.getLista();}

    int getNElements(void) const { return nElements; }
    QString getElementName(void) const { return elementName; }

    typedef QVector<PlyProperty*>::iterator iterator;

    iterator begin(){ return propertyList.begin(); }
    iterator end()  { return propertyList.end();   }

    int findByName(QString _name)
    {
        for(int i = 0; i < propertyList.size(); ++i)
            if(propertyList[i]->getPropertyName() == _name)
                return i;
        return -1;
    }

    void addProperty(PlyProperty* p) { propertyList.push_back(p); }
    PlyProperty* getProperty(int i)const  { return propertyList[i]; }
    int getPropertyListSize(void)const {return propertyList.size(); }
    QVector<PlyProperty*> getLista(void)const {return propertyList; }

};

class PlyParser : public QObject
{
    Q_OBJECT
public:
    PlyParser(const QString& filename) : file(filename) {
        this->stream = new QTextStream(&file);
        qDebug() << filename;
        qDebug() << QDir(".").absolutePath();
    }
    int parse(void);

    int findByName(QString _name)
    {
        for(int i = 0; i < elementsList.size(); ++i )
            if(elementsList[i].getElementName() == _name)
                return i;
        return -1;
    }

    class Iterator
    {
    public:
        Triangulo getTriangulo(void)
        {
            Ponto_3D v1;
            Ponto_3D v2;
            Ponto_3D v3;

            PlyListProperty *pl;
            PlyScalarProperty *ps;

            int ind;
            float x,y,z;

            pl = ((PlyListProperty*)(itelementsList[fi].getProperty(li)));
            ind = pl->getData(i,0);

            ps = ((PlyScalarProperty*)(itelementsList[vi].getProperty(xi)));
            x = ps->getData(ind);
            ps = ((PlyScalarProperty*)(itelementsList[vi].getProperty(yi)));
            y = ps->getData(ind);
            ps = ((PlyScalarProperty*)(itelementsList[vi].getProperty(zi)));
            z = ps->getData(ind);

            v1 = Ponto_3D(x,y,z);

            ind = ((PlyListProperty*)(itelementsList[fi].getProperty(li)))->getData(i,1);

            x = ((PlyScalarProperty*)(itelementsList[vi].getProperty(xi)))->getData(ind);
            y = ((PlyScalarProperty*)(itelementsList[vi].getProperty(yi)))->getData(ind);
            z = ((PlyScalarProperty*)(itelementsList[vi].getProperty(zi)))->getData(ind);

            v2 = Ponto_3D(x,y,z);

            ind = ((PlyListProperty*)(itelementsList[fi].getProperty(li)))->getData(i,2);

            x = ((PlyScalarProperty*)(itelementsList[vi].getProperty(xi)))->getData(ind);
            y = ((PlyScalarProperty*)(itelementsList[vi].getProperty(yi)))->getData(ind);
            z = ((PlyScalarProperty*)(itelementsList[vi].getProperty(zi)))->getData(ind);

            v3 = Ponto_3D(x,y,z);

            return Triangulo(-1, v1,v2,v3);
        }

        Iterator(int _i, int _vi, int _fi, int _li, int _xi, int _yi, int _zi, const QVector<PlyElement> &_elementsList):
                i(_i) , vi(_vi) , fi(_fi), li(_li), xi(_xi), yi(_yi), zi(_zi), itelementsList(_elementsList){}

        Iterator(const Iterator& it):
                i(it.i), vi(it.vi) , fi(it.fi), li(it.li), xi(it.xi), yi(it.yi), zi(it.zi), itelementsList(it.itelementsList) {}
        Iterator& operator++() { ++i; return *this; }
        //Iterator& operator++(int a) { Iterator it(*this); ++i; return it; }
        bool operator ==(Iterator& it) { return it.i == i; }
        bool operator !=(Iterator& it) { return it.i != i; }

        int i;
        const int vi;
        const int fi;
        const int li;
        const int xi;
        const int yi;
        const int zi;
        const QVector<PlyElement> &itelementsList;

    };

    typedef PlyParser::Iterator iterator_st;   // iterador para triangulos sem textura

    iterator_st begin(void);
    iterator_st end(void);

private:
    QVector<PlyElement> elementsList;
    QFile file;
    QTextStream *stream;
    QString line;

    bool semPalavras(QString s) {  s.replace(QString(" "), QString(""));  return s.isEmpty(); }

    QString primeiraPalavra() { QTextStream ts(&line, QIODevice::ReadOnly); QString ret; ts >> ret; return ret; }
    void newNoBlancLine();

    int header(void);
    int elements(void);
    int element(void);
    int property(PlyElement &element);
    int cproperty(PlyElement &element);
    int elementLists(void);
    int elementList(PlyElement &element);

    int propertyData(PlyListProperty *pl, QTextStream *st);
    int propertyData(PlyScalarProperty *ps, QTextStream *st);
};

#endif	/* _PLYPARSER_H */

