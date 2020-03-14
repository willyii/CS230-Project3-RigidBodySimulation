////
////  main.cpp
////  CS230-RigidBodySimulation
////
////  Created by 易昕龙 on 2/26/20.
////  Copyright © 2020 易昕龙. All rights reserved.
////
//
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLUT/GLUT.h>
#include "Sphere.h"
#include "Plane.h"
#include "Object.h"

// Shader File Path
const std::string vertexPath = "/Users/yixinlong/Desktop/CS230/Project3/CS230-Project3-RigidBodySimulation/CS230-RigidBodySimulation/CS230-RigidBodySimulation/vertex";
const std::string fragmentPath = "/Users/yixinlong/Desktop/CS230/Project3/CS230-Project3-RigidBodySimulation/CS230-RigidBodySimulation/CS230-RigidBodySimulation/fragment";

glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) 800/600, 0.1f, 100.0f); // project matrix of this object. set default value, it won't change
glm::mat4 view = glm::lookAt(
                        glm::vec3(20.0, 1.0, 20.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 1.0f, 0.0f)
                    );// view matrix of this object, set default value, it won't change


// declare function
void processInput(GLFWwindow *window);
GLFWwindow* init();




int main(int argc, const char * argv[]) {
    std::vector<Object*> objects;
    objects.push_back(new Plane(20));
    objects.push_back(new Sphere(1));
    int num_object = objects.size();
    std::cout<<"length:" <<num_object<<std::endl;

    // Initialize the window
    GLFWwindow* window = init();
    glEnable(GL_DEPTH_TEST);


    // Initialize the Shader
    Shader ourShader(vertexPath.c_str(), fragmentPath.c_str());

    // vertex buffer object
    unsigned int VAOs[num_object], VBOs[num_object], EBO[num_object];
    glGenVertexArrays(num_object, VAOs);
    glGenBuffers(num_object, VBOs);
    glGenBuffers(num_object, EBO);

    
    for(int i=0; i<num_object; i++){
        
        //VAO
        glBindVertexArray(VAOs[i]);
        
        //VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
        glBufferData(GL_ARRAY_BUFFER, objects[i]->getVertexSize(), objects[i]->getVertices(), GL_DYNAMIC_DRAW);

        //EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, objects[i]->getIndexSize(), objects[i]->getIndices(), GL_DYNAMIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    
    }

    // timing
    float deltaTime = 0.0f;    // time between current frame and last frame
    float lastFrame = 0.0f;
    // main loop render happens here
    while(!glfwWindowShouldClose(window))
    {
        
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime += currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        if(deltaTime < 0.01) continue;
        
        std::cout<<"Delta Time"<<deltaTime<<std::endl;
        std::cout<<"Sphere y position: "<<objects[1]->getPosition().y<<std::endl;
        
        // Make sure it will close
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        //Original Shader
        ourShader.use();
        
        ourShader.setMat4("view", view);

        ourShader.setMat4("projection", projection);
        
        
        for(int i=0;i<num_object;i++){

            ourShader.setMat4("model", objects[i]->getModel());

            objects[i]->updateVelocity(deltaTime, objects);
            
            //bind buffer stuff
            glBindVertexArray(VAOs[i]);
            glDrawElements(GL_TRIANGLES,  (unsigned int)objects[i]->getIndexCount(), GL_UNSIGNED_INT, 0);
            
        }

        
        //check if window should be close
        glfwSwapBuffers(window);
        glfwPollEvents();
        deltaTime = 0.0f;
    }

    for(unsigned i=0; i < objects.size(); i++)
    {
        glDeleteVertexArrays(1, &VAOs[i]);
        glDeleteBuffers(1, &VBOs[i]);
    }
    glfwTerminate();

    return 0;
}


