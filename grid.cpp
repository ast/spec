//
//  grid.cpp
//  fgt
//
//  Created by Albin Stigö on 04/12/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#include "grid.hpp"

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Grid::Grid():
m_grid_shader("grid"),
m_grid_vbo(GL_ARRAY_BUFFER, GL_STATIC_DRAW)
{
    
    glm::mat4 ortho = glm::ortho(0.0f, 1.0f, -300.0f, 0.0f, -1.0f, 1.0f);
    m_grid_shader.use();
    m_grid_shader.setUniform("proj", ortho);
    
    vector<float> grid;
    // horizontal lines
    for(int i = 1; i < 10; i++) {
        grid.push_back(0.);
        grid.push_back(-i*20);
        grid.push_back(1.);
        grid.push_back(-i*20);
    }
    // vertical lines
    for(int i = 1; i < 10; i++) {
        float ymax = 0;
        float ymin = -200;
        float x    = i / 10.0;
        
        grid.push_back(x);
        grid.push_back(ymax);
        grid.push_back(x);
        grid.push_back(ymin);
    }
    
    // Upload to GPU
    m_grid_vbo.bind();
    m_grid_vbo.bufferData(grid.size() * sizeof(float), grid.data());
}

Grid::~Grid() { 

}

void Grid::draw() {
    m_grid_shader.use();
    m_grid_shader.enableVertexAttribArray("vec");
    m_grid_vbo.bind();
    m_grid_shader.vertexAttribPointer("vec", 2, GL_FLOAT, GL_FALSE, 0);
    glDrawArrays(GL_LINES, 0, 36); // number of vertecies
    m_grid_vbo.release();
    m_grid_shader.disableVertexAttribArray("vec");
    m_grid_shader.release();

}
