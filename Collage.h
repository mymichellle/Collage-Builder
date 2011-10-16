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
#include "BaseFont.h"
#include "Utility.h"
#include <iostream>

#define MAX_ELEMENTS    20
#define COLLAGE_MENU_HEIGHT     200
#define COLLAGE_DISPLAY_WIDTH   WINDOW_WIDTH
#define COLLAGE_DISPLAY_HEIGHT  WINDOW_HEIGHT - COLLAGE_MENU_HEIGHT

class Collage
{
private:    
    // Constructors
    Collage();
    // these are declard but not implemented
    Collage(Collage const&);
    void operator=(Collage const&);
    
    // Current page
    BasePage *displayPage;
    
    // Elements of the collage
    BaseElement* elements[MAX_ELEMENTS];
    int numElements;
    int getZValue(BaseElement *elem);
    
    // Fonts
    BaseFont *mainFont;
    
    // Collage States
    bool created;
    
    // Default Img Values
    float defaultImgRotation;
    BaseColor *defaultImgColor;
    double defaultImgSize;
    int defaultImgWidth;
    int defaultImgHeight;
    
    // Default Text Values
    float defaultTextRotation;
    BaseColor *defaultTextColor;
    double defaultTextSize;
    int defaultTextWidth;
    int defaultTextHeight;
    
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
    void setDefaultValues(enum BaseElement::Type t, int w, int h, double s, float r, BaseColor *c);
    bool addElement(BaseElement *elem);
    bool removeElement(BaseElement *elem);
    bool moveElementForward(BaseElement *elem);
    bool moveElementBackward(BaseElement *elem);
    void setupCollage();
    
    void drawElements();
    void drawElements(int offsetX, int offsetY);
    
    int getNumberOfElements();
    BaseElement *getElement(int index);
    BaseFont *getFont();
    float getDefaultRotation(enum BaseElement::Type t);
    BaseColor* getDefaultColor(enum BaseElement::Type t);
    double getDefaultSize(enum BaseElement::Type t);
    int getDefaultWidth(enum BaseElement::Type t);
    int getDefaultHeight(enum BaseElement::Type t);
};

#endif
