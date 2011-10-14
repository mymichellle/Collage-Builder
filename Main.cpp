//
//  Main.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/1/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include "Collage.h"
#include "MainPage.h"
#include "Utility.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

// Pass all display calls into the collage program
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    Collage::sharedCollage().display();
    
    glutSwapBuffers();
}

// Pass all reshape calls into the collage program
void reshape(int w, int h)
{
    Collage::sharedCollage().reshape(w,h);
}

// Pass all mouse presses into the collage program
void mouse(int button, int state, int x, int y) 
{
    // Convert mouse coords to origin in lower-left
    correctCoords(x,y);
    Collage::sharedCollage().mouse(button, state, x, y);
}

void mouseMotion(int x, int y)
{
    correctCoords(x,y);
    Collage::sharedCollage().mouseMotion(x, y);
}

void keyboard(unsigned char key, int x, int y)
{
    correctCoords(x,y);
    Collage::sharedCollage().keyboard(key, x, y);
}

/*
 * Create Display Window
 */
int main(int argc, char** argv)
{    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT); 
    glutInitWindowPosition (400, 100);
    glutCreateWindow ("Collage Builder");
        
    // Set the GL origin to be at the lower left
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glViewport(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // Set the first page
    Collage::sharedCollage().setDisplayPage(new MainPage());
    
    // Main Functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape); 
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}