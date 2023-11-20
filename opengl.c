#include <SFML/Window.h>
#include <SFML/OpenGL.h>
#include <SFML/Graphics.h>
#include <GLES3/gl3.h>

#include <stdbool.h>
#include <stdlib.h>

#define WIDTH  800
#define HEIGHT 600

int main() {
    sfWindow* window = sfWindow_create((sfVideoMode){ HEIGHT, WIDTH, 32 }, "SFML OpenGL", sfTitlebar | sfResize | sfClose, NULL);
    
    sfWindow_setVerticalSyncEnabled(window, false);
    sfWindow_setActive(window, true);

    glViewport(0, 0, WIDTH, HEIGHT);
 
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
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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
        sfWindow_display(window);
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    sfWindow_destroy(window);

    return 0;
}
