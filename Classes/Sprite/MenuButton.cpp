//
//  MenuButton.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//


#include "MenuButton.h"
#include "XSprite.h"

MenuButton * MenuButton::create(std::string icon1,
                                std::string icon2,
                                std::string text1,
                                std::string text2,
                                CallFunc *callFunc) {
    
    MenuButton *mb = new MenuButton(icon1, icon2, text1, text2, callFunc);
    if ( ! mb->init() )
    {
        CC_SAFE_DELETE(mb);
        return nullptr;
    }
    
    mb->autorelease();
    return mb;
}

MenuButton::MenuButton(std::string icon1,
                       std::string icon2,
                       std::string text1,
                       std::string text2,
                       CallFunc *callFunc) {
    
    this->_icon1 = icon1;
    this->_icon2 = icon2;
    this->_text1 = text1;
    this->_text2 = text2;
    this->_callFunc = callFunc;
    this->_callFunc->retain();
}

bool MenuButton::init()  {
    
    isTouched = false;
    
    attach = NULL;
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(MenuButton::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(MenuButton::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(MenuButton::onTouchesEnded, this);
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    normalTex = addXTexture("wide-button-bg-normal.png");
    downTex = addXTexture("wide-button-bg-down.png");
    int x, y;
    
    Sprite *icon1 = NULL, *icon2 = NULL;
    background_sprite = Sprite::create("wide-button-bg-normal.png");
    addChild(background_sprite);
    
    if(_icon1 != "") {
        icon1 = Sprite::create(_icon1);
        icon1->setScale((background_sprite->getContentSize().height - 30) / icon1->getContentSize().height);
        addChild(icon1);
        int x = background_sprite->getPosition().x - background_sprite->getContentSize().width / 2 + icon1->getContentSize().width * icon1->getScale() / 2 + 10;
        int y = 2;
        icon1->setPosition(Vec2(x, y));
    }
    
    if(_icon2 != "") {
        icon2 = Sprite::create(_icon2);
        icon2->setScale((background_sprite->getContentSize().height - 30) / icon2->getContentSize().height);
        addChild(icon2);
        x = background_sprite->getPosition().x + background_sprite->getContentSize().width / 2 - icon2->getContentSize().width * icon2->getScale() / 2 - 10;
        y = 2;
        icon2->setPosition(Vec2(x, y));
    }
    
    left_label = Label::createWithTTF(_text1, "AGENCYR.TTF", 50);
    addChild(left_label);
    
    x = -background_sprite->getContentSize().width / 2 + 10 + left_label->getContentSize().width / 2;
    y = 2;
    if(icon1 != NULL) {
        x += icon1->getContentSize().width * icon1->getScale() + 10;
    }
    left_label->setPosition(Vec2(x, y));
    
    right_label = Label::createWithTTF(_text2, "AGENCYR.TTF", 40);
    addChild(right_label);
    
    x = background_sprite->getContentSize().width / 2 - 10 - right_label->getContentSize().width / 2;
    y = 2;
    if(icon2 != NULL) {
        x -= icon1->getContentSize().width * icon1->getScale() + 10;
    }
    right_label->setPosition(Vec2(x, y));
    
    return true;
}

void MenuButton::attachSprite(std::string file) {
    
    attach = Sprite::create(file);
    attach->setScale((background_sprite->getContentSize().height - 30 ) / attach->getContentSize().height);
    addChild(attach);
    int x, y;
    x = background_sprite->getContentSize().width / 2 + attach->getContentSize().width * attach->getScale() / 2 + 10;
    y = 2;
    attach->setPosition(Vec2(x, y));
}

void MenuButton::setLeftText(std::string text) {
    
    if(left_label == NULL) return;
    _text1 = text;
    
    left_label->setString(text);
}

void MenuButton::setRightText(std::string text) {
    if(right_label == NULL) return;
    _text2 = text;
    
    right_label->setString(text);
}

std::string MenuButton::getLeftText() {
    return _text1;
}

std::string MenuButton::getRightText() {
    return _text2;
}

Size MenuButton::getContentSize() {
    
  //  if(attach == NULL) {
        return background_sprite->getContentSize();
    /*} else {
        Size size = background_sprite->getContentSize();
        size.width += attach->getContentSize().width + 10;
        
        return size;
    }*/
}

cocos2d::Rect MenuButton::rectInPixels() {
    
    cocos2d::Size s = background_sprite->getTexture()->getContentSizeInPixels();
    return cocos2d::Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool MenuButton::containsTouchLocation(Touch *touch) {
    
    cocos2d::Point p = this->convertTouchToNodeSpaceAR(touch);
    cocos2d::Rect r = this->rectInPixels();
    
    if(r.origin.x <= p.x && r.origin.x + r.size.width >= p.x &&
       r.origin.y <= p.y && r.origin.y + r.size.height >= p.y) {
        return true;
    } else {
        return false;
    }
}

void MenuButton::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent) {
    
    if (this->containsTouchLocation(touches[0])) {
        background_sprite->setTexture(downTex);
        isTouched = true;
    }
    /*background_sprite->getl
    Rect rect = background_sprite->getBoundingBox();
    rect.origin.x += this->getPosition().x;
    rect.origin.y += this->getPosition().y;
    if(rect.containsPoint(touches[0]->getLocation())) {
        background_sprite->setTexture(downTex);
        isTouched = true;
    }*/
}

void MenuButton::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent) {
    if(isTouched) {
        background_sprite->setTexture(normalTex);
        isTouched = false;
    }
    
    Rect rect = background_sprite->getBoundingBox();
    rect.origin.x += this->getPosition().x;
    rect.origin.y += this->getPosition().y;
    if(rect.containsPoint(touches[0]->getLocation())) {
        _callFunc->execute();
    }
}