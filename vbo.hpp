//
//  vbo.hpp
//  fgt
//
//  Created by Albin Stigö on 04/12/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#ifndef vbo_hpp
#define vbo_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VBO {
    GLuint m_vbo;
    GLenum m_usage;
    GLenum m_target;

public:
    VBO(GLenum target, GLenum usage);
    ~VBO();
    void bufferData(GLsizeiptr size, const GLvoid * data);
    void bind();
    void release();
    GLuint vbo();
};

#endif /* vbo_hpp */
