//
//  CreatePage.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/04/11.
//  Copyright 2011 ??? . All rights reserved.
//


#include <GL/glut.h>
#include <GLUT/glut.h>

#include "ImagePage.h"
#include "Utility.h"
#include "Collage.h"
#include "CreatePage.h"

using namespace std;

ImagePage::ImagePage()
{    
    title = "Image";
    
    btn_save = new BaseButton("SAVE", WINDOW_WIDTH-100, 70);    
    btn_back = new BaseButton("BACK", 100, 70);
}

void ImagePage::mouse(int button, int state, int x, int y)
{
    if(btn_save->mouse(button, state, x, y))
        onSavePress();
    if(btn_back->mouse(button, state, x, y))
        onBackPress();
}

void ImagePage::onSavePress()
{
    Collage::sharedCollage().addElement(new BaseElement());
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void ImagePage::onBackPress()
{
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void ImagePage::display()
{
    glPushMatrix();
    
    // Draw the title
    glColor3f(0, 0, 0);
    glRasterPos3f(getMainTitleX(title), getMainTitleY(title), 0.5);    
    displayString(title);
    
    // Draw buttons
    btn_save->draw();
    btn_back->draw();
    
    glFlush();
    glPopMatrix();
}