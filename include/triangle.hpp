#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>
#include <iostream>
using namespace std;

// --V--TODO: implement this class and add more fields as necessary,

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
		E1 = vertices[1] - vertices[0];
		E2 = vertices[2] - vertices[0];
		normal = Vector3f::cross(E1, E2).normalized();
	}

	bool intersect(const Ray &ray, Hit &hit, float tmin) override
	{
		Vector3f Ro = ray.getOrigin();
		Vector3f Rd = ray.getDirection();
		float d = Vector3f::dot(normal, vertices[0]);
		float RHS = d - Vector3f::dot(Ro, normal);
		if (Vector3f::dot(Rd, normal) > 1e-9 || Vector3f::dot(Rd, normal) < -1e-9)
		{
			float t = RHS / Vector3f::dot(Rd, normal);
			if (t > tmin && t < hit.getT())
			{
				Vector3f hit_point = Ro + t * Rd; // judge if point is in triangle
				Vector3f judge1 = Vector3f::cross(E1, hit_point - vertices[0]);
				Vector3f judge2 = Vector3f::cross(vertices[2] - vertices[1], hit_point - vertices[1]);
				Vector3f judge3 = Vector3f::cross(vertices[0] - vertices[2], hit_point - vertices[2]);
				if (Vector3f::dot(judge1, judge2) > 0 && Vector3f::dot(judge1, judge3) > 0)
				{
					if (t <= tmin || t >= hit.getT())
						return false;
					else
					{
						if (Vector3f::dot(normal, Rd) > 0)
							hit.set(t, material, -normal);
						else
							hit.set(t, material, normal);
						return true;
					}
				}
			}
		}
		return false;
	}
	Vector3f normal;
	Vector3f vertices[3];

protected:
	Vector3f E1, E2;
};

#endif // TRIANGLE_H
