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
#include "ImageElement.h"
#include "TextElement.h"

using namespace std;

CollagePage::CollagePage()
{   
    // Get the name of the collage
    title = Collage::sharedCollage().getName();
    activeElement = NULL;
    
    // Initialize or load the collage
    Collage::sharedCollage().setupCollage();
    
    // Initialize the buttons and text boxes
    btn_back = new BaseButton("BACK", 75, 50);
    btn_delete = new BaseButton("DELTE", 75, 125);
    btn_copy = new BaseButton("COPY", 75, 200);
    btn_lock = new ToggleButton("LOCK RATIO", 300, COLLAGE_MENU_HEIGHT - 70);
    btn_forward = new BaseButton("FORWARD", 300, COLLAGE_MENU_HEIGHT-125);
    btn_backward = new BaseButton("BACKWARD", 300, COLLAGE_MENU_HEIGHT - 180);
    dialog_rotation = new BaseDialog("ROTATION: ", "0", 300, COLLAGE_MENU_HEIGHT - 225); 
    
    // RED
    slider_red = new BaseSlider("RED:",WINDOW_WIDTH - 230, COLLAGE_MENU_HEIGHT-75, 0, 255);
    dialog_red = new BaseDialog("", "0", WINDOW_WIDTH-70, COLLAGE_MENU_HEIGHT-75);
    // GREEN
    slider_green = new BaseSlider("GREEN:",WINDOW_WIDTH - 230, COLLAGE_MENU_HEIGHT-125, 0, 255);
    dialog_green = new BaseDialog("", "0", WINDOW_WIDTH-70, COLLAGE_MENU_HEIGHT-125);
    // BLUE
    slider_blue = new BaseSlider("BLUE:",WINDOW_WIDTH - 230, COLLAGE_MENU_HEIGHT-175, 0, 255);
    dialog_blue = new BaseDialog("", "0", WINDOW_WIDTH-70, COLLAGE_MENU_HEIGHT-175);
    // ALPHA
    slider_alpha = new BaseSlider("OPACITY:",WINDOW_WIDTH - 230, COLLAGE_MENU_HEIGHT-225, 0, 255);
    dialog_alpha = new BaseDialog("", "255", WINDOW_WIDTH-70, COLLAGE_MENU_HEIGHT-225);
}

// Pass user input to the Collage Elements
void CollagePage::mouseMotion(int x, int y)
{
    // Pass mouse press to elements moving (0,0) to above the control panel
    int numElements = Collage::sharedCollage().getNumberOfElements();
    for(int i = 0; i < numElements; i++)
    {
        Collage::sharedCollage().getElement(i)->mouseMotion(x,y-COLLAGE_MENU_HEIGHT);
        // update the control panel
        updateControlPanel();
    }
    
    // Pass mouse movement to the sliders and update any changes
    if(slider_red->mouseMotion(x,y))
        dialog_red->setValue(slider_red->getValue());
    if(slider_green->mouseMotion(x,y))
        dialog_green->setValue(slider_green->getValue());
    if(slider_blue->mouseMotion(x,y))
        dialog_blue->setValue(slider_blue->getValue());
    if(slider_alpha->mouseMotion(x,y))
        dialog_alpha->setValue(slider_alpha->getValue());
}

// Pass user input to the Collage Elements
void CollagePage::mouse(int button, int state, int x, int y)
{
    // Pass mouse movements to the elements if the mouse is in the collage display
    if(y >= COLLAGE_MENU_HEIGHT)
    {
        // Pass mouse press to elements moving offsetting the mouse by the collage menu
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
        
        if(!selectedElement)
            activeElement = NULL;
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
    if(btn_lock->mouse(button, state, x,y))
        onLockPress();
    if(btn_copy->mouse(button, state, x,y))
        onCopyPress();
    
    //Pass mouse onto text boxes
    dialog_red->mouse(button, state, x, y);
    dialog_blue->mouse(button, state, x,y);
    dialog_green->mouse(button, state, x,y);
    dialog_alpha->mouse(button, state, x,y);
    dialog_rotation->mouse(button, state, x,y);
    
    
    // Pass the mouse to the sliders
    slider_red->mouse(button, state, x, y);
    slider_green->mouse(button, state, x, y);
    slider_blue->mouse(button, state, x, y);
    slider_alpha->mouse(button, state, x, y);
}

// Pass user input to the dialog boxes
void CollagePage::keyboard(unsigned char key, int x, int y)
{
    dialog_rotation->keyboard(key, x, y);
    
    // Update the red slider if the text box changes
    if(dialog_red->keyboard(key, x, y))
        slider_red->setValue(atof(dialog_red->getValue().c_str()));
    
    // Update the green slider if the text box changes
    if(dialog_green->keyboard(key, x, y))
        slider_green->setValue(atof(dialog_green->getValue().c_str()));
    
    // Update the blue slider if the text box changes
    if(dialog_blue->keyboard(key, x, y))
        slider_blue->setValue(atof(dialog_blue->getValue().c_str()));
    
    // Update the alpha slider if the text box changes
    if(dialog_alpha->keyboard(key, x, y))
        slider_alpha->setValue(atof(dialog_alpha->getValue().c_str()));
}

// Go back to the create page
void CollagePage::onBackPress()
{
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

// Delete the active element
void CollagePage::onDeletePress()
{
    if(activeElement != NULL)
    {
        Collage::sharedCollage().removeElement(activeElement);
        activeElement = NULL;
    }
}

// Copy the active element
void CollagePage::onCopyPress()
{
    if(activeElement != NULL)
    {
        // Create the correct type IMAGE or TEXT
        if(activeElement->getElementType() == BaseElement::IMAGE_ELEMENT)
        {
            Collage::sharedCollage().addElement(new ImageElement((ImageElement*)activeElement));
        }
        else if(activeElement->getElementType() == BaseElement::TEXT_ELEMENT)
        {
            Collage::sharedCollage().addElement(new TextElement((TextElement*)activeElement));
        }
    }
}

// Move the active element forward one level at a time
void CollagePage::onForwardPress()
{
    if(activeElement != NULL)
        Collage::sharedCollage().moveElementForward(activeElement);
}

// Move the active element object backward one level at a time
void CollagePage::onBackwardPress()
{
    if(activeElement != NULL)
        Collage::sharedCollage().moveElementBackward(activeElement);
}

// Lock / Unlock the aspect ratio of the active element
void CollagePage::onLockPress()
{
    if(activeElement != NULL)
        activeElement->setLockRatio(btn_lock->getSelected());
}

// Update the active element based on the control panel
void CollagePage::updateActiveElement()
{
    if(activeElement != NULL)
    {
        activeElement->setColor4(atof(dialog_red->getValue().c_str())/255, 
                            atof(dialog_green->getValue().c_str())/255,
                            atof(dialog_blue->getValue().c_str())/255,
                            atof(dialog_alpha->getValue().c_str())/255);
        activeElement->setRotation(atof(dialog_rotation->getValue().c_str()));
    }
}

// Update the control panel to display the values for the current element
void CollagePage::updateControlPanel()
{
    if(activeElement != NULL)
    {
        dialog_rotation->setValue(activeElement->getRotation());
        BaseColor *color = activeElement->getColor();
        dialog_red->setValue(color->color.red * 255);
        dialog_green->setValue(color->color.green * 255);
        dialog_blue->setValue(color->color.blue * 255);
        dialog_alpha->setValue(color->color.alpha*255);
        btn_lock->setSelected(activeElement->getLockRatio());
        
        slider_red->setValue(color->color.red*255);
        slider_green->setValue(color->color.green*255);
        slider_blue->setValue(color->color.blue*255);
        slider_alpha->setValue(color->color.alpha*255);
    }
}

// Draw the Collage
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
    glColor3f(0,0,0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(0, COLLAGE_MENU_HEIGHT);
    glVertex2f(WINDOW_WIDTH, COLLAGE_MENU_HEIGHT);
    glEnd();
    
    // Draw the title
    glColor3f(0, 0, .4);
    glPushMatrix();
    int w = Collage::sharedCollage().getFont()->calculateWidth(title,.75);
    int h = Collage::sharedCollage().getFont()->calculateHeight(title,.75);
    glTranslatef((WINDOW_WIDTH-w)/2, COLLAGE_MENU_HEIGHT - h, 0);
    Collage::sharedCollage().getFont()->draw(title, 0.75, .75);
    glPopMatrix();
    
    // Draw buttons and text boxes and sliders
    btn_back->draw();
    if(activeElement != NULL)
    {
        btn_delete->draw();
        btn_copy->draw();
        btn_forward->draw();
        btn_backward->draw();
        btn_lock->draw();
        dialog_red->draw();
        dialog_green->draw();
        dialog_blue->draw();
        dialog_alpha->draw();
        dialog_rotation->draw();
        slider_red->draw();
        slider_green->draw();
        slider_blue->draw();
        slider_alpha->draw();
    }
    
    glFlush();
    glPopMatrix();
}