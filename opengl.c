#include <SFML/Window.h>
#include <SFML/OpenGL.h>
#include <SFML/Graphics.h>
#include <GLES3/gl3.h>

#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH  800
#define HEIGHT 800

int main() {
    sfWindow* window = sfWindow_create((sfVideoMode){ WIDTH, HEIGHT, 32 }, "SFML OpenGL", sfTitlebar | sfResize | sfClose, NULL);
    
    sfWindow_setVerticalSyncEnabled(window, false);
    sfWindow_setActive(window, true);

    glViewport(100, 100, WIDTH, HEIGHT);
 
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.0f,
         0.0f,  0.5f,  0.0f 
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n" // 0.15f, 0.13f, 0.32f
        "   float red   = gl_FragCoord.x / 800;\n"
        "   float green = gl_FragCoord.y / 800;\n"
        "   float blue  = 0;\n"
        "   FragColor = vec4(red, green, blue, 1.0f);\n"
        "}\0";

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);

    while (sfWindow_isOpen(window)) {
        sfEvent event;

        while (sfWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfWindow_close(window);
            }
            else if (event.type == sfEvtResized) {
                glViewport(0, 0, event.size.width, event.size.height);
                sfWindow_setSize(window, (sfVector2u) { event.size.width, event.size.height});
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        sfWindow_display(window);
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    sfWindow_destroy(window);

    return 0;
}
