//
//  Sphere.hpp
//  CS230-RigidBodySimulation
//
//  Created by 易昕龙 on 3/7/20.
//  Copyright © 2020 易昕龙. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "Object.h"
#include "Plane.h"

class Sphere:public Object
{
public:
    Sphere(float radius,
           bool moveable = true,
           glm::vec3 position = glm::vec3(0.0f, 15.0f ,0.0f),
           glm::vec3 velocity = glm::vec3(0.0f, 0.0f ,0.0f));
    ~Sphere();
    void init() override;
    void printSelf() override;
    void updateVertices(float time) override;
    void updateVelocity(float time, std::vector<Object*> &objects) override;
    void caculateForce(std::vector<Object*> &objects) override;
    bool collision(std::vector<Object*> &objects) override;
    // some methods to get vars
    float getRadius() const {return radius;}
    

    
private:
    //vars
    float radius;
    //methods
    void addIndices(float x, float y, float z);
    void addVertices(float x, float y, float z);
    bool intersect(Sphere* object);
    bool intersect(Plane* object);


    

};




#endif /* Sphere_hpp */
