//
//  Truck.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "CoinManager.h"
#include "DoodleTruck.h"
#include "GameDefine.h"

CoinManager *coinManager = NULL;

static void
postStepRemove(cpSpace *space, cpShape *shape, void *unused)
{
    
    Sprite *sprite = (Sprite *)shape->data;
    MoveTo *action1 = MoveTo::create(1.0, sprite->getPosition() + Vec2(0, 150));
    FadeOut *action2 = FadeOut::create(1.0);
    Spawn *spawn = Spawn::create(action1, action2, NULL);
    sprite->runAction(spawn);
    
    cpSpaceRemoveBody(space, shape->body);
    cpSpaceRemoveShape(space, shape);
    
    cpShapeFree(shape);
    cpBodyFree(shape->body);
    
    if(sprite->getTag() == FUEL) {
        coinManager->setFuel(100);
    }
    if(sprite->getTag() == COIN500) {
        coinManager->addCoin(500);
    }
    if(sprite->getTag() == COIN100) {
        coinManager->addCoin(100);
    }
    if(sprite->getTag() == COIN25) {
        coinManager->addCoin(25);
    }
    if(sprite->getTag() == COIN5) {
        coinManager->addCoin(5);
    }
}

static int
begin(cpArbiter *arb, cpSpace *space, void *unused)
{
    // Get the cpShapes involved in the collision
    // The order will be the same as you defined in the handler definition
    // a->collision_type will be BULLET_TYPE and b->collision_type will be MONSTER_TYPE
    cpShape *a, *b; cpArbiterGetShapes(arb, &a, &b);
    
    // Alternatively you can use the CP_ARBITER_GET_SHAPES() macro
    // It defines and sets the variables for you.
    //CP_ARBITER_GET_SHAPES(arb, a, b);
    
    // Add a post step callback to safely remove the body and shape from the space.
    // Calling cpSpaceRemove*() directly from a collision handler callback can cause crashes.
    cpSpaceAddPostStepCallback(space, (cpPostStepFunc)postStepRemove, b, NULL);
    
    // The object is dead, don’t process the collision further
    return 0;
}

CoinManager::CoinManager() {
    
    coin = 0;
    fuel = 100;
    initCointData();
}

CoinManager * CoinManager::sharedCoinManager() {
    if(coinManager == NULL) {
        coinManager = new CoinManager();
    }
    return coinManager;
}

void CoinManager::initCointData() {
    coinData[0] = CoinData(1110, 464, 0);
    coinData[1] = CoinData(1920, 440, 1);
    coinData[2] = CoinData(3619, 460, 2);
    
}

int CoinManager::getCoin() {
    return coin;
}

void CoinManager::addCoin(int c) {
    coin += c;
}

float CoinManager::getFuel() {
    return fuel;
}

void CoinManager::setFuel(float f) {
    fuel = f;
}

std::string CoinManager::getCoinString() {
    
    char s[20];
    sprintf(s, "%d", coin);
    std::string str = s;
    int n = str.length();
    for(int i = 0; i < 6 - n; i++) {
        str = "0" + str;
    }
    str = str.substr(0, 3) + " " + str.substr(3);
    
    return str;
}

void CoinManager::setupChipmunk() {
    
}

void CoinManager::showCoinData(Layer *layer) {
    
    SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("coins.plist","coins.png");
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    cpSpace *space = doodleTruck->getSpace();
    
    for(int i = 0; i < 3; i++) {
        
        Sprite *sprite;
        
        if(coinData[i].type == FUEL) {
            sprite = Sprite::create("fuel-canister.png");
            sprite->setTag(0);
        } else if(coinData[i].type == COIN500) {
            sprite = Sprite::createWithSpriteFrameName("Coin500.png");
            sprite->setTag(1);
        } else if(coinData[i].type == COIN100) {
            sprite = Sprite::createWithSpriteFrameName("Coin100.png");
            sprite->setTag(2);
        } else if(coinData[i].type == COIN25) {
            sprite = Sprite::createWithSpriteFrameName("Coin25.png");
            sprite->setTag(3);
        } else if(coinData[i].type == COIN5) {
            sprite = Sprite::createWithSpriteFrameName("Coin5.png");
            sprite->setTag(4);
        }
        
        float mass = 1;
        cpBody * coin_body = cpBodyNew(mass, cpMomentForCircle(mass, 29, 29, cpvzero));
        cpShape *shape = cpCircleShapeNew(coin_body, 29, cpvzero);
        shape->group = BOX2D_COIN_GROUP;
        shape->collision_type = COIN_COLLISION;
        shape->data	= sprite;
        
        
        layer->addChild(sprite);
        sprite->setPosition(Vec2(coinData[i].x * doodleTruck->getScaleY(),
                                 coinData[i].y * doodleTruck->getScaleY()));
        
        cpSpaceAddShape(space, shape);
        coin_body->p.x = sprite->getPosition().x;
        coin_body->p.y = sprite->getPosition().y;
        coin_body->f = cpv(0, 500);
        cpSpaceAddBody(space, coin_body);
    }
    
    cpSpaceAddCollisionHandler(space, BODY_COLLISION, COIN_COLLISION, begin, NULL, NULL, NULL, NULL);
}


