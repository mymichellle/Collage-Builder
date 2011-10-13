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
    void calculateResize(int xp, int yp, int corner, double *ans);
    double calculateRotate(int xp1, int yp1, int xp2, int yp2);
    
    // Debug
    void draw();
    
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
    //CornerBox *corners[numCorners];
    //void setCorners();
    //enum CornerType selectedCorner;
    
    // Debug
    void print();
    
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
    void setWidth(int w, bool locked);
    void setHeight(int h, bool locked);
    void setRotation(float r);
    void setColor(float r, float g, float b);
    bool mouse(int button, int state, int xpops, int ypos);
    bool mouseMotion(int xpos, int ypos);
    void draw();
};


#endif