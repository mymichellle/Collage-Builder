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
#include "BaseDialog.h"

class MainPage : public BasePage
{
private:
    
    BaseDialog *dialog_name;
    BaseDialog *dialog_file;
    
    BaseButton *btn_new;
    BaseButton *btn_load;
    BaseButton *btn_continue;
    
    void onNewPress();
    void onLoadPress();
    void onContinuePress();
    
public:
    MainPage();
    void mouse(int button, int state, int x, int y);
    void keyboard(unsigned char key, int x, int y);
    void display();
};

#endif