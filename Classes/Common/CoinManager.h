//
//  GameObject.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__CoinManager__
#define __HillClimb__CoinManager__

#include <cocos/cocos2d.h>

USING_NS_CC;

enum {
    FUEL,
    COIN500,
    COIN100,
    COIN25,
    COIN5
};

struct CoinData {
    float x;
    float y;
    int type;   // 0: fuel, 1: 500, 2: 100, 3: 25, 4: 5
    
    CoinData(float _x, float _y, int _type)
    {
        x = _x;
        y = _y;
        type = _type;
    };
    
    CoinData() {
        x = 0;
        y = 0;
        type = -1;
    }
};


class CoinManager {
    
private:
    CoinData coinData[3];
    int coin;
    float fuel;
    
public:
    // contructor
    CoinManager();
    
    static CoinManager * sharedCoinManager();
    
    void initCointData();
    void showCoinData(Layer *layer);
    void setupChipmunk();
    
    int getCoin();
    void addCoin(int c);
    
    float getFuel();
    void setFuel(float f);
    
    std::string getCoinString();

};

#endif /* defined(__HillClimb__CoinManager__) */
