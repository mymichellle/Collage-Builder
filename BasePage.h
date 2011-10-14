//
//  BasePage.h
//  Collage
//
//  Created by Michelle Alexander on 9/23/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef BasePage_h
#define BasePage_h

#include <string>

class BasePage
{
protected:
    int width;
    int height;
    std::string title;
    
public:
    BasePage();
    virtual void mouse(int button, int state, int x, int y);
    virtual void mouseMotion(int x, int y);
    virtual void keyboard(unsigned char key, int x, int y);
    virtual void enterPage();
    virtual void display();
    virtual void cleanUp();
};

#endif