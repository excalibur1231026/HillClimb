//
//  XSprite.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#import "XSprite.h"
#import "CommonFunc.h"
#import "DoodleTruck.h"


XSprite::XSprite(std::string filename, bool YScale) {
    
    if(YScale) {
        xinitWithFileWithYScale(filename);
    } else {
        xinitWithFile(filename);
    }
}

Sprite * XSprite::xspriteWithFile(std::string filename) {
    
    Sprite *sprite = Sprite::create(filename);
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    
    if (doodleTruck->getScaleX() * doodleTruck->getScaleY() != 1.0f) {
        sprite->setScale(doodleTruck->getScaleX(), doodleTruck->getScaleY());
    } else {
        ;
    }
    return sprite;
}

Sprite * XSprite::xspriteWithFileWithYScale(std::string filename) {
    Sprite *sprite = Sprite::create(filename);
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    
    if (doodleTruck->getScaleX() * doodleTruck->getScaleY() != 1.0f) {
        sprite->setScale(doodleTruck->getScaleY(), doodleTruck->getScaleY());
    } else {
        ;
    }
    return sprite;
}


void XSprite::xinitWithFile(std::string filename) {
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    
    this->setTexture(filename);
    
	
	if (doodleTruck->getScaleX() * doodleTruck->getScaleY() != 1.0f) {
        this->setScale(doodleTruck->getScaleX(), doodleTruck->getScaleY());
	} else {
        ;
    }
}

void XSprite::xinitWithFileWithYScale(std::string filename) {
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    
    this->setTexture(filename);
    
	if (doodleTruck->getScaleX() * doodleTruck->getScaleY() != 1.0f) {
        this->setScale(doodleTruck->getScaleY(), doodleTruck->getScaleY());
	}
	else {
		;
	}
}

XSprite::~XSprite() {
    Director::getInstance()->getTextureCache()->removeTexture(this->getTexture());
}


Texture2D* addXTexture(std::string filename) {
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    
    Texture2D *tex = Director::getInstance()->getTextureCache()->addImage(filename);
    
	/*CGImageRef cg_image = getImageFromPNGFile(filename.UTF8String);
	int w = CGImageGetWidth(cg_image);
	int h = CGImageGetHeight(cg_image);
	
	if (doodleTruck->getScaleX() * doodleTruck->getScaleY() != 1.0f) {
		CGImageRef cg_scaledImage = getScaledImage(cg_image, w * doodleTruck.scaleX, h * doodleTruck.scaleY);
		CGImageRelease(cg_image);
		CCTexture2D *tex = [[CCTextureCache sharedTextureCache] addCGImage:cg_scaledImage forKey:filename];
		CGImageRelease(cg_scaledImage);
		return tex;
	}
	else {
		CCTexture2D *tex = [[CCTextureCache sharedTextureCache] addCGImage:cg_image forKey:filename];
		CGImageRelease(cg_image);
		return tex;
	}*/
    return tex;
}

Texture2D* addXTextureWithYScale(std::string filename)
{
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    
    Texture2D *tex = Director::getInstance()->getTextureCache()->addImage(filename);
    
    /*CGImageRef cg_image = getImageFromPNGFile(filename.UTF8String);
     int w = CGImageGetWidth(cg_image);
     int h = CGImageGetHeight(cg_image);
     
     if (doodleTruck->getScaleX() * doodleTruck->getScaleY() != 1.0f) {
     CGImageRef cg_scaledImage = getScaledImage(cg_image, w * doodleTruck.scaleX, h * doodleTruck.scaleY);
     CGImageRelease(cg_image);
     CCTexture2D *tex = [[CCTextureCache sharedTextureCache] addCGImage:cg_scaledImage forKey:filename];
     CGImageRelease(cg_scaledImage);
     return tex;
     }
     else {
     CCTexture2D *tex = [[CCTextureCache sharedTextureCache] addCGImage:cg_image forKey:filename];
     CGImageRelease(cg_image);
     return tex;
     }*/
    return tex;

	/*DoodleTruck *doodleTruck = [DoodleTruck sharedDoodleTruck];
	CGImageRef cg_image = getImageFromPNGFile(filename.UTF8String);
	int w = CGImageGetWidth(cg_image);
	int h = CGImageGetHeight(cg_image);
	
	if (doodleTruck.scaleX * doodleTruck.scaleY != 1.0f) {
		CGImageRef cg_scaledImage = getScaledImage(cg_image, w * doodleTruck.scaleY, h * doodleTruck.scaleY);
		CGImageRelease(cg_image);
		CCTexture2D *tex = [[CCTextureCache sharedTextureCache] addCGImage:cg_scaledImage forKey:filename];
		CGImageRelease(cg_scaledImage);
		return tex;
	}
	else {
		CCTexture2D *tex = [[CCTextureCache sharedTextureCache] addCGImage:cg_image forKey:filename];
		CGImageRelease(cg_image);
		return tex;
	}*/
}
