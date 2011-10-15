//
//  TextElement.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/13/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include "TextElement.h"
#include "Utility.h"
#include "Collage.h"
#include <iostream>


using namespace std;

TextElement::TextElement(string s, int centerX, int centerY)
{
    elementType = TEXT_ELEMENT;
    text = s;
    width = 1;
    height = 1;
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
    scaleX = 1;
    scaleY = 1;
    updateDimensions();
    
    // Initialize the corners
    selectedCorner = CNONE;
}

void TextElement::setText(string s)
{
    text = s;
}

void TextElement::updateDimensions()
{
    width = Collage::sharedCollage().getFont()->calculateWidth(text);
    height = Collage::sharedCollage().getFont()->calculateHeight(text);
}

void TextElement::setFontSize(double s)
{
    scaleX = s;
    scaleY = s;
    updateDimensions();
}

void TextElement::setFontScale(double w, double h)
{
    scaleX = w;
    scaleY = h;
    updateDimensions();
}
/*
void BaseElement::setWidth(int w, bool locked)
{
    //cout<<"setWidth w = "<<w<<endl;
    if(locked)
    {
        cout<<"LOCKED"<<endl;
        double scale = w/width;
        height = height*scale;
    }
    width = w;
}

void BaseElement::setHeight(int h, bool locked)
{
    if(locked)
    {
        double scale = h/height;
        width = width * scale;
    }
    height = h;
}
*/

void TextElement::drawElement()
{  
    // Draw the text using the basefont
    Collage::sharedCollage().getFont()->draw(text, scaleX, scaleY);
}