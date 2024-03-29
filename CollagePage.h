//
//  CollagePage.h
//  Collage
//
//  Created by Michelle Alexander on 10/05/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef CollagePage_h
#define CollagePage_h

#include "BasePage.h"
#include "BaseButton.h"
#include "BaseSlider.h"
#include "ToggleButton.h"
#include "BaseDialog.h"
#include "BaseElement.h"

class CollagePage: public BasePage
{
    // Buttons
    BaseButton *btn_back;
    BaseButton *btn_delete;
    BaseButton *btn_forward;
    BaseButton *btn_backward;
    ToggleButton *btn_lock;
    BaseButton *btn_copy;
    
    // Text Boxes
    BaseDialog *dialog_red;
    BaseDialog *dialog_green;
    BaseDialog *dialog_blue;
    BaseDialog *dialog_rotation;
    BaseDialog *dialog_alpha;
    
    
    // Sliders
    BaseSlider *slider_red;
    BaseSlider *slider_green;
    BaseSlider *slider_blue;
    BaseSlider *slider_alpha;
    
    // Button callbacks
    void onBackPress();
    void onDeletePress();
    void onCopyPress();
    void onForwardPress();
    void onBackwardPress();
    void onLockPress();
    
    // Private Helper functions
    BaseElement *activeElement;
    void updateActiveElement();
    void updateControlPanel();
    
public:
    CollagePage();
    void mouse(int button, int state, int x, int y);
    void mouseMotion(int x, int y);
    void keyboard(unsigned char key, int x, int y);
    void display();
    
};

#endif