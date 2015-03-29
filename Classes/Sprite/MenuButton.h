//
//  MenuButton.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__MenuButton__
#define __HillClimb__MenuButton__


#include <cocos/cocos2d.h>

USING_NS_CC;

class MenuButton : public Layer {
    
private:
	
    std::string         _icon1;
    std::string         _icon2;
    std::string         _text1;
    std::string         _text2;
    
    Sprite *            background_sprite;
    Sprite *            attach;
    Label *             left_label;
    Label *             right_label;
    
    Texture2D *         normalTex;
    Texture2D *         downTex;
    
    bool                isTouched;
    
    CallFunc *          _callFunc;
    
public:
    
    MenuButton(std::string icon1, std::string icon2, std::string text1, std::string text2, CallFunc *callFunc);
    
    static MenuButton * create(std::string icon1, std::string icon2, std::string text1, std::string text2, CallFunc *callFunc);
    
    /**
     * Initialize menubutton
     */
    bool init();
    
    Size getContentSize();
    cocos2d::Rect rectInPixels();
    void attachSprite(std::string file);
    bool containsTouchLocation(Touch *touch);
    
    void setLeftText(std::string text);
    void setRightText(std::string text);
    std::string getLeftText();
    std::string getRightText();
    
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent);
    
};

#endif /* defined(__HillClimb__MenuButton__) */