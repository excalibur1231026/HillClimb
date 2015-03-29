//
//  StartLayer.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "GetCoinLayer.h"
#include "StartLayer.h"
#include "MenuButton.h"

Scene *GetCoinLayer::scene() {
    
    Scene * s = Scene::create();
    GetCoinLayer * layer = GetCoinLayer::create();
	s->addChild(layer);
	return	s;
}

GetCoinLayer::GetCoinLayer() {
   
}

bool GetCoinLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    Size s = Director::getInstance()->getWinSize();
    
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
    
    Layer *scroll_layer = Layer::create();
    scroll_layer->setAnchorPoint(Vec2(0, 0));
    
    int content_width = 0;
    int content_height = 0;
    
    int offset = 0;
    
    Vector<MenuButton *> menuArray;
    
    MenuButton *menuBtn1 = MenuButton::create("icon-morecoins.png", "videoplay-icon.png", "15000", "WATCH VIDEO", CallFunc::create(CC_CALLBACK_0(GetCoinLayer::onMenuClicked, this)));
    menuBtn1->attachSprite("save-free.png");
    MenuButton *menuBtn2 = MenuButton::create("icon-morecoins.png", "", "150 000 + AD FREE", "12.00", CallFunc::create(CC_CALLBACK_0(GetCoinLayer::onMenuClicked, this)));
    MenuButton *menuBtn3 = MenuButton::create("icon-morecoins.png", "", "3000 000 + AD FREE", "18.00", CallFunc::create(CC_CALLBACK_0(GetCoinLayer::onMenuClicked, this)));
    menuBtn3->attachSprite("save-25.png");
    MenuButton *menuBtn4 = MenuButton::create("icon-morecoins.png", "", "750 000 + AD FREE", "30.00", CallFunc::create(CC_CALLBACK_0(GetCoinLayer::onMenuClicked, this)));
    menuBtn4->attachSprite("save-50.png");
    MenuButton *menuBtn5 = MenuButton::create("icon-morecoins.png", "", "2 000 000", "68.00", CallFunc::create(CC_CALLBACK_0(GetCoinLayer::onMenuClicked, this)));
    menuBtn5->attachSprite("save-60.png");
    MenuButton *menuBtn6 = MenuButton::create("icon-morecoins.png", "", "4 000 000 + AD FREE", "98.00", CallFunc::create(CC_CALLBACK_0(GetCoinLayer::onMenuClicked, this)));
    menuBtn6->attachSprite("save-70.png");
    MenuButton *menuBtn7 = MenuButton::create("icon-morecoins.png", "", "8 000 000 + AD FREE", "163.00", CallFunc::create(CC_CALLBACK_0(GetCoinLayer::onMenuClicked, this)));
    menuBtn7->attachSprite("save-75.png");
    MenuButton *menuBtn8 = MenuButton::create("icon-morecoins.png", "", "20 000 000 + AD FREE", "328.00", CallFunc::create(CC_CALLBACK_0(GetCoinLayer::onMenuClicked, this)));
    menuBtn8->attachSprite("save-80.png");
    
    menuArray.pushBack(menuBtn1);
    menuArray.pushBack(menuBtn2);
    menuArray.pushBack(menuBtn3);
    menuArray.pushBack(menuBtn4);
    menuArray.pushBack(menuBtn5);
    menuArray.pushBack(menuBtn6);
    menuArray.pushBack(menuBtn7);
    menuArray.pushBack(menuBtn8);
    
    offset = menuBtn1->getContentSize().height / 2;
    
    for(int i = 7; i >= 0; i--) {
        
        MenuButton *menu_button = menuArray.at(i);
        scroll_layer->addChild(menu_button);
        
        menu_button->setPosition(Vec2(50 + menu_button->getContentSize().width / 2, offset));
        
        offset = menu_button->getContentSize().height + menu_button->getPosition().y + 10;
        
        content_width = menu_button->getContentSize().width + 150;
        content_height = offset;
    }
    
    content_height -= menuBtn1->getContentSize().height / 2 + 10;
    scrollView = ScrollView::create(Size(content_width + 50, s.height - 250), scroll_layer);
    scrollView->setDirection(ScrollView::Direction::VERTICAL);
    scrollView->setBounceable(true);
    
    scrollView->setTouchEnabled(true);
    scrollView->setPosition(Vec2(100, -sprite->getContentSize().height + 210));
    Size contentSize = Size(content_width, content_height);
    scrollView->setContentSize(contentSize);
    scrollView->setDelegate(this);
    
    this->addChild(scrollView);
    
    bar = ScrollBarView::create(scrollView, ScrollBarView::BarType::VERTICAL_OUT);
    
    MenuItemSprite *backBtn = MenuItemSprite::create(Sprite::create("back_button_normal.png"), Sprite::create("back_button_down.png"), NULL, this, menu_selector(GetCoinLayer::onBack));
    
    Menu * menu = Menu::create(backBtn, NULL);
    menu->alignItemsHorizontallyWithPadding(40);
    
    this->addChild(menu);
    menu->setPosition(Vec2(scrollView->getPosition().x + 180, 60));
    return true;
}

void GetCoinLayer::onBack(Ref *pSender) {
    
    Scene * scene = StartLayer::scene();
    Director::getInstance()->replaceScene(scene);
}

void GetCoinLayer::onButtonClick(Ref *pSender) {
    
}

void GetCoinLayer::onMenuClicked() {}

void GetCoinLayer::scrollViewDidScroll(ScrollView* view) {
    bar->refresh();
}
