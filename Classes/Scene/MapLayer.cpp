//
//  MapLayer.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#import "MapLayer.h"

#include "DoodleTruck.h"

#include "TruckLayer.h"
#include "PlayLayer.h"
#include "LabelInfo.h"
#include "XSprite.h"


Scene * MapLayer::scene() {
    Scene * s = Scene::create();
    MapLayer * layer = MapLayer::create();
    s->addChild(layer);
    
	return	s;
}

MapLayer::MapLayer() {
	
}

bool MapLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    cocos2d::Size s = Director::getInstance()->getWinSize();
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    
    Sprite * bg_sprite = XSprite::xspriteWithFile(IMG_SPRITE_BG);
    this->addChild(bg_sprite);
    
    bg_sprite->setPosition(Vec2(s.width/2, s.height/2));
    
    int cols = MAX_MAP / 2;
    for (int i = 0; i < MAX_MAP; i++) {
        
        char s1[100], s2[100];
        sprintf(s1, "select level_%02d_nml.png", i + 1);
        sprintf(s2, "select level_%02d_act.png", i + 1);
        
        std::string level_nml = s1;
        std::string level_act = s2;
        
        Sprite *level_normal = XSprite::xspriteWithFile(level_nml);
        Sprite *level_select = XSprite::xspriteWithFile(level_act);
        //MenuItemSprite *item = [CCMenuItemImage itemFromNormalSprite:level_normal selectedSprite:level_select target:self selector:@selector(onMap:)];
        
        //MenuItemSprite *[item = MenuItemImage::create(level_normal, level_select, <#const std::string &disabledImage#>, //);
        MenuItemSprite* item = MenuItemSprite::create(level_normal, level_select, NULL, this, menu_selector(MapLayer::onMap));
        
        map_menu[i] = item;
        int col = i % cols + 1;
        int row = i / cols;
        item->setPosition(Vec2(s.width / (cols + 1) * col, s.height / 4.0f * (3 - row)));
        
        int recorded_count = getRecordedCount(i);
        int star_index = 0;
        if (recorded_count >= getFineStoneNum(i))
            star_index = 2;
        else if (recorded_count >= getPassStoneNum(i))
            star_index = 1;
        
        if (star_index) {
            Sprite *star_sprite = XSprite::xspriteWithFile("");//:[NSString stringWithFormat:@"star_%d.png", star_index]];
            item->addChild(star_sprite);
            star_sprite->setPosition(Vec2(star_sprite->getContentSize().width /2, star_sprite->getContentSize().height /2));
        }
    }
    menu = Menu::createWithItem(map_menu[0]);
    
    
    for (int i = 1; i < MAX_MAP; i++)
        menu->addChild(map_menu[i]);
    
    map_menu[doodleTruck->getMapIndex()]->selected();
    
    Sprite *back_normal = XSprite::xspriteWithFile(IMG_BACK_NOR);
    Sprite *back_select = XSprite::xspriteWithFile(IMG_BACK_HIGH);
    MenuItemSprite* item_back = MenuItemSprite::create(back_normal, back_select, NULL, this, menu_selector(MapLayer::onBack));
    
    Sprite *ok_normal = XSprite::xspriteWithFile(IMG_OK_NOR);
    Sprite *ok_select = XSprite::xspriteWithFile(IMG_OK_HIGH);
    MenuItemSprite* item_ok = MenuItemSprite::create(ok_normal, ok_select, NULL, this, menu_selector(MapLayer::onOk));
    
    menu->addChild(item_back);
    menu->addChild(item_ok);
    item_back->setPosition(Vec2(s.width / 2.0f - s.width / 5.0f, item_back->getContentSize().height));
    item_ok->setPosition(Vec2(s.width / 2.0f + s.width / 5.0f, item_ok->getContentSize().height));
    
    menu->setPosition(Vec2(s.width, 0));
    
    this->addChild(menu);
    
    doneEnter();
    
    return true;
}

void MapLayer::onMap(Object *pSender) {
    
    DoodleTruck * doodleTruck = DoodleTruck::sharedDoodleTruck();
	for (int i = 0; i < MAX_MAP; i++) 
	{
		if (map_menu[i] == pSender) {
            map_menu[i]->selected();
			doodleTruck->setMapIndex(i);
		} else {
			map_menu[i]->unselected();
		}
	}
}

void MapLayer::onBack(Object *pSender) {
    
    cocos2d::Size s= Director::getInstance()->getWinSize();
	MoveBy * moveAction = MoveBy::create(1, Vec2(s.width, 0));
    Sequence *action = Sequence::create(moveAction, CallFunc::create(CC_CALLBACK_0(MapLayer::doneBack, this)), NULL);
    menu->runAction(action);
	
}

void MapLayer::onOk(Object *pSender) {
    
    cocos2d::Size s = Director::getInstance()->getWinSize();
    MoveBy * moveAction = MoveBy::create(1, Vec2(-s.width, 0));
    Sequence *action = Sequence::create(moveAction, CallFunc::create(CC_CALLBACK_0(MapLayer::doneOk, this)), NULL);
	menu->runAction(action);
}

void MapLayer::doneEnter() {
    
	cocos2d::Size s = Director::getInstance()->getWinSize();
    
    MoveBy * moveAction = MoveBy::create(1, Vec2(-s.width, 0));
    
    menu->runAction(moveAction);
}

void MapLayer::doneBack() {
    
    Director::getInstance()->replaceScene(TruckLayer::scene());
}


void MapLayer::doneOk() {
    Director::getInstance()->replaceScene(PlayLayer::scene());
}

