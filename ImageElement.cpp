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

ImageElement::ImageElement(string s, int xpos, int ypos)
{
    x = xpos;
    y = ypos;
    z = 0;
    width = 256;
    height = 256;
    color = new BaseColor(0,0,0,0);
    rotation = 0;
    bounds = new BoundingBox(x, y, width, height, rotation);
    
    // Movement properties
    selected = false;
    moveable = false;
    rotateable = false;
    startX = 0;
    startY = 0;
    
    // Initialize the corners
    selectedCorner = CNONE;

    setImage(s);
        
}

void ImageElement::setImage(string s)
{
    // Texture test
    int channels, force_channels = 0;
   	unsigned char *result = stbi_load(s.c_str(),
                                      &width, &height, &channels, force_channels );
    if( result == NULL )
	{
        cout<<"TEST FAIL "<<stbi_failure_reason()<<endl;
	} else
        
        // make it a texture
        glGenTextures(1, &tex_2d); /* Note: sometimes glGenTextures fails (usually no OpenGL context)	*/
    glBindTexture( GL_TEXTURE_2D, tex_2d );
    
    // bilinear filter the original
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
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
    
    glColor3f(1,1,1);
    
    glBegin( GL_QUADS );
    glTexCoord2f(0.0f,0.0f); glVertex2f(0.0f,height);
    glTexCoord2f(1.0f,0.0f); glVertex2f(width,height);
    glTexCoord2f(1.0f,1.0f); glVertex2f(width,0.0f);
    glTexCoord2f(0.0f,1.0f); glVertex2f(0.0f,0.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}
