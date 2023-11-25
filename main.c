#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaders.h"
#include "linmath.h"

#define ERR(msg) { fprintf(stderr, msg); }

int main() {
    glewExperimental = true;
    if (!glfwInit()) { ERR("glfwInit"); return -1; };

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1024, 768, "GLFW, GLEW, OpenGL", NULL, NULL);
    if (window == NULL) { ERR("createWindow"); glfwTerminate(); return -1; }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) { ERR("glewInit"); return -1; }

    GLuint vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };

    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); 

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint programID = loadShaders("shader/vertex.vertexshader", "shader/fragment.fragmentshader");

    mat4x4 proj;
    mat4x4_perspective(proj, 1.5f, 4.0f / 3.0f, 0.1f, 100.0f);

    mat4x4 view;
    mat4x4_look_at(view, (vec3) { 4, 3, 3 }, (vec3) { 0, 0, 0 }, (vec3) { 0, 1, 0});

    mat4x4 model;
    mat4x4_identity(model);

    // mvp = proj * view * model

    mat4x4 mvp;
    mat4x4_mul(mvp, proj, view);
    mat4x4_mul(mvp, mvp, model);

    GLuint matrixID = glGetUniformLocation(programID, "mvp");

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
                );

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    return 0;
}
