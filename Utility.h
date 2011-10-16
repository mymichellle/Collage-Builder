//
//  Utility.h
//  Collage
//
//  Created by Michelle Alexander on 10/02/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef Utility_h
#define Utility_h

#include <GL/glut.h>
#include <string>

using namespace std;

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

#define DISPLAY_FONT    GLUT_BITMAP_HELVETICA_18 //GLUT_BITMAP_9_BY_15;

static void displayString(std::string s)
{
    for (string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(DISPLAY_FONT, c);
    }
}

static int displayStringWidth(string s)
{
    // Calculate the width of the string to be displayed
    return glutBitmapLength	( DISPLAY_FONT, (const unsigned char *)s.c_str()); 	
}

static int displayStringHeight(string s)
{
    // Return the font height
    if(DISPLAY_FONT == GLUT_BITMAP_HELVETICA_18)
        return 15;
    else if(DISPLAY_FONT == GLUT_BITMAP_9_BY_15)
        return 15;
    else 
        return 1;
}

static int getMainTitleX(string s)
{
    return WINDOW_WIDTH/2 - displayStringWidth(s)/2;
}

static int getMainTitleY(string s)
{
    return WINDOW_HEIGHT - 50;
}

// Flip the y-axis
static void correctCoords(int &aX, int &aY)
{	
    aY=WINDOW_HEIGHT-aY;
}

/*	Upscaling the image uses simple bilinear interpolation	*/
static int up_scale_image
(
 const unsigned char* const orig,
 int width, int height, int channels,
 unsigned char* resampled,
 int resampled_width, int resampled_height
 )
{
	float dx, dy;
	int x, y, c;
    
    /* error(s) check	*/
    if ( 	(width < 1) || (height < 1) ||
        (resampled_width < 2) || (resampled_height < 2) ||
        (channels < 1) ||
        (NULL == orig) || (NULL == resampled) )
    {
        /*	signify badness	*/
        return 0;
    }
    /*
     for each given pixel in the new map, find the exact location
     from the original map which would contribute to this guy
     */
    dx = (width - 1.0f) / (resampled_width - 1.0f);
    dy = (height - 1.0f) / (resampled_height - 1.0f);
    for ( y = 0; y < resampled_height; ++y )
    {
    	/* find the base y index and fractional offset from that	*/
    	float sampley = y * dy;
    	int inty = (int)sampley;
    	/*	if( inty < 0 ) { inty = 0; } else	*/
		if( inty > height - 2 ) { inty = height - 2; }
		sampley -= inty;
        for ( x = 0; x < resampled_width; ++x )
        {
			float samplex = x * dx;
			int intx = (int)samplex;
			int base_index;
			/* find the base x index and fractional offset from that	*/
			/*	if( intx < 0 ) { intx = 0; } else	*/
			if( intx > width - 2 ) { intx = width - 2; }
			samplex -= intx;
			/*	base index into the original image	*/
			base_index = (inty * width + intx) * channels;
            for ( c = 0; c < channels; ++c )
            {
            	/*	do the sampling	*/
				float value = 0.5f;
				value += orig[base_index]
                *(1.0f-samplex)*(1.0f-sampley);
				value += orig[base_index+channels]
                *(samplex)*(1.0f-sampley);
				value += orig[base_index+width*channels]
                *(1.0f-samplex)*(sampley);
				value += orig[base_index+width*channels+channels]
                *(samplex)*(sampley);
				/*	move to the next channel	*/
				++base_index;
            	/*	save the new value	*/
            	resampled[y*resampled_width*channels+x*channels+c] =
                (unsigned char)(value);
            }
        }
    }
    /*	done	*/
    return 1;
}


// Define an object to define Color

class BaseColor{

private:
    struct Color{
        float red;
        float green;
        float blue;
        float alpha;
    };    
    
public:
    BaseColor(float r, float g, float b, float a)
    {
        color.red=r;color.green=g;color.blue=b;color.alpha=a;
    }
    Color color;
};

#endif