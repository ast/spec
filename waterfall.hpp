//
//  waterfall.hpp
//  fgt
//
//  Created by Albin Stigö on 05/12/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#ifndef waterfall_hpp
#define waterfall_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "vbo.hpp"

class Waterfall {
    Shader m_quad;
    Shader m_line;
    
    VBO *m_quad_vbo;
    VBO *m_pow;
    VBO *m_bin;
    int m_N;
    int m_H;
    int m_scanline;
    
    GLuint m_fbo;
    GLuint m_fbo_text;
    void createFramebuffer();
    
public:
    Waterfall(VBO *pow, VBO *bin, int N);
    ~Waterfall();
    
    void update();
    void draw();
};

#endif /* waterfall_hpp */
