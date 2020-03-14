//
//  Sphere.cpp
//  CS230-RigidBodySimulation
//
//  Created by 易昕龙 on 3/7/20.
//  Copyright © 2020 易昕龙. All rights reserved.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Sphere.h"
#include <GLUT/GLUT.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>




// Initial
Sphere::Sphere(float radius, bool moveable, glm::vec3 position, glm::vec3 velocity)
{
    this->name = 1;
    this->radius = radius;
    this->moveable = moveable;
    this->position = position;
    this->force = glm::vec3();
//    this->velocity = velocity;
    this->velocity = glm::vec3(0.0f, -2.0f , 0.0f);
    this->model = glm::translate(glm::mat4(1.0f), position);
    init();

}

Sphere::~Sphere()
{

}

// Initialize the sphere
void Sphere::init()
{
    const float PI = acos(-1);
    //Define angle and step
    int stackCount = 100, sectorCount = 100;
    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;
    
    float x,y,z,xy;
    
    
    // vertices
    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cos(stackAngle);             // r * cos(u)
        z = radius * sin(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi
            
            // vertex position
            x = xy * cos(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sin(sectorAngle);             // r * cos(u) * sin(v)
            rs.push_back(glm::vec3(x,y,z));
            addVertices(x,y,z);
        }
    }
    
    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if(i != 0)
            {
                addIndices(k1, k2, k1+1);   // k1---k2---k1+1
            }

            if(i != (stackCount-1))
            {
                addIndices(k1+1, k2, k2+1); // k1+1---k2---k2+1
            }
        }
    }
    
    mass = this->getVertexCount();
}

//push index to the back
void Sphere::addIndices(float x, float y, float z)
{
    this->indices.push_back(x);
    this->indices.push_back(y);
    this->indices.push_back(z);

}

//push vertex to the back
void Sphere::addVertices(float x, float y, float z)
{
    this->vertices.push_back(x);
    this->vertices.push_back(y);
    this->vertices.push_back(z);
}

//caculate the force of this object
void Sphere::caculateForce(std::vector<Object*> &objects)
{
    this->force = glm::vec3(0.0f, 0.0f ,0.0f);
    force.y += mass * -9.8f;//add gravity to the object
    // todo: caculate the collusion and its force
}


//Update the vocelity
void Sphere::updateVelocity(float time, std::vector<Object*> &objects)
{
    if(!moveable) return;
    caculateForce(objects);
    velocity += (force/mass) * time;
    if(glm::length(velocity) < 0.1) velocity = glm::vec3();
    updateVertices(time);
    if(collision(objects)) {velocity = velocity * (-0.5f);return;}
}

//Change the vertices data according to the center
void Sphere::updateVertices(float time)
{
    //update the position, other velocity can be caculate by r
    position += velocity * time;
    model = glm::translate(glm::mat4(1.0f), position);
}


//detecte if this object collision with other or not
bool Sphere::collision(std::vector<Object*> &objects)
{
    for(unsigned int i =0; i< objects.size(); i++)
    {
        // if object self, do not check
        if(objects[i] == this) continue;
        
        // set intersect indicator
        bool indicator = false;
        switch(objects[i]->getName()){
                
            case 1:// if this object is Sphere
                indicator = intersect(dynamic_cast<Sphere*>(objects[i]));
            
            case 2:// if this object is Plane
                indicator = intersect(dynamic_cast<Plane*>(objects[i]));
        }
        if(indicator == true) return true;
    }
    return false;
}


//Check if intersect with Sphere or not
bool Sphere::intersect(Sphere *object)
{
    //check dynamic cast work or not
    if(object == nullptr) {std::cout<<"Error: null pointer in intersectSphere"<<std::endl; return false;}
    
    //check intersection
    float distance = glm::length(this->position - object->getPosition());
    return distance < (this->radius + object->getRadius());
}


//Check if intersect with Sphere or not
bool Sphere::intersect(Plane *object)
{
    //check dynamic cast work or not
    if(object == nullptr) {std::cout<<"Error: null pointer in intersectPlane"<<std::endl; return false;}
    
    if(abs(position.y - object->getPosition().y) > radius) return false;
    return true;
//    //Assuming the plane won't rotate in all time;
//    float dist_x = abs(position.x - object->getPosition().x);
//    float dist_y = abs(position.y - object->getPosition().y);
//    float dist_z = abs(position.z - object->getPosition().z);
//
//    float slope;
//    if(dict_z < dist_x) slope = atan(dist_z/dist_x);
//    else slope = atan(dist_x/dist_z);
//

}



///////////////////////////////////////////////////////////////////////////////
// Debug stuff
///////////////////////////////////////////////////////////////////////////////
void Sphere::printSelf()
{
    std::cout << "===== Sphere =====\n"
              << "        Radius: " << radius << "\n"
              << "   Index Count: " << indices.size() << "\n"
              << "  Vertex Count: " << vertices.size()/3 << "\n"
              << "       r Count: " << rs.size() << "\n"
              << "        Center: " << position.x  << ","
              << position.y  << ","
              << position.z  <<std::endl;
}

