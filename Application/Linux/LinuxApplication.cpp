//
// Created by joker on 8/17/18.
//

#include "LinuxApplication.hpp"

#include <iostream>
#include <GL/freeglut.h>


void RenderFunc()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Test");

    glutDisplayFunc(RenderFunc);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutMainLoop();

    return 0;
}