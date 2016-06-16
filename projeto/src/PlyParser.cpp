#include <PlyParser.h>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>

void PlyParser::newNoBlancLine()
{
    QString pp;
    do{
        line = stream->readLine();
        pp = primeiraPalavra();
    }while(semPalavras(pp) || pp == "comment" || pp == "{" || pp == "obj_info");
}

int PlyParser::parse(void)
{
    file.open(QIODevice::ReadOnly);
    stream = new QTextStream(&file);
    newNoBlancLine();

    if(header() == 0)
        return 0;

    return elementLists();
}

int PlyParser::header(void)
{
    QString word;
    QTextStream *st = new QTextStream(&line, QIODevice::ReadOnly);

    *st >> word;
    if(word != "ply")
        return 0;

    delete st;
    newNoBlancLine();
    st = new QTextStream(&line, QIODevice::ReadOnly);

    *st >> word;
    if(word != "format")
        return 0;
    *st >> word;
    if(word != "ascii")
        return 0;
    *st >> word;
    if(word != "1.0")
        return 0;

    delete st;
    newNoBlancLine();

    if(elements() == 0)
        return 0;

    //newNoBlancLine();
    st = new QTextStream(&line, QIODevice::ReadOnly);
    *st >> word;
    if(word != "end_header")
        return 0;

    delete st;

    return 1;
}

int PlyParser::elements(void)
{
    if(element() == 0)
        return 0;

    while(element() == 1);

    return 1;
}

int PlyParser::element(void)
{
    QString pp = primeiraPalavra();
    QString word;
    QTextStream *st;
    int qtd = -1;


    if(pp != "element")
        return 0;

    st = new QTextStream(&line, QIODevice::ReadOnly);

    *st >> word;

    *st >> word;
    if(word != "vertex" && word != "face" && word != "material")
        return 0;

    *st >> qtd;
    if(qtd == -1)
        return 0;

    PlyElement element(word,qtd);

    delete st;
    newNoBlancLine();

    property(element);
    elementsList.push_back(element);

    return 1;
}

int PlyParser::property(PlyElement &element)
{
    if(cproperty(element) == 0)
        return 0;

    while(cproperty(element) == 1);

    return 1;
}

int PlyParser::cproperty(PlyElement &element)
{
    QString word;
    QTextStream *st;
    QString pp = primeiraPalavra();

    if(pp != "property")
        return 0;

    st = new QTextStream(&line, QIODevice::ReadOnly);
    *st >> word; // retirar property

    *st >> word; // tipo ou list
    if(word == "list")
    {
        *st >> word; // uchar
        *st >> word; // int
        *st >> word; // nome

        PlyListProperty *lp = new PlyListProperty(word);
        element.addProperty(lp);

    }else
    {
        *st >> word; // nome

        PlyScalarProperty *sp = new PlyScalarProperty(word);
        element.addProperty(sp);
    }

     delete st;
     newNoBlancLine();

     return 1;
}


int PlyParser::elementLists(void)
{
    for(int i = 0 ; i < elementsList.size(); ++i)
    {
        if(elementList(elementsList[i]) == 0)
            return 0;
    }

    return 1;
}

int PlyParser::elementList(PlyElement &element)
{
    PlyListProperty *pl = NULL;
    PlyScalarProperty * ps = NULL;
    QTextStream *st;

    for(int i = 0; i < element.getNElements(); ++i)
    {
        newNoBlancLine();
        st = new QTextStream(&line, QIODevice::ReadOnly);
        for(int j = 0; j < element.getPropertyListSize(); ++j)
        {
            if(element.getProperty(j)->getType() == PlyProperty::SCALAR)
            {
                ps = ((PlyScalarProperty*) element.getProperty(j));
                if(propertyData(ps, st) == 0)
                    return 0;
            }else
            {
                pl = (PlyListProperty*)element.getProperty(j);
                if(propertyData(pl, st) == 0)
                    return 0;
            }
        }
        delete st;
    }

    return 1;
}

int PlyParser::propertyData(PlyListProperty *pl, QTextStream *st)
{
    QVector<int> vec;
    int val;
    int tam;

    *st >> tam;

    if(tam != 3) // somente triangulos
        return 0;

    for(int i = 0; i < tam; ++i)
    {
        *st >> val;
        vec.push_back(val);
    }
    pl->addData(vec);

    return 1;
}

int PlyParser::propertyData(PlyScalarProperty *ps, QTextStream *st)
{
    float val;

    *st >> val;

    ps->addData(val);

    return 1;
}

PlyParser::iterator_st PlyParser::begin(void)
{
    int vi, fi, li, xi, yi, zi;

    vi = findByName("vertex");
    fi = findByName("face");

    li = elementsList[fi].findByName("vertex_indices");

    xi = elementsList[vi].findByName("x");
    yi = elementsList[vi].findByName("y");
    zi = elementsList[vi].findByName("z");

    PlyParser::Iterator it(0,vi,fi,li,xi,yi,zi,elementsList);
    return it;
}

PlyParser::iterator_st PlyParser::end(void)
{
    int vi, fi, li, xi, yi, zi;
    int fim;

    vi = findByName("vertex");
    fi = findByName("face");

    li = elementsList[fi].findByName("vertex_indices");

    xi = elementsList[vi].findByName("x");
    yi = elementsList[vi].findByName("y");
    zi = elementsList[vi].findByName("z");

    fim = elementsList[fi].getNElements();

    PlyParser::Iterator it(fim,vi,fi,li,xi,yi,zi,elementsList);
    return it;
}
