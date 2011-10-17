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
        glColor3f(1, 1, 1);
    }
    else
    {
        glColor3f(.8,.8,.8);
        glColor3f(1, 1, 1);
    }
    
    // Draw the box
    glPointSize(1);
    glRectf(x, y, x+width, y+height);
    // Draw an outline around the text box
    if(active)
    {
        glColor3f(.4,.4,1);
        glLineWidth(3);
    }
    else
    {
        glColor3f(.5,.5,.5);
        glLineWidth(2);
    }
    
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y); 
        glVertex2f(x+width, y);
        glVertex2f(x+width, y+height);
        if(!active)
        {
            glLineWidth(3);
            glColor3f(0,0,0);
        }
        glVertex2f(x, y+height);
    glEnd();
    
    
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
    valLength = val.length();
}

void BaseDialog::setValue(float f)
{
    ostringstream buffer;
    buffer<<f;
    val = buffer.str();
    valLength = val.length();
}

bool BaseDialog::pointInBounds(int xCord, int yCord)
{
    if( x <= xCord && xCord <= x + width && 
       y <= yCord && yCord <= y+height)
        return true;
    return false;
}