//
//  Collage.cpp
//  Collage
//
//  Created by Michelle Alexander on 9/23/11.
//  Copyright 2011 ??? . All rights reserved.
//
//  Collage is a singleton that can be accessed throughout the program
//  All user interactions are sent through the Collage to the active page
//  All information about the collage's elements and default settings is stored here

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

#include "Collage.h"

using namespace std;

// One Collage is created when the application is run
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
    setDefaultValues(BaseElement::IMAGE_ELEMENT, 100,100,1,0,new BaseColor(1,1,1,1));
    setDefaultValues(BaseElement::TEXT_ELEMENT, 1,1,1,0,new BaseColor(0,0,0,1));
    
    numElements = 0;
    created = false;
    randomized = false;
}

void Collage::display(void)
{
    displayPage->display();
}

// Ability to modify the reshape function
void Collage::reshape(int w, int h)
{

}

// Pass mouse press activities to the active page
void Collage::mouse(int button, int state, int x, int y) 
{
    displayPage->mouse(button, state, x, y);
}

// Pass mouseMotion activites to the active page
void Collage::mouseMotion(int x, int y)
{
    displayPage->mouseMotion(x,y);
}

// Pass Keyboard activites to the active page
void Collage::keyboard(unsigned char key, int x, int y)
{
    displayPage->keyboard(key,x,y);
}

// Change the Active Page
void Collage::setDisplayPage(BasePage *newPage)
{
    displayPage->cleanUp();
    displayPage = NULL;
    displayPage = newPage;
    glutPostRedisplay();
}

// Reset the collage remove all old elements and change the name
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
    setDefaultValues(BaseElement::IMAGE_ELEMENT, 100,100,1,0,new BaseColor(1,1,1,1));
    setDefaultValues(BaseElement::TEXT_ELEMENT, 1,1,1,0,new BaseColor(0,0,0,1));
    
    // Reset states
    created = true;
    randomized = false;
}

// To begin a collage set the default values
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

// Add an element to the collage
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

// remove an element
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

// move an element forward in the z direction
// note all elements are technically on the same z plane this 
// just changes the order they are drawn in
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

// move an element backward in the z direction
// note all elements are technically on the same z plane this 
// just changes the order they are drawn in
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

// Get the z order of the element
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

// Initialize the collages display
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
        
            // update the elements bounds
            elements[i]->updateBounds();
        }
    }
}

// Draw the elements with zero offset
void Collage::drawElements()
{
    drawElements(0,0);
}

// Draw the elements with an offset
void Collage::drawElements(int offsetX, int offsetY)
{
    
    glTranslatef(offsetX, offsetY, 0);
    for(int i = 0; i < numElements; i++)
    {
        elements[i]->draw();
    }
}

// Return the number of elements
int Collage::getNumberOfElements()
{
    return numElements;
}

// Get the element at z index
BaseElement* Collage::getElement(int index)
{
    return elements[index];
}

// Get the active font to write words to the screen
BaseFont* Collage::getFont()
{
    return mainFont;
}

// Access the default rotation set on the settings page
float Collage::getDefaultRotation(enum BaseElement::Type t)
{
    if(t == BaseElement::IMAGE_ELEMENT)
        return defaultImgRotation;
    else if( t == BaseElement::TEXT_ELEMENT)
        return defaultTextRotation;
    else
        return 0;
}

// Access the default color set on the settings page
BaseColor* Collage::getDefaultColor(enum BaseElement::Type t)
{
    if(t == BaseElement::IMAGE_ELEMENT)
        return defaultImgColor;
    else if( t == BaseElement::TEXT_ELEMENT)
        return defaultTextColor;
    else
        return new BaseColor(0,0,0,1);
}

// Access the default size set on the settings page
double Collage::getDefaultSize(enum BaseElement::Type t)
{
    if(t == BaseElement::IMAGE_ELEMENT)
        return defaultImgSize;
    else if( t == BaseElement::TEXT_ELEMENT)
        return defaultTextSize;
    else
        return 0;
}

// Access the default width set on the settings page
int Collage::getDefaultWidth(enum BaseElement::Type t)
{
    if(t == BaseElement::IMAGE_ELEMENT)
        return defaultImgWidth;
    else if( t == BaseElement::TEXT_ELEMENT)
        return defaultTextRotation;
    else
        return 0;
}

// access the default height set on the settings page
int Collage::getDefaultHeight(enum BaseElement::Type t)
{
    if(t == BaseElement::IMAGE_ELEMENT)
        return defaultImgHeight;
    else if( t == BaseElement::TEXT_ELEMENT)
        return defaultTextHeight;
    else
        return 0;
}

// Check if there is an active collage
bool Collage::isCreated()
{
    return created;
}

// Get the name of the active Collage
string Collage::getName()
{
    return name;
}