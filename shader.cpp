//
//  shader.cpp
//  fgt
//
//  Created by Albin Stigö on 01/12/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#include "shader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

string Shader::contentsOfFile(string path) {
    ifstream file(path);
    stringstream strbuf;
    if(!file.is_open()) {
        throw runtime_error("no can do");
    }
    strbuf << file.rdbuf();
    return strbuf.str();
}

void Shader::compileShaderOrLogAndDie(GLuint shader) {
    GLint success = 0;
    int max_log_length = 2048;
    
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint log_size = 0;
        char error_log[max_log_length];
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
        glGetShaderInfoLog(shader, max_log_length, &max_log_length, &error_log[0]);
        // print
        cout << error_log << endl;
        // throw
        throw runtime_error("no compile");
    }
}

Shader::Shader(string name) {
    
#ifdef __linux__
    //linux code goes here
    const string prefix = "shaders/";
#else
    const string prefix = "/mnt/pi/src/fgt2/fgt2/shaders/";
#endif
    
    printf("prefix: %s\n", prefix.c_str());
    
    string v_src = contentsOfFile(prefix + name + ".vert");
    string f_src = contentsOfFile(prefix + name + ".frag");
    
    // Create some shaders
    GLuint v, f;

    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);
    // Pointer juggling
    const char *v_src_c_str = v_src.c_str();
    const char *f_src_c_str = f_src.c_str();
    glShaderSource(v, 1, &v_src_c_str, NULL);
    glShaderSource(f, 1, &f_src_c_str, NULL);
    // Compile shaders
    compileShaderOrLogAndDie(v);
    compileShaderOrLogAndDie(f);
    // Create a program
    GLuint p;
    p = glCreateProgram();
    
    // Attach shaders to program
    glAttachShader(p,v);
    glAttachShader(p,f);
    // Link
    glLinkProgram(p);
    
    if(glGetError()) {
        throw runtime_error("some error");
    }
    
    m_program = p;
}

Shader::~Shader() {
    glDeleteProgram(m_program);
}

void Shader::use() {
    glUseProgram(m_program);
}

void Shader::release() {
    glUseProgram(0);
}

GLuint Shader::program() {
    return m_program;
}

GLuint Shader::attribLocation(string name) {
    GLuint ret = glGetAttribLocation(m_program, name.c_str());
    return ret;
}

void Shader::enableVertexAttribArray(string name) {
    glEnableVertexAttribArray(attribLocation(name));
}

GLuint Shader::uniformLocation(string name) {
    GLuint ret =  glGetUniformLocation(m_program, name.c_str());
    return ret;
}

void Shader::setUniform(string name, glm::mat4 &mat4) {
    // Notice that all matrix types are column-major rather than row-major.
    // Hence the need to pass GL_FALSE to glUniformMatrix4fv
    glUniformMatrix4fv(uniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::setUniform(string name, GLint v0) {
    glUniform1i(uniformLocation(name), v0);
}

void Shader::setUniform(string name, GLfloat v0) {
    glUniform1f(uniformLocation(name), v0);
}

void Shader::vertexAttribPointer(string name, GLint size, GLenum type, GLboolean normalized, GLsizei stride) { 
    glVertexAttribPointer(attribLocation(name), size, type, normalized, stride, 0);
}

void Shader::disableVertexAttribArray(string name) { 
    glDisableVertexAttribArray(attribLocation(name));
}

