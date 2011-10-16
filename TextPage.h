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

class TextPage: public BasePage
{
private:
    TextElement *element;
    
    BaseButton *btn_save;
    BaseButton *btn_back;
    
    BaseDialog *dialog_text;
    BaseDialog *dialog_red;
    BaseDialog *dialog_green;
    BaseDialog *dialog_blue;
    BaseDialog *dialog_rotation;
    BaseDialog *dialog_size;
    
    void onSavePress();
    void onBackPress();
    
    void defineTextElement();
    void setDefaultValues();

public:
    TextPage();
    void mouse(int button, int state, int x, int y);
    void mouseMotion(int x, int y);
    void keyboard(unsigned char key, int x, int y);
    void display();
    
};

#endif