//
//  BaseFont.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/14/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include "BaseFont.h"
#include "stb_image.h"
#include <iostream>
#include <fstream>

using namespace std;

BaseFont::BaseFont(int t)
{
    // Load the png font as a texture
    int channels, 
        force_channels = 0, 
        width, 
        height;
   	unsigned char *result = stbi_load("font.png",
                                      &width, &height, &channels, force_channels );
    if( result == NULL )
	{
        cout<<"Font was not loaded! "<<stbi_failure_reason()<<endl;
	}
    
    // Create a texture from the PNG font
    glGenTextures(1, &tex_2d); /* Note: sometimes glGenTextures fails (usually no OpenGL context)	*/
    glBindTexture( GL_TEXTURE_2D, tex_2d );
    
    // bilinear filter the original
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    // clamp to edges, no repeat
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
    
    glTexImage2D(GL_TEXTURE_2D, 0,
                 GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, result );
    
    
    // release the image data
	stbi_image_free(result);
    
    // read int the character map
    readInMap("font.dat");
}

int BaseFont::calculateWidth(string s, double scalex)
{
    int calcW = 0;
    for(int i = 0; i < s.length(); i++)
    {
        // Find the char map offset by the start character
        calcW += charMap[s[i]-START_CHARACTERS].width*scalex;
    }
    return calcW;
}

int BaseFont::calculateHeight(string s, double scaley)
{
    return charMap[0].height * scaley;
}

float BaseFont::drawChar(char c, float xpos, double scalex, double scaley)
{
    // Calculate the array index
    int map = c-START_CHARACTERS;

    // Calculate the positions of the texture
    float x = charMap[map].x/512.0f,
    y =charMap[map].y/512.0f,
    x2 = (charMap[map].x + charMap[map].width)/512.0f,
    y2 = (charMap[map].y + charMap[map].height)/512.0f,
    w = charMap[map].width*scalex,
    h = charMap[map].height*scaley;
    
    // Draw the character
    glBegin( GL_QUADS );
    glTexCoord2f(x ,y); glVertex2f(xpos,h);
    glTexCoord2f(x2,y); glVertex2f(xpos + w,h);
    glTexCoord2f(x2,y2); glVertex2f(xpos + w,0.0f);
    glTexCoord2f(x,y2); glVertex2f(xpos,0.0f);
    glEnd();
    
    // return the next xpos
    return xpos + w;
}

void BaseFont::draw(std::string s)
{
    // Draw with default scale of 1
    draw(s, 1, 1);
}

void BaseFont::draw(std::string s, double scalex, double scaley)
{
    // Make sure to use the font texture
    glBindTexture( GL_TEXTURE_2D, tex_2d );
    
    // Allow for transparent layers
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glEnable(GL_TEXTURE_2D);
    float xpos = 0;
    
    for(int i = 0; i < s.length(); i++)
    {
        xpos = drawChar(s[i], xpos, scalex, scaley);
    }
    
    glDisable(GL_TEXTURE_2D);
}

void BaseFont::readInMap(string n)
{
    ifstream myReadFile;
    myReadFile.open("font.dat");
    string output;
    int index = 0;
    
    // Read in character map from file
    if(myReadFile.is_open())
    {
        while(!myReadFile.eof())
        {
            myReadFile >> output;
            // each line has {###,###,###,###,###}
            for(int i = 0; i < NUM_VARIABLES && output.length() >17 ; i++)
            {
                switch(i)
                {
                    case 0:
                        charMap[index].x = atof(output.substr(1,3).c_str());
                        break;
                    case 1:
                        charMap[index].y = atof(output.substr(5,3).c_str());
                        break;
                    case 2:
                        charMap[index].width = atof(output.substr(9,3).c_str());
                         break;
                    case 3:
                        charMap[index].height = atof(output.substr(13,3).c_str());
                        break;
                    case 4:
                        charMap[index].ascii = atoi(output.substr(17,3).c_str());
                         break;
                    default:
                        break;
                }
                
            }
            index++;
            
            output.clear();
        }
    }
    myReadFile.close();
    
}