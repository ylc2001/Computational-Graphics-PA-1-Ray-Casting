#ifndef SPHERE_H
#define SPHERE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>

// TODO: Implement functions and add more fields as necessary

class Sphere : public Object3D
{
public:
    Sphere() : _center(Vector3f())
    {
        // unit ball at the center
        _radius = 1;
    }

    Sphere(const Vector3f &center, float radius, Material *material) : Object3D(material), _center(Vector3f(center))
    {
        //
        _radius = radius;
    }

    ~Sphere() override = default;

    bool intersect(const Ray &r, Hit &h, float tmin) override
    {
        //
        //Vector3f Ro = r.getOrigin();
        //Vector3f Rd = r.getDirection();
        //Vector3f Pc = this->_center;
        //float b = Vector3f::dot(Rd, Ro - Pc);
        //float c = Vector3f::dot(Ro - Pc, Ro - Pc) - (_radius * _radius);
        //if (b * b - c >= 0)
        //{
        //    float t_1 = -b + sqrt(b * b - c);
        //}
        //else
        //{
        //    return false;
        //}
    }

protected:
    Vector3f &_center;
    float _radius;
};

#endif
