//
//  BaseButton.h
//  Collage
//
//  Created by Michelle Alexander on 9/23/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef BaseButton_h
#define BaseButton_h

#define BUTTON_WIDTH 120
#define BUTTON_HEIGHT 50

#include <string>
#include "Utility.h"

class BaseButton
{
protected:
    int width;
    int height;
    int x,y;
    std::string label;
    BaseColor *fillColor;
    BaseColor *selectColor;
    BaseColor *fontColor;
    
    bool selected;
    
    bool pointInBounds(int xCord, int yCord);
    
public:
    BaseButton();
    BaseButton(std::string s, int xCord, int yCord);
    virtual bool mouse(int button, int state, int x, int y);
    void draw();
};

#endif