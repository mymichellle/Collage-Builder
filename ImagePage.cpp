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
    fileName = "Basketball.png";
    
    // Initialize the element being defined
    element = new ImageElement(fileName,0,0);
    
    btn_save = new BaseButton("SAVE", WINDOW_WIDTH-75, WINDOW_HEIGHT - 50);
    btn_back = new BaseButton("BACK", 75, WINDOW_HEIGHT - 50);
    btn_load = new BaseButton("LOAD", WINDOW_WIDTH/2, WINDOW_HEIGHT - 150);
    
    dialog_file = new BaseDialog("FILE: ", fileName, WINDOW_WIDTH/2, WINDOW_HEIGHT-100, 200);
    dialog_red = new BaseDialog("RED: ", "0", WINDOW_WIDTH-150, WINDOW_HEIGHT-200);
    dialog_green = new BaseDialog("GREEN: ", "0", WINDOW_WIDTH-150, WINDOW_HEIGHT-250);
    dialog_blue = new BaseDialog("BLUE: ", "0", WINDOW_WIDTH-150, WINDOW_HEIGHT-300);
    dialog_alpha = new BaseDialog("OPACITY: ", "0", WINDOW_WIDTH-150, WINDOW_HEIGHT-350);
    dialog_width = new BaseDialog("WIDTH: ", "100", 200, WINDOW_HEIGHT-200);
    dialog_height = new BaseDialog("HEIGHT: ", "100", 200, WINDOW_HEIGHT-250);
    dialog_rotation = new BaseDialog("ROTATION: ", "0",200, WINDOW_HEIGHT-300);
    

    // Load the default values
    setDefaultValues();
}

void ImagePage::setDefaultValues()
{
    // Load the Collages default settings
    BaseColor *color = Collage::sharedCollage().getDefaultColor(BaseElement::IMAGE_ELEMENT);
    
    dialog_red->setValue(color->color.red*255);
    dialog_green->setValue(color->color.green*255);
    dialog_blue->setValue(color->color.blue*255);
    dialog_alpha->setValue(color->color.alpha*255);
    dialog_width->setValue(Collage::sharedCollage().getDefaultWidth(BaseElement::IMAGE_ELEMENT));
    dialog_height->setValue(Collage::sharedCollage().getDefaultHeight(BaseElement::IMAGE_ELEMENT));
    dialog_rotation->setValue(Collage::sharedCollage().getDefaultRotation(BaseElement::IMAGE_ELEMENT));
    
}

void ImagePage::mouse(int button, int state, int x, int y)
{
    if(btn_save->mouse(button, state, x, y))
        onSavePress();
    if(btn_back->mouse(button, state, x, y))
        onBackPress();
    if(btn_load->mouse(button, state, x, y))
        onLoadPress();
    
    // Pass the mouse movement to the dialog boxes
    dialog_file->mouse(button, state, x, y);
    dialog_red->mouse(button, state, x, y);
    dialog_blue->mouse(button, state, x,y);
    dialog_green->mouse(button, state, x,y);
    dialog_alpha->mouse(button, state, x,y);
    dialog_width->mouse(button, state, x, y);
    dialog_height->mouse(button, state, x, y);
    dialog_rotation->mouse(button, state, x,y);
}

void ImagePage::keyboard(unsigned char key, int x, int y)
{
    dialog_file->keyboard(key, x, y);
    dialog_red->keyboard(key, x, y);
    dialog_blue->keyboard(key, x, y);
    dialog_alpha->keyboard(key, x, y);
    dialog_green->keyboard(key, x, y);
    dialog_width->keyboard(key, x, y);
    dialog_height->keyboard(key, x, y);
    dialog_rotation->keyboard(key, x, y);
}

void ImagePage::onSavePress()
{
    // update the element add it and exit to main page
    defineImageElement();
    Collage::sharedCollage().addElement(element);
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void ImagePage::onBackPress()
{
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void ImagePage::onLoadPress()
{
    // Assign the value in the dialog box to the file name when laod is pressed
    fileName = dialog_file->getValue();
    element->setImage(fileName);
    
    // Set width and height dialog boxes to the widht/height of new image
    dialog_width->setValue(element->getWidth());
    dialog_height->setValue(element->getHeight());
    
    // redraw new image
    glutPostRedisplay();
}

void ImagePage::defineImageElement()
{
    element->setColor4(atof(dialog_red->getValue().c_str())/255, 
                      atof(dialog_green->getValue().c_str())/255,
                      atof(dialog_blue->getValue().c_str())/255,
                      atof(dialog_alpha->getValue().c_str())/255);
    element->setRotation(atof(dialog_rotation->getValue().c_str()));
    element->setWidth(atof(dialog_width->getValue().c_str()));
    element->setHeight(atof(dialog_height->getValue().c_str()));
}

void ImagePage::display()
{
    // update the element
    defineImageElement();
    
    glPushMatrix();
    
    // Draw the title
    glColor3f(0, 0, 0);
    glRasterPos3f(getMainTitleX(title), getMainTitleY(title), 0.5);    
    displayString(title);
    
    // Draw buttons
    btn_save->draw();
    btn_back->draw();
    btn_load->draw();
    
    // Draw dialog boxes
    dialog_file->draw();
    dialog_red->draw();
    dialog_blue->draw();
    dialog_alpha->draw();
    dialog_green->draw();
    dialog_width->draw();
    dialog_height->draw();
    dialog_rotation->draw();
    
    // Draw a preview/thumbnail of the element
    glPushMatrix();
    
    // translate to the middle of the screen
    glTranslatef(WINDOW_WIDTH/2, 10, 0);
    
    // scale the image to fit in a 100x100 spot maintaining aspect ratio
    double scalePrev = 100.0/element->getWidth();
    if(scalePrev < 100.0/element->getHeight())
    {
        scalePrev = 100.0/element->getHeight();
    }
    glScalef(scalePrev, scalePrev, 1);
    element->draw();
    
    glPopMatrix();
    
    glFlush();
    glPopMatrix();
}