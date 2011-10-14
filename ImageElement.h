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
//#include "Simple OpenGL Image Library/src/SOIL.h"
#include "stb_image.h"

class ImageElement: public BaseElement
{
private:
    GLuint tex_2d;
    
    unsigned char* img;
    void drawElement();
    
public:
    ImageElement();
};

#endif