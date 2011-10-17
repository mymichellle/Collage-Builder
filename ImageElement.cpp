//
//  ImageElement.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/12/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include "iostream"

#include "ImageElement.h"

using namespace std;

// Create a new ImageElement
ImageElement::ImageElement(string s, int xpos, int ypos)
{
    // Set Properties
    fileName = s;
    elementType = IMAGE_ELEMENT;
    x = xpos;
    y = ypos;
    z = 0;
    width = 256;
    height = 256;
    color = new BaseColor(1,1,1,1);
    rotation = 0;

    // initialize bounds and states load image
    initialize();
    setImage(fileName);
}

// Create a copy of an Image Element
ImageElement::ImageElement(ImageElement *copy)
{
    // Copy Properties
    fileName = copy->getFileName();
    elementType = IMAGE_ELEMENT;
    x = copy->getX() + 1; // offset the new copy
    y = copy->getY() + 1; // offset the new copy
    z = 0;
    width = copy->getWidth();
    height = copy->getHeight();
    BaseColor *cColor = copy->getColor();
    color = new BaseColor(cColor->color.red, cColor->color.green, cColor->color.blue, cColor->color.alpha);
    rotation = copy->getRotation();
    setImage(fileName);
    // Reset width and height because this value is changed to the images default
    width = copy->getWidth();
    height = copy->getHeight();
    
    // initialize bounds and states load image
    initialize();
}

void ImageElement::initialize()
{
    // Set the bounds
    bounds = new BoundingBox(x, y, width, height, rotation);
    
    // Movement properties
    selected = false;
    moveable = false;
    rotateable = false;
    startX = 0;
    startY = 0;
    
    // Initialize the corners
    selectedCorner = CNONE;
}

void ImageElement::setImage(string s)
{
    // Texture test
    int channels, force_channels = 0;
    int w = width, h = height;
    
    // Load the image
   	unsigned char *result = stbi_load(s.c_str(),&w, &h, &channels, force_channels );
    if( result == NULL )
    {
        cout<<"Image Load Faild: "<<stbi_failure_reason()<<endl;
	}
    
    // Get the new values for width and height
    width = w;
    height = h;
    
    // Need this for JPG images to be loaded
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    
    // make it a texture
    glGenTextures(1, &tex_2d); /* Note: sometimes glGenTextures fails (usually no OpenGL context)	*/
    glBindTexture( GL_TEXTURE_2D, tex_2d );
    
    // bilinear filter the original
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    // stop image at edges, no repeat
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
    
    glTexImage2D(GL_TEXTURE_2D, 0,
                 GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, result );
    
    // get rid of img data
	stbi_image_free(result);
}

void ImageElement::drawElement()
{
    // Make sure to use the image texture
    glBindTexture( GL_TEXTURE_2D, tex_2d );
    
    // Allow for transparent layers
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glEnable(GL_TEXTURE_2D);
    
    // Set the overlay color with a 50% opacity
    glColor4f(color->color.red,color->color.green,color->color.blue, color->color.alpha);
    
    glBegin( GL_QUADS );
    glTexCoord2f(0.0f,0.0f); glVertex2f(0.0f,height);
    glTexCoord2f(1.0f,0.0f); glVertex2f(width,height);
    glTexCoord2f(1.0f,1.0f); glVertex2f(width,0.0f);
    glTexCoord2f(0.0f,1.0f); glVertex2f(0.0f,0.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}
