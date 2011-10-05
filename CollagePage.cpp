//
//  CollagePage.h
//  Collage
//
//  Created by Michelle Alexander on 10/05/11.
//  Copyright 2011 ??? . All rights reserved.
//
#include <GL/glut.h>
#include <GLUT/glut.h>

#include "CollagePage.h"
#include "Utility.h"
#include "Collage.h"
#include "CreatePage.h"

using namespace std;

CollagePage::CollagePage()
{    
    title = "Collage";
    
    btn_back = new BaseButton("BACK", 100, 70);
}

void CollagePage::mouseMotion(int x, int y)
{
    int numElements = Collage::sharedCollage().getNumberOfElements();
    // Pass mouse movement to elements
    for(int i = 0; i < numElements; i++)
    {
        Collage::sharedCollage().getElement(i)->mouseMotion(x,y);
    }
}

void CollagePage::mouse(int button, int state, int x, int y)
{
    int numElements = Collage::sharedCollage().getNumberOfElements();
    // Pass mouse press to elements
    for(int i = 0; i < numElements; i++)
    {
        Collage::sharedCollage().getElement(i)->mouse(button, state, x,y);
    }
    
    // Check for button presses
    if(btn_back->mouse(button, state, x, y))
        onBackPress();
}

void CollagePage::onBackPress()
{
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void CollagePage::display()
{
    glPushMatrix();
    
    // Draw the title
    glColor3f(0, 0, 0);
    glRasterPos3f(getMainTitleX(title), getMainTitleY(title), 0.5);    
    displayString(title);
    
    // Draw buttons
    btn_back->draw();
    
    // Draw the Elements
    Collage::sharedCollage().drawElements();
    
    glFlush();
    glPopMatrix();
}