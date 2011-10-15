//
//  CollagePage.h
//  Collage
//
//  Created by Michelle Alexander on 10/05/11.
//  Copyright 2011 ??? . All rights reserved.
//
#include <GL/glut.h>
#include <GLUT/glut.h>

#include "CollagePage.h"
#include "Utility.h"
#include "Collage.h"
#include "CreatePage.h"

using namespace std;

CollagePage::CollagePage()
{    
    title = "Collage";
    activeElement = NULL;
    // Initialize or load the collage
    Collage::sharedCollage().setupCollage();
    
    btn_back = new BaseButton("BACK", 75, 50);
    btn_delete = new BaseButton("DELTE", WINDOW_WIDTH-75, 50);
    btn_forward = new BaseButton("ELEMENT FORWARD", 300, COLLAGE_MENU_HEIGHT-50);
    btn_backward = new BaseButton("ELEMENT BACKWARD", 300, COLLAGE_MENU_HEIGHT - 125);
    dialog_rotation = new BaseDialog("ROTATION: ", "0", 300, COLLAGE_MENU_HEIGHT - 175);
    dialog_red = new BaseDialog("RED: ", "0", WINDOW_WIDTH-200, COLLAGE_MENU_HEIGHT-50);
    dialog_green = new BaseDialog("GREEN: ", "0", WINDOW_WIDTH-200, COLLAGE_MENU_HEIGHT-100);
    dialog_blue = new BaseDialog("BLUE: ", "0", WINDOW_WIDTH-200, COLLAGE_MENU_HEIGHT-150);
    
}

void CollagePage::mouseMotion(int x, int y)
{
    int numElements = Collage::sharedCollage().getNumberOfElements();
    // Pass mouse press to elements moving (0,0) to above the control panel
    for(int i = 0; i < numElements; i++)
    {
        Collage::sharedCollage().getElement(i)->mouseMotion(x,y-COLLAGE_MENU_HEIGHT);
        // update the control panel to reflect any rotation done by the mouse
        updateControlPanel();
    }
}

void CollagePage::mouse(int button, int state, int x, int y)
{
    // Pass mouse movements to the elements if the mouse is in the collage display
    if(y >= COLLAGE_MENU_HEIGHT)
    {
        
        // Pass mouse press to elements moving offsetting the mosue by the collage menu
        bool selectedElement = false;
        bool elementState;
        int numElements = Collage::sharedCollage().getNumberOfElements();
        // start with closest z (highest index)
        for(int i = numElements-1; i >= 0; i--)
        {
            elementState = Collage::sharedCollage().getElement(i)->mouse(button, state, x,y-COLLAGE_MENU_HEIGHT);
            
            // If the element is selected
            if(elementState)
            {
                // If there was already a selected item, deselect the current element it is further back
                if(selectedElement)
                {
                    Collage::sharedCollage().getElement(i)->deselect();
                }
                else
                {
                    // set the active element
                    selectedElement = true;
                    activeElement = Collage::sharedCollage().getElement(i);
                    // update the control pannel to show the active element
                    updateControlPanel();
                }
            }
        }
    }
    
    // Check for button presses
    if(btn_back->mouse(button, state, x, y))
        onBackPress();
    if(btn_delete->mouse(button, state, x, y))
        onDeletePress();
    if(btn_forward->mouse(button, state, x, y))
        onForwardPress();
    if(btn_backward->mouse(button, state, x, y))
        onBackwardPress();
    
    //Pass mouse onto text boxes
    dialog_red->mouse(button, state, x, y);
    dialog_blue->mouse(button, state, x,y);
    dialog_green->mouse(button, state, x,y);
    dialog_rotation->mouse(button, state, x,y);
}

void CollagePage::keyboard(unsigned char key, int x, int y)
{
    dialog_red->keyboard(key, x, y);
    dialog_blue->keyboard(key, x, y);
    dialog_green->keyboard(key, x, y);
    dialog_rotation->keyboard(key, x, y);
}

void CollagePage::onBackPress()
{
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

void CollagePage::onDeletePress()
{
    if(activeElement != NULL)
    {
        Collage::sharedCollage().removeElement(activeElement);
        activeElement = NULL;
    }
}

void CollagePage::onForwardPress()
{
    if(activeElement != NULL)
        Collage::sharedCollage().moveElementForward(activeElement);
}

void CollagePage::onBackwardPress()
{
    if(activeElement != NULL)
        Collage::sharedCollage().moveElementBackward(activeElement);
}

void CollagePage::updateActiveElement()
{
    if(activeElement != NULL)
    {
        activeElement->setColor(atof(dialog_red->getValue().c_str())/255, 
                          atof(dialog_green->getValue().c_str())/255,
                          atof(dialog_blue->getValue().c_str())/255);
        activeElement->setRotation(atof(dialog_rotation->getValue().c_str()));
    }
}

void CollagePage::updateControlPanel()
{
    if(activeElement != NULL)
    {
        dialog_rotation->setValue(activeElement->getRotation());
        BaseColor *color = activeElement->getColor();
        dialog_red->setValue(color->color.red * 255);
        dialog_green->setValue(color->color.green * 255);
        dialog_blue->setValue(color->color.blue * 255);
    }
}

void CollagePage::display()
{
    glPushMatrix();
    
    //update the selectedElement
    updateActiveElement();
    
    glPushMatrix();
    // Draw the Elements
    Collage::sharedCollage().drawElements(0, COLLAGE_MENU_HEIGHT);
    glPopMatrix();
    
    // Draw the Control Pannel
    glColor3f(.8,.8,.8);
    glRectf(0,0,WINDOW_WIDTH,COLLAGE_MENU_HEIGHT);
    
    // Draw the title
    glColor3f(0, 0, 0);
    glRasterPos3f(WINDOW_WIDTH/2, COLLAGE_MENU_HEIGHT - 20, 0.5);    
    displayString(title);
    
    // Draw buttons and text boxes
    btn_back->draw();
    btn_delete->draw();
    btn_forward->draw();
    btn_backward->draw();
    dialog_red->draw();
    dialog_green->draw();
    dialog_blue->draw();
    dialog_rotation->draw();
    
    glFlush();
    glPopMatrix();
}