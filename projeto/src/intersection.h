#ifndef INTERSECTION_H
#define INTERSECTION_H

class Objeto_3D;

class Intersection
{
    const Objeto_3D * m_object;
    float m_parametrizedDistance;

public:
    enum Mode{
        Nearest,
        First
    };

    Intersection();
    Intersection(const Objeto_3D * m_object, float distance);
    Intersection(const Intersection& copy);

    bool hasIntersection()const;
    float getParametrizedDistance()const;
    const Objeto_3D* getObject()const;

    void clear();
    void setValues(const Objeto_3D * m_object, float distance);

    bool hasPositiveIntersection(float threshold)const;

    const Intersection& operator=(const Intersection& copy);

    static const Intersection& nearest(const Intersection& i1, const Intersection& i2, float threshold);

};

#endif // INTERSECTION_H
