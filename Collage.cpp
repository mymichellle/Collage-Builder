//
//  Collage.cpp
//  Collage
//
//  Created by Michelle Alexander on 9/23/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

#include "Collage.h"


Collage::Collage()
{
    // Set color to white
    glClearColor(1,1,1,0);
    glShadeModel(GL_FLAT);
    
    // Initial Page
    displayPage = new BasePage();
    
    numElements = 0;
}

void Collage::display(void)
{
    displayPage->display();
}

void Collage::reshape(int w, int h)
{

}

void Collage::mouse(int button, int state, int x, int y) 
{
    displayPage->mouse(button, state, x, y);
}

void Collage::mouseMotion(int x, int y)
{
    displayPage->mouseMotion(x,y);
}

void Collage::setDisplayPage(BasePage *newPage)
{
    displayPage->cleanUp();
    displayPage = NULL;
    displayPage = newPage;
    glutPostRedisplay();
}

bool Collage::addElement(BaseElement *elem)
{
    if(numElements < MAX_ELEMENTS)
    {
        elements[numElements] = elem;
        numElements++;
        return true;
    }
    else
        return false;
}

void Collage::drawElements()
{
    for(int i = 0; i < numElements; i++)
        elements[i]->draw();
}

int Collage::getNumberOfElements()
{
    return numElements;
}

BaseElement* Collage::getElement(int index)
{
    return elements[index];
}