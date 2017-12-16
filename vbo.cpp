//
//  vbo.cpp
//  fgt
//
//  Created by Albin Stigö on 04/12/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#include "vbo.hpp"

VBO::VBO(GLenum target, GLenum usage) :
    m_target(target),
    m_usage(usage) {
    glGenBuffers(1, &m_vbo);
}

VBO::~VBO() {
    glDeleteBuffers(1, &m_vbo);
}

GLuint VBO::vbo() { 
    return m_vbo;
}

void VBO::bind() {
    glBindBuffer(m_target, m_vbo);;
}

void VBO::release() {
    glBindBuffer(m_target, 0);
}

void VBO::bufferData(GLsizeiptr size, const GLvoid *data) { 
    bind();
    glBufferData(m_target, size, data, m_usage);
}

