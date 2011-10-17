//
//  MainPage.cpp
//  Collage
//
//  Created by Michelle Alexander on 9/23/11.
//  Copyright 2011 ??? . All rights reserved.
//
//  This is the first page the user sees. 
//  For now you can create a New Collage and give it a name
//  If you have already created a collage you will also be given the
//  Option to continue

#include "Collage.h"
#include "MainPage.h"
#include "CreatePage.h"
#include "BaseButton.h"
#include "Utility.h"

#include <GL/glut.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

// Initialize the pages dialog boxes, buttons, and title
MainPage::MainPage()
{
    dialog_name = new BaseDialog("Name: ", "My Collage", WINDOW_WIDTH/2, WINDOW_HEIGHT - 250, 200);
    btn_new = new BaseButton("New", WINDOW_WIDTH/2, WINDOW_HEIGHT - 325);
    dialog_file = new BaseDialog("Load: ", "... doesnt work!", WINDOW_WIDTH/2, WINDOW_HEIGHT -300, 200);
    btn_load = new BaseButton("Load", WINDOW_WIDTH/2, WINDOW_HEIGHT - 350);
    btn_continue = new BaseButton("Continue", WINDOW_WIDTH/2, WINDOW_HEIGHT - 450);
    
    title = "Collage Builder";
}

void MainPage::onNewPress()
{
    // Reset the collage
    Collage::sharedCollage().createNewCollage(dialog_name->getValue());
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void MainPage::onLoadPress()
{
    title = dialog_file->getValue();
    glutPostRedisplay();
}

void MainPage::onContinuePress()
{
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void MainPage::mouse(int button, int state, int x, int y)
{
    // Check if the new or load buttons were pressed
    if(btn_new->mouse(button, state, x, y))
        onNewPress();
    if(Collage::sharedCollage().isCreated() && btn_continue->mouse(button, state, x, y))
        onContinuePress();
    
    dialog_name->mouse(button, state, x, y);
    
    //Load Features to be added
    //if(btn_load->mouse(button, state, x, y))
    // onLoadPress();
    //dialog_file->mouse(button, state, x, y);
}

void MainPage::keyboard(unsigned char key, int x, int y)
{
    dialog_name->keyboard(key, x, y);
    dialog_file->keyboard(key, x, y);
}

void MainPage::display()
{
    glPushMatrix();
            
    // Draw the title
    glColor3f(0, 0, .4);
    glPushMatrix();
    int w = Collage::sharedCollage().getFont()->calculateWidth(title,1.3);
    glTranslatef((WINDOW_WIDTH-w)/2, WINDOW_HEIGHT - 100, 0);
    Collage::sharedCollage().getFont()->draw(title, 1.3, 1.3);
    glPopMatrix();
    
    
    // Draw the buttons
    btn_new->draw();
    //btn_load->draw();
    // Only display the continue button if a collage has already been started
    if(Collage::sharedCollage().isCreated())
        btn_continue->draw();
    
    // Draw the text boxes
    dialog_name->draw();
    //dialog_file->draw();
    
    
    glFlush();
    glPopMatrix();
}