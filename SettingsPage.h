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

class SettingsPage: public BasePage
{
    
    BaseButton *btn_back;
    
    void onBackPress();
    
public:
    SettingsPage();
    void mouse(int button, int state, int x, int y);
    void display();
    
};

#endif