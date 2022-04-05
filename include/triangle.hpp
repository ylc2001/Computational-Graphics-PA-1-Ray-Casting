#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>
#include <iostream>
using namespace std;

// TODO: implement this class and add more fields as necessary,
class Triangle : public Object3D
{

public:
	Triangle() = delete;

	// a b c are three vertex positions of the triangle
	Triangle(const Vector3f &a, const Vector3f &b, const Vector3f &c, Material *m) : Object3D(m)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->material = material;
	}

	bool intersect(const Ray &ray, Hit &hit, float tmin) override
	{
		return false;
	}
	Vector3f normal;
	Vector3f vertices[3];

protected:
	Vector3f a, b, c;
	Material *material;
};

#endif // TRIANGLE_H
