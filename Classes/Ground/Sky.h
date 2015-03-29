//
//  Sky.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__Sky__
#define __HillClimb__Sky__

#include <cocos/cocos2d.h>
#include "chipmunk.h"

USING_NS_CC;

class Sky : public Node {

public:
    Sky();
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
};

#endif /* defined(__HillClimb__Sky__) */