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
    // Properties
    elementType = TEXT_ELEMENT;
    text = s;
    width = 1;
    height = 1;
    x = centerX - width/2;
    y = centerY - height/2;
    color = new BaseColor(0,0,0,0);
    rotation = 0;
    
    // Initialize states
    initialize();
}

TextElement::TextElement(TextElement *copy)
{
    // Copy Properties
    elementType = TEXT_ELEMENT;
    text = copy->getText();
    width = copy->getWidth();
    height = copy->getHeight();
    x = copy->getX()+1;// offset the copy
    y = copy->getY()+1;// offset the copy
    rotation = copy->getRotation();
    BaseColor *cColor = copy->getColor();
    color = new BaseColor(cColor->color.red, cColor->color.green, cColor->color.blue, cColor->color.alpha);

    // Initialize states
    initialize();
}

void TextElement::initialize()
{
    // Create Bounds
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
    width = Collage::sharedCollage().getFont()->calculateWidth(text, scaleX);
    height = Collage::sharedCollage().getFont()->calculateHeight(text, scaleY);
}

void TextElement::updateSize()
{
    // Get the width and height for a scale of 1
    double w = Collage::sharedCollage().getFont()->calculateWidth(text, 1);
    double h = Collage::sharedCollage().getFont()->calculateHeight(text, 1);
    
    // Calcualte the new scale = NewDimension/OldDimensino
    scaleX = width/w;
    scaleY = height/h;
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

void TextElement::setWidth(int w)
{
    width = w;
    updateSize();
}

void TextElement::setHeight(int h)
{
    height = h;
    updateSize();
}


void TextElement::drawElement()
{  
    // Draw the text using the basefont
    Collage::sharedCollage().getFont()->draw(text, scaleX, scaleY);
}