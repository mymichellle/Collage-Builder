//
//  CreatePage.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/04/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include <GL/glut.h>
#include <GLUT/glut.h>

#include "CreatePage.h"
#include "Collage.h"
#include "TextPage.h"
#include "ImagePage.h"
#include "SettingsPage.h"
#include "MainPage.h"
#include "CollagePage.h"

using namespace std;

CreatePage::CreatePage()
{    
    title = "Create A Collage";
    
    btn_text = new BaseButton("TEXT", WINDOW_WIDTH/2, WINDOW_HEIGHT - 200);
    btn_image = new BaseButton("IMAGE", WINDOW_WIDTH/2, WINDOW_HEIGHT - 300);
    btn_settings = new BaseButton("SETTINGS", WINDOW_WIDTH/2, WINDOW_HEIGHT - 400);
    btn_collage = new BaseButton("COLLAGE", WINDOW_WIDTH/2, WINDOW_HEIGHT - 500);
    btn_back = new BaseButton("BACK", 100, 70);
}

void CreatePage::mouse(int button, int state, int x, int y)
{
    // Check if a button was pressed
    if(btn_text->mouse(button, state, x, y))
        onTextPress();
    if(btn_image->mouse(button, state, x, y))
        onImagePress();
    if(btn_settings->mouse(button, state, x, y))
        onSettingsPress();
    if(btn_collage->mouse(button, state, x, y))
        onCollagePress();
    if(btn_back->mouse(button, state, x, y))
        onBackPress();
}

void CreatePage::onTextPress()
{
    Collage::sharedCollage().setDisplayPage(new TextPage());
}

void CreatePage::onImagePress()
{
    Collage::sharedCollage().setDisplayPage(new ImagePage());
}

void CreatePage::onSettingsPress()
{
    Collage::sharedCollage().setDisplayPage(new SettingsPage());
}

void CreatePage::onCollagePress()
{
    Collage::sharedCollage().setDisplayPage(new CollagePage());
}

void CreatePage::onBackPress()
{
    Collage::sharedCollage().setDisplayPage(new MainPage());
}

void CreatePage::display()
{
    glPushMatrix();
    
    // Draw the title
    glColor3f(0, 0, .4);
    glPushMatrix();
    int w = Collage::sharedCollage().getFont()->calculateWidth(title,1);
    glTranslatef((WINDOW_WIDTH-w)/2, WINDOW_HEIGHT - 100, 0);
    Collage::sharedCollage().getFont()->draw(title);
    glPopMatrix();
    
    // Draw the buttons
    btn_text->draw();
    btn_image->draw();
    btn_settings->draw();
    btn_collage->draw();
    btn_back->draw();
    
    glFlush();
    glPopMatrix();
}