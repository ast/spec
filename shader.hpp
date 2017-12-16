//
//  shader.hpp
//  fgt
//
//  Created by Albin Stigö on 01/12/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>

using namespace std;

class Shader {
    GLuint m_program;
    static string contentsOfFile(string path);
    static void compileShaderOrLogAndDie(GLuint shader);
public:
    Shader(string name);
    ~Shader();
    GLuint program();
    GLuint attribLocation(string name);
    void enableVertexAttribArray(string name);
    void disableVertexAttribArray(string name);
    void vertexAttribPointer(string name, GLint size, GLenum type, GLboolean normalized, GLsizei stride);
    GLuint uniformLocation(string name);
    void setUniform(string name, glm::mat4 &mat4);
    void setUniform(string name, GLint v0);
    void setUniform(string name, GLfloat v0);
    void use();
    void release();
};


#endif /* shader_hpp */
