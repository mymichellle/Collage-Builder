//
//  ImageElement.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/12/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include "iostream"

#include "ImageElement.h"

ImageElement::ImageElement()
{
    x = 0;
    y = 0;
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

    
    
    // Texture test
    int channels, force_channels = 0;
   	unsigned char *result = stbi_load( /*"img_cheryl.jpg"*/ "img_test.png",
                                      &width, &height, &channels, force_channels );
    if( result == NULL )
	{
        cout<<"TEST FAIL "<<stbi_failure_reason()<<endl;
	} else
	{
		cout<<"TEST Image loaded"<<endl;
        cout<<"Width , height, channels "<< width << " " << height << " " << channels<<endl;
	}
    
    // make it a texture
    img = (unsigned char*)malloc( width*height*channels );
    memcpy(img, result, width*height*channels);
    
    glGenTextures(1, &tex_2d); /* Note: sometimes glGenTextures fails (usually no OpenGL context)	*/
    glBindTexture( GL_TEXTURE_2D, tex_2d );
    
    
    //setup
    //glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    // when texture area is small, bilinear filter the original
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    // when texture area is large, bilinear filter the original
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
    //endsetup
    
    
    glTexImage2D(GL_TEXTURE_2D, 0,
                 GL_RGBA, width, height, 0,
                 GL_BGRA, GL_UNSIGNED_BYTE, img );
    
    
    // get rid of img data
	stbi_image_free(result);
    
}

void ImageElement::drawElement()
{
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
