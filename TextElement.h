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
    // Properties
    std::string text;
    void drawElement();
    double scaleX;
    double scaleY;
    
    // Private helpers
    void initialize();
    void setFontScale(double w, double h);
    void updateDimensions();
    void updateSize();
    void setWidth(int w);
    void setHeight(int h);
    
public:
    TextElement(std::string s, int centerX, int centerY);
    TextElement(TextElement *copy);
    
    // Getters and Setters
    void setText(std::string s);
    void setFontSize(double s);
    std::string getText(){return text;};
};

#endif