//
//  CreatePage.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/04/11.
//  Copyright 2011 ??? . All rights reserved.
//


#include <GL/glut.h>
#include <GLUT/glut.h>

#include "ImagePage.h"
#include "Utility.h"
#include "Collage.h"
#include "CreatePage.h"

using namespace std;

ImagePage::ImagePage()
{    
    // Title and default file
    title = "Image";
    fileName = "Basketball.png";
    
    // Initialize the element being defined
    element = new ImageElement(fileName,0,0);
    
    // Buttons
    btn_save = new BaseButton("SAVE", WINDOW_WIDTH-75, 50);
    btn_back = new BaseButton("BACK", 75,  50);
    btn_load = new BaseButton("LOAD", WINDOW_WIDTH/2, WINDOW_HEIGHT - 200);
    btn_lock = new ToggleButton("LOCK RATIO", 200, WINDOW_HEIGHT-350);
    
    // Sliders and Text boxes
    dialog_file = new BaseDialog("FILE: ", fileName, WINDOW_WIDTH/2, WINDOW_HEIGHT-150, 400);
    dialog_width = new BaseDialog("WIDTH: ", "100", 200, WINDOW_HEIGHT-250);
    dialog_height = new BaseDialog("HEIGHT: ", "100", 200, WINDOW_HEIGHT-300);
    dialog_rotation = new BaseDialog("ROTATION: ", "0",200, WINDOW_HEIGHT-400);
    
    // RED
    slider_red = new BaseSlider("RED:",WINDOW_WIDTH - 300, WINDOW_HEIGHT - 300, 0, 255);
    dialog_red = new BaseDialog("", "0", WINDOW_WIDTH-100, WINDOW_HEIGHT-300);
    // GREEN
    slider_green = new BaseSlider("GREEN:",WINDOW_WIDTH - 300, WINDOW_HEIGHT - 350, 0, 255);
    dialog_green = new BaseDialog("", "0", WINDOW_WIDTH-100, WINDOW_HEIGHT-350);
    // BLUE
    slider_blue = new BaseSlider("BLUE:",WINDOW_WIDTH - 300, WINDOW_HEIGHT - 400, 0, 255);
    dialog_blue = new BaseDialog("", "0", WINDOW_WIDTH-100, WINDOW_HEIGHT-400);
    // ALPHA
    slider_alpha = new BaseSlider("OPACITY:",WINDOW_WIDTH - 300, WINDOW_HEIGHT - 450, 0, 255);
    dialog_alpha = new BaseDialog("", "255", WINDOW_WIDTH-100, WINDOW_HEIGHT-450);
    
    // Load the default values
    setDefaultValues();
}

// Initialize input devices to the saved default settings
void ImagePage::setDefaultValues()
{
    // Load the Collages default settings
    BaseColor *color = Collage::sharedCollage().getDefaultColor(BaseElement::IMAGE_ELEMENT);
    
    dialog_red->setValue(color->color.red*255);
    dialog_green->setValue(color->color.green*255);
    dialog_blue->setValue(color->color.blue*255);
    dialog_alpha->setValue(color->color.alpha*255);
    dialog_width->setValue(Collage::sharedCollage().getDefaultWidth(BaseElement::IMAGE_ELEMENT));
    dialog_height->setValue(Collage::sharedCollage().getDefaultHeight(BaseElement::IMAGE_ELEMENT));
    dialog_rotation->setValue(Collage::sharedCollage().getDefaultRotation(BaseElement::IMAGE_ELEMENT));
    
    slider_red->setValue(color->color.red*255);
    slider_green->setValue(color->color.green*255);
    slider_blue->setValue(color->color.blue*255);
    slider_alpha->setValue(color->color.alpha*255);
}

// Pass the mouse actions to the buttons/dialogs/sliders
void ImagePage::mouse(int button, int state, int x, int y)
{
    if(btn_save->mouse(button, state, x, y))
        onSavePress();
    if(btn_back->mouse(button, state, x, y))
        onBackPress();
    if(btn_load->mouse(button, state, x, y))
        onLoadPress();
    if(btn_lock->mouse(button, state, x, y))
        onLockPress();
    
    // Pass the mouse movement to the dialog boxes
    dialog_file->mouse(button, state, x, y);
    dialog_red->mouse(button, state, x, y);
    dialog_blue->mouse(button, state, x,y);
    dialog_green->mouse(button, state, x,y);
    dialog_alpha->mouse(button, state, x,y);
    dialog_width->mouse(button, state, x, y);
    dialog_height->mouse(button, state, x, y);
    dialog_rotation->mouse(button, state, x,y);
    
    // Pass the mouse to the sliders
    slider_red->mouse(button, state, x, y);
    slider_green->mouse(button, state, x, y);
    slider_blue->mouse(button, state, x, y);
    slider_alpha->mouse(button, state, x, y);
}

// pass mouse movements to the sliders updating text boxes with changes
void ImagePage::mouseMotion(int x, int y)
{
    if(slider_red->mouseMotion(x,y))
        dialog_red->setValue(slider_red->getValue());
    if(slider_green->mouseMotion(x,y))
        dialog_green->setValue(slider_green->getValue());
    if(slider_blue->mouseMotion(x,y))
        dialog_blue->setValue(slider_blue->getValue());
    if(slider_alpha->mouseMotion(x,y))
        dialog_alpha->setValue(slider_alpha->getValue());
}

// Pass user keyboard input to the text boxes
void ImagePage::keyboard(unsigned char key, int x, int y)
{
    dialog_file->keyboard(key, x, y);
    
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
    
    // Get the aspect ratio before making any changes to width/height
    double widthToHeight = (double)element->getWidth()/element->getHeight();
    
    // Check if locked to do height calculations
    if(dialog_width->keyboard(key, x, y) && element->getLockRatio())
    {
        // Calcualte the height = H/W * w
        double h = atof(dialog_width->getValue().c_str()) * 1/widthToHeight;
        dialog_height->setValue(h);
    }
    
    // Check if the locked to do width calculations
    if(dialog_height->keyboard(key, x, y) && element->getLockRatio())
    {
        // Calculate the width = W/H * h
        double w = atof(dialog_height->getValue().c_str()) * widthToHeight;
        dialog_width->setValue(w);
    }
        
    dialog_rotation->keyboard(key, x, y);
}

// Save the element and return to the previous page
void ImagePage::onSavePress()
{
    // update the element add it and exit to main page
    defineImageElement();
    Collage::sharedCollage().addElement(element);
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

// Return to the previous page, discard changes
void ImagePage::onBackPress()
{
    Collage::sharedCollage().setDisplayPage(new CreatePage());
}

// Upload a new file
void ImagePage::onLoadPress()
{
    // Assign the value in the dialog box to the file name when laod is pressed
    fileName = dialog_file->getValue();
    
    // Load the image at its default values
    bool previousLock = element->getLockRatio();
    element->setLockRatio(false);
    
    element->setImage(fileName);
    
    // Set width and height dialog boxes to the widht/height of new image
    dialog_width->setValue(element->getWidth());
    dialog_height->setValue(element->getHeight());
    
    // Reset the element ratio lock
    element->setLockRatio(previousLock);
    
    // redraw new image
    glutPostRedisplay();
}

// Lock the aspect ratio of the element
void ImagePage::onLockPress()
{
    element->setLockRatio(btn_lock->getSelected());
}

// Set the image element
void ImagePage::defineImageElement()
{
    // Set the elements properties based on the page's settings
    element->setColor4(atof(dialog_red->getValue().c_str())/255, 
                      atof(dialog_green->getValue().c_str())/255,
                      atof(dialog_blue->getValue().c_str())/255,
                      atof(dialog_alpha->getValue().c_str())/255);
    element->setRotation(atof(dialog_rotation->getValue().c_str()));
    element->setLockRatio(btn_lock->getSelected());
    element->setWidth(atof(dialog_width->getValue().c_str()));
    element->setHeight(atof(dialog_height->getValue().c_str()));
}

// Display
void ImagePage::display()
{
    // update the element
    defineImageElement();
    
    glPushMatrix();
    
    // Draw the title
    glColor3f(0, 0, .4);
    glPushMatrix();
    int w = Collage::sharedCollage().getFont()->calculateWidth(title,1);
    glTranslatef((WINDOW_WIDTH-w)/2, WINDOW_HEIGHT - 100, 0);
    Collage::sharedCollage().getFont()->draw(title);
    glPopMatrix();
    
    // Draw the header
    glColor3f(0, 0, .4);
    glPushMatrix();
    // translate into place
    glTranslatef(WINDOW_WIDTH/2, WINDOW_HEIGHT - 270, 0);
    // scale text to .6
    Collage::sharedCollage().getFont()->draw("Color Overlay:", .6,.6);
    glPopMatrix();
    
    // Draw the header
    glColor3f(0, 0, .4);
    glPushMatrix();
    // translate into place
    glTranslatef(50, 200, 0);
    // scale text to .75
    Collage::sharedCollage().getFont()->draw("Preview:", .6,.6);
    glPopMatrix();
    
    // Draw buttons
    btn_save->draw();
    btn_back->draw();
    btn_load->draw();
    btn_lock->draw();
    
    // Draw dialog boxes
    dialog_file->draw();
    dialog_red->draw();
    dialog_blue->draw();
    dialog_alpha->draw();
    dialog_green->draw();
    dialog_width->draw();
    dialog_height->draw();
    dialog_rotation->draw();
    
    // Draw the sliders
    slider_red->draw();
    slider_green->draw();
    slider_blue->draw();
    slider_alpha->draw();
    
    // Draw a preview/thumbnail of the element
    glPushMatrix();
    
    // translate to the middle of the screen
    double thumbnailSize = 200.0;
    glTranslatef((WINDOW_WIDTH-thumbnailSize)/2, 10, 0);
    
    // scale the image to fit in a 200x200 spot maintaining aspect ratio
    double scalePrev = thumbnailSize/element->getWidth();
    if(scalePrev > thumbnailSize/element->getHeight())
    {
        scalePrev = thumbnailSize/element->getHeight();
    }
    glScalef(scalePrev, scalePrev, 1);
    element->draw();
    
    glPopMatrix();
    
    glFlush();
    glPopMatrix();
}