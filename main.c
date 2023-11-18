#include <SFML/Graphics.h>
#include <SFML/OpenGL.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Types.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Window.h>
#include <stdint.h>
#include <stdio.h>

int main() {
    sfVideoMode mode = {800, 600, 32};

    sfContextSettings settings;

    settings.depthBits         = 24;
    settings.stencilBits       = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion      = 3;
    settings.minorVersion      = 0;

    sfRenderWindow* window = sfRenderWindow_create(mode, "eRdiv", sfResize | sfClose, &settings);
    sfClock*        clock  = sfClock_create();

    double angle = 0;

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

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -200.f);

        angle = sfClock_getElapsedTime(clock).microseconds * 1e-6;

        glRotatef(angle * 50, 1.f, 0.f, 0.f);
        glRotatef(angle * 30, 0.f, 1.f, 0.f);
        glRotatef(angle * 90, 0.f, 0.f, 1.f);

glBegin(GL_QUADS);
        glColor3f(0,1,1); //cyan
        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f(-50.f,  50.f, -50.f);
        glVertex3f( 50.f,  50.f, -50.f);
        glVertex3f( 50.f, -50.f, -50.f);

        glColor3f(0,0,1); //blue
        glVertex3f( 50.f, -50.f, 50.f);
        glVertex3f( 50.f,  50.f, 50.f);
        glVertex3f(-50.f,  50.f, 50.f);
        glVertex3f(-50.f, -50.f, 50.f);

        glColor3f(1,0,1); //magenta
        glVertex3f(-50.f, -50.f,  50.f);
        glVertex3f(-50.f,  50.f,  50.f);
        glVertex3f(-50.f,  50.f, -50.f);
        glVertex3f(-50.f, -50.f, -50.f);

        glColor3f(0,1,0); //green
        glVertex3f(50.f, -50.f, -50.f);
        glVertex3f(50.f,  50.f, -50.f);
        glVertex3f(50.f,  50.f,  50.f);
        glVertex3f(50.f, -50.f,  50.f);

        glColor3f(1,1,0); //yellow
        glVertex3f(-50.f, -50.f,  50.f);
        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f( 50.f, -50.f, -50.f);
        glVertex3f( 50.f, -50.f,  50.f);

        glColor3f(1,0,0); //red
        glVertex3f( 50.f, 50.f,  50.f);
        glVertex3f( 50.f, 50.f, -50.f);
        glVertex3f(-50.f, 50.f, -50.f);
        glVertex3f(-50.f, 50.f,  50.f);
glEnd();

        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);

    return 0;
}
