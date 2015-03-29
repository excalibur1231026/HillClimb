//
//  drawSpace.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__GameDefine__
#define __HillClimb__GameDefine__

#pragma mark Ground

#define MAX_MAP					16
#define MAX_STONES				10
#define STONE_KIND_NUM			4

#define	INTERVAL_MAKE_STONE		0.7f

#define AIR_INTERVAL			0.5f

#pragma mark Image

#define IMG_SPRITE_BG			 "sprite_bg.png"
#define IMG_SPRITE_SET_BG		 "setting_bg.png"

#define IMG_PLAY_NOR			 "play_nor.png"
#define IMG_PLAY_HIGH			 "play_high.png"
#define IMG_SETTINGS_NOR		 "settings_nor.png"
#define IMG_SETTINGS_HIGH		 "settings_high.png"
#define IMG_BACK_NOR			 "back_nor.png"
#define IMG_BACK_HIGH			 "back_high.png"
#define IMG_OK_NOR				 "ok_nor.png"
#define IMG_OK_HIGH				 "ok_high.png"

#define IMG_FORWARD_NOR					 "forward_nor.png"
#define IMG_FORWARD_ACT					 "forward_act.png"
#define IMG_BACKWARD_NOR				 "backward_nor.png"
#define IMG_BACKWARD_ACT				 "backward_act.png"


#define IMG_STONE_SENDER				"sender.png"
#define IMG_STONE_RECEIVER				"receive.png"

#define	IMG_PAUSE_NOR					"pause_nor.png"
#define IMG_PAUSE_ACT					"pause_act.png"

#define IMG_SCORE						"score.png"
#define IMG_RETRY_NORMAL				"retry_normal.png"
#define IMG_RETRY_DOWN					"retry_down.png"
#define IMG_BACK_NORMAL					 "back_normal.png"
#define IMG_BACK_DOWN					 "back_down.png"
#define IMG_NEXT_NORMAL					 "next_normal.png"
#define IMG_NEXT_DOWN					 "next_down.png"
#define IMG_FAILED						 "failed.png"
#define IMG_TIME_UP						 "time_up.png"

#define IMG_SOUND						 "sound.png"
#define IMG_MUSIC						 "music.png"
#define IMG_SOUND_ON					 "on.png"
#define IMG_SOUND_OFF					 "off.png"
#define IMG_SPEED						 "speed.png"
#define IMG_GAMEMODE					 "gamemode.png"
#define IMG_SLOW						 "slow.png"
#define IMG_NORMAL						 "normal.png"
#define IMG_FAST						 "fast.png"
#define IMG_FREEMODE					 "free.png"
#define IMG_TIMEMODE					 "time.png"

#define IMG_FFIRE						 "truck_fire.png"
#define IMG_BFIRE						 "truck_back_fire.png"

#define IMG_BLINKER_DIS					 "blinker_dis.png"
#define IMG_BLINKER_LOAD				 "blinker_load.png"
#define IMG_BLINKER_GO					 "blinker_go.png"

#define IMG_NUMBER						 "number.png"
#define CHAR_MAP_WIDTH					35
#define CHAR_MAP_HEIGHT					45

#define IMG_POPUP_BG					 "popup_bg.png"

#define IMG_LEVEL						 "level.png"
#define IMG_TIME						 "time_menu.png"

#define IMG_WAIT						 "wait.png"
#define IMG_LETSGO						 "lets_go.png"
#pragma mark SOUND

#define SND_DRIVE						 "truck_drive.wav"
#define	SND_STRIKE						 "stone_strike.aif"
#define SND_GROUND_STRIKE				 "stone_ground_strike.wav"
#define SND_BG							 "success.wav"

#pragma mark BOX2D

#define	DEFAULT_GRAVITY			-500.0f

#define STONE_MASS				1.0f

#define GROUND_U				1.0f
#define	SENDER_U				0.5f

#define STONE_E					0.3f
#define STONE_U					1.0f

#define TRUCK_BODY_E			0.1f        // truck elasticity
#define TRUCK_BODY_U			0.7f        // truck friction

#define	TRUCK_WHEEL_E			0.3f        // wheel elasticity
#define TRUCK_WHEEL_U			1.0f        // wheel friction


#define BOX2D_TRUCK_GROUP		-1
#define BOX2D_COIN_GROUP        3

#define TRUCK_WHEEL_RADIUS		32.0f

#define TRUCK_LEFT_SPRING_STIFFNESS		375.0f  // left spring stiffness
#define TRUCK_RIGHT_SPRING_STIFFNESS	375.0f  // right spring stiffness

#define TRUCK_SPRING_DAMPING		20.0f       // Tuck spring damping

#define TRUCK_MAX_SPEED				4 * M_PI
#define	MOTOR_UP_RATE_SPEED			20.0f

#define TRUCK_MASS					10.0f       // truck mass
#define TRUCK_LEFT_WHEELMASS		3.0f        // left wheel mass
#define TRUCK_RIGHT_WHEELMASS		3.0f        // right wheel mass

#define	V_LIMIT_STONE_TRUCK_STRIKE		50.0f
#define	V_LIMIT_STONE_GROUND_STRIKE		50.0f

#define MAX_DELTA_FRAME				0.04f	// 1/25

#define ROAD_BEGIN_x					180.0f
enum COLLISION_INFO
{
    BODY_COLLISION = 10,
    COIN_COLLISION,
    STONE_COLLISION,
    GROUND_COLLISION,
};

#pragma mark SCORE

#define LEVEL_SCORE					150.0f
#define STONE_MAX_SCORE				30.0f

#define SCORE_FILE					 "score.dat"

#define TASK_MSG					 "Your delivery target of load is %d"

#endif /* defined(__HillClimb__drawSpace__) */
