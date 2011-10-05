//
//  BaseElement.h
//  Collage
//
//  Created by Michelle Alexander on 9/23/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef BaseElement_h
#define BaseElement_h

#include "Utility.h"

#define CORNER_SIZE 5

class CornerBox
{
private:
    int x;
    int y;
    bool selected;
    
public:
    CornerBox(int xpos, int ypos);
    void draw();
    bool pointInBounds(int xpos, int ypos);
    void setPosition(int xpos, int ypos);
    void select(bool s);
    bool isSelected();
    
};

class BaseElement
{
protected:
    enum Type{
        IMAGE_ELEMENT,
        TEXT_ELEMENT
    };

    // Coordinates lower left
    int x;
    int y;
    int z;
    
    // Bounding box dimensions
    int width;
    int height;
    
    // Bounding box corners
    static const int numCorners = 4;
    enum CornerType{
        CBL,
        CBR,
        CTR,
        CTL
    };
    CornerBox *corners[numCorners];
    void setCorners();
    
    // Properties
    BaseColor *color;
    double rotation;
    enum Type elementType;
    
    // States
    bool selected;
    bool moveable;
    
    // Manipulation Variables
    int startX;
    int startY;
    
    bool pointInBounds(int xCord, int yCord);
    
public:
    BaseElement();
    void setPosition(int xpos, int ypos);
    void setWidth(int w, bool locked);
    void setHeight(int h, bool locked);
    void setRotation(double r);
    void setColor(float r, float g, float b);
    bool mouse(int button, int state, int xpops, int ypos);
    bool mouseMotion(int xpos, int ypos);
    virtual void draw();
};


#endif