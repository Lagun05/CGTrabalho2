#include "intersection.h"

Intersection::Intersection():
    m_object( (Objeto_3D*)0), m_parametrizedDistance(-1.0)
{

}

Intersection::Intersection(const Objeto_3D * object, float distance) :
    m_object(object), m_parametrizedDistance(distance)
{
}

Intersection::Intersection(const Intersection& copy) :
    m_object(copy.m_object), m_parametrizedDistance(copy.m_parametrizedDistance)
{

}

const Intersection& Intersection::operator=(const Intersection& copy)
{
    m_object = copy.m_object;
    m_parametrizedDistance = copy.m_parametrizedDistance;
    return *this;
}

void Intersection::clear()
{
    m_object = (Objeto_3D*)0;
    m_parametrizedDistance = -1.0;
}

void Intersection::setValues(const Objeto_3D * object, float distance)
{
    m_object = object;
    m_parametrizedDistance = distance;
}

bool Intersection::hasIntersection()const
{
    return m_object != (Objeto_3D*)0;
}
float Intersection::getParametrizedDistance()const
{
    return m_parametrizedDistance;
}

const Objeto_3D* Intersection::getObject()const
{
    return m_object;
}

bool Intersection::hasPositiveIntersection(float threshold)const
{
    return m_object != (Objeto_3D*)0 && m_parametrizedDistance > threshold;
}

const Intersection& Intersection::nearest(const Intersection& i1, const Intersection& i2, float threshold)
{
    if(i1.hasPositiveIntersection(threshold) && i2.hasPositiveIntersection(threshold))
    {
       if( i1.getParametrizedDistance() < i2.getParametrizedDistance())
        return i1;
       else
        return i2;
    }

    if(i1.hasPositiveIntersection(threshold))
        return i1;

    return i2;
}
