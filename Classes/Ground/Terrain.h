//
//  Terrain.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__Terrain__
#define __HillClimb__Terrain__

#include <cocos/cocos2d.h>
#include "chipmunk.h"

USING_NS_CC;

#define kMaxHillKeyPoints 1000
#define kHillSegmentWidth 5
#define kMaxHillVertices 4000
#define kMaxBorderVertices 800

class Terrain : public Node {
    
private:
    
    int _nHillVertices;
    Vec2 _hillVertices[kMaxHillVertices];
    Vec2 _hillTexCoords[kMaxHillVertices];
    int _nBorderVertices;
    Vec2 _borderVertices[kMaxBorderVertices];
    
    Vec2 _hillKeyPoints[125];
    Sprite * _stripes;
    
    int _fromKeyPointI;
    int _toKeyPointI;
    
    int _offsetX;
    
public:
    Terrain();
    
    void resetHillVertices();
    void setOffsetX(float newOffsetX);
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    void setupChipmunk();
    Sprite * generateStripesSprite();
    
};

#endif /* defined(__HillClimb__Terrain__) */