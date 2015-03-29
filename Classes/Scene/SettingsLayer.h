//
//  SettingsLayer.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__SettingsLayer__
#define __HillClimb__SettingsLayer__


#include <cocos/cocos2d.h>

USING_NS_CC;

class SettingsLayer : public Layer {
    
private:
	Menu *	menu;
	
	MenuItemToggle *		item_sound;
	MenuItemToggle *		item_music;
	MenuItemToggle *		item_speed;
	MenuItemToggle *		item_mode;
    
public:
    
    SettingsLayer();
    static Scene * scene();
};


#endif /* defined(__HillClimb__SettingsLayer__) */