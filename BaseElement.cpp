//
//  BaseElement.cpp
//  Collage
//
//  Created by Michelle Alexander on 10/1/11.
//  Copyright 2011 ??? . All rights reserved.
//

#include <GL/gl.h>
#include "BaseElement.h"
#include "Collage.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>

BaseElement::BaseElement()
{
    x = 0;
    y = 0;
    z = 0;
    width = 10;
    height = 10;
    color = new BaseColor(0,0,0,0);
    rotation = 15;
    bounds = new BoundingBox(x, y, width, height, rotation);
    
    // Movement properties
    selected = false;
    moveable = false;
    rotateable = false;
    startX = 0;
    startY = 0;
    
    // Initialize the corners
    selectedCorner = CNONE;
}

// Updateing the bounds takes a lot of calculations
// Only call after a movement/resize/rotation is final
void BaseElement::updateBounds()
{
    bounds->setOrigin(x,y);
    bounds->setDimensions(width, height);
    bounds->setAngle(rotation);
}

void BaseElement::setPosition(int xpos, int ypos)
{
    x = xpos;
    y = ypos;
}

void BaseElement::setWidth(int w, bool locked)
{
    //cout<<"setWidth w = "<<w<<endl;
    if(locked)
    {
        cout<<"LOCKED"<<endl;
        double scale = w/width;
        height = height*scale;
    }
    width = w;
}

void BaseElement::setHeight(int h, bool locked)
{
    if(locked)
    {
        double scale = h/height;
        width = width * scale;
    }
    height = h;
}

int BaseElement::getWidth()
{
    return width;
}

int BaseElement::getHeight()
{
    return height;
}

float BaseElement::getRotation()
{
    return rotation;
}

BaseColor* BaseElement::getColor()
{
    return color;
}

void BaseElement::setRotation(float r)
{
    rotation = r;
}

void BaseElement::setColor(float r, float g, float b)
{
    color->color.red = r, color->color.green = g, color->color.blue = b;
}

void BaseElement::deselect()
{
    cout<<"Deselect "<<endl;
    selected = false;
    rotateable = false;
    moveable = false;
}

bool BaseElement::pointInBounds(int xCord, int yCord)
{
    // If the Element is selected check bounding boxes too
    if( selected )
    {
        selectedCorner = (CornerType)bounds->checkCorners(xCord, yCord);
    }
    else
    {
        selectedCorner = CNONE;
    }
    
    // If no corner is selected, check in the main object bounds
    if(selectedCorner == CNONE)
    {
        return bounds->pointInBounds(xCord, yCord);
    }
    else
        return true;
}

// Returns true if the button was successfully clicked
bool BaseElement::mouse(int button, int state, int xpos, int ypos)
{
    
    //cout<<"BaseElement mouse button "<<button<<" state "<<state<<" ("<<xpos<<", "<<ypos<<")"<<endl;
    //cout<<"bounds ("<<x<<", "<<y<<", "<<x+width<<", "<<y+height<<")"<<endl;

    if(button == GLUT_LEFT_BUTTON && pointInBounds(xpos,ypos))
    {        
        // Resize is available if element is already selected
        if( selected )
        {
           
        }
        
        
        if (state == GLUT_DOWN)
        {
            // moveable is set when the mouse is pressed down in the element
            moveable = true;
            startX = xpos;
            startY = ypos;
        }else if( state == GLUT_UP && moveable)
        {
            // selected is true if the mouse went down and up in the element
            selected = true;
            moveable = false;
            selectedCorner = CNONE;
        }
        else
        {
            // Not selected if the mouse did not originate in the element
            selected = false;
            selectedCorner = CNONE;
        }
        
    }
    // Rotate Case
    else if(selected && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        selected = true;
        rotateable = true;
        moveable = false;
        selectedCorner = CNONE;
    }else if (button == GLUT_RIGHT_BUTTON && pointInBounds(xpos,ypos))
    {
        Collage::sharedCollage().moveElementBackward(this);
    }else
    {
        // De-select the element if left button is pressed somewhere else
        selected = false;
        moveable = false;
        rotateable = false;
        selectedCorner = CNONE;
    }
    
    // TODO: better checks if bounds needs to be updated this is too frequent
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        updateBounds();
    
    // re-draw the button
    glutPostRedisplay();
    return (selected || moveable);
}

bool BaseElement::mouseMotion(int xpos, int ypos)
{
    //cout<<"BaseElement mouseMotion ("<<xpos<<", "<<ypos<<")"<<endl;
    
    // Move the selected object if no corner is set
    if(moveable && selectedCorner == CNONE)
    {
        // Move the element the difference of the previous mouse location and current
        setPosition(x + (xpos - startX), y + (ypos - startY));
        
        // save the new mouse position
        startX = xpos;
        startY = ypos;
    }
    else if(selectedCorner != CNONE)
    {
        // Check if a corner is selected
        // Movement of a corner changes size.
        int w = width;
        int h = height;
        
        // resize is handled differently at each corner
        double resized[4];
        bounds->calculateResize(xpos, ypos, selectedCorner, resized);
        x = resized[0];
        y = resized[1];
        setWidth(resized[2], false);
        setHeight(resized[3], false);
       // cout<<"Width and height " << w << " " << h<<endl<<endl;
        /*
        switch(selectedCorner)
        {
            case CBL:
                // Origin x, y change
                x = x - (startX - xpos);
                y = y - (startY - ypos);
                h = h + (startY - ypos);
                w = w + (startX - xpos);
                setWidth(w, false);
                setHeight(h, false);
                break;
            case CBR:
                // x stays the same, y changes
                
                y = y - (startY - ypos);
                w = w + (xpos - startX);
                h = h + (startY - ypos);
                setWidth(w, false);
                setHeight(h, false);
                // Calculate the new origin, w and h
                bounds->calculateResize(xpos, ypos, CBR, resized);
                x = resized[0];
                y = resized[1];
                setWidth(resized[2], false);
                setHeight(resized[3], false);
                
                break;
            case CTR:
                // Origin x, y stays the same
                w = w + (xpos - startX);
                h = h + (ypos - startY);
                setWidth(w, false);
                setHeight(h, false);
                break;
            case CTL:
                // y stays the same, x changes
                x = x - (startX - xpos);
                w = w + (startX - xpos);
                h = h + (ypos - startY);
                setWidth(w, false);
                setHeight(h, false);
                break;
            default:
                break;
        }*/
        
        // If a corner is moved no other action should be done to the object
        // save new mouse point
        startX = xpos;
        startY = ypos;
    }
    else if(rotateable)
    {
        // Rotate if the item is selected and the mouse is moved outside the element
        //cout<<"ROTATE"<<endl;
        double deltaAngle = bounds->calculateRotate(startX, startY, xpos, ypos);
        
        setRotation(rotation + deltaAngle);
        
        startX = xpos;
        startY = ypos;
    }
    
    // redraw the page
    glutPostRedisplay();
}

void BaseElement::draw()
{
    glPushMatrix();
        // Translate to the correct location
        glTranslatef(x, y, z);
        
        glPushMatrix();
            // Set the rotation of the element
            glRotatef(rotation, 0, 0, 1);
            
            // Set the color of the element
            if(moveable)
                glColor3f(0,0,1);
            else if(selected)
            {
                glColor3f(0,1,0);
            }
            else
                glColor3f(color->color.red,color->color.green,color->color.blue);
            glPointSize(1);
            
            // Draw the Correct size
            drawElement();
            
            // Draw the bounding box corners if selected
            if(selected)
            {
                drawCorners();
            }
        glPopMatrix();
    
    glFlush();
    glPopMatrix();
        
        
    //DEBUG - Show Bounding Box
    glPushMatrix();
        bounds->draw();
    glPopMatrix();
    //DEBUG
}

void BaseElement::drawElement()
{
    glRectf(0,0,width,height);
}

void BaseElement::drawCorners()
{
    bool pushed;
    for(int i = 0; i < bounds->numCorners; i++)
    {
        pushed = false;
        
        // Set the color
        if(i == selectedCorner)
            glColor3f(1,0,0);
        else
            glColor3f(1,0,1);
        
        // Translate to the corner
        if(i == 0)
        { 
            glPushMatrix();
            glTranslatef(-CORNER_SIZE/2, -CORNER_SIZE/2, 0);
            pushed = true;
        }
        else if( i == 1)
        {
            glPushMatrix();
            glTranslatef(width - CORNER_SIZE/2, -CORNER_SIZE/2, 0);
            pushed = true;
        }
        else if(i == 2)
        {
            glPushMatrix();
            glTranslatef(width - CORNER_SIZE/2, height - CORNER_SIZE/2, 0);
            pushed = true;
        }
        else
        {
            glPushMatrix();
            glTranslatef(-CORNER_SIZE/2, height - CORNER_SIZE/2, 0);
            pushed = true;
        } 
        
        // Draw the rect
        if(pushed)
        {
            glRectf(0,0,CORNER_SIZE, CORNER_SIZE);
            
            glFlush();
            glPopMatrix();
        }
        
    }

}

// Bounding Box - public
BoundingBox::BoundingBox(int x, int y, int w, int h, int a)
{
    xO = x;
    yO = y;
    width = w;
    height = h;
    setAngle( a ); // convert to radians
    calculateBounds();
}

bool BoundingBox::pointInBounds(int xp, int yp)
{
    /*cout << " check point (" << xp << ", " << yp << ")" << endl;
    print();
    cout << "left : " << checkLeft(xp, yp) << endl;
    cout << "right : " << checkRight(xp, yp) << endl;
    cout << "top : " << checkTop(xp, yp) << endl;
    cout << "bottom : " << checkBottom(xp, yp) << endl;
    cout << "sides : " << checkLeft(xp, yp) * checkRight(xp, yp) << endl;
    cout << "tops : " << checkTop(xp, yp) * checkBottom(xp, yp) << endl;
    */
    // Check if the point is in between the top bottom and side lines (all return 0 or negative)
    if(checkTop(xp,yp)<= 0 && 
       checkBottom(xp,yp) <= 0 && 
       checkLeft(xp,yp)<=0 &&
       checkRight(xp,yp) <= 0)
        return true;
    
    return false;
}

int BoundingBox::checkCorners(int xp, int yp)
{
    // Check if the point is CORNER_SIZE away from a corner point
    double distance;
    
    // Bottom Left
    distance = sqrt( pow((xp - xO), 2) + pow((yp - yO), 2) );
    if( distance < CORNER_SIZE )
        return CBL;
    
    // Bottom Right
    distance = sqrt( pow((xp - xBR), 2) + pow((yp - yBR), 2) );
    if( distance < CORNER_SIZE )
        return CBR;
    
    // Top Left
    distance = sqrt( pow((xp - xTL), 2) + pow((yp - yTL), 2) );
    if( distance < CORNER_SIZE )
        return CTL;
    
    // Top Right
    distance = sqrt( pow((xp - xTR), 2) + pow((yp - yTR), 2) );
    if( distance < CORNER_SIZE )
        return CTR;
    
    return CNONE;
}

void BoundingBox::calculateResize(int xp, int yp, int corner, double *ans)
{
    double  xn = 0, 
            yn = 0, 
            dh = 0, 
            dw = 0,
            xO1 = 0,
            yO1 = 0;
    
    if(corner == CBL)
    {
        
        // Find intersection (xn, yn) of two lines
        // bottom of element and perpendicular line going through (xp, yp)
        xn = (mainSlope * xp - sideSlope * xO - yp + yO) / (mainSlope - sideSlope);
        yn = mainSlope * (xn - xp) + yp;
        
        // Calculate the change in width and height (dw, dh)
        dh = sqrt( pow((xO - xn),2) + pow((yO - yn),2) );
        dw = sqrt( pow((xp - xn),2) + pow((yp - yn),2) );
        
        // If the point is inside the box (negative value from checkLeft/Bottom)
        // The size is getting smaller
        if(checkLeft(xp, yp) < 0)
            dw = dw * -1;
        if(checkBottom(xp, yp) < 0)
            dh = dh * -1;
        
        // if width/ height is negative invert the dw/dh
        if(width < 0)
            dw = dw*-1;
        if(height < 0)
            dh = dh*-1;
        
        // New origin is (xp,yp)
        xO1 = xp;
        yO1 = yp;
    }
    
    if(corner == CBR)
    {
        // Find intersection (xn, yn) of two lines
        // bottom of element and perpendicular line going through (xp, yp)
        xn = (mainSlope * xp - sideSlope * xBR - yp + yBR) / (mainSlope - sideSlope);
        yn = mainSlope * (xn - xp) + yp;
        
        // Calculate the change in width and height (dw, dh)
        dh = sqrt( (xBR - xn)*(xBR - xn) + (yBR - yn)*(yBR - yn) );
        dw = sqrt( (xp - xn)*(xp - xn) + (yp - yn)*(yp - yn) );
        
        // If the point is inside the right or bottom then the shape is getting smaller dw/dh should be negative
        if(checkRight(xp, yp) < 0)
            dw = dw * -1;
        if(checkBottom(xp, yp) < 0)
            dh = dh * -1;
        
        // if width/ height is negative invert the dw/dh
        if(width < 0)
            dw = dw*-1;
        if(height < 0)
            dh = dh*-1;
        
        // Calculate the new origin (xO1, yO1)
        xO1 = xO + dh * cos(angle - PI/2); // angle minus 90 degrees
        yO1 = yO + dh * sin(angle - PI/2); // angle minus 90 degrees
    }
    
    if(corner == CTR)
    {
        // Find intersection (xn, yn) of two lines
        // bottom of element and perpendicular line going through (xp, yp)
        xn = (mainSlope * xp - sideSlope * xTR - yp + yTR) / (mainSlope - sideSlope);
        yn = mainSlope * (xn - xp) + yp;
        
        
        // Calculate the change in width and height (dw, dh)
        dh = sqrt( (xTR - xn)*(xTR - xn) + (yTR - yn)*(yTR - yn) );
        dw = sqrt( (xp - xn)*(xp - xn) + (yp - yn)*(yp - yn) );
        
        // Retain the direction of the change 
        // Acts opposite if angle is below the x axis
        if(checkRight(xp, yp) < 0)// && angle > 0 && angle < 180 || checkRight(xp, yp) > 0 && angle >180)
            dw = dw * -1;
        if(checkTop(xp, yp) < 0 )//&& angle > 0 && angle < 180)
            dh = dh * -1;
        
        // if width/ height is negative invert the dw/dh
        if(width < 0)
            dw = dw*-1;
        if(height < 0)
            dh = dh*-1;
        
        // Origin remains the same
        xO1 = xO;
        yO1 = yO;
    }
    
    if(corner == CTL)
    {
        // Find intersection (xn, yn) of two lines
        // bottom of element and perpendicular line going through (xp, yp)
        xn = (sideSlope * xTL - mainSlope * xp + yp - yTL) / (sideSlope - mainSlope);
        yn = yp - mainSlope * (xp - xn);
        
        
        // Calculate the change in width and height (dw, dh)
        dh = sqrt( (xn - xTL)*(xn - xTL) + (yn - yTL)*(yn - yTL) );
        dw = sqrt( (xp - xn)*(xp - xn) + (yp - yn)*(yp - yn) );
        
        
        // If the point is inside the box (negative value from checkLeft/Top)
        // The size is getting smaller
        if(checkLeft(xp, yp) < 0)
            dw = dw * -1;
        if(checkTop(xp, yp) < 0)
            dh = dh * -1;
        
        // if width/ height is negative invert the dw/dh
        if(width < 0)
            dw = dw*-1;
        if(height < 0)
            dh = dh*-1;
        
        // Calculate the new origin (xO1, yO1)
        xO1 = xO + dw * cos(angle + PI); // 180 plus  angle
        yO1 = yO + dw * sin(angle + PI); // 180 plus angle
    }
    
    
    //print();
   /* cout << "calculateResize : " << endl;
    cout << "mouse : (" << xp << ", " << yp <<")"<<endl;
    cout << "origin : (" << xO << ", " << yO <<")"<<endl;
    cout << "new origin : (" << xO1 << ", " << yO1 <<")"<<endl;
    cout << "dw, dh : (" << dw << ", " << dh <<")"<<endl;
    cout << "xn, yn : (" << xn << ", " << yn <<")"<<endl<<endl;*/
    
    
    ans[0] = xO1;
    ans[1] = yO1;
    ans[2] = width + dw;
    ans[3] = height + dh;
}

double BoundingBox::calculateRotate(int xp1, int yp1, int xp2, int yp2)
{
    // TODO: convert to rotate around center...
    // Treat xO, yO as the origin
    double angle1 = atan2(xp1-xO, yp1-yO);
    double angle2 = atan2(xp2-xO, yp2-yO);
   
    // Return the difference in degrees
    return (angle2-angle1) * -180/PI;
}


void BoundingBox::draw()
{
    glColor3f(1,1,0);
    glRectf(xO- CORNER_SIZE/2,yO- CORNER_SIZE/2,xO+ CORNER_SIZE/2, yO + CORNER_SIZE/2);
    
    glRectf(xBR- CORNER_SIZE/2,yBR- CORNER_SIZE/2,xBR+ CORNER_SIZE/2, yBR + CORNER_SIZE/2);
    
    glRectf(xTL- CORNER_SIZE/2,yTL- CORNER_SIZE/2,xTL+ CORNER_SIZE/2, yTL + CORNER_SIZE/2);
    
    glRectf(xTR- CORNER_SIZE/2,yTR- CORNER_SIZE/2,xTR+ CORNER_SIZE/2, yTR + CORNER_SIZE/2);
    
    glRectf(xC - 1, yC - 1, xC + 1, yC + 1);
}

void BoundingBox::setAngle(int a)
{
    // correct angle to be between -360 to 360
    if(a >= 360 || a <= -360)
    {
        a - (360 * a/360);
    }
    
    // correct angle further to be between 0 <= angle < 360
    if(a < 0)
    {
        a = 360 + a;
    }
    
    if(a == 360)
        a = 0;
    
    // if angle is 180 or 90 set it to exactly PI or PI/2
    if(a == 180)
        angle = PI;
    else if( a == 90)
        angle = PI/2;
    else
        angle = a * PI/180; // convert to radians
    
    calculateBounds();
}

void BoundingBox::setOrigin(int xp, int yp)
{
    xO = xp;
    yO = yp;
    calculateBounds();
}

void BoundingBox::setDimensions(int w, int h)
{
    width = w;
    height = h;
    calculateBounds();
}

// Bounding Box - private

void BoundingBox::calculateBounds()
{
    mainSlope = tan(angle);
    sideSlope =  tan(angle + (PI/2)); // add 90 degrees
    
    // Endpoints ( xO + length*cos(angle), yO + length*sin(angle) )
    xBR = xO + width * cos(angle);
    yBR = yO + width * sin(angle);
    xTR = xBR + height * cos(angle + (PI/2));
    yTR = yBR + height * sin(angle + (PI/2));
    xTL = xO + height * cos(angle + (PI/2));
    yTL = yO + height * sin(angle + (PI/2));
    xC  = xO + sqrt( pow(width/2, 2) + pow(height/2, 2)) * cos(angle + atan(height/width));
    yC  = yO + sqrt( pow(width/2, 2) + pow(height/2, 2)) * sin(angle + atan(height/width));
    
    // Offset = y - slope * x
    offsetB = yO - mainSlope * xO;
    offsetT = yTL - mainSlope * xTL;
    offsetL = yO - sideSlope * xO;
    offsetR = yBR - sideSlope * xBR;
}

/* Based on equation of a line y = mx + b
 * Returns:
 *  0 - point is on line
 *  negative - if point is on the element side of the line
 *  positive - if point is on the outside of the line
 */
int BoundingBox::checkBottom(int xp, int yp)
{
    // return negative or 0 if the point is inside the right bottom of the box
    int calc = yp - mainSlope * xp - offsetB; // equation of the top side 0 = y - mx - b
    
    // If the height is negative the image has been flipped and calculations will be opposite
    if(height<0)
    {
        calc = -1*calc;
    }
    
    if(angle >= 0 && angle < PI/2 || angle > 3*PI/2 && angle < 2*PI)
    {
        // First & 4th Quadrants
        return -1*calc; 
    }
    else if(angle > PI/2 && angle < 3*PI/2)
    {
        // When the box is flipped side to side the line equations are opposite
        return calc; 
    }
    else if(angle == PI/2)
    {
        // Special case when angle is 90 degrees because bottom is a vertical line
        return xp - xO;
    }
    else // angle is 270 degrees
    {
        // Special case when angle 270 degrees because bottom is a vertical line
        return xO - xp;
    }
}

int BoundingBox::checkTop(int xp, int yp)
{
    // return negative or 0 if the point is inside the top side of the box
    int calc = yp - mainSlope * xp - offsetT; // equation of the top side 0 = y - mx - b
    
    // If the height is negative the image has been flipped and calculations will be opposite
    if(height<0)
    {
        calc = -1*calc;
    }
    
    // First & 4th Quadrants
    if(angle >= 0 && angle < PI/2 || angle > 3*PI/2 && angle < 2*PI)
    {
        return calc; 
    }
    else if(angle > PI/2 && angle < 3*PI/2)
    {
        return -1*calc; // When the box is flipped side to side the line equations are opposite
    }
    else if(angle == PI/2)
    {
        // Special case when angle is 90 degrees because top is a vertical line
        return xTR - xp;
    }
    else // angle is 270 degrees
    {
        // Special case when angle 270 degrees because top is a vertical line
        return xp - xTR;
    }
}

int BoundingBox::checkLeft(int xp, int yp)
{
    // return negative or 0 if the point is inside the left side of the box
    int calc = yp - sideSlope * xp - offsetL; // equation of the right side 0 = y - mx - b
    
    // If the width is negative the image has been flipped and calculations will be opposite
    if(width<0)
    {
        calc = -1*calc;
    }
    
    // First & Second Quadrants
    if(angle > 0 && angle < PI)
    {
        return -1*calc; 
    }
    else if(angle > PI && angle < 2*PI)
    {
        return calc; // When the box is flipped upside down the line equations are opposite
    }
    else if(angle == 0)
    {
        // Special case when angle is 0 degrees because the side is a vertical line
        return xO - xp;
    }
    else
    {
        // Special case when angle is 180 degrees because the side is a vertical line
        return xp - xO;
    }
}

int BoundingBox::checkRight(int xp, int yp)
{
    // return negative or 0 if the point is inside the right side of the box
    int calc = yp - sideSlope * xp - offsetR; // equation of the right side 0 = y - mx - b
    
    // If the width is negative the image has been flipped and calculations will be opposite
    if(width<0)
    {
        calc = -1*calc;
    }
    
    // First & Second Quadrants
    if(angle > 0 && angle < PI)
    {
        return calc; 
    }
    else if(angle > PI && angle < 2*PI)
    {
        // When the box is flipped upside down the line equations are opposite
        return -1*calc;
    }
    else if(angle == 0)
    {
        // Special case when angle is 0 degrees because the side is a vertical line
        return xp - xBR;
    }
    else
    {
        // Special case when angle is 180 degrees because the side is a vertical line
        return xBR - xp;
    }
}

void BoundingBox::print()
{
    cout<<"Origin : (" << xO << ", " << yO <<")"<<endl;
    cout<<"Btm Rt : (" << xBR << ", " << yBR <<")"<<endl;
    cout<<"Top Rt : (" << xTR << ", " << yTR <<")"<<endl;
    cout<<"Top Lt : (" << xTL << ", " << yTL <<")"<<endl;
    cout<<"mainSlope = " << mainSlope << endl;
    cout<<"sideSlope = " << sideSlope << endl;
    cout<<"Lines: y = mx + b"<<endl;
    cout<<"       y = " << mainSlope << "x + " << offsetB << endl;
    cout<<"       y = " << mainSlope << "x + " << offsetT << endl;
    cout<<"       y = " << sideSlope << "x + " << offsetL << endl;
    cout<<"       y = " << sideSlope << "x + " << offsetR << endl;
}



