//
//  StartLayer.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "MoreLayer.h"
#include "StartLayer.h"
#include "MenuButton.h"

Scene *MoreLayer::scene() {
    
    Scene * s = Scene::create();
    MoreLayer * layer = MoreLayer::create();
	s->addChild(layer);
	return	s;
}

MoreLayer::MoreLayer() {
   
}

bool MoreLayer::init() {
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
    
    MenuButton *menuBtn1 = MenuButton::create("icon-moreapps-moreapps.png", "", "FINGERSOFT GAMES & APPS", "", CallFunc::create(CC_CALLBACK_0(MoreLayer::onMenuClicked, this)));
    MenuButton *menuBtn2 = MenuButton::create("levelsgold.png", "", "ACHIEVEMENTS", "", CallFunc::create(CC_CALLBACK_0(MoreLayer::onMenuClicked, this)));
    MenuButton *menuBtn3 = MenuButton::create("icon-moreapps-highscores.png", "", "HIGH SCORES", "", CallFunc::create(CC_CALLBACK_0(MoreLayer::onMenuClicked, this)));
    MenuButton *menuBtn4 = MenuButton::create("icon-moreapps-merchandise.png", "", "MERCHANDISE", "", CallFunc::create(CC_CALLBACK_0(MoreLayer::onMenuClicked, this)));
    MenuButton *menuBtn5 = MenuButton::create("icon-scrolling-toggle.png", "", "SCROLLING BACKGROUND: ON", "", CallFunc::create(CC_CALLBACK_0(MoreLayer::onMenuClicked, this)));
    MenuButton *menuBtn6 = MenuButton::create("icon-replay.png", "", "ENABLE REPLAYS", "", CallFunc::create(CC_CALLBACK_0(MoreLayer::onMenuClicked, this)));
    MenuButton *menuBtn7 = MenuButton::create("icon-replay.png", "", "WATCH REPLAYS", "", CallFunc::create(CC_CALLBACK_0(MoreLayer::onMenuClicked, this)));
    MenuButton *menuBtn8 = MenuButton::create("icon-moreapps-share.png", "", "SHARE HILL CLIMB RACING", "", CallFunc::create(CC_CALLBACK_0(MoreLayer::onMenuClicked, this)));
    MenuButton *menuBtn9 = MenuButton::create("icon-moreapps-facebook.png", "",  "FINGERSOFT ON FACEBOOK", "", CallFunc::create(CC_CALLBACK_0(MoreLayer::onMenuClicked, this)));
    MenuButton *menuBtn10 = MenuButton::create("icon-moreapps-about.png", "", "ABOUT", "", CallFunc::create(CC_CALLBACK_0(MoreLayer::onMenuClicked, this)));
    MenuButton *menuBtn11 = MenuButton::create("icon-moreapps-about.png", "", "PRIVACY POLICY", "", CallFunc::create(CC_CALLBACK_0(MoreLayer::onMenuClicked, this)));
    
    menuArray.pushBack(menuBtn1);
    menuArray.pushBack(menuBtn2);
    menuArray.pushBack(menuBtn3);
    menuArray.pushBack(menuBtn4);
    menuArray.pushBack(menuBtn5);
    menuArray.pushBack(menuBtn6);
    menuArray.pushBack(menuBtn7);
    menuArray.pushBack(menuBtn8);
    menuArray.pushBack(menuBtn9);
    menuArray.pushBack(menuBtn10);
    menuArray.pushBack(menuBtn11);
    
    offset = menuBtn1->getContentSize().height / 2;
    
    for(int i = 10; i >= 0; i--) {
        
        MenuButton *menu_button = menuArray.at(i);
        scroll_layer->addChild(menu_button);
        
        menu_button->setPosition(Vec2(50 + menu_button->getContentSize().width / 2, offset));
        
        offset = menu_button->getContentSize().height + menu_button->getPosition().y + 10;
        
        content_width = menu_button->getContentSize().width;
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
    
    MenuItemSprite *backBtn = MenuItemSprite::create(Sprite::create("back_button_normal.png"), Sprite::create("back_button_down.png"), NULL, this, menu_selector(MoreLayer::onBack));
    
    Menu * menu = Menu::create(backBtn, NULL);
    menu->alignItemsHorizontallyWithPadding(40);
    
    this->addChild(menu);
    menu->setPosition(Vec2(scrollView->getPosition().x + 180, 60));
    return true;
}

void MoreLayer::onBack(Ref *pSender) {
    
    Scene * scene = StartLayer::scene();
    Director::getInstance()->replaceScene(scene);
}

void MoreLayer::onButtonClick(Ref *pSender) {
    
}

void MoreLayer::onMenuClicked() {}

void MoreLayer::scrollViewDidScroll(ScrollView* view) {
    bar->refresh();
}
