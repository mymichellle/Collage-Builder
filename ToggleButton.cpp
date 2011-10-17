//
//  ToggleButton.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/17/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include "ToggleButton.h"
#include <iostream>

using namespace std;

ToggleButton::ToggleButton(string s, int xCord, int yCord)
{
    width = BUTTON_WIDTH;
    height = BUTTON_HEIGHT;
    
    // xCord and yCord represent the center of the button
    // convert to lower left corner
    x = xCord - width/2;
    y = yCord - height/2;
    
    label = s;
    
    fillColor = new BaseColor(0, 0, .4, 1);
    selectColor = new BaseColor(0.5,0.5,0.7,1);
    fontColor = new BaseColor(1,1,1,1);
    
    selected = false;
    mouseDownInButton = false;
}

// Returns true if the button was successfully clicked
bool ToggleButton::mouse(int button, int state, int x, int y)
{
    bool buttonClicked = false;
    
    if(button == GLUT_LEFT_BUTTON && pointInBounds(x,y))
    {
        if (state == GLUT_DOWN)
        {
            mouseDownInButton = true;
            // invert selected's previous state
            selected = !selected;
        }
        else if( state == GLUT_UP && mouseDownInButton)
        {
            buttonClicked = true;
            // Clear mouse down
            mouseDownInButton = false;
        }        
        
    }
    else if( button == GLUT_LEFT_BUTTON && mouseDownInButton)
    {
        // If the mouse started in the button but moved before release
        // reverset the selection
        selected = !selected;
        // Clear mouse down
        mouseDownInButton = false;
    }
    
    // re-draw the button
    glutPostRedisplay();
    
    
    return buttonClicked;

}

void ToggleButton::setSelected(bool s)
{
     selected = s;
}