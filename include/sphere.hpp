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

    Sphere(const Vector3f &center, float radius, Material *material)
        : Object3D(material), _center(center)
    {
        //
        _radius = radius;
    }

    ~Sphere() override = default;

    bool intersect(const Ray &r, Hit &h, float tmin) override
    {
        //
        Vector3f Ro = r.getOrigin();
        Vector3f Rd = r.getDirection();
        Vector3f Pc = this->_center;
        float b = Vector3f::dot(Rd, Ro - Pc);
        float c = Vector3f::dot(Ro - Pc, Ro - Pc) - (_radius * _radius);
        float result_t;
        if (b * b - c >= 0)
        {
            float t_1 = -b + sqrt(b * b - c);
            float t_2 = -b - sqrt(b * b - c);
            if (t_1 == t_2)
            {
                if (t_1 < tmin)
                    return false;
                else
                {
                    result_t = t_1;
                    // return true;
                }
            }
            else
            {
                if (max(t_1, t_2) < tmin)
                    return false;
                else if (min(t_1, t_2) < tmin)
                {
                    result_t = max(t_1, t_2);
                    // return true;
                }
                else
                {
                    result_t = min(t_1, t_2);
                    // return true;
                }
            }
            Vector3f n = Ro + (result_t * Rd) - Pc; //法向量
            n.normalize();
            h.set(result_t, this->material, n);
            return true;
        }
        else
        {
            return false;
        }
    }

protected:
    Vector3f _center;
    float _radius;
};

#endif
