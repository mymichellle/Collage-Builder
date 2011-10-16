//
//  TextElement.h
//  Collage
//
//  Created by Michelle Alexander on 10/13/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef TextElement_h
#define TextElement_h

#include "BaseElement.h"
#include <string>

class TextElement: public BaseElement
{
private:
    std::string text;
    void drawElement();
    double scaleX;
    double scaleY;
    
    void setFontScale(double w, double h);
    void updateDimensions();
    void updateSize();
    void setWidth(int w);
    void setHeight(int h);
    
public:
    TextElement(std::string s, int centerX, int centerY);
    void setText(std::string s);
    void setFontSize(double s);
};

#endif