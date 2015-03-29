//
//  SelectiveScroll.cpp
//  SelectiveScroll
//
//  Created by TOSHITAKA NAKAGAWA on 2013/08/07.
//
//

#include "SelectiveScroll.h"

#define SCROLL_DEACCEL_RATE  0.95f
#define SCROLL_DEACCEL_DIST  1.0f
#define BOUNCE_DURATION      0.15f
#define INSET_RATIO          0.2f
#define MOVE_INCH            7.0f/160.0f
#define BOUNCE_BACK_FACTOR   0.35f

SelectiveScroll* SelectiveScroll::create(Size size, Node* container/* = nullptr*/)
{
    SelectiveScroll* pRet = new SelectiveScroll();
    if (pRet && pRet->initWithViewSize(size, container))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void SelectiveScroll::deaccelerateScrolling(float dt)
{
    
    if (_dragging)
    {
        this->unschedule(schedule_selector(SelectiveScroll::deaccelerateScrolling));
        return;
    }
    
    float newX, newY;
    Vec2 maxInset, minInset;
    
    _container->setPosition(_container->getPosition() + _scrollDistance);
    
    if (_bounceable)
    {
        maxInset = _maxInset;
        minInset = _minInset;
    }
    else
    {
        maxInset = this->maxContainerOffset();
        minInset = this->minContainerOffset();
    }
    
    newX = _container->getPosition().x;
    newY = _container->getPosition().y;
    
    _scrollDistance     = _scrollDistance * SCROLL_DEACCEL_RATE;
    this->setContentOffset(Vec2(newX, newY));
    
    if ((fabsf(_scrollDistance.x) <= SCROLL_DEACCEL_DIST &&
         fabsf(_scrollDistance.y) <= SCROLL_DEACCEL_DIST) ||
        newX >= maxInset.x || newX <= minInset.x)
    {
        this->unschedule(schedule_selector(SelectiveScroll::deaccelerateScrolling));
        this->relocateContainer(true);
        
        fixPosition();
    }
}

void SelectiveScroll::fixPosition() {
    
    Size s = Director::getInstance()->getWinSize();
    Vector<Node *> sprites = _container->getChildren();
    
    Node *temp = NULL;
    float scale = 0.0;
    for(int i = 0; i < sprites.size(); i++) {
        
        Node *sprite = sprites.at(i);
        if(sprite->getScale() > scale) {
            scale = sprite->getScale();
            temp = sprite;
        }
    }
    
    if(temp == NULL) return;
    
    int sprite_offset_x = s.width / 2 - (temp->getPosition().x + temp->getContentSize().width / 2 + _container->getPosition().x + this->getPosition().x);
    
    
    MoveTo * action = MoveTo::create(0.6, Vec2(_container->getPosition().x + sprite_offset_x * temp->getScale(), 0));
    _container->runAction(action);
}

void SelectiveScroll::setContentOffset(Vec2 offset, bool animated/* = false*/) {
    ScrollView::setContentOffset(offset, animated);
    
}

void SelectiveScroll::drawSpriteUpdate() {
    
    Size s = Director::getInstance()->getWinSize();
    Vector<Node *> sprites = _container->getChildren();
    
    for(int i = 0; i < sprites.size(); i++) {
        
        Node * sprite = sprites.at(i);
        
        int sprite_offset_x = fabs(s.width / 2 - (sprite->getPosition().x + sprite->getContentSize().width / 2 + _container->getPosition().x + this->getPosition().x));
        
        
        if(sprite_offset_x > sprite->getContentSize().width) sprite_offset_x = sprite->getContentSize().width;
        float scale = 0.5 * (float)sprite_offset_x / (float)sprite->getContentSize().width;
        
        sprite->setScale(1 - scale);
        
        if(i != 0) {
            Node *temp = sprites.at(i - 1);
            sprite->setPosition(Vec2(temp->getPosition().x + temp->getContentSize().width * temp->getScale() + 20, 0));
        }
    }
}

void SelectiveScroll::onTouchEnded(Touch* touch, Event* event)
{
    if (!this->isVisible())
    {
        return;
    }
    
    auto touchIter = std::find(_touches.begin(), _touches.end(), touch);
    
    if (touchIter != _touches.end())
    {
        if (_touches.size() == 1 && _touchMoved)
        {
            this->schedule(schedule_selector(SelectiveScroll::deaccelerateScrolling));
        }
        _touches.erase(touchIter);
    }
    
    if (_touches.size() == 0)
    {
        _dragging = false;
        _touchMoved = false;
    }
}