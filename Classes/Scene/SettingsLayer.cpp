//
//  SettingsLayer.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#import "SettingsLayer.h"

#import "DoodleTruck.h"
#import "TruckLayer.h"
#import "XSprite.h"

Scene *	SettingsLayer::scene() {
    
    Scene * s = Scene::create();
	SettingsLayer * layer = new SettingsLayer();
	s->addChild(layer);
	return	s;
}

SettingsLayer::SettingsLayer() {

    cocos2d::Size s = Director::getInstance()->getWinSize();
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
		
    Sprite * bg_sprite = XSprite::xspriteWithFile(IMG_SPRITE_SET_BG);
    this->addChild(bg_sprite);
    bg_sprite->setPosition(Vec2(s.width/2, s.height/2));
		
    MenuItemSprite *item_sound_title = MenuItemSprite::create(XSprite::xspriteWithFile(IMG_SOUND), NULL);
    item_sound_title->setEnabled(false);
		
    MenuItemSprite *item_on = MenuItemSprite::create(XSprite::xspriteWithFile(IMG_SOUND_ON), XSprite::xspriteWithFile(IMG_SOUND_ON));
    MenuItemSprite *item_off = MenuItemSprite::create(XSprite::xspriteWithFile(IMG_SOUND_OFF), XSprite::xspriteWithFile(IMG_SOUND_OFF));
	/*
    item_sound = MenuItemToggle::create itemWithTarget:self selector:@selector(onSound) items:item_on, item_off, nil];
		
		CCMenuItemSprite *item_music_title = [CCMenuItemSprite itemFromNormalSprite:[XSprite xspriteWithFile:IMG_MUSIC] selectedSprite:[XSprite xspriteWithFile:IMG_MUSIC]];
		[item_music_title setIsEnabled:NO];
		
		CCMenuItemSprite *item_music_on = [CCMenuItemSprite itemFromNormalSprite:[XSprite xspriteWithFile:IMG_SOUND_ON] selectedSprite:[XSprite xspriteWithFile:IMG_SOUND_ON]];
		CCMenuItemSprite *item_music_off = [CCMenuItemSprite itemFromNormalSprite:[XSprite xspriteWithFile:IMG_SOUND_OFF] selectedSprite:[XSprite xspriteWithFile:IMG_SOUND_OFF]];
		
		item_music = [CCMenuItemToggle itemWithTarget:self selector:@selector(onMusic) items:item_music_on, item_music_off, nil];
		
		CCMenuItemSprite *item_speed_title = [CCMenuItemSprite itemFromNormalSprite:[XSprite xspriteWithFile:IMG_SPEED] selectedSprite:[XSprite xspriteWithFile:IMG_SPEED]];
		[item_speed_title setIsEnabled:NO];
		
		CCMenuItemSprite *item_slow = [CCMenuItemSprite itemFromNormalSprite:[XSprite xspriteWithFile:IMG_SLOW] selectedSprite:[XSprite xspriteWithFile:IMG_SLOW]];
		CCMenuItemSprite *item_normal = [CCMenuItemSprite itemFromNormalSprite:[XSprite xspriteWithFile:IMG_NORMAL] selectedSprite:[XSprite xspriteWithFile:IMG_NORMAL]];
		CCMenuItemSprite *item_fast = [CCMenuItemSprite itemFromNormalSprite:[XSprite xspriteWithFile:IMG_FAST] selectedSprite:[XSprite xspriteWithFile:IMG_FAST]];
				
		item_speed = [CCMenuItemToggle itemWithTarget:self selector:@selector(onSpeed) items:item_slow, item_normal, item_fast, nil];
		
		CCMenuItemSprite *item_mode_title = [CCMenuItemSprite itemFromNormalSprite:[XSprite xspriteWithFile:IMG_GAMEMODE] selectedSprite:[XSprite xspriteWithFile:IMG_GAMEMODE]];
		[item_mode_title setIsEnabled:NO];
		
		CCMenuItemSprite *item_freemode = [CCMenuItemSprite itemFromNormalSprite:[XSprite xspriteWithFile:IMG_FREEMODE] selectedSprite:[XSprite xspriteWithFile:IMG_FREEMODE]];
		CCMenuItemSprite *item_timemode = [CCMenuItemSprite itemFromNormalSprite:[XSprite xspriteWithFile:IMG_TIMEMODE] selectedSprite:[XSprite xspriteWithFile:IMG_TIMEMODE]];
		
		item_mode = [CCMenuItemToggle itemWithTarget:self selector:@selector(onMode) items:item_freemode, item_timemode, nil];
		
		CCMenuItemSprite *item_ok = [CCMenuItemSprite itemFromNormalSprite:[XSprite xspriteWithFile:IMG_OK_NOR] selectedSprite:[XSprite xspriteWithFile:IMG_OK_HIGH] target:self selector:@selector(onOk)];
		
		menu = [CCMenu menuWithItems:item_sound_title , item_music_title, item_sound, item_music, item_speed_title, item_speed, item_mode_title, item_mode, item_ok, nil];
		
		[self addChild:menu];
		
		menu.position = ccp(s.width, 0);
		
		item_sound_title.position = ccp(s.width/3, s.height/6 * 5);
		item_sound.position = ccp(s.width/3 * 2, s.height/6 * 5);
		item_music_title.position = ccp(s.width/3, s.height/3 * 2);
		item_music.position = ccp(s.width/3 * 2, s.height/ 3 * 2);
		item_speed_title.position = ccp(s.width/3, s.height/2);
		item_speed.position = ccp(s.width/3 * 2, s.height/2);
		item_mode_title.position = ccp(s.width/3, s.height/3);
		item_mode.position = ccp(s.width/3 * 2, s.height/3);
		item_ok.position = ccp(s.width/2, s.height/6);
		
		[item_sound setSelectedIndex:doodleTruck.soundEnabled ? 0 : 1];
		[item_music setSelectedIndex:doodleTruck.musicEnabled ? 0 : 1];
		[item_mode setSelectedIndex:doodleTruck.mode];
		[item_speed setSelectedIndex:doodleTruck.speedSence];
		
		[self performSelector:@selector(doneEnter)];
	}
	return self;*/
}
/*
-(void)	doneEnter
{
	CGSize s = [[CCDirector sharedDirector] winSize];
	id moveAction = [CCMoveBy actionWithDuration:1 position:ccp(-s.width, 0)];
	[menu runAction:moveAction];
	
}

-(void)	onOk
{
	CGSize s = [[CCDirector sharedDirector] winSize];
	id moveAction = [CCMoveBy actionWithDuration:1 position:ccp(s.width/2, 0)];
	id action = [CCSequence actions:moveAction,
				 [CCCallFunc actionWithTarget:self selector:@selector(donePlay)],
				 nil ];
	[menu runAction:action];
}

-(void)	donePlay
{
	[[CCDirector sharedDirector] replaceScene:[TruckLayer scene]];
}

-(void)	onSound
{
	DoodleTruck *doodleTruck = [DoodleTruck sharedDoodleTruck];
	doodleTruck.soundEnabled = item_sound.selectedIndex? NO : YES;
}

-(void)	onMusic
{
	DoodleTruck *doodleTruck = [DoodleTruck sharedDoodleTruck];
	doodleTruck.musicEnabled = item_music.selectedIndex? NO : YES;
}

-(void) onSpeed
{
	DoodleTruck *doodleTruck = [DoodleTruck sharedDoodleTruck];
	doodleTruck.speedSence = item_speed.selectedIndex;
}

-(void)	onMode
{
	DoodleTruck *doodleTruck = [DoodleTruck sharedDoodleTruck];
	doodleTruck.mode = item_mode.selectedIndex;
}

*/
