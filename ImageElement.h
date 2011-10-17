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
    // Texture
    GLuint tex_2d;
    std::string fileName;
    
    // Initialize states
    void initialize();
    
    // Display
    void drawElement();
    
public:
    ImageElement(std::string s, int w, int h);
    ImageElement(ImageElement *copy);
    
    // Getters and Setters
    void setImage(std::string s);
    std::string getFileName(){return fileName;};
};

#endif