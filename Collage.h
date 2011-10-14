//
//  Collage.h
//  Collage
//
//  Created by Michelle Alexander on 10/1/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef Collage_h
#define Collage_h

#include "BasePage.h"
#include "BaseElement.h"
#include "Utility.h"
#include <iostream>

class Collage
{
private:    
    // Constructors
    Collage();
    // these are declard but not implemented
    Collage(Collage const&);
    void operator=(Collage const&);
    
    BasePage *displayPage;
    BaseElement* elements[MAX_ELEMENTS];
    int numElements;
    
public:
    // Singleton Collage
    static Collage& sharedCollage()
    {
        static Collage instance;
        return instance;
    }
    
    void mouse(int button, int state, int x, int y);
    void mouseMotion(int x, int y);
    void keyboard(unsigned char key, int x, int y);
    void display();
    void reshape(int w, int h);
    
    void setDisplayPage(BasePage *newPage);
    bool addElement(BaseElement *elem);
    void drawElements();
    
    int getNumberOfElements();
    BaseElement *getElement(int index);
    
};

#endif
