#include <SFML/Graphics.h>
#include <SFML/OpenGL.h>
#include <SFML/System/Clock.h>
#include <stdint.h>
#include <stdio.h>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH  600

void drawCube() {
    glBegin(GL_QUADS);
    // Front face
    glColor3f(1.0f, 0.0f, 0.0f);  // Red
    glVertex3f(-50.0f, -50.0f, 50.0f);
    glVertex3f(50.0f, -50.0f, 50.0f);
    glVertex3f(50.0f, 50.0f, 50.0f);
    glVertex3f(-50.0f, 50.0f, 50.0f);

    // Back face
    glColor3f(0.0f, 1.0f, 0.0f);  // Green
    glVertex3f(-50.0f, -50.0f, -50.0f);
    glVertex3f(50.0f, -50.0f, -50.0f);
    glVertex3f(50.0f, 50.0f, -50.0f);
    glVertex3f(-50.0f, 50.0f, -50.0f);

    // Top face
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue
    glVertex3f(-50.0f, 50.0f, 50.0f);
    glVertex3f(50.0f, 50.0f, 50.0f);
    glVertex3f(50.0f, 50.0f, -50.0f);
    glVertex3f(-50.0f, 50.0f, -50.0f);

    // Bottom face
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow
    glVertex3f(-50.0f, -50.0f, 50.0f);
    glVertex3f(50.0f, -50.0f, 50.0f);
    glVertex3f(50.0f, -50.0f, -50.0f);
    glVertex3f(-50.0f, -50.0f, -50.0f);

    // Right face
    glColor3f(1.0f, 0.0f, 1.0f);  // Magenta
    glVertex3f(50.0f, -50.0f, 50.0f);
    glVertex3f(50.0f, 50.0f, 50.0f);
    glVertex3f(50.0f, 50.0f, -50.0f);
    glVertex3f(50.0f, -50.0f, -50.0f);

    // Left face
    glColor3f(0.0f, 1.0f, 1.0f);  // Cyan
    glVertex3f(-50.0f, -50.0f, 50.0f);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    glVertex3f(-50.0f, 50.0f, -50.0f);
    glVertex3f(-50.0f, -50.0f, -50.0f);

    glEnd();
}

int main() {
    sfVideoMode mode = {WINDOW_HEIGHT, WINDOW_WIDTH, 32};

    sfContextSettings settings;

    settings.depthBits         = 24;
    settings.stencilBits       = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion      = 3;
    settings.minorVersion      = 0;

    sfRenderWindow* window = sfRenderWindow_create(mode, "eRdiv", sfResize | sfClose, &settings);
    sfClock*        clock  = sfClock_create();

    double angle = 0;

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 300.0f);

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;

        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                // close window
                sfRenderWindow_close(window);
            }
            else if
                (event.type == sfEvtResized) {
                    // adjust viewport on resize
                    glViewport(0, 0, event.size.width, event.size.height);
                }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        angle = sfClock_getElapsedTime(clock).microseconds * 1e-6;

        glLoadIdentity();
        glTranslatef(0.f, 0.f, -150.f);
        glRotatef(angle * 50, 1.f, 0.f, 0.f);
        glRotatef(angle * 30, 0.f, 1.f, 0.f);
        glRotatef(angle * 90, 0.f, 0.f, 1.f);
       
        drawCube();

        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);

    return 0;
}
