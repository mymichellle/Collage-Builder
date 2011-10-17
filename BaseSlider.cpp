//
//  BaseSlider.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/17/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include "BaseSlider.h"
#include <Gl/gl.h>
#include <iostream>

using namespace std;

BaseSlider::BaseSlider(string l, int xCord, int yCord, int minVal, int maxVal)
{
    // Properties
    label = l;
    width = SLIDER_WIDTH;
    height = SLIDER_HEIGHT;
    min = minVal;
    max = maxVal;
    value = 0;
    
    // (xCord, yCord) given as center point, convert to btm left
    x = xCord - width/2;
    y = yCord - height/2;
    position = 100;
    moveable = false;
}

// Calculate the value based on the current position
double BaseSlider::valueToPosition()
{
    // scale the value to position coords and shift by x
    double calcPos = value * ((double)width/max);
    
    // Keep the position between 0 and width
    if(calcPos < 0)
        calcPos = 0;
    else if(calcPos > width)
        calcPos = width;
    
    return calcPos;
}

// Calculate the position based on the current value
double BaseSlider::positionToValue()
{
    // remove the x offset and scale the position ot value
    double calcVal = (position) * ((double)max/width);
    
    // Keep the value between min and max
    if(calcVal < min)
        calcVal = min;
    else if(calcVal > max)
        calcVal = max;
    
    return calcVal;
}

// Check if the point is within the slider bounds
bool BaseSlider::pointInBounds(int xp, int yp)
{
    // Check if the point is inside the slider
    if(yp > y && yp < y + height && 
       xp > ((x + position)-SLIDER_BOX/2) && 
       xp < ((x+position)+SLIDER_BOX/2))
    {
        return true;
    }
    return false;
}

// Set the slider value
double BaseSlider::setValue(double v)
{
    // Make sure the value is within bounds
    if(value > max)
        value = max;
    else if (value < min)
        value = min;
    else
        value = v;

    // Calcualte the new position
    position = valueToPosition();
    
    // Re-draw the slider
    glutPostRedisplay();
}

// Mouse events
bool BaseSlider::mouse(int button, int state, int x, int y)
{
    // If the mouse is pressed inside the slider box, the box is moveable
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && pointInBounds(x,y))
        moveable = true;
    else
        moveable = false;
    
    return moveable;
}

// Moves the slider if it is selected and returns true if a change has been made
bool BaseSlider::mouseMotion(int xpos, int ypos)
{
    // If the slider has been selected drag with the mouse
    if(moveable)
    {
        if(xpos-x < 0)
            position = 0;
        else if(xpos-x > width)
            position = width;
        else
            position = xpos - x;
        value = positionToValue();
    
        // re-draw the slider
        glutPostRedisplay();
        return true;
    }
    
    // No changes made
    return false;
}

// Display
void BaseSlider::draw()
{
    glPushMatrix();
    
    // Translate to x, y
    glTranslatef(x, y, 0);
    
    // Draw the slider bar
    glColor3f(0,0,0);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(0, SLIDER_HEIGHT/2);
    glVertex2f(width, SLIDER_HEIGHT/2);
    glEnd();
    
    // Draw the slider
    if(moveable)
        glColor3f(.4,.4,1);
    else
        glColor3f(.5,.5,.5);
    glRectf(position-SLIDER_BOX/2, 0, position+SLIDER_BOX/2, SLIDER_HEIGHT);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0,0,0);
    // Place the label to the left
    int labelW = displayStringWidth(label);
    int labelH = displayStringHeight(label);
    glRasterPos3f(x - labelW - SLIDER_BOX, y+(height/2 - labelH/2), 0.5);
    
    // Draw label
    displayString(label);
    
    glPopMatrix();
}

