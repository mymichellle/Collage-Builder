//
//  ImagePage.h
//  Collage
//
//  Created by Michelle Alexander on 10/04/11.
//  Copyright 2011 ??? . All rights reserved.
//
//  Defines the Image Page where the user creates and image element

#ifndef ImagePage_h
#define ImagePage_h

#include "BasePage.h"
#include "BaseButton.h"
#include "ToggleButton.h"
#include "BaseDialog.h"
#include "BaseSlider.h"
#include "ImageElement.h"
#include <string>

class ImagePage: public BasePage
{
    // Element
    ImageElement *element;
    std::string fileName;
    
    // Buttons
    BaseButton *btn_save;
    BaseButton *btn_back;
    BaseButton *btn_load;
    ToggleButton *btn_lock;
    
    // Text boxes
    BaseDialog *dialog_file;
    BaseDialog *dialog_red;
    BaseDialog *dialog_green;
    BaseDialog *dialog_blue;
    BaseDialog *dialog_alpha;
    BaseDialog *dialog_rotation;
    BaseDialog *dialog_width;
    BaseDialog *dialog_height;
    
    // Sliders
    BaseSlider *slider_red;
    BaseSlider *slider_green;
    BaseSlider *slider_blue;
    BaseSlider *slider_alpha;
    
    // Button call backs
    void onSavePress();
    void onBackPress();
    void onLoadPress();
    void onLockPress();
    
    // Private Helper functions
    void defineImageElement();
    void setDefaultValues();
  
public:
    ImagePage();
    
    // User input
    void mouse(int button, int state, int x, int y);
    void mouseMotion(int x, int y);
    void keyboard(unsigned char key, int x, int y);
    
    // Display
    void display();
    
};

#endif