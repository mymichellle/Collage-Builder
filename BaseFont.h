//
//  BaseFont.h
//  Collage
//
//  Created by Michelle Alexander on 10/14/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef BaseFont_h
#define BaseFont_h

#include <string>
#include <GL/glut.h>

#define START_CHARACTERS 32
#define NUM_CHARACTERS 94
#define NUM_VARIABLES 5

class BaseFont
{    
public:
    BaseFont(int t);
    void draw(std::string);
    void draw(std::string, double scalex, double scaley);
    int calculateWidth(std::string, double scalex);
    int calculateHeight(std::string, double scaley);
    
private:
    int type;
    GLuint tex_2d;
    void readInMap(std::string n);
    float drawChar(char c, float xpos, double xscale, double yscale);
    
    struct FontChar
    {
        float x;
        float y;
        float width;
        float height;
        int ascii;
    };
    
    struct FontChar charMap[NUM_CHARACTERS];
    
};

#endif