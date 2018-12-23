//
// Created by Henrik Nielsen on 19/11/2018.
//

#include "Render.h"
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

// GLUT runs as a console application starting at main()
void RenderRectangle(GLfloat x, GLfloat y, GLfloat directionInDegrees, Color color);

// Initialize OpenGL Graphics
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Black and opaque
}

// Called back when timer expired
void Timer(int value) {
    int refreshMills = 16; // refresh interval in milliseconds
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, Timer, 0); // next Timer call milliseconds later
}

// Handler for window-repaint event. Call back when the window first appears and
// whenever the window needs to be re-painted.
void display() {
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
    glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix


    glutSwapBuffers();   // Double buffered - swap the front and back buffers

    // Change the rotational angle after each display()
}

void RenderRectangle(GLfloat x, GLfloat y, GLfloat directionInDegrees, Color color) {
    glPushMatrix();
    glTranslatef(x / 10000, y / 10000, 0);
    glRotatef(directionInDegrees, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glColor3f(color.R, color.G, color.B);
    auto size = 0.005f;
    auto length = 0.004f;
    glVertex2f(-size - length, -size);
    glVertex2f(size + length, -size);
    glVertex2f(size + length, size);
    glVertex2f(-size - length, size);
    glEnd();
    glPopMatrix();
}

void RenderRoad() {

}

// Handler for window re-size event. Called back when the window first appears and
// whenever the window is re-sized with its new width and height
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat) width / (GLfloat) height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();

    int clippingPlaneSize = 1;

    if (width >= height) {
        // aspect >= clippingPlaneSize, set the height from -clippingPlaneSize to clippingPlaneSize, with larger width
        gluOrtho2D(-clippingPlaneSize * aspect, clippingPlaneSize * aspect, -clippingPlaneSize, clippingPlaneSize);
    } else {
        // aspect < clippingPlaneSize, set the width to -clippingPlaneSize to clippingPlaneSize, with larger height
        gluOrtho2D(-clippingPlaneSize, clippingPlaneSize, -clippingPlaneSize / aspect, clippingPlaneSize / aspect);
    }
}

void Setup(int argc, char **argv, void (*loop)()) {
    glutInit(&argc, argv);          // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE);  // Enable double buffered mode
    glutInitWindowSize(640, 480);   // Set the window's initial width & height - non-square
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("Traffic simulator");  // Create window with the given title
    glutDisplayFunc(loop);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    glutTimerFunc(500, Timer, 0);     // First timer call after 500 ms

    initGL();                       // Our own OpenGL initialization
}

namespace Ecs::Systems {
    Render::Render(World &world, void (*loop)()) : System(world) {
        SetRequiredComponents<Transform, Ecs::Components::Render>();
        Setup(0, nullptr, loop);
    }

    void Render::Update() {
        glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
        glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix

        System::Update();

        glutSwapBuffers();   // Double buffered - swap the front and back buffers
    }


    void Render::OnUpdate(Entity e) {

        auto r = world.GetComponent<Ecs::Components::Render>(e.GetId());

        // TODO: enum instead of string
        if(r.Type == "car")
        {
            auto transform = world.GetComponent<Transform>(e.GetId());
            RenderRectangle(transform.X, transform.Y, transform.Orientation, r.Color);
        }
        else if(r.Type == "trafficLight")
        {
            auto transform = world.GetComponent<Transform>(e.GetId());
            RenderRectangle(transform.X, transform.Y, transform.Orientation, r.Color);
        }

    }

    void Render::Start() {
        glutMainLoop();                 // Enter the infinite event-processing loop
    }

}
