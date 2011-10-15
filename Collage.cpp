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
    
    // Initialize Font
    mainFont = new BaseFont(0);
    
    numElements = 0;
    created = false;
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

void Collage::keyboard(unsigned char key, int x, int y)
{
    displayPage->keyboard(key,x,y);
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

bool Collage::removeElement(BaseElement *elem)
{
    bool found = false;
    for(int i = 0; i < numElements; i++)
    {
        // If the element has been found move all other elements up
        if(found)
        {
            elements[i-1] = elements[i];
        }
        else if(elem == elements[i])
        {
            found = true;
            elements[i] = NULL;
        }
    }
    
    // decriment the numElements
    if(found)
        numElements--;
    
    return found;
}

bool Collage::moveElementForward(BaseElement *elem)
{
    int index = getZValue(elem);
    if(index < 0)
        return false; // No element found
    else if(index == numElements-1)
        return true; // element already at the front
    else
    {
        BaseElement *temp = elements[index];
        elements[index] = elements[index+1];
        elements[index+1] = temp;
        return true;
    }
        
}
bool Collage::moveElementBackward(BaseElement *elem)
{
    int index = getZValue(elem);
    if(index < 0)
        return false; // No element found
    else if(index == 0)
        return true; // element already at the back
    else
    {
        BaseElement *temp = elements[index];
        elements[index] = elements[index-1];
        elements[index-1] = temp;
        return true;
    }
    
}

int Collage::getZValue(BaseElement *elem)
{
    int z = -1;
    for(int i = 0; i < numElements; i++)
    {
        if(elements[i] == elem)
            z = i;
    }
    return z;
}

void Collage::setupCollage()
{
    // If this is the first time the collage is displayed
    // Randomize the location of elements
    if(!created)
    {
        
    }
}

void Collage::drawElements()
{
    drawElements(0,0);
}

void Collage::drawElements(int offsetX, int offsetY)
{
    
    glTranslatef(offsetX, offsetY, 0);
    for(int i = 0; i < numElements; i++)
    {
        elements[i]->draw();
    }
}

int Collage::getNumberOfElements()
{
    return numElements;
}

BaseElement* Collage::getElement(int index)
{
    return elements[index];
}

BaseFont* Collage::getFont()
{
    return mainFont;
}