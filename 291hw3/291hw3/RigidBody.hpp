//
//  RigidBody.hpp
//  291hw3
//
//  Created by Chiu Chi Kwan on 2020/5/27.
//  Copyright © 2020 ChiuChiuKwan. All rights reserved.
//

#ifndef RigidBody_hpp
#define RigidBody_hpp

#include <stdio.h>
#include "main.h"
#include "core.h"

class RigidBody
{
private:
    GLuint VAO;
    GLuint VBO_positions, VBO_normals, EBO;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;
    glm::vec3 color;

public:
    // Cube Information
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> CollisionPositions;
    float Mass = 0.1f;
    glm::vec3 ground_normal = glm::vec3(0.f, 1.f, 0.f);
    
    glm::vec3 Position = glm::vec3(0.f);
    
    glm::vec3 Force = glm::vec3 (0.f);
    glm::vec3 Torque = glm::vec3 (0.f);
    glm::mat3 PrincipalInertia = glm::mat3(1.f);
    glm::vec3 Momentum;
    glm::vec3 Velocity = glm::vec3(0.f, 0.f, 0.0f);
    glm::mat3 Orientation = glm::mat3(1.f);
    glm::vec3 AngularVelocity = glm::vec3 (0.0f, 0.0f, 0.f);
    glm::vec3 AngularMomentum = glm::vec3 (0.0f, 0.0f, 3.16f);

    RigidBody(float a, float b, float c, glm::vec3 center, glm::vec3 colour, glm::vec3 rotate, float deg, glm::vec3 translate, float m);
    ~RigidBody();
    glm::mat4 model = glm::mat4(1.f);
    
    bool move = false;
    void draw(const glm::mat4& viewProjMtx, GLuint shader);
    
    void ApplyForce(const glm::vec3&f, const glm::vec3&pos);
    void Integrate(float timestep);
    bool Collision(float ground);
    glm::vec3 ComputeImpact(glm::vec3 pos, float theta, float mu);
};


#endif /* RigidBody_hpp */
