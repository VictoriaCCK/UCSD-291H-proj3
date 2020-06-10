//
//  Ground.hpp
//  291hw3
//
//  Created by Chiu Chi Kwan on 2020/5/27.
//  Copyright © 2020 ChiuChiuKwan. All rights reserved.
//


#ifndef ground_hpp
#define ground_hpp

#include <stdio.h>
#include "core.h"

////////////////////////////////////////////////////////////////////////////////

class Ground
{
private:
    GLuint VAO;
    GLuint VBO_positions, VBO_normals, EBO;
    
    glm::mat4 model;
    glm::vec3 color;
    
    // Ground Information
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;
    
public:
    Ground(glm::vec3 cubeMin=glm::vec3(-500, -2.5, -1000), glm::vec3 cubeMax=glm::vec3(500, 2.5, 1000));
    ~Ground();
    
    float theta = 0.8f;
    float mu = 0.001f;
    void draw(const glm::mat4& viewProjMtx, GLuint shader);
    void update();
    
    void spin(float deg);
};

////////////////////////////////////////////////////////////////////////////////

#endif /* ground_hpp */
