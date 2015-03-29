//
//  XSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__GetCoinLayer__
#define __HillClimb__GetCoinLayer__


#include <cocos/cocos2d.h>
#include "cocos-ext.h"
#include "ScrollBarView.h"


USING_NS_CC_EXT;
USING_NS_CC;

class GetCoinLayer : public Layer, public ScrollViewDelegate {
    
private:
    Menu *	menu;
    
    ScrollView *scrollView;
    ScrollBarView *bar;
public:
    GetCoinLayer();
    
    CREATE_FUNC(GetCoinLayer);
    
    virtual bool init();
    static Scene * scene();
    
    void onMenuClicked();
    void onButtonClick(Ref *pSender);
    virtual void scrollViewDidScroll(ScrollView* view);
    
    void onBack(Ref *pSender);
};


#endif /* defined(__HillClimb__GetCoinLayer__) */