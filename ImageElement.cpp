//
//  ImageElement.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/12/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include "ImageElement.h"

ImageElement::ImageElement()
{
    x = 0;
    y = 0;
    z = 0;
    width = 100;
    height = 50;
    color = new BaseColor(1,0,0,0);
    rotation = 15;
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

void ImageElement::drawElement()
{
    glRectf(0,0,width,height);
}
