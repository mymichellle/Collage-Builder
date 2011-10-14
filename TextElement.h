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
public:
    TextElement(std::string s, int centerX, int centerY);
};

#endif