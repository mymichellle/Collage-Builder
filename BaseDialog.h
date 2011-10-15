//
//  BaseDialog.h
//  Collage
//
//  Created by Michelle Alexander on 10/13/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef BaseDialog_h
#define BaseDialog_h

#include <string>

class BaseDialog
{
protected:
    void initialize(std::string t, std::string d, int centerX, int centerY, int w);
    
    int width;
    int height;
    int x;
    int y;
    int textX;
    int textY;
    std::string val;
    int valLength;
    std::string label;
    
    bool pointInBounds(int xCord, int yCord);
    bool active;
    bool pressed;
    
public:
    BaseDialog(std::string t, std::string d, int centerX, int centerY);
    BaseDialog(std::string t, std::string d, int centerX, int centerY, int w);
    bool mouse(int button, int state, int x, int y);
    bool mouseMotion(int x, int y);
    void keyboard(unsigned char key, int x, int y);
    void draw();
    std::string getValue();
    
};

#endif