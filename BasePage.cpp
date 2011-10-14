//
//  BasePage.cpp
//  Collage
//
//  Created by Michelle Alexander on 9/23/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include "Collage.h" //includes BasePage.h

#include <GL/glut.h>
#include <stdlib.h>

BasePage::BasePage()
{
    width = 400;
    height = 400;
}

void BasePage::enterPage()
{
}

void BasePage::mouse(int button, int state, int x, int y) 
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN){
                Collage::sharedCollage().setDisplayPage(new BasePage());
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
            {
                exit(0);
            }
            break;
        default:
            break;
    }
}

void BasePage::mouseMotion(int x, int y)
{
    
}

void BasePage::keyboard(unsigned char key, int x, int y)
{
    
}

void BasePage::display(void)
{
    glPushMatrix();
    
    glColor3f(1,0,1);
    glPointSize(6);
    
    glBegin(GL_POINTS);
    float k, h, v;
    for( k=0; k < 10; k++)
    {
        h = rand()%200-100;
        v = rand()%200-100;
        glVertex3f(h,v, 0);
    }
    glEnd();
    
    glFlush();
    glPopMatrix(); 
}

void BasePage::cleanUp(void)
{
    
}
