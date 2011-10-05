//
//  CreatePage.h
//  Collage
//
//  Created by Michelle Alexander on 10/04/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef CreatePage_h
#define CreatePage_h

#include "BasePage.h"
#include "BaseButton.h"

class CreatePage: public BasePage
{
    BaseButton *btn_text;
    BaseButton *btn_image;
    BaseButton *btn_settings;
    BaseButton *btn_collage;
    BaseButton *btn_back;
    
    void onTextPress();
    void onImagePress();
    void onSettingsPress();
    void onCollagePress();
    void onBackPress();
    
public:
    CreatePage();
    void mouse(int button, int state, int x, int y);
    void display();
    
};

#endif