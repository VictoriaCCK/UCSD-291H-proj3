//
//  RigidBody.cpp
//  291hw3
//
//  Created by Chiu Chi Kwan on 2020/5/27.
//  Copyright © 2020 ChiuChiuKwan. All rights reserved.
//

#include "RigidBody.hpp"

////////////////////////////////////////////////////////////////////////////////

RigidBody::RigidBody(float a, float b, float c, glm::vec3 center, glm::vec3 colour, glm::vec3 rotate, float deg, glm::vec3 translate, float m)
{
    // Model matrix.
    model = glm::mat4(1.0f);

    // The color of the RigidBody. Try setting it to something else!
    color = colour;
    
    Mass = m;
    
    Orientation = glm::mat3(1.f);
    Orientation = glm::mat3(glm::rotate(glm::mat4(1.f), glm::radians(deg), rotate) * glm::mat4(Orientation));
    Position = center + translate;
    
    model = glm::mat4(Orientation);
    model = glm::translate(glm::mat4(1.f), translate) * model;
    
    PrincipalInertia[0][0] = Mass * (pow(b*2, 2) + pow(c*2, 2)) / 12.f;
    PrincipalInertia[1][1] = Mass * (pow(a*2, 2) + pow(c*2, 2)) / 12.f;
    PrincipalInertia[2][2] = Mass * (pow(a*2, 2) + pow(b*2, 2)) / 12.f;
    
    AngularVelocity = glm::inverse(PrincipalInertia) * AngularMomentum;
    
    vertices = {
        glm::vec3( - a, - b, c),
        glm::vec3(   a, - b, c),
        glm::vec3( - a,   b, c),
        glm::vec3(   a,   b, c),

        glm::vec3(    a,  - b,  - c),
        glm::vec3(  - a,  - b,  - c),
        glm::vec3(  - a,    b,  - c),
        glm::vec3(    a,    b,  - c)
    };

    // Specify vertex positions
    positions = {
        // Front
        glm::vec3( - a, - b, c),
        glm::vec3(   a, - b, c),
        glm::vec3(   a,   b, c),
        glm::vec3( - a,   b, c),

        // Back
        glm::vec3(   a, - b, - c),
        glm::vec3( - a, - b, - c),
        glm::vec3( - a,   b, - c),
        glm::vec3(   a,   b, - c),

        // Top
        glm::vec3( - a, b,   c),
        glm::vec3(   a, b,   c),
        glm::vec3(   a, b, - c),
        glm::vec3( - a, b, - c),

        // Bottom
        glm::vec3(  - a,  - b,  - c),
        glm::vec3(    a,  - b,  - c),
        glm::vec3(    a,  - b,    c),
        glm::vec3(  - a,  - b,    c),

        // Left
        glm::vec3(  - a,  - b,  - c),
        glm::vec3(  - a,  - b,    c),
        glm::vec3(  - a,    b,    c),
        glm::vec3(  - a,    b,  - c),

        // Right
        glm::vec3( a, - b,   c),
        glm::vec3( a, - b, - c),
        glm::vec3( a,   b, - c),
        glm::vec3( a,   b,   c)
    };

    // Specify normals
    normals = {
        // Front
        glm::vec3(0,0,1),
        glm::vec3(0,0,1),
        glm::vec3(0,0,1),
        glm::vec3(0,0,1),

        // Back
        glm::vec3(0,0,-1),
        glm::vec3(0,0,-1),
        glm::vec3(0,0,-1),
        glm::vec3(0,0,-1),

        // Top
        glm::vec3(0,1,0),
        glm::vec3(0,1,0),
        glm::vec3(0,1,0),
        glm::vec3(0,1,0),

        // Bottom
        glm::vec3(0,-1,0),
        glm::vec3(0,-1,0),
        glm::vec3(0,-1,0),
        glm::vec3(0,-1,0),

        // Left
        glm::vec3(-1,0,0),
        glm::vec3(-1,0,0),
        glm::vec3(-1,0,0),
        glm::vec3(-1,0,0),

        // Right
        glm::vec3(1,0,0),
        glm::vec3(1,0,0),
        glm::vec3(1,0,0),
        glm::vec3(1,0,0)
    };
    
    // Specify indices
    indices = {
        0,1,2,        0,2,3,            // Front
        4,5,6,        4,6,7,            // Back
        8,9,10,        8,10,11,        // Top
        12,13,14,    12,14,15,        // Bottom
        16,17,18,    16,18,19,        // Left
        20,21,22,    20,22,23,        // Right
    };
    
    // Generate a vertex array (VAO) and two vertex buffer objects (VBO).
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO_positions);
    glGenBuffers(1, &VBO_normals);

    // Bind to the VAO.
    glBindVertexArray(VAO);

    // Bind to the first VBO - We will use it to store the vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), positions.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    // Bind to the second VBO - We will use it to store the normals
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* normals.size(), normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    // Generate EBO, bind the EBO to the bound VAO and send the data
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    // Unbind the VBOs.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////////////////////

RigidBody::~RigidBody()
{
    // Delete the VBOs and the VAO.
    glDeleteBuffers(1, &VBO_positions);
    glDeleteBuffers(1, &VBO_normals);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

////////////////////////////////////////////////////////////////////////////////

void RigidBody::draw(const glm::mat4& viewProjMtx, GLuint shader)
{
    // actiavte the shader program
    glUseProgram(shader);

    // get the locations and send the uniforms to the shader
    glUniformMatrix4fv(glGetUniformLocation(shader, "viewProj"), 1, false, (float*)&viewProjMtx);
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, (float*)&model);
    glUniform3fv(glGetUniformLocation(shader, "DiffuseColor"), 1, &color[0]);

    // Bind the VAO
    glBindVertexArray(VAO);

    // draw the points using triangles, indexed with the EBO
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // Unbind the VAO and shader program
    glBindVertexArray(0);
    glUseProgram(0);
}


void RigidBody::ApplyForce(const glm::vec3&f, const glm::vec3&pos)
{
    Force += f;
//    std::cout<<" pre Torque is "<<to_string(Torque)<<std::endl;
    Torque += glm::cross(pos - Position, f);
}

void RigidBody::Integrate(float timestep)
{
//    std::cout<<" AngularMomentum is "<<to_string(AngularMomentum)<<std::endl;
    AngularMomentum += Torque;
//    std::cout<<" add torque is "<<to_string(Torque)<<std::endl;
    glm::mat3 Inertia = Orientation * PrincipalInertia *  glm::transpose(Orientation);
    AngularVelocity = glm::inverse(Inertia) * AngularMomentum;
//    std::cout<<" Inertia-1 is "<<to_string(glm::inverse(Inertia))<<std::endl;
//    std::cout<<" AngularVelocity is "<<to_string(AngularVelocity)<<std::endl;
    if(glm::length(AngularVelocity) != 0) Orientation = glm::mat3(glm::axisAngleMatrix(AngularVelocity * timestep, glm::length(AngularVelocity * timestep))) * Orientation;
    

    Velocity += Force / Mass;
    Velocity += glm::vec3(0.f , -9.8f, 0.f) * timestep;
    Position += Velocity * timestep;
    model = glm::translate(glm::mat4(1.f), Position) * glm::mat4(Orientation);
    
    
    Force = glm::vec3(0.f);
    Torque = glm::vec3(0.f);
}

bool RigidBody::Collision(float ground)
{
    bool collise = false;
    std::vector<glm::vec3>().swap(CollisionPositions);
    for (int i = 0; i < vertices.size(); i++) {
        glm::vec4 new_p = model * glm::vec4(vertices[i], 1);
        if (new_p.y <= ground) {
            collise = true;
            CollisionPositions.push_back(new_p);
        }
    }
    return collise;
}

glm::vec3 RigidBody::ComputeImpact(glm::vec3 pos, float theta, float mu)
{
    glm::vec3 j = glm::vec3(0.f);
    
    glm::mat3 Inertia = Orientation * PrincipalInertia *  glm::transpose(Orientation);
    
    glm::vec3 r = pos - Position;
    
    glm::vec3 Vr = Velocity + cross(AngularVelocity, r);

//    Fictionless j
    j = glm::vec3(0.f , - (1 + theta) * dot(Vr, ground_normal), 0.f);
    float denominator = 1.f / Mass + dot (ground_normal, cross(glm::inverse(Inertia) * cross(r, ground_normal), r));


    if(denominator == 0) j = glm::vec3(0.f);
    else j /= denominator;
    
//  Fiction
    
    glm::vec3 Vnorm = dot(Vr, ground_normal) * ground_normal;

    glm::vec3 Vtan = Vr - Vnorm;
    if (glm::length(Vtan) != 0) Vtan = glm::normalize(Vtan);

    glm::vec3 friction = glm::vec3(-dot(Vr, Vtan), 0.f, - dot(Vr, Vtan));


    float friction_denominator = 1.f / Mass + dot (Vtan, cross(glm::inverse(Inertia) * cross(r, Vtan), r));


    if(friction_denominator == 0) friction = glm::vec3(0.f);
    else friction /= friction_denominator;


    if (glm::length(friction) >= glm::length(j * mu)) {
        friction = glm::normalize(Vtan);
        friction *= ( -mu * glm::length(j));
    }
    
    j += friction;

    return j ;
}

////////////////////////////////////////////////////////////////////////////////
