//////
//////  main.cpp
//////  CS230-RigidBodySimulation
//////
//////  Created by 易昕龙 on 2/26/20.
//////  Copyright © 2020 易昕龙. All rights reserved.
//////
////
//#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <cmath>
//#include "Shader.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <GLUT/GLUT.h>
//
//// Shader File Path
//const std::string vertexPath = "/Users/yixinlong/Desktop/CS230/Project3/CS230-Project3-RigidBodySimulation/CS230-RigidBodySimulation/CS230-RigidBodySimulation/vertex";
//const std::string fragmentPath = "/Users/yixinlong/Desktop/CS230/Project3/CS230-Project3-RigidBodySimulation/CS230-RigidBodySimulation/CS230-RigidBodySimulation/fragment";
//const std::string lightvPath = "/Users/yixinlong/Desktop/CS230/Project3/CS230-Project3-RigidBodySimulation/CS230-RigidBodySimulation/CS230-RigidBodySimulation/light_vertex";
//const std::string lightfPath = "/Users/yixinlong/Desktop/CS230/Project3/CS230-Project3-RigidBodySimulation/CS230-RigidBodySimulation/CS230-RigidBodySimulation/light_frag";
//
//float vertices[] = {
//    -0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f,  0.5f, -0.5f,
//     0.5f,  0.5f, -0.5f,
//    -0.5f,  0.5f, -0.5f,
//    -0.5f, -0.5f, -0.5f,
//
//    -0.5f, -0.5f,  0.5f,
//     0.5f, -0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f,  0.5f,
//    -0.5f, -0.5f,  0.5f,
//
//    -0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f, -0.5f,
//    -0.5f, -0.5f, -0.5f,
//    -0.5f, -0.5f, -0.5f,
//    -0.5f, -0.5f,  0.5f,
//    -0.5f,  0.5f,  0.5f,
//
//     0.5f,  0.5f,  0.5f,
//     0.5f,  0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//
//    -0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f,  0.5f,
//     0.5f, -0.5f,  0.5f,
//    -0.5f, -0.5f,  0.5f,
//    -0.5f, -0.5f, -0.5f,
//
//    -0.5f,  0.5f, -0.5f,
//     0.5f,  0.5f, -0.5f,
//     0.5f,  0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f, -0.5f,
//};
//
//
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//
//
//// declare function
//void processInput(GLFWwindow *window);
////int Shader(const std::string FilePath, std::string Shader_type);
//GLFWwindow* init();
//
//
//int main(int argc, const char * argv[]) {
//
//
//    // Initialize the window
//    GLFWwindow* window = init();
//    glEnable(GL_DEPTH_TEST);
//
//
//    // Initialize the Shader
//    Shader ourShader(vertexPath.c_str(), fragmentPath.c_str());
//    Shader lightShader(lightvPath.c_str(),  lightfPath.c_str());
//
//    // vertex buffer object
//    unsigned int VAOs, VBOs;
//    glGenVertexArrays(1, &VAOs);
//    glGenBuffers(1, &VBOs);
//
////    glutSolidSphere(0.3,2,3);
//
//    //VBO
//    glBindBuffer(GL_ARRAY_BUFFER, VBOs);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    //VAO
//    glBindVertexArray(VAOs);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//
//    //LightVAO
//    unsigned int LightVAO;
//    glGenVertexArrays(1, &LightVAO);
//    glBindVertexArray(LightVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBOs);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//
//    glutSolidSphere(3.0, 3, 3);
//
//
//    // main loop render happens here
//    while(!glfwWindowShouldClose(window))
//    {
//        // per-frame time logic
//        // --------------------
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//        processInput(window);
//
//
//        // render
//        // ------
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        //Original Shader
//        ourShader.use();
//        ourShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
//        ourShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
//
//        // View Marix
//        glm::mat4 view = glm::lookAt(
//                           glm::vec3(0.0f, 0.0f, 6.0f),
//                           glm::vec3(0.0f, 0.0f, 5.0f),
//                           glm::vec3(0.0f, 1.0f, 0.0f));
//        ourShader.setMat4("view", view);
//
//        // Projection Matrix
//        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) 800/600, 0.1f, 100.0f);
//        ourShader.setMat4("projection", projection);
//
//        // Model Matrix
//        glm::mat4 model = glm::mat4(1.0f);
//        ourShader.setMat4("model", model);
//
//        // Draw the cube
//        glBindVertexArray(VAOs);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//        //Light Shader
//        lightShader.use();
//        lightShader.setMat4("projection", projection);
//        lightShader.setMat4("view", view);
//        model = glm::translate(glm::mat4(1.0f), lightPos);
//        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
//        lightShader.setMat4("model", model);
//
//        //Draw the light
//        glBindVertexArray(LightVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//        glBindVertexArray(0);
//
//        //check if window should be close
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
////    glDeleteVertexArrays(1, &VAO);
//    glfwTerminate();
//
//
//    return 0;
//}
//
//
//
//

//#include <windows.h>
//#include <GL/glut.h>
#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#endif
//#include <GLUT/GLUT.h>
 
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
 
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
 
static void display(void)
{
 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);
 
    glPushMatrix();
        glTranslated(0.0,1.2,-6);
        glutSolidSphere(1,50,50);
    glPopMatrix();
 
    glPushMatrix();
        glTranslated(0.0,-1.2,-6);
        glutWireSphere(1,16,16);
    glPopMatrix();
 
    glutSwapBuffers();
}
 
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
 
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
 
/* Program entry point */
 
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
 
    glutCreateWindow("Programming Techniques - 3D Spheres");
 
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
 
    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
 
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
 
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
 
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
 
    glutMainLoop();
 
    return EXIT_SUCCESS;
}
