#ifndef GROUP_H
#define GROUP_H

#include "object3d.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include <iostream>
#include <vector>

// TODO: Implement Group - add data structure to store a list of Object*
class Group : public Object3D
{

public:
    Group()
    {
        this->num_objects = 0;
    }

    explicit Group(int num_objects)
    {
        this->num_objects = num_objects;
        objects.clear();
    }

    ~Group() override
    {
    }

    bool intersect(const Ray &r, Hit &h, float tmin) override
    {
        bool result = false;
        for (int index = 0; index < objects.size(); index++)
        {
            result |= objects[index]->intersect(r, h, tmin);
        }
    }

    void addObject(int index, Object3D *obj)
    {
        objects.push_back(obj);
        num_objects++;
    }

    int getGroupSize()
    {
        return num_objects;
    }

private:
    int num_objects;
    vector<Object3D *> objects;
};

#endif
