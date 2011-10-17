//
//  SettingsPage.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/05/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include <GL/glut.h>
#include <GLUT/glut.h>

#include "SettingsPage.h"
#include "Utility.h"
#include "Collage.h"
#include "CreatePage.h"

using namespace std;

SettingsPage::SettingsPage()
{    
    title = "Settings";
    
    btn_save = new BaseButton("SAVE", WINDOW_WIDTH-75, 50);
    btn_back = new BaseButton("BACK", 75,  50);
    
    // Text Settings
    dialog_text_red = new BaseDialog("RED: ", "0", WINDOW_WIDTH-150, WINDOW_HEIGHT-150);
    dialog_text_green = new BaseDialog("GREEN: ", "0", WINDOW_WIDTH-150, WINDOW_HEIGHT-200);
    dialog_text_blue = new BaseDialog("BLUE: ", "0", WINDOW_WIDTH-150, WINDOW_HEIGHT-250);
    dialog_text_size = new BaseDialog("SIZE: ", "1", 200, WINDOW_HEIGHT-200);
    dialog_text_rotation = new BaseDialog("ROTATION: ", "0",200, WINDOW_HEIGHT-250);
    
    // Image Settings
    dialog_img_red = new BaseDialog("RED: ", "0", WINDOW_WIDTH-150, WINDOW_HEIGHT/2 - 50);
    dialog_img_green = new BaseDialog("GREEN: ", "0", WINDOW_WIDTH-150, WINDOW_HEIGHT/2-100);
    dialog_img_blue = new BaseDialog("BLUE: ", "0", WINDOW_WIDTH-150, WINDOW_HEIGHT/2-150);
    dialog_img_width = new BaseDialog("WIDTH: ", "100", 200, WINDOW_HEIGHT/2-50);
    dialog_img_height = new BaseDialog("HEIGHT: ", "100", 200, WINDOW_HEIGHT/2-100);
    dialog_img_rotation = new BaseDialog("ROTATION: ", "0",200, WINDOW_HEIGHT/2-150);
    
    // Load the default values
    setDefaultValues();
}

void SettingsPage::setDefaultValues()
{
    // Load the Collages default settings
    BaseColor *color = Collage::sharedCollage().getDefaultColor(BaseElement::TEXT_ELEMENT);
    
    dialog_text_red->setValue(color->color.red*255);
    dialog_text_green->setValue(color->color.green*255);
    dialog_text_blue->setValue(color->color.blue*255);
    dialog_text_size->setValue(Collage::sharedCollage().getDefaultSize(BaseElement::TEXT_ELEMENT));
    dialog_text_rotation->setValue(Collage::sharedCollage().getDefaultRotation(BaseElement::TEXT_ELEMENT));
    
    // Image Defaults
    color = Collage::sharedCollage().getDefaultColor(BaseElement::IMAGE_ELEMENT);
    
    dialog_img_red->setValue(color->color.red*255);
    dialog_img_green->setValue(color->color.green*255);
    dialog_img_blue->setValue(color->color.blue*255);
    dialog_img_width->setValue(Collage::sharedCollage().getDefaultWidth(BaseElement::IMAGE_ELEMENT));
    dialog_img_height->setValue(Collage::sharedCollage().getDefaultHeight(BaseElement::IMAGE_ELEMENT));
    dialog_img_rotation->setValue(Collage::sharedCollage().getDefaultRotation(BaseElement::IMAGE_ELEMENT));
}

void SettingsPage::mouse(int button, int state, int x, int y)
{
    
    if(btn_back->mouse(button, state, x, y))
        onBackPress();
    if(btn_save->mouse(button, state, x, y))
        onSavePress();
    
    // Pass the mouse movement to the input items
    dialog_text_red->mouse(button, state, x, y);
    dialog_text_green->mouse(button, state, x, y);
    dialog_text_blue->mouse(button, state, x, y);
    dialog_text_rotation->mouse(button, state, x, y);
    dialog_text_size->mouse(button, state, x, y);
    dialog_img_red->mouse(button, state, x, y);
    dialog_img_green->mouse(button, state, x, y);
    dialog_img_blue->mouse(button, state, x, y);
    dialog_img_rotation->mouse(button, state, x, y);
    dialog_img_width->mouse(button, state, x, y);
    dialog_img_height->mouse(button, state, x, y);
}

void SettingsPage::keyboard(unsigned char key, int x, int y)
{
    // Pass the keyboard events to the input items
    dialog_text_red->keyboard(key, x, y);
    dialog_text_green->keyboard(key, x, y);
    dialog_text_blue->keyboard(key, x, y);
    dialog_text_rotation->keyboard(key, x, y);
    dialog_text_size->keyboard(key, x, y);
    dialog_img_red->keyboard(key, x, y);
    dialog_img_green->keyboard(key, x, y);
    dialog_img_blue->keyboard(key, x, y);
    dialog_img_rotation->keyboard(key, x, y);
    dialog_img_width->keyboard(key, x, y);
    dialog_img_height->keyboard(key, x, y);
}

void SettingsPage::onBackPress()
{
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void SettingsPage::onSavePress()
{
    float r = atof(dialog_img_rotation->getValue().c_str());
    float red = atof(dialog_img_red->getValue().c_str())/255;
    float green = atof(dialog_img_green->getValue().c_str())/255;
    float blue = atof(dialog_img_blue->getValue().c_str())/255;
    BaseColor *c =  new BaseColor(red, green, blue, 1);
    double s = 1;
    int w = atoi(dialog_img_width->getValue().c_str());
    int h = atoi(dialog_img_height->getValue().c_str());
    
    Collage::sharedCollage().setDefaultValues(BaseElement::IMAGE_ELEMENT, w, h, s, r, c);
    
    r = atof(dialog_text_rotation->getValue().c_str());
    red = atof(dialog_text_red->getValue().c_str())/255;
    green = atof(dialog_text_green->getValue().c_str())/255;
    blue = atof(dialog_text_blue->getValue().c_str())/255;
    c = new BaseColor(red, green, blue, 1);
    s = atof(dialog_text_size->getValue().c_str());
    w = h = 1;
    
    Collage::sharedCollage().setDefaultValues(BaseElement::TEXT_ELEMENT, w, h, s, r, c);
    
    // Go back to main page
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void SettingsPage::display()
{
    glPushMatrix();
    
    // Draw the title
    glColor3f(0, 0, .4);
    glPushMatrix();
    int w = Collage::sharedCollage().getFont()->calculateWidth(title,1);
    glTranslatef((WINDOW_WIDTH-w)/2, WINDOW_HEIGHT - 100, 0);
    Collage::sharedCollage().getFont()->draw(title);
    glPopMatrix();
    
    // Draw the header
    glColor3f(0, 0, .4);
    glPushMatrix();
        // translate into place
        glTranslatef(10, WINDOW_HEIGHT - 150, 0);
        // scale text to .6
        Collage::sharedCollage().getFont()->draw("Text Defaults:", .6,.6);
    glPopMatrix();
    
    // Draw the header
    glColor3f(0, 0, .4);
    glPushMatrix();
        // translate into place
        glTranslatef(10, WINDOW_HEIGHT/2 - 25, 0);  
        // scale text to .6  
        Collage::sharedCollage().getFont()->draw("Image Defaults:", .6,.6);
    glPopMatrix();
    
    // Draw buttons
    btn_back->draw();
    btn_save->draw();
    
    // Draw input items
    dialog_text_red->draw();
    dialog_text_green->draw();
    dialog_text_blue->draw();
    dialog_text_rotation->draw();
    dialog_text_size->draw();
    dialog_img_red->draw();
    dialog_img_green->draw();
    dialog_img_blue->draw();
    dialog_img_rotation->draw();
    dialog_img_width->draw();
    dialog_img_height->draw();
    
    glFlush();
    glPopMatrix();
}