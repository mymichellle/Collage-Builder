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

using namespace std;

Collage::Collage()
{
    // Set color to white
    glClearColor(1,1,1,0);
    glShadeModel(GL_FLAT);
    
    // Initial Page
    displayPage = new BasePage();
    
    // Initialize Font
    mainFont = new BaseFont(0);
    
    // Initialize default values
    setDefaultValues(BaseElement::IMAGE_ELEMENT, 100,100,1,0,new BaseColor(0,0,0,0));
    setDefaultValues(BaseElement::TEXT_ELEMENT, 1,1,1,0,new BaseColor(0,0,0,0));
    
    numElements = 0;
    created = false;
    randomized = false;
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

void Collage::createNewCollage(string n)
{
    // Assign the new name
    name = n;
    
    // Remove any elements
    for(int i = 0; i < numElements; i++)
    {
        elements[i] = NULL;
    }
    numElements = 0;
    
    // Reset default values
    setDefaultValues(BaseElement::IMAGE_ELEMENT, 100,100,1,0,new BaseColor(1,1,1,.75f));
    setDefaultValues(BaseElement::TEXT_ELEMENT, 1,1,1,0,new BaseColor(0,0,0,0));
    
    // Reset states
    created = true;
    randomized = false;
}

void Collage::setDefaultValues(enum BaseElement::Type t, int w, int h, double s, float r, BaseColor *c)
{
    if(t == BaseElement::IMAGE_ELEMENT)
    {
        defaultImgRotation = r;
        defaultImgColor = c;
        defaultImgSize = s;
        defaultImgWidth = w;
        defaultImgHeight = h;
    }
    else if(t == BaseElement::TEXT_ELEMENT)
    {
        defaultTextRotation = r;
        defaultTextColor = c;
        defaultTextSize = s;
        defaultTextWidth = w;
        defaultTextHeight = h;
    }
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
    if(!randomized)
    {
        randomized = true;
        int w, h;
        for(int i = 0; i < numElements; i++)
        {
            // generate a random position at least 50 pixels away from the edges
            elements[i]->setPosition(rand() % (COLLAGE_DISPLAY_WIDTH - 100) + 50, rand()%(COLLAGE_DISPLAY_HEIGHT - 100)+50);
        }
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

float Collage::getDefaultRotation(enum BaseElement::Type t)
{
    if(t == BaseElement::IMAGE_ELEMENT)
        return defaultImgRotation;
    else if( t == BaseElement::TEXT_ELEMENT)
        return defaultTextRotation;
    else
        return 0;
}

BaseColor* Collage::getDefaultColor(enum BaseElement::Type t)
{
    if(t == BaseElement::IMAGE_ELEMENT)
        return defaultImgColor;
    else if( t == BaseElement::TEXT_ELEMENT)
        return defaultTextColor;
    else
        return new BaseColor(0,0,0,1);
}

double Collage::getDefaultSize(enum BaseElement::Type t)
{
    if(t == BaseElement::IMAGE_ELEMENT)
        return defaultImgSize;
    else if( t == BaseElement::TEXT_ELEMENT)
        return defaultTextSize;
    else
        return 0;
}

int Collage::getDefaultWidth(enum BaseElement::Type t)
{
    if(t == BaseElement::IMAGE_ELEMENT)
        return defaultImgWidth;
    else if( t == BaseElement::TEXT_ELEMENT)
        return defaultTextRotation;
    else
        return 0;
}

int Collage::getDefaultHeight(enum BaseElement::Type t)
{
    if(t == BaseElement::IMAGE_ELEMENT)
        return defaultImgHeight;
    else if( t == BaseElement::TEXT_ELEMENT)
        return defaultTextHeight;
    else
        return 0;
}

bool Collage::isCreated()
{
    return created;
}

string Collage::getName()
{
    return name;
}