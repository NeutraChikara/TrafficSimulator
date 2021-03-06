//
// Created by Henrik Nielsen on 19/11/2018.
//

#include "Render.h"
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>

// GLUT runs as a console application starting at main()
void RenderRectangle(GLfloat x, GLfloat y, GLfloat directionInDegrees, Color color);

// Initialize OpenGL Graphics
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Black and opaque
}

// Called back when timer expired
void Timer(int value) {
    auto refreshMills = 16; // refresh interval in milliseconds
    glutPostRedisplay();      // Post re-paint request to activate call to Loop
    glutTimerFunc(refreshMills, Timer, 0); // next Timer call milliseconds later
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

void RenderRoad(Transform first, Transform second, Color color) {

    auto x1 = (GLfloat) first.X / 10000;
    auto y1 = (GLfloat) first.Y / 10000;
    auto x2 = (GLfloat) second.X / 10000;
    auto y2 = (GLfloat) second.Y / 10000;

    if (x2 < x1 || y1 < y2) {
        auto xTemp = x1;
        x1 = x2;
        x2 = xTemp;

        auto yTemp = y1;
        y1 = y2;
        y2 = yTemp;
    }

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(color.R, color.G, color.B);

    auto vectorX = x1 - x2;
    auto vectorY = y1 - y2;
    auto length = std::sqrt(vectorX * vectorX + vectorY * vectorY);
    auto midLineLength = 0.01f;
    auto midLineWidth = 0.0015f;
    auto midLineSeperationDistance = 0.035f;
    auto trackWidth = 0.045f;
    auto lineWidth = 0.002f;
    auto junctionPadding = trackWidth;
    auto numOfMidLines = static_cast<int>((length - 2 * junctionPadding) / (midLineLength + midLineSeperationDistance));

    if (vectorY == 0) {
        glVertex2f(x1 + junctionPadding, y1 + trackWidth);
        glVertex2f(x2 - junctionPadding, y2 + trackWidth);
        glVertex2f(x2 - junctionPadding, y2 + lineWidth + trackWidth);
        glVertex2f(x1 + junctionPadding, y1 + lineWidth + trackWidth);

        glVertex2f(x1 + junctionPadding, y1 - trackWidth);
        glVertex2f(x2 - junctionPadding, y2 - trackWidth);
        glVertex2f(x2 - junctionPadding, y2 - lineWidth - trackWidth);
        glVertex2f(x1 + junctionPadding, y1 - lineWidth - trackWidth);

        while (numOfMidLines--) {
            auto currentStartX = (midLineSeperationDistance + midLineLength) * numOfMidLines;
            glVertex2f(x1 + junctionPadding + currentStartX + midLineSeperationDistance, y1 + midLineWidth);
            glVertex2f(x1 + junctionPadding + currentStartX + midLineSeperationDistance + midLineLength,
                       y1 + midLineWidth);
            glVertex2f(x1 + junctionPadding + currentStartX + midLineSeperationDistance + midLineLength,
                       y1 - midLineWidth);
            glVertex2f(x1 + junctionPadding + currentStartX + midLineSeperationDistance, y1 - midLineWidth);
        }

    } else if (vectorX == 0) {
        glVertex2f(x1 + trackWidth, y1 - junctionPadding);
        glVertex2f(x2 + trackWidth, y2 + junctionPadding);
        glVertex2f(x2 + trackWidth + lineWidth, y2 + junctionPadding);
        glVertex2f(x1 + trackWidth + lineWidth, y1 - junctionPadding);

        glVertex2f(x1 - trackWidth, y1 - junctionPadding);
        glVertex2f(x2 - trackWidth, y2 + junctionPadding);
        glVertex2f(x2 - trackWidth + lineWidth, y2 + junctionPadding);
        glVertex2f(x1 - trackWidth + lineWidth, y1 - junctionPadding);

        while (numOfMidLines--) {
            auto currentStartY = (midLineSeperationDistance + midLineLength) * numOfMidLines;
            glVertex2f(x1 + midLineWidth, y1 - junctionPadding - currentStartY - midLineSeperationDistance);
            glVertex2f(x1 + midLineWidth,
                       y1 - junctionPadding - currentStartY - midLineSeperationDistance - midLineLength);
            glVertex2f(x1 - midLineWidth,
                       y1 - junctionPadding - currentStartY - midLineSeperationDistance - midLineLength);
            glVertex2f(x1 - midLineWidth, y1 - junctionPadding - currentStartY - midLineSeperationDistance);
        }
    }

    glEnd();
    glPopMatrix();
}

void RenderLightBox(GLfloat width, GLfloat height, bool isGreen, Color color) {
    auto centerWidth = width / 2;
    auto centerHeight = height / 2;
    glBegin(GL_LINE_LOOP);
    glColor3f(color.R, color.G, color.B);
    glVertex2f(-centerWidth, -centerHeight);
    glVertex2f(centerWidth, -centerHeight);
    glVertex2f(centerWidth, centerHeight);
    glVertex2f(-centerWidth, centerHeight);
    glEnd();

    if (isGreen) {
        glTranslatef(0, centerHeight /2, 0);
        glColor3f(0, 1, 0);
    } else {
        glTranslatef(0, -centerHeight /2, 0);
        glColor3f(1, 0, 0);
    }

    glBegin(GL_QUADS);
    auto size = 0.007f;
    glVertex2f(-size, -size);
    glVertex2f(size, -size);
    glVertex2f(size, size);
    glVertex2f(-size, size);
    glEnd();
}

void RenderTrafficLight(Transform transform, bool directionAllowed[], Color color) {
    auto x = transform.X;
    auto y = transform.Y;
    auto rotationInDegrees = 0;
    auto width = 0.03f;
    auto height = 0.05f;
    auto lightX = 0.075f;
    auto lightY = 0.08f;

    glPushMatrix();
    glTranslatef(x / 10000.f, y / 10000.f, 0);

    glPushMatrix();
    glTranslatef(lightX, -lightY, 0);
    RenderLightBox(width, height, directionAllowed[3], color);
    glPopMatrix();

    glPushMatrix();
    rotationInDegrees = -90;
    glRotatef(rotationInDegrees, 0.0f, 0.0f, 1.0f);
    glTranslatef(lightX, -lightY, 0);
    RenderLightBox(width, height, directionAllowed[0], color);
    glPopMatrix();

    glPushMatrix();
    rotationInDegrees = 180;
    glRotatef(rotationInDegrees, 0.0f, 0.0f, 1.0f);
    glTranslatef(lightX, -lightY, 0);
    RenderLightBox(width, height, directionAllowed[1], color);
    glPopMatrix();

    glPushMatrix();
    rotationInDegrees = 90;
    glRotatef(rotationInDegrees, 0.0f, 0.0f, 1.0f);
    glTranslatef(lightX, -lightY, 0);
    RenderLightBox(width, height, directionAllowed[2], color);
    glPopMatrix();

    glPopMatrix();
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

namespace Ecs::Systems {

    Render::InputHandler *Render::Instance;

    void Render::Setup(int argc, char **argv, void (*loop)()) {
        glutInit(&argc, argv);          // Initialize GLUT
        glutInitDisplayMode(GLUT_DOUBLE);  // Enable double buffered mode
        glutInitWindowSize(640 * 2, 480 * 2);   // Set the window's initial width & height - non-square
        glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
        glutCreateWindow("Traffic Simulator");  // Create window with the given title
        glutKeyboardFunc(InputHandler::KeyPressedWrapper);
        glutDisplayFunc(loop);       // Register callback handler for window re-paint event
        glutReshapeFunc(reshape);       // Register callback handler for window re-size event
        auto firstCallDelay = 500u;
        glutTimerFunc(firstCallDelay, Timer, 0);

        initGL();                       // Our own OpenGL initialization
    }


    Render::Render(World &world, void (*loop)()) : System(world) {
        SetRequiredComponents<Transform, Ecs::Components::Render>();
        Instance = new InputHandler(world);
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
        if (r.Type == "car") {
            auto transform = world.GetComponent<Transform>(e.GetId());
            RenderRectangle(transform.X, transform.Y, transform.Orientation, r.Color);
        } else if (r.Type == "roadGraph") {
            auto graph = world.GetComponent<RoadGraph>(e.GetId());
            for (auto &edge : graph.Edges) {
                auto trafficLightFirst = edge.first;
                auto trafficLightSecond = edge.second;

                auto firstTransform = world.GetComponent<Transform>(trafficLightFirst);
                auto secondTransform = world.GetComponent<Transform>(trafficLightSecond);

                RenderRoad(firstTransform, secondTransform, r.Color);
            }
        } else if (r.Type == "trafficLight") {
            auto directionAllowed = world.GetComponent<Ecs::Components::TrafficLight>(e.GetId()).IsDirectionAllowed;
            auto transform = world.GetComponent<Transform>(e.GetId());
            RenderTrafficLight(transform, directionAllowed, r.Color);
        }

    }

    void Render::Start() {
        glutMainLoop();     // Enter the infinite event-processing loop
    }

    Render::~Render() {
        delete Instance;
    }

    Render::InputHandler::InputHandler(World &world) : System(world) {
        SetRequiredComponents<Ecs::Components::TrafficLight>();
    }

    void Render::InputHandler::OnUpdate(Entity e) {
        auto &tl = world.GetComponent<Ecs::Components::TrafficLight>(e.GetId());
        if (Increase)
            tl.CountsBeforeChange += 10;
        else if (tl.CountsBeforeChange != 0)
            tl.CountsBeforeChange -= 10;

        std::cout << e.GetId() << "       " << tl.CountsBeforeChange << std::endl;
    }

    void Render::InputHandler::KeyPressed(unsigned char key, int x, int y) {


        switch (key) {
            case '+' :
                Increase = true;
                Update();
                break;
            case '-' :
                Increase = false;
                Update();
                break;
            default:
                break;
        }
    }

    void Render::InputHandler::KeyPressedWrapper(unsigned char key, int x, int y) {
        Instance->KeyPressed(key, x, y);
    }

    void Render::InputHandler::Update() {
        std::cout << "Timing for traffic lights changed" << std::endl;
        std::cout << "Id" << "      " << "Timing" << std::endl;
        System::Update();
        std::cout << std::endl;
    }
}
