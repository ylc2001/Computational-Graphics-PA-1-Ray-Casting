#ifndef CAMERA_H
#define CAMERA_H

#include "ray.hpp"
#include <vecmath.h>
#include <float.h>
#include <cmath>

class Camera
{
public:
    Camera(const Vector3f &center, const Vector3f &direction, const Vector3f &up, int imgW, int imgH)
    {
        this->center = center;
        this->direction = direction.normalized();
        this->horizontal = Vector3f::cross(this->direction, up).normalized();
        this->up = Vector3f::cross(this->horizontal, this->direction);
        this->width = imgW;
        this->height = imgH;
    }

    // Generate rays for each screen-space coordinate
    virtual Ray generateRay(const Vector2f &point) = 0;
    virtual ~Camera() = default;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // Extrinsic parameters
    Vector3f center;
    Vector3f direction;
    Vector3f up;
    Vector3f horizontal;

protected:
    // Intrinsic parameters
    int width;
    int height;
};

// --V--TODO: Implement Perspective camera
// You can add new functions or variables whenever needed.
class PerspectiveCamera : public Camera
{

public:
    PerspectiveCamera(const Vector3f &center, const Vector3f &direction,
                      const Vector3f &up, int imgW, int imgH, float angle) : Camera(center, direction, up, imgW, imgH)
    {
        // angle is in radian.
        this->angle = angle;
    }

    Ray generateRay(const Vector2f &point) override
    {
        // Fx = Fy
        float Fx = this->getWidth() / (2 * tan(angle / 2));
        float Fy = this->getHeight() / (2 * tan(angle / 2));
        float u = point.x();
        float v = point.y();
        int cx = this->getWidth() / 2;
        int cy = this->getHeight() / 2;
        // Vector3f direction = Vector3f((u - cx) / Fx, (cy - v) / Fy, 1);
        Vector3f Ray_direction = ((u - cx) / Fx) * this->horizontal + ((cy - v) / Fy) * this->up + this->direction;
        Ray_direction.normalize();
        return Ray(this->center, Ray_direction);
    }

    float angle;
};

#endif // CAMERA_H
