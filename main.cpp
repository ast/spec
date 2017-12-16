//
//  main.cpp
//  fgt2
//
//  Created by Albin Stigö on 05/12/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cstdlib>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/un.h>
#include <unistd.h>
#include <signal.h>
#include <algorithm>
#include <string.h>

#include "spectrum.hpp"
#include "waterfall.hpp"
#include "grid.hpp"

typedef struct {
    Spectrum    *spectrum;
    Waterfall   *waterfall;
    Grid        *grid;
} user_pointer_t;

int sd;
const int N = 2048;
const int MAXEVENTS = 16;

int create_socket() {
    int err;
    struct sockaddr_un addr;
    const int periods = 4;
    const string name = "/tmp/sdrclient";
    // Remove in case it exists already
    unlink(name.c_str());
    
    int sd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(sd < 0) {
        throw runtime_error("socket()");
    }
    
    // Set socket to be non-blocking.
    int flags = fcntl(sd, F_GETFL, 0);
    fcntl(sd, F_SETFL, flags | O_NONBLOCK);
    
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, name.c_str());
    
    // Set size of receive buffer
    int recv_buf = N * sizeof(float) * periods;
    err = setsockopt(sd, SOL_SOCKET, SO_RCVBUF, &recv_buf, sizeof(recv_buf));
    if(err < 0) {
        throw runtime_error("setsockopt");
    }
    
    if(::bind(sd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        throw runtime_error("bind");
    }
    
    return sd;
}

void windowResize(GLFWwindow* window, int width, int height) {
    printf("%d - %d\n", width, height);
    user_pointer_t *user_ptr = (user_pointer_t*) glfwGetWindowUserPointer(window);
    
    glViewport(0, 0, width, height);
}

int main(int argc, const char * argv[]) {
    
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Hints */
    glfwWindowHint(GLFW_SAMPLES, 2);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 600, "Spectrum", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    // Gladly
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    
    sd = create_socket();
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    VBO *pow_vbo = new VBO(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    VBO *bin_vbo = new VBO(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    
    vector<float>bins(N);
    int n = 0;
    generate(bins.begin(), bins.end(), [&n] { return (float)n++;});
    
    // Zero this buffer
    pow_vbo->bufferData(bins.size() * sizeof(float), 0);
    // Bin numbers
    bin_vbo->bufferData(bins.size() * sizeof(float), &bins[0]);
    
    // I guess we have a current context.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Spectrum *spectrum = new Spectrum(pow_vbo, bin_vbo, N);
    Waterfall *waterfall = new Waterfall(pow_vbo, bin_vbo, N);
    Grid *grid = new Grid();
    
    // Make these accessible in our callbacks
    user_pointer_t user_ptr = {
        .grid = grid,
    };
    glfwSetWindowUserPointer(window, &user_ptr);
    
    glfwSetFramebufferSizeCallback(window, windowResize);
    
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    
    float data[N] = {0};
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        int ret = 0;
        if((ret = recvfrom(sd, data, sizeof(data), 0, NULL, NULL)) > 0) {
            //printf("%f\n", data[1024]);
            pow_vbo->bufferData(sizeof(data), data);
            waterfall->update();
        }
        
        grid->draw();
        waterfall->draw();
        spectrum->draw();
        
        // Swap front and back buffers
        glfwSwapBuffers(window);
        glfwWaitEventsTimeout(0.03);
    }
    
    glfwTerminate();
    return 0;
}
