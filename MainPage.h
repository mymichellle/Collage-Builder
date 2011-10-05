//
//  MainPage.h
//  Collage
//
//  Created by Michelle Alexander on 9/23/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef MainPage_h
#define MainPage_h

#include "BasePage.h"
#include "BaseButton.h"

class MainPage : public BasePage
{
private:
    BaseButton *btn_new;
    BaseButton *btn_load;
    void onNewPress();
    void onLoadPress();
    
public:
    MainPage();
    void mouse(int button, int state, int x, int y);
    void display();
};

#endif