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

class CollagePage: public BasePage
{
    
    BaseButton *btn_back;
    
    void onBackPress();
    
public:
    CollagePage();
    void mouse(int button, int state, int x, int y);
    void mouseMotion(int x, int y);
    void display();
    
};

#endif