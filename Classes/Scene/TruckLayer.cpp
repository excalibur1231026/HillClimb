//
//  TruckLayer.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#import "TruckLayer.h"

#include "DoodleTruck.h"

#import "MapLayer.h"
#import "StartLayer.h"

#import "XSprite.h"


Scene *TruckLayer::scene() {
    
    Scene * s = Scene::create();
    TruckLayer * layer = TruckLayer::create();
	s->addChild(layer);
	return	s;
}

TruckLayer::TruckLayer() {
    
    
}

bool TruckLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    cocos2d::Size s = Director::getInstance()->getWinSize();
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    
    Sprite * bg_sprite = XSprite::xspriteWithFile(IMG_SPRITE_BG);
    this->addChild(bg_sprite);
    bg_sprite->setPosition(Vec2(s.width/2, s.height/2));
    
    for (int i = 0; i < 3; i++) {

        char str1[100], str2[100];
        sprintf(str1, "truck_%d.png", i + 1);
        sprintf(str2, "truck_%d_sel.png", i + 1);
        
        std::string truck_nor = str1;
        std::string truck_sel = str2;
        Sprite *sprite_normals = XSprite::xspriteWithFile(truck_nor);
        Sprite *sprite_select = XSprite::xspriteWithFile(truck_sel);
        item_car[i] = MenuItemSprite::create(sprite_normals, sprite_select, NULL, this, menu_selector(TruckLayer::onCar));
        item_car[i]->setPosition(Vec2(s.width / 4.0f * (i + 1), s.height / 5.0f * 3));
    }
    
    Sprite *back_normal = XSprite::xspriteWithFile(IMG_BACK_NOR);
    Sprite *back_select = XSprite::xspriteWithFile(IMG_BACK_HIGH);
    MenuItemSprite *item_back = MenuItemSprite::create(back_normal, back_select, NULL, this, menu_selector(TruckLayer::onBack));
    Sprite *ok_normal = XSprite::xspriteWithFile(IMG_OK_NOR);
    Sprite *ok_select = XSprite::xspriteWithFile(IMG_OK_HIGH);
    MenuItemSprite *item_ok = MenuItemSprite::create(ok_normal, ok_select, NULL, this, menu_selector(TruckLayer::onOk));
				
    menu = Menu::create(item_car[0], item_car[1], item_car[2], item_back, item_ok, NULL);
    item_back->setPosition(Vec2(s.width / 2.0f - s.width / 5.0f, item_back->getContentSize().height));
    item_ok->setPosition(Vec2(s.width / 2.0f + s.width / 5.0f, item_ok->getContentSize().height));
    
    menu->setPosition(Vec2(s.width, 0));
    this->addChild(menu);
    item_car[doodleTruck->getTruckType()]->selected();
    doneEnter();
    
    return true;
}

void TruckLayer::doneEnter() {
    
    cocos2d::Size s = Director::getInstance()->getWinSize();
	
    MoveBy * moveAction = MoveBy::create(1, Vec2(-s.width, 0));
    
	menu->runAction(moveAction);
}

void TruckLayer::onCar(Ref * pSender) {
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
	for (int i = 0; i < 3; i++) {
		if (item_car[i] == pSender)
		{
			doodleTruck->setTruckType(i);
			item_car[i]->selected();
		} else {
			item_car[i]->unselected();
		}
	}
}

void TruckLayer::onBack(Ref * pSender) {
    
    cocos2d::Size s = Director::getInstance()->getWinSize();
    
    MoveBy * moveAction = MoveBy::create(1, Vec2(s.width, 0));
    Sequence * action = Sequence::create(moveAction, CallFunc::create(CC_CALLBACK_0(TruckLayer::doneBack, this)), NULL);
	menu->runAction(action);
}

void TruckLayer::onOk(Ref * pSender) {
    
    cocos2d::Size s = Director::getInstance()->getWinSize();
	
    MoveBy * moveAction = MoveBy::create(1, Vec2(-s.width, 0));
    Sequence * action = Sequence::create(moveAction, CallFunc::create(CC_CALLBACK_0(TruckLayer::doneOk, this)), NULL);
	menu->runAction(action);
}

void TruckLayer::doneBack() {
    
    Director::getInstance()->replaceScene(StartLayer::scene());
}

void TruckLayer::doneOk() {
    Director::getInstance()->replaceScene(MapLayer::scene());
}