//
//  XSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__XSprite__
#define __HillClimb__XSprite__

#import <cocos/cocos2d.h>

USING_NS_CC;

class XSprite : public Sprite {
    
public:
    
    ~XSprite();
    
    static Sprite * xspriteWithFile(std::string filename);
    static Sprite * xspriteWithFileWithYScale(std::string filename);
    
    XSprite(std::string filename, bool YScale);
    
    void xinitWithFile(std::string filename);
    void xinitWithFileWithYScale(std::string filename);
};


Texture2D* addXTexture(std::string filename);
Texture2D* addXTextureWithYScale(std::string filename);


#endif /* defined(__HillClimb__XSprite__) */