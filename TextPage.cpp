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

using namespace std;

TextPage::TextPage()
{    
    title = "Text";
    
    btn_save = new BaseButton("SAVE", WINDOW_WIDTH-75, WINDOW_HEIGHT - 50);
    btn_back = new BaseButton("BACK", 75, WINDOW_HEIGHT - 50);
    
    dialog_text = new BaseDialog("TEXT: ", "caption", WINDOW_WIDTH/2, WINDOW_HEIGHT-100);
    dialog_red = new BaseDialog("RED: ", "0", WINDOW_WIDTH-150, WINDOW_HEIGHT-150);
    dialog_green = new BaseDialog("GREEN: ", "0", WINDOW_WIDTH-150, WINDOW_HEIGHT-200);
    dialog_blue = new BaseDialog("BLUE: ", "0", WINDOW_WIDTH-150, WINDOW_HEIGHT-250);
    dialog_size = new BaseDialog("SIZE: ", "1", 200, WINDOW_HEIGHT-200);
    dialog_rotation = new BaseDialog("ROTATION: ", "0",200, WINDOW_HEIGHT-250);
    
    // Initialize the element being defined
    element = new TextElement(dialog_text->getValue(),150,10);
}

void TextPage::mouse(int button, int state, int x, int y)
{
    if(btn_save->mouse(button, state, x, y))
        onSavePress();
    if(btn_back->mouse(button, state, x, y))
        onBackPress();
    
    // Pass the mouse movement to the dialog boxes
    dialog_text->mouse(button, state, x, y);
    dialog_red->mouse(button, state, x, y);
    dialog_blue->mouse(button, state, x,y);
    dialog_green->mouse(button, state, x,y);
    dialog_size->mouse(button, state, x, y);
    dialog_rotation->mouse(button, state, x,y);
}

void TextPage::mouseMotion(int x, int y)
{
    // pass mouse movements to the dialog box
    dialog_text->mouseMotion(x,y);
}

void TextPage::keyboard(unsigned char key, int x, int y)
{
    dialog_text->keyboard(key, x, y);
    dialog_red->keyboard(key, x, y);
    dialog_blue->keyboard(key, x, y);
    dialog_green->keyboard(key, x, y);
    dialog_size->keyboard(key, x, y);
    dialog_rotation->keyboard(key, x, y);
}

void TextPage::onSavePress()
{
    defineTextElement();
    Collage::sharedCollage().addElement(element);
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void TextPage::onBackPress()
{
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void TextPage::defineTextElement()
{
    element->setText(dialog_text->getValue().c_str());
    element->setColor(atof(dialog_red->getValue().c_str())/255, 
                      atof(dialog_green->getValue().c_str())/255,
                      atof(dialog_blue->getValue().c_str())/255);
    element->setRotation(atof(dialog_rotation->getValue().c_str()));
    element->setFontSize(atof(dialog_size->getValue().c_str()));
}

void TextPage::display()
{
    // update the preview
    defineTextElement();
    
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
    dialog_red->draw();
    dialog_blue->draw();
    dialog_green->draw();
    dialog_size->draw();
    dialog_rotation->draw();
    
    // Draw a preview of the text object
    glPushMatrix();
    element->draw();
    glPopMatrix();
    
    glFlush();
    glPopMatrix();
}