//
// Created by Henrik Nielsen on 19/11/2018.
//


/* Disabled for Windows development, works on linux when GLUT is installed

#include "Render.h"
#include <GLUT/glut.h>  // GLUT, include glu.h and gl.h

 // GLUT runs as a console application starting at main()
void RenderSquare(GLfloat, GLfloat, GLfloat);

// global variable
GLfloat angle = 0.0f;  // rotational angle of the shapes
int refreshMills = 16; // refresh interval in milliseconds

// Initialize OpenGL Graphics
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Black and opaque
}

// Called back when timer expired
void Timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, Timer, 0); // next Timer call milliseconds later
}

// Handler for window-repaint event. Call back when the window first appears and
// whenever the window needs to be re-painted.
void display() {
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
    glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix

    RenderSquare(-1, 0, -5);
    RenderSquare(0, 0.7, 5);
    RenderSquare(1, 0, angle);

    glutSwapBuffers();   // Double buffered - swap the front and back buffers

    // Change the rotational angle after each display()
    angle += 1.0f;
}

void RenderSquare(GLfloat x, GLfloat y, GLfloat directionInDegrees)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(directionInDegrees, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.02f, -0.02f);
    glVertex2f( 0.02f, -0.02f);
    glVertex2f( 0.02f,  0.02f);
    glVertex2f(-0.02f,  0.02f);
    glEnd();
    glPopMatrix();
}

// Handler for window re-size event. Called back when the window first appears and
// whenever the window is re-sized with its new width and height
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();
    if (width >= height) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}

void Setup(int argc, char** argv)
{
    glutInit(&argc, argv);          // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE);  // Enable double buffered mode
    glutInitWindowSize(640, 480);   // Set the window's initial width & height - non-square
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("Traffic simulator");  // Create window with the given title
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    glutTimerFunc(0, Timer, 0);     // First timer call immediately
    initGL();                       // Our own OpenGL initialization
    glutMainLoop();                 // Enter the infinite event-processing loop
}
*/