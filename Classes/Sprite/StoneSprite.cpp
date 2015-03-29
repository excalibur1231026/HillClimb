//
//  StoneSprite.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "StoneSprite.h"

#include "DoodleTruck.h"
#include "XSprite.h"

float stoneSizes[] = {
	1.0f, 0.8f, 0.6f, 1.0f, 0.8f, 0.6f, 0.8f, 1.0f, 1.0f, 0.8f,
};

float stoneWeights[] = {
	1.0f, 4.0f, 2.5f, 2.0f,
};


StoneSprite::StoneSprite() {
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    int stone_index = doodleTruck->getMapIndex() % STONE_KIND_NUM + 1;
    
    char s[100];
    sprintf(s, "stone_%d.png", stone_index);
    std::string path = s;
    this->initWithFile(path);
    
    Texture2D *tex = addXTextureWithYScale(path);
    cocos2d::Rect rect = Rect::ZERO;
	rect.size = tex->getContentSize();
    this->setTexture(tex);
    this->setTextureRect(rect);
    this->schedule(schedule_selector(StoneSprite::onLookMoving), 0.2f);
}

void StoneSprite::onLookMoving(float dt) {
    old_pos = this->getPosition();
}

bool StoneSprite::isMoving() {
	int diff_x = this->getPosition().x - old_pos.x;
	int diff_y = this->getPosition().y - old_pos.y;
	return diff_x * diff_y ? true : false;
}

int StoneSprite::movingAmountY() {
	int diff_y = this->getPosition().y - old_pos.y;
	return diff_y;
}

void StoneSprite::setupChipmunk() {
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
	
	cpSpace *space = doodleTruck->getSpace();
	cpVect s_p = cpv(doodleTruck->getScaleY() * stoneSizes[stoneId], doodleTruck->getScaleY() * stoneSizes[stoneId]);
	double mass = STONE_MASS * stoneWeights[doodleTruck->getMapIndex() % STONE_KIND_NUM] * stoneSizes[stoneId];
	int num = 0;
	cpVect verts[8];
	int stone_type = doodleTruck->getMapIndex() % STONE_KIND_NUM;
    
	switch (stone_type) {
		case 0:
			num = 6;
			verts[0] = cpv(-25 * s_p.x, 0 * s_p.y);
			verts[1] = cpv(-5 * s_p.x, 12 * s_p.y);
			verts[2] = cpv(15 * s_p.x, 12 * s_p.y);
			verts[3] = cpv(25 * s_p.x, 0 * s_p.y);
			verts[4] = cpv(15 * s_p.x, -12 * s_p.y);
			verts[5] = cpv(-5 * s_p.x, -12 * s_p.y);
			break;
		case 1:
			num = 7;
			verts[0] = cpv(-55 * s_p.x, 0 * s_p.y);
			verts[1] = cpv(-47 * s_p.x, 15 * s_p.y);
			verts[2] = cpv(0 * s_p.x, 40 * s_p.y);
			verts[3] = cpv(47 * s_p.x, 15 * s_p.y);
			verts[4] = cpv(55 * s_p.x, 0 * s_p.y);
			verts[5] = cpv(-5 * s_p.x, -40 * s_p.y);
			verts[6] = cpv(-30 * s_p.x, -34 * s_p.y);
			break;
		case 2:
			num = 6;
			verts[0] = cpv(-37 * s_p.x, 23 * s_p.y);
			verts[1] = cpv(-8 * s_p.x, 30 * s_p.y);
			verts[2] = cpv(37 * s_p.x, 23 * s_p.y);
			verts[3] = cpv(37 * s_p.x, -23 * s_p.y);
			verts[4] = cpv(-8 * s_p.x, -30 * s_p.y);
			verts[5] = cpv(-37 * s_p.x, -23 * s_p.y);
			break;
		case 3:
			num = 8;
			verts[0] = cpv(-32 * s_p.x, 0 * s_p.y);
			verts[1] = cpv(-6 * s_p.x, 20 * s_p.y);
			verts[2] = cpv(6 * s_p.x, 20 * s_p.y);
			verts[3] = cpv(32 * s_p.x, 5 * s_p.y);
			verts[4] = cpv(32 * s_p.x, -5 * s_p.y);
			verts[5] = cpv(-5 * s_p.x, -20 * s_p.y);
			verts[6] = cpv(-20 * s_p.x, -20 * s_p.y);
			verts[7] = cpv(-27 * s_p.x, -10 * s_p.y);
		default:
			break;
	}
	
	body = cpBodyNew(mass, cpMomentForPoly(mass, num, verts, cpvzero));
    body->p = cpv(this->getPosition().x, this->getPosition().y);
	cpSpaceAddBody(space, body);
	
	cpShape* shape = cpPolyShapeNew(body, num, verts, cpvzero);
	shape->e = STONE_E; shape->u = STONE_U;
	shape->data = this;
	shape->collision_type = STONE_COLLISION;
	cpSpaceAddShape(space, shape);
	
    this->setScale(this->getScaleX() * stoneSizes[stoneId], this->getScaleY() * stoneSizes[stoneId]);
}

double StoneSprite::score() {
	return STONE_MAX_SCORE * stoneSizes[stoneId];
}