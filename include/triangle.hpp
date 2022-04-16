#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>
#include <iostream>
using namespace std;

// --V--TODO: implement this class and add more fields as necessary,

// reference: https://blog.csdn.net/linolzhang/article/details/55548707

class Triangle : public Object3D
{

public:
	Triangle() = delete;

	// a b c are three vertex positions of the triangle
	Triangle(const Vector3f &a, const Vector3f &b, const Vector3f &c, Material *m) : Object3D(m)
	{
		vertices[0] = a;
		vertices[1] = b;
		vertices[2] = c;
		Vector3f E1 = vertices[1] - vertices[0];
		Vector3f E2 = vertices[2] - vertices[0];
		normal = Vector3f::cross(E1, E2).normalized();
	}

	bool intersect(const Ray &ray, Hit &hit, float tmin) override
	{
		Vector3f Ro = ray.getOrigin();
		Vector3f Rd = ray.getDirection();
		Vector3f P = Vector3f::cross(Rd, E2);
		float det = Vector3f::dot(E1, P);
		if (fabs(Vector3f::dot(Rd, normal)) > 1e-9)
		{
			Vector3f S = Ro - vertices[0];
			float u = Vector3f::dot(S, P) / det;
			if (u < 0 || u > 1)
				return false;

			Vector3f Q = Vector3f::cross(S, E1);
			float v = Vector3f::dot(Rd, Q) / det;
			if (v < 0 || u + v > 1)
				return false;

			float t = Vector3f::dot(E2, Q) / det;

			if (Vector3f::dot(Rd, normal) > 0)
				hit.set(t, material, -normal);
			else
				hit.set(t, material, normal);
			return true;
		}
		return false;
	}
	Vector3f normal;
	Vector3f vertices[3];

protected:
	Vector3f E1, E2;
};

#endif // TRIANGLE_H
