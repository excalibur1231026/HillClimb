//
//  StartLayer.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "StageLayer.h"
#include "StartLayer.h"
#include "EquipLayer.h"
#include "GetCoinLayer.h"

Scene *StageLayer::scene() {
    
    Scene * s = Scene::create();
    StageLayer * layer = StageLayer::create();
	s->addChild(layer);
	return	s;
}

StageLayer::StageLayer() {
   
}

bool StageLayer::init() {
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
    
    MenuItemSprite *vehicleBtn = MenuItemSprite::create(Sprite::create("vehicle_button_normal.png"), Sprite::create("vehicle_button_down.png"), NULL, this, menu_selector(StageLayer::onVehicle));
    MenuItemSprite *cointBtn = MenuItemSprite::create(Sprite::create("getcoin_button_normal.png"), Sprite::create("getcoin_button_down.png"), NULL, this, menu_selector(StageLayer::onGetCoin));
    MenuItemSprite *nextBtn = MenuItemSprite::create(Sprite::create("next_button_normal.png"), Sprite::create("next_button_down.png"), NULL, this, menu_selector(StageLayer::onNext));
    
    Menu * menu = Menu::create(vehicleBtn, cointBtn, nextBtn, NULL);
    menu->alignItemsHorizontallyWithPadding(40);
    
    this->addChild(menu);
    menu->setPosition(Vec2(s.width / 2.0f, s.height / 3 - 90));
    
    initStageData();
    initStageView();
    return true;
}

void StageLayer::initStageData() {
    
    stageData[0] = StageData("COUNTRYSIDE", "stage-icon-countryside.png", "lowres-stage-icon-countryside.png", 1000);
    stageData[1] = StageData("DESERT", "stage-icon-desert.png", "lowres-stage-icon-desert.png", 75000);
    stageData[2] = StageData("ARCTIC", "stage-icon-arctic.png", "lowres-stage-icon-arctic.png", 100000);
    stageData[3] = StageData("HIGHWAY", "stage-icon-highway.png", "lowres-stage-icon-highway.png", 120000);
    stageData[4] = StageData("CAVE", "stage-icon-cave.png", "lowres-stage-icon-cave.png", 140000);
    stageData[5] = StageData("MOON", "stage-icon-moon.png", "lowres-stage-icon-moon.png", 160000);
    stageData[6] = StageData("MARS", "stage-icon-mars.png", "lowres-stage-icon-mars.png", 175000);
    stageData[7] = StageData("XMAS", "stage-icon-xmas.png", "lowres-stage-icon-xmas.png", 200000);
    stageData[8] = StageData("ALIEN PLANET", "stage-icon-alienplanet.png", "lowres-stage-icon-alienplanet.png", 250000);
    stageData[9] = StageData("ARCTIC CAVE", "stage-icon-arctic-cave.png", "lowres-stage-icon-arctic-cave.png", 350000);
    stageData[10] = StageData("FOREST", "stage-icon-forest.png", "lowres-stage-icon-forest.png", 400000);
    stageData[11] = StageData("MOUNTAIN", "stage-icon-cliffs.png", "lowres-stage-icon-cliffs.png", 430000);
    stageData[12] = StageData("MUDPOOL", "stage-icon-mud.png", "lowres-stage-icon-mud.png", 750000);
    stageData[13] = StageData("VOLCANO", "stage-icon-volcano.png", "lowres-stage-icon-volcano.png", 800000);
    stageData[14] = StageData("BEACH", "stage-icon-beach.png", "lowres-stage-icon-beach.png", 1000000);
    stageData[15] = StageData("ROLLER COASTER", "stage-icon-rollercoaster.png", "lowres-stage-icon-rollercoaster.png", 1000000);
    stageData[16] = StageData("NIGHT", "stage-icon-night.png", "lowres-stage-icon-night.png", 1000000);
    stageData[17] = StageData("ROOFTOPS", "stage-icon-rooftops.png", "lowres-stage-icon-rooftops.png", 1000000);
    stageData[18] = StageData("JUNKYARD", "stage-icon-junkyard.png", "lowres-stage-icon-junkyard.png", 800000);
    stageData[19] = StageData("CONSTRUCTION", "stage-icon-construction.png", "lowres-stage-icon-construction.png", 1000000);
    stageData[20] = StageData("RAINBOW", "stage-icon-rainbow.png", "lowres-stage-icon-rainbow.png", 1200000);
    stageData[21] = StageData("HAUNTED", "stage-icon-haunted.png", "lowres-stage-icon-haunted.png", 1500000);
    stageData[22] = StageData("NORTHPOLE", "stage-icon-northpole.png", "lowres-stage-icon-northpole.png", 1500000);
    
    this->schedule(schedule_selector(StageLayer::startSchedule));
}

void StageLayer::startSchedule(float dt) {
    scrollView->drawSpriteUpdate();
}

void StageLayer::initStageView() {
    
    cocos2d::Size s = Director::getInstance()->getWinSize();
    Layer *scroll_layer = Layer::create();
    scroll_layer->setAnchorPoint(Vec2(0, 0));
    
    int content_width = 0;
    int content_height = 0;
    
    int offset = 0;
    for(int i = 0; i < 23; i++) {
        
        Sprite * sprite = Sprite::create(stageData[i].small_file);
        
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

void StageLayer::onVehicle(Ref *pSender) {
    
    Scene * scene = StartLayer::scene();
    Director::getInstance()->replaceScene(scene);
}

void StageLayer::onGetCoin(Ref *pSender) {
    
    Scene * scene = GetCoinLayer::scene();
    Director::getInstance()->replaceScene(scene);
}

void StageLayer::onNext(Ref *pSender) {
    
    Scene * scene = EquipLayer::scene();
    Director::getInstance()->replaceScene(scene);
}
