//
//  waterfall.cpp
//  fgt
//
//  Created by Albin Stigö on 05/12/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#include "waterfall.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Waterfall::Waterfall(VBO *pow, VBO *bin, int N):
m_pow(pow),
m_bin(bin),
m_quad("textured_quad"),
m_line("colored_line"),
m_N(N),
m_H(512),
m_scanline(0)
{
    GLfloat quad_vertices[] = {-1, -1, // bottom left corner
        -1,  1, // top left corner
        1,  1, // top right corner
        1, 1, // top right
        1,-1, // bottom right
        -1,-1}; // bottom left corner
    
    m_quad_vbo = new VBO(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    // upload quad vertecies
    m_quad_vbo->bufferData(sizeof(quad_vertices), quad_vertices);
    
    glm::mat4 ortho;
    
    // Setup uniforms for textured quad
    m_quad.use();
    ortho = glm::ortho(-1.0f, 1.0f, -1.0f, 2.5f, -1.0f, 1.0f);
    m_quad.setUniform("ortho", ortho);
    m_quad.setUniform("waterfall", 0);
    m_quad.release();
    // Uniforms for rendering to texture
    m_line.use();
    ortho = glm::ortho(0.f, (float)m_N, 0.f, (float)m_H, -1.0f, 1.0f);
    m_line.setUniform("ortho", ortho);
    m_line.release();
    
    createFramebuffer();
}

void Waterfall::createFramebuffer() {
    glGenTextures(1, &m_fbo_text);
    glBindTexture(GL_TEXTURE_2D, m_fbo_text);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_N, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fbo_text, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    // printf("%d\n", glGetError());
}

Waterfall::~Waterfall() {
    delete m_quad_vbo;
}

void Waterfall::update() {
    if (++m_scanline > m_H) {
        m_scanline = 0;
    }
    
    // Store viewport
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    // render to framebuffer texture
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0,0,m_N,m_H);
    m_line.use();

    m_pow->bind();
    m_line.enableVertexAttribArray("pow");
    m_line.vertexAttribPointer("pow", 1, GL_FLOAT, GL_FALSE, 0);
    
    m_bin->bind();
    m_line.enableVertexAttribArray("bin");
    m_line.vertexAttribPointer("bin", 1, GL_FLOAT, GL_FALSE, 0);
    
    m_line.setUniform("line", float(m_scanline));
    
    glDrawArrays(GL_POINTS, 0, m_N);
    
    m_pow->release();
    m_bin->release();
    m_line.disableVertexAttribArray("pow");
    m_line.disableVertexAttribArray("bin");
    
    m_line.release();
    // render to screen again
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // Restore viewport
    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}

void Waterfall::draw() {
    glEnable(GL_BLEND);
    glBlendColor(1.f,1.f,1.f,1.f);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    m_quad.use();

    m_quad.setUniform("offset", m_scanline/float(m_H));
    
    m_quad_vbo->bind();
    m_quad.enableVertexAttribArray("vec");
    m_quad.vertexAttribPointer("vec", 2, GL_FLOAT, GL_FALSE, 0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_fbo_text);
    m_quad.setUniform("waterfall", 0);
    
    glDrawArrays(GL_TRIANGLES, 0, 6); // number of vertecies
    m_quad_vbo->release();
    glBindTexture(GL_TEXTURE_2D, 0);
    m_quad.disableVertexAttribArray("vec");
    m_quad.release();
    
    glDisable(GL_BLEND);
}
