//
//  TextPage.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/04/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include <GL/glut.h>
#include <GLUT/glut.h>

#include "TextPage.h"
#include "Utility.h"
#include "Collage.h"
#include "CreatePage.h"
#include "iostream"
#include "TextElement.h"

using namespace std;

TextPage::TextPage()
{    
    title = "Text";
    
    btn_save = new BaseButton("SAVE", WINDOW_WIDTH-100, 70);
    btn_back = new BaseButton("BACK", 100, 70);
    dialog_text = new BaseDialog("LABEL", "DEFAULT", WINDOW_WIDTH/2, 150);
}

void TextPage::mouse(int button, int state, int x, int y)
{
    if(btn_save->mouse(button, state, x, y))
        onSavePress();
    if(btn_back->mouse(button, state, x, y))
        onBackPress();
    
    // Pass the mouse movement to the dialog boxes
    dialog_text->mouse(button, state, x, y);
}

void TextPage::mouseMotion(int x, int y)
{
    // pass mouse movements to the dialog box
    dialog_text->mouseMotion(x,y);
}

void TextPage::keyboard(unsigned char key, int x, int y)
{
    dialog_text->keyboard(key, x, y);
}

void TextPage::onSavePress()
{
    Collage::sharedCollage().addElement(new TextElement(dialog_text->getValue(), 200, 100));
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void TextPage::onBackPress()
{
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void TextPage::display()
{
    glPushMatrix();
    
    // Draw the title
    glColor3f(0, 0, 0);
    glRasterPos3f(getMainTitleX(title), getMainTitleY(title), 0.5);    
    displayString(title);
    
    // Draw buttons
    btn_save->draw();
    btn_back->draw();
    
    // Draw dialog boxes
    dialog_text->draw();
    
    glFlush();
    glPopMatrix();
}