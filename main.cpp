/*
OpenGL, GLFW, GLM program demonstrating how to draw weird squares inside of other weird squares -.-

Controls:
    A: Toggle axis drawing
    W: Toggle wireframe mode
    UP ARROW: Add a new magic square to the scene
    DOWN ARROW: Remove the last magic square from the scene
*/

#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm.hpp>
#include <ctime>

#include "MagicSquare.h"

using namespace std;

//screen constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

bool drawAxisFlag = true;
bool drawWireframe = true;

vector<MagicSquare> squaresVector;

//Draws axis going through the origin of coordinates (0, 0).
void drawAxis()
{
    if(drawAxisFlag)
    {
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
            glVertex2f(0, SCREEN_HEIGHT / 2);
            glVertex2f(0, -SCREEN_HEIGHT / 2);
            glVertex2f(-SCREEN_WIDTH / 2, 0);
            glVertex2f(SCREEN_WIDTH / 2, 0);
        glEnd();
    }
}

//Draws all the squares using their own color.
void drawSolidSquares()
{
    for(auto it = squaresVector.cbegin(); it != squaresVector.cend(); it++)
    {
        vec2 c1 = it->getC1(), c2 = it->getC2(), c3 = it->getC3(), c4 = it->getC4();
        vec3 color = it->getColor();

        glColor3f(color.r, color.g, color.b);

        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(c1.x, c1.y);
            glVertex2f(c2.x, c2.y);
            glVertex2f(c3.x, c3.y);
            glVertex2f(c4.x, c4.y);
        glEnd();
    }
}

//Draws all the squares in wireframe mode.
void drawWireframeSquares()
{
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);

    for(auto it = squaresVector.cbegin(); it != squaresVector.cend(); it++)
    {
        vec2 c1 = it->getC1(), c2 = it->getC2(), c3 = it->getC3(), c4 = it->getC4();

        glVertex2f(c1.x, c1.y);
        glVertex2f(c2.x, c2.y);
        glVertex2f(c2.x, c2.y);
        glVertex2f(c3.x, c3.y);
        glVertex2f(c3.x, c3.y);
        glVertex2f(c4.x, c4.y);
        glVertex2f(c4.x, c4.y);
        glVertex2f(c1.x, c1.y);
    }

    glEnd();
}

void display()
{
	glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxis();

    if(drawWireframe)
        drawWireframeSquares();
    else
        drawSolidSquares();

    glFlush();
}

//Adds a new square to the scene.
void addNewSquare()
{
    //If the squares vector is empty, add a new default square, otherwise grab the magic square from the last added square.
    if(squaresVector.size() == 0)
    {
        vec2 c1(-300, -300), c2(-300, 300), c3(300, 300), c4(300, -300);

        squaresVector.push_back(MagicSquare(c1, c2, c3, c4));
    }
    else
    {
        squaresVector.push_back(squaresVector.back().getMagicSquare());
    }
}

//Removes the last square from the scene.
void removeSquare()
{
    if(squaresVector.size() > 0)
        squaresVector.pop_back();
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_RELEASE)
    {
        switch(key)
        {
        case GLFW_KEY_A:
            drawAxisFlag = !drawAxisFlag;
            break;
        case GLFW_KEY_UP:
            addNewSquare();
            break;
        case GLFW_KEY_DOWN:
            removeSquare();
            break;
        case GLFW_KEY_W:
            drawWireframe = !drawWireframe;
            break;
        }
    }
}

int main()
{
    srand(unsigned(time(0)));

    GLFWwindow * window;

    /* Initialize the library */
    if(glfwInit())
    {
        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Magic Squares", NULL, NULL);

        if(window)
        {
            glfwMakeContextCurrent(window);
            glfwSetWindowPos(window, 100, 100);
            glfwSetKeyCallback(window, key_callback);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, 1, -1); //Center on (0, 0).

            //Add 4 new squares at startup.
            addNewSquare();
            addNewSquare();
            addNewSquare();
            addNewSquare();

            /* Loop until the user closes the window */
            while(!glfwWindowShouldClose(window))
            {
                /* Render here */
                display();

                /* Swap front and back buffers */
                glfwSwapBuffers(window);

                /* Poll for and process events */
                glfwPollEvents();
            }   
        }

        glfwTerminate();
    }

    return 0;
}