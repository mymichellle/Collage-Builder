//
//  ToggleButton.h
//  Collage
//
//  Created by Michelle Alexander on 10/17/11.
//  Copyright 2011 ??? . All rights reserved.
//

#ifndef ToggleButton_h
#define ToggleButton_h

#include "BaseButton.h"
#include <string>

class ToggleButton: public BaseButton
{
private:
    // States
    bool mouseDownInButton;
    
public:
    ToggleButton(std::string s, int xCord, int yCord);
    bool mouse(int button, int state, int x, int y);
    void setSelected(bool s);
    bool getSelected(){return selected;};
};

#endif