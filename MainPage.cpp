//
//  MainPage.cpp
//  Collage
//
//  Created by Michelle Alexander on 9/23/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include "Collage.h"
#include "MainPage.h"
#include "CreatePage.h"
#include "BaseButton.h"
#include "Utility.h"

#include <GL/glut.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

MainPage::MainPage()
{
    btn_new = new BaseButton("New", WINDOW_WIDTH/2, 200);
    btn_load = new BaseButton("Load", WINDOW_WIDTH/2, 100);
    
    title = "Collage Builder";
}

void MainPage::onNewPress()
{
    title = "onNewPress";
    glutPostRedisplay();
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void MainPage::onLoadPress()
{
    title = "onLoadPress";
    glutPostRedisplay();
}

void MainPage::mouse(int button, int state, int x, int y)
{
    // Check if the new or load buttons were pressed
    if(btn_new->mouse(button, state, x, y))
        onNewPress();
    if(btn_load->mouse(button, state, x, y))
        onLoadPress();
}

void MainPage::display()
{
    glPushMatrix();
            
    // Draw the title
    glColor3f(0, 0, 0);
    glRasterPos3f(getMainTitleX(title), getMainTitleY(title), 0.5);    
    displayString(title);
  
    // Draw the buttons
    btn_new->draw();
    btn_load->draw();
    
    
    glFlush();
    glPopMatrix();
}