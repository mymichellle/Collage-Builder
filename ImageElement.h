//
//  ImageElement.h
//  Collage
//
//  Created by Michelle Alexander on 10/12/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef ImageElement_h
#define ImageElement_h

#include "BaseElement.h"
#include "stb_image.h"
#include <string>

class ImageElement: public BaseElement
{
private:
    GLuint tex_2d;
    
    void drawElement();
    
public:
    ImageElement(std::string s, int w, int h);
    void setImage(std::string s);
};

#endif