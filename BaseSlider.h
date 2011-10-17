//
//  BaseSlider.h
//  Collage
//
//  Created by Michelle Alexander on 10/17/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef BaseSlider_h
#define BaseSlider_h

#include <string>
#include "Utility.h"

#define SLIDER_WIDTH 200
#define SLIDER_HEIGHT 20
#define SLIDER_BOX 10

class BaseSlider
{
private:
    // Properties
    std::string label;
    int x;
    int y;
    int width;
    int height;
    int min;
    int max;
    double value;
    double position;
    
    // Private Helper Functions
    double valueToPosition();
    double positionToValue();
    bool pointInBounds(int xp, int yp);
    
    // States
    bool moveable;
    
public:
    BaseSlider(std::string l, int xCord, int yCord, int minVal, int maxVal);
    
    // Getters and Setters
    double getValue(){return value;};
    double setValue(double v);
    
    // User interactions
    bool mouse(int button, int state, int x, int y);
    bool mouseMotion(int xpos, int ypos);
    
    // Display
    void draw();
};

#endif