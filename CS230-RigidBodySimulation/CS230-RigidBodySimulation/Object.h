//
//  Object.h
//  CS230-RigidBodySimulation
//
//  Created by 易昕龙 on 3/11/20.
//  Copyright © 2020 易昕龙. All rights reserved.
//

#ifndef Object_h
#define Object_h

#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object
{
public:
    // virtual function will be rewrite in subclass
    virtual void init(){};//initialize the vertices and indices of this object
    virtual void printSelf(){}; // print this objects' infomation
    virtual void updateVertices(float time){};
    virtual void updateVelocity(float time, std::vector<Object*> &objects){};
    virtual void caculateForce(std::vector<Object*> &objects){};
    virtual bool collision(std::vector<Object*> &objects){return false;};
    
    //Some static function that will not be modified in sub class
    const float* getVertices() const {return vertices.data();}
    const int* getIndices() const {return indices.data();}
    unsigned int getVertexCount() const { return (unsigned int)vertices.size() / 3; }
    unsigned int getIndexCount() const  { return (unsigned int)indices.size(); }
    unsigned int getVertexSize() const { return (unsigned int)vertices.size() * sizeof(float); }
    unsigned int getIndexSize() const { return (unsigned int)indices.size() * sizeof(unsigned int); }
    unsigned int getMass() const{return (unsigned int) mass;}
    glm::mat4 getModel() const {return model;}
//    glm::mat4 getProjection() const {return projection;}
//    glm::mat4 getView() const {return view;}
    int getName() const {return name;}
    glm::vec3 getPosition() const {return position;};
    glm::vec3 getVelocity() const {return velocity;}
    

protected:
    float mass;//rigid body's mass
    std::vector<float> vertices;//vertices of an object
    std::vector<int> indices; // indices of vertices in this object
    glm::mat4 model; // model matrix
    glm::vec3 velocity;// velocity of object
    glm::vec3 position;// position of object, used in translate
    std::vector<glm::vec3> rs; // r of vertices
    bool moveable;//set this object moveable or not
    glm::vec3 force; // the force this object get
    int name; // the type indicator: 1. Sphere, 2. Plane
};

#endif /* Object_h */
