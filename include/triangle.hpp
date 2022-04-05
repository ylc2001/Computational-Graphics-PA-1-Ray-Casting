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
		this->material = material;
		u = vertices[1] - vertices[0];
		v = vertices[2] - vertices[0];
		normal = Vector3f::cross(u, v);
		normal.normalize();
	}

	bool intersect(const Ray &ray, Hit &hit, float tmin) override
	{
		Vector3f Ro = ray.getOrigin();
		Vector3f Rd = ray.getDirection();
		if (fabs(Vector3f::dot(normal, Rd)) < 0.00001)
		{
			return false;
		}
		else
		{
			Vector3f w0 = Ro - vertices[0];
			float D = -Vector3f::dot(w0, normal);
			float t = -(D + Vector3f::dot(normal, Ro)) / (Vector3f::dot(normal, Rd));
			if (t < tmin)
				return false;
			else
			{
				Vector3f interPoint = Ro + t * Rd;
				float uu = Vector3f::dot(u, u);
				float uv = Vector3f::dot(u, v);
				float vv = Vector3f::dot(v, v);
				Vector3f w = interPoint - vertices[0];
				float wu = Vector3f::dot(w, u);
				float wv = Vector3f::dot(w, v);
				float A = uv * uv - uu * vv;

				float test1 = (uv * wv - vv * wu) / D;
				if (test1 < 0.0f || test1 > 1.0f) // I is outside T
					return false;

				float test2 = (uv * wu - uu * wv) / D;
				if (test2 < 0.0f || (test1 + test2) > 1.0f) // I is outside T
					return false;

				hit.set(t, this->material, normal);
				return true; // 交点在三角形内部
			}
		}
	}
	Vector3f normal;
	Vector3f vertices[3];

protected:
	//Vector3f a, b, c, n, 
	Vector3f u, v;
	Material *material;
};

#endif // TRIANGLE_H
