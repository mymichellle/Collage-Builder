//
//  TextPage.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/04/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include <GL/glut.h>
#include <GLUT/glut.h>
#include <sstream>

#include "TextPage.h"
#include "Utility.h"
#include "Collage.h"
#include "CreatePage.h"
#include "iostream"

using namespace std;

TextPage::TextPage()
{    
    // Set the title
    title = "Text";
    
    // Buttons
    btn_save = new BaseButton("SAVE", WINDOW_WIDTH-75, 50);
    btn_back = new BaseButton("BACK", 75,  50);
    
    // Sliders and Text boxes
    dialog_text = new BaseDialog("TEXT: ", "caption", WINDOW_WIDTH/2, WINDOW_HEIGHT-125, 200);
    // RED
    slider_red = new BaseSlider("RED:",WINDOW_WIDTH - 300, WINDOW_HEIGHT - 200, 0, 255);
    dialog_red = new BaseDialog("", "0", WINDOW_WIDTH-100, WINDOW_HEIGHT-200);
    // GREEN
    slider_green = new BaseSlider("GREEN:",WINDOW_WIDTH - 300, WINDOW_HEIGHT - 250, 0, 255);
    dialog_green = new BaseDialog("", "0", WINDOW_WIDTH-100, WINDOW_HEIGHT-250);
    // BLUE
    slider_blue = new BaseSlider("BLUE:",WINDOW_WIDTH - 300, WINDOW_HEIGHT - 300, 0, 255);
    dialog_blue = new BaseDialog("", "0", WINDOW_WIDTH-100, WINDOW_HEIGHT-300);
    // ALPHA
    slider_alpha = new BaseSlider("OPACITY:",WINDOW_WIDTH - 300, WINDOW_HEIGHT - 350, 0, 255);
    dialog_alpha = new BaseDialog("", "255", WINDOW_WIDTH-100, WINDOW_HEIGHT-350);
    
    dialog_size = new BaseDialog("SIZE: ", "1", 200, WINDOW_HEIGHT-200);
    dialog_rotation = new BaseDialog("ROTATION: ", "0",200, WINDOW_HEIGHT-250);
    
    // Initialize the element being defined
    element = new TextElement(dialog_text->getValue(),200,100);
    
    // Load default values
    setDefaultValues();
}

// Initialize input devices to the saved default settings
void TextPage::setDefaultValues()
{
    // Load the Collages default settings
    BaseColor *color = Collage::sharedCollage().getDefaultColor(BaseElement::TEXT_ELEMENT);
    
    dialog_red->setValue(color->color.red*255);
    dialog_green->setValue(color->color.green*255);
    dialog_blue->setValue(color->color.blue*255);
    dialog_alpha->setValue(color->color.alpha*255);
    dialog_size->setValue(Collage::sharedCollage().getDefaultSize(BaseElement::TEXT_ELEMENT));
    dialog_rotation->setValue(Collage::sharedCollage().getDefaultRotation(BaseElement::TEXT_ELEMENT));

    slider_red->setValue(color->color.red*255);
    slider_green->setValue(color->color.green*255);
    slider_blue->setValue(color->color.blue*255);
    slider_alpha->setValue(color->color.alpha*255);
}

// Pass the mouse actions to the buttons/dialogs/sliders
void TextPage::mouse(int button, int state, int x, int y)
{
    if(btn_save->mouse(button, state, x, y))
        onSavePress();
    if(btn_back->mouse(button, state, x, y))
        onBackPress();
    
    // Pass the mouse to the dialog boxes
    dialog_text->mouse(button, state, x, y);
    dialog_red->mouse(button, state, x, y);
    dialog_blue->mouse(button, state, x,y);
    dialog_green->mouse(button, state, x,y);
    dialog_alpha->mouse(button, state, x,y);
    dialog_size->mouse(button, state, x, y);
    dialog_rotation->mouse(button, state, x,y);
    
    // Pass the mouse to the sliders
    slider_red->mouse(button, state, x, y);
    slider_green->mouse(button, state, x, y);
    slider_blue->mouse(button, state, x, y);
    slider_alpha->mouse(button, state, x, y);
}

// pass mouse movements to the sliders updating text boxes with changes
void TextPage::mouseMotion(int x, int y)
{
    if(slider_red->mouseMotion(x,y))
         dialog_red->setValue(slider_red->getValue());
    if(slider_green->mouseMotion(x,y))
        dialog_green->setValue(slider_green->getValue());
    if(slider_blue->mouseMotion(x,y))
        dialog_blue->setValue(slider_blue->getValue());
    if(slider_alpha->mouseMotion(x,y))
        dialog_alpha->setValue(slider_alpha->getValue());
}

// Pass user keyboard input to the text boxes
void TextPage::keyboard(unsigned char key, int x, int y)
{
    dialog_text->keyboard(key, x, y);
    
    // Update the red slider if the text box changes
    if(dialog_red->keyboard(key, x, y))
        slider_red->setValue(atof(dialog_red->getValue().c_str()));
        
    // Update the green slider if the text box changes
    if(dialog_green->keyboard(key, x, y))
        slider_green->setValue(atof(dialog_green->getValue().c_str()));
    
    // Update the blue slider if the text box changes
    if(dialog_blue->keyboard(key, x, y))
        slider_blue->setValue(atof(dialog_blue->getValue().c_str()));
    
    // Update the alpha slider if the text box changes
    if(dialog_alpha->keyboard(key, x, y))
        slider_alpha->setValue(atof(dialog_alpha->getValue().c_str()));
    
    dialog_size->keyboard(key, x, y);
    dialog_rotation->keyboard(key, x, y);
}

// Save the element and return to the previous page
void TextPage::onSavePress()
{
    // set the values from the page
    defineTextElement();
    // Add to the collage and exit
    Collage::sharedCollage().addElement(element);
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

// Return to the previous page
void TextPage::onBackPress()
{
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

// Set the text element
void TextPage::defineTextElement()
{
    element->setText(dialog_text->getValue().c_str());
    element->setColor4(atof(dialog_red->getValue().c_str())/255, 
                      atof(dialog_green->getValue().c_str())/255,
                       atof(dialog_blue->getValue().c_str())/255,
                       atof(dialog_alpha->getValue().c_str())/255);
    element->setRotation(atof(dialog_rotation->getValue().c_str()));
    element->setFontSize(atof(dialog_size->getValue().c_str()));
}

// Display
void TextPage::display()
{
    // update the preview
    defineTextElement();
    
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
    glTranslatef(50, 200, 0);
    // scale text to .75
    Collage::sharedCollage().getFont()->draw("Preview:", .6,.6);
    glPopMatrix();
    
    // Draw buttons
    btn_save->draw();
    btn_back->draw();
    
    // Draw dialog boxes
    dialog_text->draw();
    dialog_red->draw();
    dialog_blue->draw();
    dialog_green->draw();
    dialog_alpha->draw();
    dialog_size->draw();
    dialog_rotation->draw();
    
    // Draw the sliders
    slider_red->draw();
    slider_green->draw();
    slider_blue->draw();
    slider_alpha->draw();
    
    // Draw a preview of the text object
    glPushMatrix();
    element->draw();
    glPopMatrix();
    
    glFlush();
    glPopMatrix();
}