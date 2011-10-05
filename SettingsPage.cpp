//
//  SettingsPage.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/05/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include <GL/glut.h>
#include <GLUT/glut.h>

#include "SettingsPage.h"
#include "Utility.h"
#include "Collage.h"
#include "CreatePage.h"

using namespace std;

SettingsPage::SettingsPage()
{    
    title = "Settings";
    
    btn_back = new BaseButton("BACK", 100, 70);
}

void SettingsPage::mouse(int button, int state, int x, int y)
{
    
    if(btn_back->mouse(button, state, x, y))
        onBackPress();
}

void SettingsPage::onBackPress()
{
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void SettingsPage::display()
{
    glPushMatrix();
    
    // Draw the title
    glColor3f(0, 0, 0);
    glRasterPos3f(getMainTitleX(title), getMainTitleY(title), 0.5);    
    displayString(title);
    
    // Draw buttons
    btn_back->draw();
    
    glFlush();
    glPopMatrix();
}