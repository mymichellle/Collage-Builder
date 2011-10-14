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

class TextPage: public BasePage
{
    BaseButton *btn_save;
    BaseButton *btn_back;
    
    BaseDialog *dialog_text;
    
    void onSavePress();
    void onBackPress();

public:
    TextPage();
    void mouse(int button, int state, int x, int y);
    void mouseMotion(int x, int y);
    void keyboard(unsigned char key, int x, int y);
    void display();
    
};

#endif