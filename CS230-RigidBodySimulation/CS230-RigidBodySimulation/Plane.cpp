//
//  Plane.cpp
//  CS230-RigidBodySimulation
//
//  Created by 易昕龙 on 3/10/20.
//  Copyright © 2020 易昕龙. All rights reserved.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Plane.h"
#include <GLUT/GLUT.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// Initial some variable
// Input:
// lowleft: position of lowleft vertex
// upright: position of upright vertex
// dim_step: step of each vertex along each axis
Plane::Plane(int dimension, bool moveable, glm::vec3 position, glm::vec3 velocity)
{
    this->name = 2;
    this->dimension = dimension;
    this->moveable = moveable;
    this->position = position;
    this->force = glm::vec3();
    this->velocity = velocity;
    this->model = glm::translate(glm::mat4(1.0f), position);
    init();
}

Plane::~Plane()
{
    
}

//initialize the vertices and indces
void Plane::init()
{
    //initialize the vertices
    int half = dimension/2;
    for(int i=0; i<dimension; i++){
        for(int j=0; j<dimension; j++){
            rs.push_back(glm::vec3((j-half) * dim_step, 0.0f, (i-half)*dim_step));
            addVertices((j-half)*dim_step, 0.0f, (i-half)*dim_step);
        }
    }
    
    //initialize the indices
    for(unsigned int i=0; i<dimension-1;i++){
        for(unsigned int j=0; j<dimension-1; j++){
            //first triangle
            addIndices(i*dimension+j, i*dimension+j+dimension, i*dimension+j+dimension + 1);
            //second one
            addIndices(i*dimension+j, i*dimension+j+dimension+1,
                       i*dimension+1 +j);
        }
    }
    
    //init the mass
    this->mass = getVertexCount();
}

//push vertex to the back
void Plane::addVertices(float x, float y, float z)
{
    this->vertices.push_back(x);
    this->vertices.push_back(y);
    this->vertices.push_back(z);
}


//push index to the back
void Plane::addIndices(float x, float y, float z)
{
    this->indices.push_back(x);
    this->indices.push_back(y);
    this->indices.push_back(z);

}

void Plane::caculateForce(std::vector<Object*> &objects)
{
    this->force = glm::vec3(0.0f, 0.0f ,0.0f);
    force.y += mass * -9.8f;//add gravity to the object
    // todo: caculate the collusion and its force
};

// update the velocity of the plane
void Plane::updateVelocity(float time, std::vector<Object*> &objects)
{
    if(!moveable) return;
    caculateForce(objects);
    velocity += (force/mass) * time;
    updateVertices(time);
}

// update the data of vertices
void Plane::updateVertices(float time)
{
    //update the position, other velocity can be caculate by r
    position += velocity * time;
    model = glm::translate(glm::mat4(1.0f), position);
//    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}


//detecte if this object collision with other or not
bool Plane::collision(std::vector<Object*> &objects)
{
    return false;
}




///////////////////////////////////////////////////////////////////////////////
// Debug stuff
///////////////////////////////////////////////////////////////////////////////
void Plane::printSelf()
{
    std::cout << "===== Plane =====\n"
              << "     Dimension: " << dimension << "\n"
              << "Dimension Step: " << dim_step << "\n"
              << "  Vertex Count: " << vertices.size()/3 << "\n"
              << "       r Count: " << rs.size() << "\n"
              << "        Center: " << position.x  << ","
              << position.y  << ","
              << position.z  << "\n"
              << " Indices Count: " << indices.size()
              <<std::endl;
    
    for(int i = 0; i< getVertexCount(); i++){
        std::cout<<vertices[i]<<std::endl;
    }
  
}


