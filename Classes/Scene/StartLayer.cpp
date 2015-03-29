//
//  StartLayer.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "StartLayer.h"
#include "StageLayer.h"
#include "GetCoinLayer.h"
#include "DirectionSprite.h"
#include "MenuButton.h"
#include "MoreLayer.h"

Scene *StartLayer::scene() {
    
    Scene * s = Scene::create();
    StartLayer * layer = StartLayer::create();
	s->addChild(layer);
	return	s;
}

StartLayer::StartLayer() {
   
}

bool StartLayer::init() {
    if(!Layer::init()) {
        return false;
    }
   
    initVehicleData();
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
    
    MenuItemSprite *moreBtn = MenuItemSprite::create(Sprite::create("more_button_normal.png"), Sprite::create("more_button_down.png"), NULL, this, menu_selector(StartLayer::onMore));
    MenuItemSprite *cointBtn = MenuItemSprite::create(Sprite::create("getcoin_button_normal.png"), Sprite::create("getcoin_button_down.png"), NULL, this, menu_selector(StartLayer::onGetCoin));
    MenuItemSprite *nextBtn = MenuItemSprite::create(Sprite::create("next_button_normal.png"), Sprite::create("next_button_down.png"), NULL, this, menu_selector(StartLayer::onNext));
    
    Menu * menu = Menu::create(moreBtn, cointBtn, nextBtn, NULL);
    menu->alignItemsHorizontallyWithPadding(40);
    
    this->addChild(menu);
    menu->setPosition(Vec2(s.width / 2.0f, s.height / 3 - 90));
    
    initVehicleView();
    
    this->schedule(schedule_selector(StartLayer::startSchedule));
    
    return true;
}

void StartLayer::initVehicleView() {
    
    cocos2d::Size s = Director::getInstance()->getWinSize();
    Layer *scroll_layer = Layer::create();
    scroll_layer->setAnchorPoint(Vec2(0, 0));
    
    int content_width = 0;
    int content_height = 0;
    
    int offset = 0;
    for(int i = 0; i < 23; i++) {
        
        Sprite * sprite = Sprite::create(vehicleData[i].small_file);
        
        if(i == 0)
            offset = ((s.width - 100) - sprite->getContentSize().width) / 2;
        sprite->setAnchorPoint(Vec2(0, 0));
        
        if(i != 0) {
            sprite->setScale(0.5);
        }
        sprite->setPosition(Vec2(offset, 0));
        offset += sprite->getContentSize().width * sprite->getScale() + 10;
        
        scroll_layer->addChild(sprite, 1);
        content_width = sprite->getContentSize().width + sprite->getPosition().x;
        content_height = sprite->getContentSize().height;
        
    }
    scroll_layer->setContentSize(Size(scroll_layer->getContentSize().width + offset, scroll_layer->getContentSize().height));
    
    scrollView = SelectiveScroll::create(Size(s.width - 100, content_height), scroll_layer);
    scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
    scrollView->setBounceable(true);
    
    scrollView->setTouchEnabled(true);
    scrollView->setPosition(Vec2(50, s.height / 2 - content_height / 2));
    Size contentSize = Size(content_width, content_height);
    scrollView->setContentSize(contentSize);

    this->addChild(scrollView, 160);
}

void StartLayer::startSchedule(float dt) {
    scrollView->drawSpriteUpdate();
}

void StartLayer::onMore(Ref *pSender) {
    Scene * scene = MoreLayer::scene();
    Director::getInstance()->replaceScene(scene);
}

void StartLayer::onGetCoin(Ref *pSender) {
    Scene * scene = GetCoinLayer::scene();
    Director::getInstance()->replaceScene(scene);
}

void StartLayer::onNext(Ref *pSender) {
    
    Scene * scene = StageLayer::scene();
    Director::getInstance()->replaceScene(scene);
}

void StartLayer::initVehicleData() {
    
    vehicleData[0] = VehicleData("JEEP", "car-icon-jeep.jpg", "car-icon-jeep.png", 1000);
    vehicleData[1] = VehicleData("MOTOCROSS BIKE", "car-icon-motocross-bike.jpg", "car-icon-motocross-bike.png", 75000);
    vehicleData[2] = VehicleData("MONSTER TRUCK", "car-icon-monster.jpg", "car-icon-monster.png", 100000);
    vehicleData[3] = VehicleData("TRACTOR", "car-icon-tractor.jpg", "car-icon-tractor.png", 120000);
    vehicleData[4] = VehicleData("HIPPIE VAN", "car-icon-hippievan.jpg", "car-icon-hippievan.png", 140000);
    vehicleData[5] = VehicleData("ONEWHEELER", "car-icon-onewheeler.jpg", "car-icon-onewheeler.png", 160000);
    vehicleData[6] = VehicleData("QUAD BIKE", "car-icon-quadbike.jpg", "car-icon-quadbike.png", 175000);
    vehicleData[7] = VehicleData("TOURIST BUS", "car-icon-touristbus.jpg", "car-icon-touristbus.png", 200000);
    vehicleData[8] = VehicleData("RACE CAR", "car-icon-racecar.jpg", "car-icon-racecar.png", 250000);
    vehicleData[9] = VehicleData("POLICE CAR", "car-icon-policecar.jpg", "car-icon-policecar.png", 350000);
    vehicleData[10] = VehicleData("AMBULANCE", "car-icon-ambulance.jpg", "car-icon-ambulance.png", 400000);
    vehicleData[11] = VehicleData("SUPER DIESEL 4X4", "car-icon-4x4.jpg", "car-icon-4x4.png", 430000);
    vehicleData[12] = VehicleData("RALLY CAR", "car-icon-rallycar.jpg", "car-icon-rallycar.png", 750000);
    vehicleData[13] = VehicleData("DRAGSTER", "car-icon-dragster.jpg", "car-icon-dragster.png", 800000);
    vehicleData[14] = VehicleData("TANK", "car-icon-tank.jpg", "car-icon-tank.png", 1000000);
    vehicleData[15] = VehicleData("SNOW MOBILE", "car-icon-snowmobile.jpg", "car-icon-snowmobile.png", 1000000);
    vehicleData[16] = VehicleData("TRUCK", "car-icon-truck.jpg", "car-icon-truck.png", 1000000);
    vehicleData[17] = VehicleData("DUNE BUGGY", "car-icon-dunebuggy.jpg", "car-icon-dunebuggy.png", 800000);
    vehicleData[18] = VehicleData("HOVERCRAFT", "car-icon-hovercraft.jpg", "car-icon-hovercraft.png", 1000000);
    vehicleData[19] = VehicleData("BIG FINGER", "car-icon-bigfinger.jpg", "car-icon-bigfinger.png", 1200000);
    vehicleData[20] = VehicleData("KIDDIE EXPRESS", "car-icon-train.jpg", "car-icon-train.png", 1500000);
    vehicleData[21] = VehicleData("MOONLANDER", "car-icon-moonlander.jpg", "car-icon-moonlander.png", 1500000);
    vehicleData[22] = VehicleData("SLEIGH", "car-icon-sleigh.jpg", "car-icon-sleigh.png", 1000000);
}

