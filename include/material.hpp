#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "ray.hpp"
#include "hit.hpp"
#include <iostream>

// --V--TODO: Implement Shade function that computes Phong introduced in class.
class Material
{
public:
    explicit Material(const Vector3f &d_color, const Vector3f &s_color = Vector3f::ZERO, float s = 0) : diffuseColor(d_color), specularColor(s_color), shininess(s)
    {
    }

    virtual ~Material() = default;

    virtual Vector3f getDiffuseColor() const
    {
        return diffuseColor;
    }

    Vector3f Shade(const Ray &ray, const Hit &hit,
                   const Vector3f &dirToLight, const Vector3f &lightColor)
    {
        Vector3f shaded = Vector3f::ZERO;
        Vector3f L = dirToLight;
        Vector3f N = hit.getNormal();
        Vector3f V = -ray.getDirection();
        Vector3f R = 2 * Vector3f::dot(N, L) * N - L;
        float diffuse = Vector3f::dot(L, N);
        if (diffuse < 0)
            diffuse = 0;
        float specular = Vector3f::dot(V, R);
        if (specular < 0)
            specular = 0;
        specular = pow(specular, shininess);
        // std::cout << "in shade 1" << std::endl;
        // std::cout << diffuse  << "  " << specular << std::endl;
        // this->diffuseColor.print();
        // this->specularColor.print();
        Vector3f m_result = (diffuseColor * diffuse) + (specularColor * specular);
        // std::cout << "in shade 2" << std::endl;
        shaded.x() = lightColor.x() * m_result.x();
        shaded.y() = lightColor.y() * m_result.y();
        shaded.z() = lightColor.z() * m_result.z();
        return shaded;
    }

protected:
    Vector3f diffuseColor;
    Vector3f specularColor;
    float shininess;
};

#endif // MATERIAL_H
