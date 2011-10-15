//
//  BaseDialog.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/13/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include "BaseDialog.h"
#include <string>
#include <sstream>
#include "Utility.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

BaseDialog::BaseDialog(string t, string d, int centerX, int centerY)
{
    initialize(t,d,centerX, centerY, 100);
}

BaseDialog::BaseDialog(string t, string d, int centerX, int centerY, int w)
{
    initialize(t,d,centerX, centerY, w);
}

void BaseDialog::initialize(string t, string d, int centerX, int centerY, int w)
{
    width = w;
    height = 30;
    x = centerX - width/2;
    y = centerY - height/2;
    textX = x+5;
    textY = y+5;
    
    active = false;
    pressed = false;
    
    label = t;
    val = d;
    valLength = val.length();
}

bool BaseDialog::mouse(int button, int state, int x, int y)
{
    if(pointInBounds(x,y) && button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            pressed = true;
            active = false;
        }
        else if( pressed && state == GLUT_UP) 
        {
            active = true;
            pressed = false;
        }
        else
        {
            active = false;
            pressed = false;
        }
    }
    else
    {
        active = false;
        pressed = false;
    }
    
    // Redraw
    glutPostRedisplay();
    return active;
}

bool BaseDialog::mouseMotion(int xpos, int ypos)
{
    return true;
}

void BaseDialog::keyboard(unsigned char key, int x, int y)
{
    if(active)
    {
        switch (key) {
            // Backspace
            case 8:
                if(valLength > 0)
                {
                    valLength--;
                    val.erase(valLength);
                }
                break;
                
            // Enter
            case 13:
            // Escape
            case 27:
                active = false;
                break;
            default:
                val+=key;
                valLength++;
                break;
        }
        glutPostRedisplay();
    }
}

void BaseDialog::draw()
{
    
    glPushMatrix();
    
    if(active)
    {
        glColor3f(.75, .75, .75);
        //glutSetCursor(GLUT_CURSOR_TEXT);
    }
    else
    {
        glColor3f(.6,.6,.6);
        //glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    }
    
    // Draw the box
    glPointSize(1);
    glRectf(x, y, x+width, y+height);
    
    // Set text color
    glColor3f(0,0,0);
    
    // Place the label to the left
    int labelW = displayStringWidth(label);
    int labelH = displayStringHeight(label);
    glRasterPos3f(x - labelW, y+(height/2 - labelH/2), 0.5);  
    
    // Draw label
    displayString(label);
    
    // Place the editable text inside the box
    int valW = displayStringWidth(val);
    int valH = displayStringHeight(val);
    glRasterPos3f(textX, y+(height/2 - valH/2), 0.5);  
    
    // Draw label
    displayString(val);
    
    glFlush();
    glPopMatrix();
}

string BaseDialog::getValue()
{
    return val;
}

void BaseDialog::setValue(string s)
{
    val = s;
}

void BaseDialog::setValue(float f)
{
    ostringstream buffer;
    buffer<<f;
    val = buffer.str();
}

bool BaseDialog::pointInBounds(int xCord, int yCord)
{
    if( x <= xCord && xCord <= x + width && 
       y <= yCord && yCord <= y+height)
        return true;
    return false;
}