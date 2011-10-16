//
//  ImagePage.h
//  Collage
//
//  Created by Michelle Alexander on 10/04/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef ImagePage_h
#define ImagePage_h

#include "BasePage.h"
#include "BaseButton.h"
#include "BaseDialog.h"
#include "ImageElement.h"
#include <string>

class ImagePage: public BasePage
{
    ImageElement *element;
    std::string fileName;
    
    BaseButton *btn_save;
    BaseButton *btn_back;
    BaseButton *btn_load;
    
    BaseDialog *dialog_file;
    BaseDialog *dialog_red;
    BaseDialog *dialog_green;
    BaseDialog *dialog_blue;
    BaseDialog *dialog_alpha;
    BaseDialog *dialog_rotation;
    BaseDialog *dialog_width;
    BaseDialog *dialog_height;
    
    void onSavePress();
    void onBackPress();
    void onLoadPress();
    
    void defineImageElement();
    void setDefaultValues();
  
public:
    ImagePage();
    void mouse(int button, int state, int x, int y);
    void keyboard(unsigned char key, int x, int y);
    void display();
    
};

#endif