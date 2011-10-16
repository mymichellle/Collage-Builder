//
//  SettingsPage.h
//  Collage
//
//  Created by Michelle Alexander on 10/05/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef SettingsPage_h
#define SettingsPage_h

#include "BasePage.h"
#include "BaseButton.h"
#include "BaseDialog.h"

class SettingsPage: public BasePage
{
private:
    BaseButton *btn_back;
    BaseButton *btn_save;
    
    // Text Settings
    BaseDialog *dialog_text_red;
    BaseDialog *dialog_text_green;
    BaseDialog *dialog_text_blue;
    BaseDialog *dialog_text_rotation;
    BaseDialog *dialog_text_size;
    
    // Image Settings
    BaseDialog *dialog_img_red;
    BaseDialog *dialog_img_green;
    BaseDialog *dialog_img_blue;
    BaseDialog *dialog_img_rotation;
    BaseDialog *dialog_img_width;
    BaseDialog *dialog_img_height;
    
    void onBackPress();
    void onSavePress();
    void saveSettings();
    
    void setDefaultValues();
    
public:
    SettingsPage();
    void mouse(int button, int state, int x, int y);
    void keyboard(unsigned char key, int x, int y);
    void display();
    
};

#endif