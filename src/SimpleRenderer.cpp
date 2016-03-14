//
//  SimpleRenderer.cpp
//  HelloGL2
//
//  Created by André Sá de Mello on 3/10/16.
//  Copyright © 2016 André Sá de Mello. All rights reserved.
//

#include "SimpleRenderer.hpp"
#include "Mesh.hpp"

#include "ResourcePath.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <cmath>

SimpleRenderer::SimpleRenderer(const std::vector<std::shared_ptr<Mesh>>& objects)
{
    this->objects = objects;
}

void SimpleRenderer::init()
{
    // Create and use a vertex/fragment shader program
    shader.loadFromFile(resourcePath() + "vertex.glsl", resourcePath() + "frag.glsl");
    shader.bind();
    
    GLuint shaderProgram = shader.getNativeHandle(); // To use with the OpenGL API
    
    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Set the initial triangle color
    uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
    glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);
    
    uniTrans = glGetUniformLocation(shaderProgram, "trans");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(objects[0]->getTransformation()));
    
    // Set the background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    t_last = std::chrono::high_resolution_clock::now();
    t_total = 0.0;
}

void SimpleRenderer::draw()
{
    // Clear the screen to black
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Get current time
    auto t_now = std::chrono::high_resolution_clock::now();
    
    if (!paused) {
        t_total += std::chrono::duration_cast<std::chrono::duration<double>>(t_now - t_last).count();
    }
    
    // Update counted time
    t_last = t_now;
    
    // Update the triangle color
    glUniform3f(uniColor, (sin(t_total * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
    
    // Update the transformation matrix
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(objects[0]->getTransformation()));
    
    // Draw a triangle from the 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
