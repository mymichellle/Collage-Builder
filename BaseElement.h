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

#define CORNER_SIZE 10
#define PI 3.14159265

class BoundingBox
{
public:
    BoundingBox(int x, int y, int w, int h, int a); // takes angle in degrees
    
    // Bounds Checking
    bool pointInBounds(int xp, int yp);
    int checkCorners(int xp, int yp);
    
    // Setters
    void setAngle(int a); // takes angle in degrees
    void setOrigin(int xp, int yp);
    void setDimensions(int w, int h);
    
    // Calculations
    void calculateResize(int xp, int yp, bool locked, int corner, double *ans);
    double calculateRotate(int xp1, int yp1, int xp2, int yp2);
    
    void draw(int selectedCorner);
    
    static const int numCorners = 4;
    
private:
    // Given values
    int xO;
    int yO;
    int width;
    int height;
    double angle; // Radians
    
    // Calculated values
    int xBR,yBR,xTR,yTR,xTL,yTL,xC,yC;
    double mainSlope;
    double sideSlope;
    double offsetB, offsetT, offsetL, offsetR;
    
    // Calculations
    void calculateBounds();
    int checkBottom(int xp, int yp);
    int checkTop(int xp, int yp);
    int checkLeft(int xp, int yp);
    int checkRight(int xp, int yp);
    
    // Bounding box corners
    enum CornerType{
        CBL = 0,
        CBR,
        CTR,
        CTL,
        CNONE
    };
    
    // Debug
    void print();
    
};


class BaseElement
{
public:
    enum Type{
        IMAGE_ELEMENT,
        TEXT_ELEMENT
    };
protected:
    // Coordinates lower left
    int x;
    int y;
    int z;
    
    // Bounding box dimensions
    int width;
    int height;
    BoundingBox *bounds;
    void updateBounds();
    
    // Properties
    BaseColor *color;
    float rotation;
    enum Type elementType;
    
    
    // Bounding box corners
    static const int numCorners = 4;
    enum CornerType{
        CBL = 0,
        CBR,
        CTR,
        CTL,
        CNONE
    };
    enum CornerType selectedCorner;
    
    // States
    bool selected;
    bool moveable;
    bool rotateable;
    bool lockRatio;
    
    // Manipulation Variables
    int startX;
    int startY;
    
    // Drawing helpers
    void drawCorners();
    virtual void drawElement();
    
    bool pointInBounds(int xCord, int yCord);
    
public:
    BaseElement();
    
    void setPosition(int xpos, int ypos);
    virtual void setWidth(int w);
    virtual void setHeight(int h);
    void setRotation(float r);
    void setColor(float r, float g, float b);
    void setColor4(float r, float g, float b, float a);
    void setLockRatio(bool lock);
    void deselect();
    
    int getWidth();
    int getHeight();
    float getRotation();
    bool getLockRatio();
    BaseColor* getColor();
    
    bool mouse(int button, int state, int xpops, int ypos);
    bool mouseMotion(int xpos, int ypos);
    
    void draw();
};


#endif