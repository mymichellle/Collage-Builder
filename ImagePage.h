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

class ImagePage: public BasePage
{
    BaseButton *btn_save;
    BaseButton *btn_back;
    
    void onSavePress();
    void onBackPress();
  
public:
    ImagePage();
    void mouse(int button, int state, int x, int y);
    void display();
    
};

#endif