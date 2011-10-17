//
//  TextPage.h
//  Collage
//
//  Created by Michelle Alexander on 10/04/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef TextPage_h
#define TextPage_h

#include "BasePage.h"
#include "BaseButton.h"
#include "BaseDialog.h"
#include "TextElement.h"
#include "BaseSlider.h"

class TextPage: public BasePage
{
private:
    // Element being created
    TextElement *element;
    
    // Buttons
    BaseButton *btn_save;
    BaseButton *btn_back;
    
    // Text Entry Boxes
    BaseDialog *dialog_text;
    BaseDialog *dialog_red;
    BaseDialog *dialog_green;
    BaseDialog *dialog_blue;
    BaseDialog *dialog_alpha;
    BaseDialog *dialog_rotation;
    BaseDialog *dialog_size;
    
    // Sliders
    BaseSlider *slider_red;
    BaseSlider *slider_green;
    BaseSlider *slider_blue;
    BaseSlider *slider_alpha;
    
    // Button Responders
    void onSavePress();
    void onBackPress();
    
    // Helper Function
    void defineTextElement();
    void setDefaultValues();
    
public:
    TextPage();
    
    // User Interaction
    void mouse(int button, int state, int x, int y);
    void mouseMotion(int x, int y);
    void keyboard(unsigned char key, int x, int y);
    
    // Display
    void display();
};

#endif