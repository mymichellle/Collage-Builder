//
//  Utility.h
//  Collage
//
//  Created by Michelle Alexander on 10/02/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef Utility_h
#define Utility_h

#include <GL/glut.h>
#include <string>

using namespace std;

#define WINDOW_WIDTH    600
#define WINDOW_HEIGHT   400
#define MAX_ELEMENTS    20

#define DISPLAY_FONT    GLUT_BITMAP_HELVETICA_18 //GLUT_BITMAP_9_BY_15;

static void displayString(std::string s)
{
    for (string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(DISPLAY_FONT, c);
    }
}

static int displayStringWidth(string s)
{
    // Calculate the width of the string to be displayed
    return glutBitmapLength	( DISPLAY_FONT, (const unsigned char *)s.c_str()); 	
}

static int displayStringHeight(string s)
{
    // Return the font height
    if(DISPLAY_FONT == GLUT_BITMAP_HELVETICA_18)
        return 15;
    else if(DISPLAY_FONT == GLUT_BITMAP_9_BY_15)
        return 15;
    else 
        return 1;
}

static int getMainTitleX(string s)
{
    return WINDOW_WIDTH/2 - displayStringWidth(s)/2;
}

static int getMainTitleY(string s)
{
    return WINDOW_HEIGHT - 50;
}

// Flip the y-axis
static void correctCoords(int &aX, int &aY)
{	
    aY=WINDOW_HEIGHT-aY;
}

// Define an object to define Color

class BaseColor{

private:
    struct Color{
        float red;
        float green;
        float blue;
        float alpha;
    };    
    
public:
    BaseColor(float r, float g, float b, float a)
    {
        color.red=r;color.green=g;color.blue=b;color.alpha=a;
    }
    Color color;
};

#endif