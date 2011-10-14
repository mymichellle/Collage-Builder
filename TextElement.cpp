//
//  TextElement.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/13/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include "TextElement.h"
#include "Utility.h"
#include <iostream>

using namespace std;

TextElement::TextElement(string s, int centerX, int centerY)
{
    text = s;
    width = displayStringWidth(text);
    height = displayStringHeight(text);
    x = centerX - width/2;
    y = centerY - height/2;
    color = new BaseColor(0,0,0,0);
    rotation = 0;
    bounds = new BoundingBox(x, y, width, height, rotation);
    
    // Movement properties
    selected = false;
    moveable = false;
    rotateable = false;
    startX = 0;
    startY = 0;
    
    // Initialize the corners
    selectedCorner = CNONE;
}

void TextElement::drawElement()
{
    // Draw the string
    glColor3f(1,0,0);
    glRasterPos3f(0, 0, 0.5);    
    displayString(text);
}