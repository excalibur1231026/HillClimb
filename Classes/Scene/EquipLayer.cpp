//
//  StartLayer.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "EquipLayer.h"
#include "StageLayer.h"
#include "PlayLayer.h"
#include "GetCoinLayer.h"

Scene * EquipLayer::scene() {
    
    Scene * s = Scene::create();
    EquipLayer * layer = EquipLayer::create();
	s->addChild(layer);
	return	s;
}

EquipLayer::EquipLayer() {
   
}

bool EquipLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    cocos2d::Size s = Director::getInstance()->getWinSize();
    
    LayerColor *lc = LayerColor::create(Color4B(0x2C, 0x30, 0x33, 255));
    addChild(lc);
    
    Sprite *sprite = Sprite::create("bar.png");
    sprite->setScale(s.width / sprite->getContentSize().width,
                     s.height / 6 / sprite->getContentSize().height);
    this->addChild(sprite);
    sprite->setPosition(Vec2(s.width / 2, s.height - s.height / 12));
    
    Sprite *coin_sprite = Sprite::create("coin-icon.png");
    this->addChild(coin_sprite);
    coin_sprite->setPosition(Vec2(20 + coin_sprite->getContentSize().width / 2, sprite->getPosition().y));
    
    Label *coin_label = Label::createWithTTF("734 333", "AGENCYR.TTF", 55);
    this->addChild(coin_label);
    coin_label->setPosition(Vec2(coin_sprite->getPosition().x + coin_sprite->getContentSize().width / 2 + 10 + coin_label->getContentSize().width / 2, sprite->getPosition().y));
    
    MenuItemSprite *stageBtn = MenuItemSprite::create(Sprite::create("stage_button_normal.png"), Sprite::create("stage_button_down.png"), NULL, this, menu_selector(EquipLayer::onStage));
    MenuItemSprite *cointBtn = MenuItemSprite::create(Sprite::create("getcoin_button_normal.png"), Sprite::create("getcoin_button_down.png"), NULL, this, menu_selector(EquipLayer::onGetCoin));
    MenuItemSprite *startBtn = MenuItemSprite::create(Sprite::create("start_button_normal.png"), Sprite::create("start_button_down.png"), NULL, this, menu_selector(EquipLayer::onStart));
    
    Menu * menu = Menu::create(stageBtn, cointBtn, startBtn, NULL);
    menu->alignItemsHorizontallyWithPadding(40);
    
    this->addChild(menu);
    menu->setPosition(Vec2(s.width / 2.0f, s.height / 3 - 90));
    
    Sprite * car_sprite = Sprite::create("stage-icon-countryside.png");
    this->addChild(car_sprite);
    car_sprite->setPosition(Vec2(s.width / 2, s.height / 2));
    return true;
}

void EquipLayer::onStage(Ref *pSender) {
    
    Scene * scene = StageLayer::scene();
    Director::getInstance()->replaceScene(scene);
}

void EquipLayer::onGetCoin(Ref *pSender) {
    Scene * scene = GetCoinLayer::scene();
    Director::getInstance()->replaceScene(scene);
}

void EquipLayer::onStart(Ref *pSender) {
    
    Scene * scene = PlayLayer::scene();
    Director::getInstance()->replaceScene(scene);
}
