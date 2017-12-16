//
//  spectrum.cpp
//  fgt
//
//  Created by Albin Stigö on 04/12/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#include "spectrum.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Spectrum::~Spectrum() { 
    ;
}

Spectrum::Spectrum(VBO *pow, VBO *bin, int N):
    m_pow(pow),
    m_bin(bin),
    m_line("fft_line"),
    m_N(N)
{
        m_line.use();
        glm::mat4 ortho = glm::ortho(0.0f, 2047.0f, -300.0f, 0.0f, -1.0f, 1.0f);
        m_line.setUniform("ortho", ortho);
        m_line.release();
}

void Spectrum::draw() {
    
    m_line.use();

    m_line.enableVertexAttribArray("bin");
    m_bin->bind();
    m_line.vertexAttribPointer("bin", 1, GL_FLOAT, GL_FALSE, 0);

    m_line.enableVertexAttribArray("pow");
    m_pow->bind();
    m_line.vertexAttribPointer("pow", 1, GL_FLOAT, GL_FALSE, 0);

    glDrawArrays(GL_LINE_STRIP, 0, m_N); // number of vertecies

    m_bin->release();
    m_pow->release();
    
    m_line.disableVertexAttribArray("pow");
    m_line.disableVertexAttribArray("bin");
    
    m_line.release();
}
