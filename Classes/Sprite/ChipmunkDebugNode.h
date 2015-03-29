//
// desc: ChipmunkDebugNode.h
//

#ifndef _CHIPMUNKDEBUGNODE_H_
#define _CHIPMUNKDEBUGNODE_H_

//
// includes
//
#include <cocos/cocos2d.h>
#include "chipmunk.h"

USING_NS_CC;
//
// struct ChipmunkDebugNode
//
struct ChipmunkDebugNode : cocos2d::Node
{
    //
    // static methods
    //
    static ChipmunkDebugNode *create(cpSpace *space);
    static void DrawShape(cpShape *shape, void *data);
    
    //
    // init
    //
    virtual bool init(cpSpace *space);
    
    //
    // overload draw
    //
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    
    //
    // variables
    //
    cpSpace *_space;
};

#endif // #ifndef _CHIPMUNKDEBUGNODE_H_