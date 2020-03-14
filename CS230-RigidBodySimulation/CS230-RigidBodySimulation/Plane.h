//
//  Plane.hpp
//  CS230-RigidBodySimulation
//
//  Created by 易昕龙 on 3/10/20.
//  Copyright © 2020 易昕龙. All rights reserved.
//

#ifndef Plane_h
#define Plane_h

#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "Object.h"

class Plane:public Object
{
public:
    Plane(int dimension,
          bool moveable = false,
          glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f));
    ~Plane();
    
    void init() override;
    void printSelf() override;
    void updateVertices(float time) override;
    void updateVelocity(float time, std::vector<Object*> &objects) override;
    void caculateForce(std::vector<Object*> &objects) override;
    bool collision(std::vector<Object*> &objects) override;
    
    //some method to get vars
    int getDim() const {return dimension;}
    float getDimStep() const {return dim_step;}
    
    
private:
    //methods
    void addIndices(float x, float y, float z);
    void addVertices(float x, float y, float z);
    
    //vars
    float dim_step = 0.3f;
    int dimension;
};

#endif /* Plane_hpp */
