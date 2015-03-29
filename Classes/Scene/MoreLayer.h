//
//  XSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__MoreLayer__
#define __HillClimb__MoreLayer__


#include <cocos/cocos2d.h>
#include "cocos-ext.h"
#include "ScrollBarView.h"


USING_NS_CC_EXT;
USING_NS_CC;

class MoreLayer : public Layer, public ScrollViewDelegate {
    
private:
    Menu *	menu;
    
    ScrollView *scrollView;
    ScrollBarView *bar;
public:
    MoreLayer();
    
    CREATE_FUNC(MoreLayer);
    
    virtual bool init();
    static Scene * scene();
    
    void onMenuClicked();
    void onButtonClick(Ref *pSender);
    virtual void scrollViewDidScroll(ScrollView* view);
    
    void onBack(Ref *pSender);
};


#endif /* defined(__HillClimb__MoreLayer__) */