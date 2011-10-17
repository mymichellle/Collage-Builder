//
//  BaseButton.cpp
//  Collage
//
//  Created by Michelle Alexander on 9/23/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include "BaseButton.h"
#include <Gl/gl.h>
#include <iostream>

using namespace std;

BaseButton::BaseButton(string s, int xCord, int yCord)
{
    width = 120;
    height = 50;
    
    // xCord and yCord represent the center of the button
    // convert to lower left corner
    x = xCord - width/2;
    y = yCord - height/2;
    
    label = s;
    
    fillColor = new BaseColor(0, 0, .4, 1);
    selectColor = new BaseColor(0.5,0.5,0.7,1);
    fontColor = new BaseColor(1,1,1,1);
    
    selected = false;
}

bool BaseButton::pointInBounds(int xCord, int yCord)
{
    if( x <= xCord && xCord <= x + width && 
       y <= yCord && yCord <= y+height)
        return true;
    return false;
}

// Returns true if the button was successfully clicked
bool BaseButton::mouse(int button, int state, int x, int y)
{
    bool buttonClicked = false;
    
    if(button == GLUT_LEFT_BUTTON && pointInBounds(x,y))
    {
        if (state == GLUT_DOWN)
        {
            selected = true;
        }
        else if( state == GLUT_UP)
        {
            selected = false;
            buttonClicked = true;
        }
        
        // re-draw the button
        glutPostRedisplay();
    }
    else
    {
        // Make sure the button does not get "stuck" selected
        selected = false;
        // re-draw the button
        glutPostRedisplay();
    }
    
    return buttonClicked;
}

// Draws the button
void BaseButton::draw()
{
    
    glPushMatrix();
    
    if(selected)
        glColor3f(selectColor->color.red, selectColor->color.green, selectColor->color.blue);
    else
        glColor3f(fillColor->color.red, fillColor->color.green, fillColor->color.blue);
    
    // Draw the button
    glPointSize(3);
    glRectf(x, y, x+width, y+height);
    
    // Make the button look 3D
    glLineWidth(3);
    if(selected)
        glColor3f(1,1,1);
    else
        glColor3f(0,0,0);
    
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y); 
    glVertex2f(x+width, y);
    if(selected)
        glColor3f(0,0,0);
    else
        glColor3f(selectColor->color.red, selectColor->color.green, selectColor->color.blue);
    glVertex2f(x+width, y+height);
    glVertex2f(x, y+height);
    glEnd();
    
    // Set the label color
    glColor3f(fontColor->color.red, fontColor->color.green, fontColor->color.blue);
    
    // Center the label
    int labelW = displayStringWidth(label);
    int labelH = displayStringHeight(label);
    glRasterPos3f(x+(width/2 - labelW/2), y+(height/2 - labelH/2), 0.5);  
    
    // Draw label
    displayString(label);
    
    glFlush();
    glPopMatrix();
}