//
//  BaseElement.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/1/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include <GL/gl.h>
#include "BaseElement.h"
#include <stdlib.h>
#include <iostream>

BaseElement::BaseElement()
{
    x = 0;
    y = 0;
    z = 0;
    width = 10;
    height = 10;
    color = new BaseColor(0,0,0,0);
    rotation = 0;
    
    selected = false;
    moveable = false;
    startX = 0;
    startY = 0;
    
    // Initialize the corners
    setCorners();
}

void BaseElement::setCorners()
{
    corners[CBL] = new CornerBox(x, y);
    corners[CBR] = new CornerBox(x+width, y);
    corners[CTR] = new CornerBox(x+width, y+height);
    corners[CTL] = new CornerBox(x, y+height);
}

void BaseElement::setPosition(int xpos, int ypos)
{
    x = xpos;
    y = ypos;
}

void BaseElement::setWidth(int w, bool locked)
{
    if(locked)
    {
        double scale = w/width;
        height = height*scale;
    }
    width = w;
    
    // update the corners
    setCorners();
}

void BaseElement::setHeight(int h, bool locked)
{
    if(locked)
    {
        double scale = h/height;
        width = width * scale;
    }
    height = height;
    
    // update the corners
    setCorners();
}

void BaseElement::setRotation(double r)
{
    rotation = r;
}

void BaseElement::setColor(float r, float g, float b)
{
    color->color.red = r, color->color.green = g, color->color.blue = b;
}

bool BaseElement::pointInBounds(int xCord, int yCord)
{
    if( x <= xCord && xCord <= x + width && 
       y <= yCord && yCord <= y+height)
        return true;
    return false;
}

// Returns true if the button was successfully clicked
bool BaseElement::mouse(int button, int state, int xpos, int ypos)
{
    
    //cout<<"BaseElement mouse button "<<button<<" state "<<state<<" ("<<xpos<<", "<<ypos<<")"<<endl;
    //cout<<"bounds ("<<x<<", "<<y<<", "<<x+width<<", "<<y+height<<")"<<endl;
    bool cornerSelect = false;
    
    if(selected && button == GLUT_LEFT_BUTTON)
    {
        cout<<"BaseElement checking corners"<<endl;
        // Check the corners
        for(int i = 0; i < numCorners; i++)
        {
            if(corners[i]->pointInBounds(xpos, ypos))
            {
                cout<<"CORNERFOUND"<<endl;
                corners[i]->select(true);
                cornerSelect = true;
                glutPostRedisplay();
            }
            else 
                corners[i]->select(false);
        }
    }
    
    if(!cornerSelect  && button == GLUT_LEFT_BUTTON && pointInBounds(xpos,ypos))
    {

        if (state == GLUT_DOWN)
        {
            moveable = true;
            startX = xpos;
            startY = ypos;
        }
        else if( state == GLUT_UP && moveable)
        {
            selected = true;
            moveable = false;
        }
        else
        {
            selected = false;
        }
        
        // re-draw the button
        glutPostRedisplay();
    }
    else
    {
        // Make sure the button does not get "stuck" selected
        selected = false;
        moveable = false;
        cout<<"BaseElement mouse button UNPRESS"<<endl;
        // re-draw the button
        glutPostRedisplay();
    }
    
    return selected;
}

bool BaseElement::mouseMotion(int xpos, int ypos)
{
    //cout<<"BaseElement mouseMotion ("<<xpos<<", "<<ypos<<")"<<endl;
    
    // Check if a corner is selected
    // Movement of a corner changes size.
    for(int i = 0; i < numCorners; i++)
    {
        if(corners[i]->isSelected())
        {
            int w = width;
            int h = height;
            
            // Size change is handled differently at each corner
            switch(i)
            {
                case CBL:
                    // Origin x, y change
                    
                    break;
                case CBR:
                    // x stays the same y changes
                    
                    break;
                case CTR:
                    // Origin x, y stays the same
                    w = w + (xpos - startX);
                    h = h + (ypos - startY);
                    setWidth(w, false);
                    setHeight(h, false);
                    break;
                case CTL:
                    // y stays the same
                    
                    break;
                default:
                    break;
            }
            
            // If a corner is moved no other action should be done to the object
            // save new mouse point
            startX = xpos;
            startY = ypos;
            // redraw page
            glutPostRedisplay();
            return true;
        }
    }
    
    if(moveable)
    {
        // Move the element the difference of the previous mouse location and current
        setPosition(x + (xpos - startX), y + (ypos - startY));
        // update the corner locations
        setCorners();
        
        // save the new mouse position
        startX = xpos;
        startY = ypos;
    }
    glutPostRedisplay();
}

void BaseElement::draw()
{
    glPushMatrix();
    if(moveable)
        glColor3f(0,0,1);
    else if(selected)
        glColor3f(0,1,0);
    else
        glColor3f(color->color.red,color->color.green,color->color.blue);
    glPointSize(1);
    
    glRectf(x,y,x+width, y+width);
    
    // Draw the bounding box corners if selected
    if(selected)
    {
        for(int i = 0; i < numCorners; i++)
            corners[i]->draw();
    }
    
    glFlush();
    glPopMatrix(); 
}

// Corner Functions
CornerBox::CornerBox(int xpos, int ypos)
{
    x = xpos;
    y = ypos;
    selected = false;
}

void CornerBox::draw()
{
    if(selected)
        glColor3f(1,0,0);
    else
        glColor3f(1,0,1);
    glRectf(x - (CORNER_SIZE/2), y - (CORNER_SIZE/2), x + CORNER_SIZE/2, y + CORNER_SIZE/2);
}

bool CornerBox::pointInBounds(int xpos, int ypos)
{
    if(xpos > x - (CORNER_SIZE/2) && xpos < x + (CORNER_SIZE/2) &&
       ypos > y - (CORNER_SIZE/2) && ypos < y + (CORNER_SIZE/2))
        return true;
    return false;
}

void CornerBox::select(bool s)
{
    selected = s;
}

bool CornerBox::isSelected()
{
    return selected;
}

