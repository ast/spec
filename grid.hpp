//
//  grid.hpp
//  fgt
//
//  Created by Albin Stigö on 04/12/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#ifndef grid_hpp
#define grid_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vbo.hpp"
#include "shader.hpp"

class Grid {
    Shader m_grid_shader;
    VBO m_grid_vbo;
    
public:
    Grid();
    ~Grid();
    
    void draw();
};


#endif /* grid_hpp */
