//
//  Truck.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "Truck.h"

#include "DoodleTruck.h"
#include "GameDefine.h"
#include "XSprite.h"

Truck::Truck() {

    DoodleTruck * doodleTruck = DoodleTruck::sharedDoodleTruck();
    char s[100];
    sprintf(s, "truck%d.png", doodleTruck->getTruckType() + 1);
    std::string body_path = s;
    std::string wheel_path = "truck_wheel.png";
    
    driver_Body = XSprite::xspriteWithFileWithYScale("driver-body.png");
    driver_Head = XSprite::xspriteWithFileWithYScale("driver-head.png");
    
    bodySprite = XSprite::xspriteWithFileWithYScale(body_path);
    lWheelSprite = XSprite::xspriteWithFileWithYScale(wheel_path);
    rWheelSprite = XSprite::xspriteWithFileWithYScale(wheel_path);
    
    /*bodySprite->setVisible(false);
    lWheelSprite->setVisible(false);
    rWheelSprite->setVisible(false);
    driver_Head->setVisible(false);
    driver_Body->setVisible(false);
    */
}

void Truck::adjustPosition(Vec2 pos)
{
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    
    switch (doodleTruck->getTruckType()) {
        case 0:
            
            bodySprite->setPosition(Vec2((bodySprite->getContentSize().width + 420) * doodleTruck->getScaleY() / 2,
                                         500 * doodleTruck->getScaleY()));
            lWheelSprite->setPosition(bodySprite->getPosition() +
                                      Vec2(-82 * doodleTruck->getScaleY(), -54 * doodleTruck->getScaleY()));
            
            rWheelSprite->setPosition(bodySprite->getPosition() +
                                      Vec2(82 * doodleTruck->getScaleY(), -54 * doodleTruck->getScaleY()));
            
            driver_Body->setPosition(bodySprite->getPosition() +
                                     Vec2(8 * doodleTruck->getScaleY(), 0 * doodleTruck->getScaleY()));
            
            driver_Head->setPosition(driver_Body->getPosition() +
                                     Vec2(-13 * doodleTruck->getScaleY(), 45 * doodleTruck->getScaleY()));
            
            break;
        case 1:
            lWheelSprite->setPosition(pos + Vec2(180 * doodleTruck->getScaleX(), lWheelSprite->getContentSize().height * 0.5f));
            rWheelSprite->setPosition(lWheelSprite->getPosition() + Vec2(260 * doodleTruck->getScaleY(), 0));
            bodySprite->setPosition(lWheelSprite->getPosition() + Vec2(80 * doodleTruck->getScaleY(), 100 * doodleTruck->getScaleY()));
            
            fFireSprite->setPosition(Vec2(270 * doodleTruck->getScaleY(), 10 * doodleTruck->getScaleY()));
            bFireSprite->setPosition(fFireSprite->getPosition());
            break;
        case 2:
            lWheelSprite->setPosition(pos + Vec2(150 * doodleTruck->getScaleX(), lWheelSprite->getContentSize().height * 0.5f));
            rWheelSprite->setPosition(lWheelSprite->getPosition() + Vec2(240 * doodleTruck->getScaleY(), 0));
            bodySprite->setPosition(lWheelSprite->getPosition() + Vec2(110 * doodleTruck->getScaleY(), 90 * doodleTruck->getScaleY()));
            
            fFireSprite->setPosition(Vec2(220 * doodleTruck->getScaleY(),  35 * doodleTruck->getScaleY()));
            bFireSprite->setPosition(fFireSprite->getPosition());
            break;
        default:
            break;
    }
}

void Truck::effectForwardDrive(bool show_flag) {
    fFireSprite->setVisible(show_flag);
}

void Truck::effectBackwardDrive(bool show_flag) {
    bFireSprite->setVisible(show_flag);
}

void Truck::setupChipmunk1() {
    
    DoodleTruck * doodleTruck = DoodleTruck::sharedDoodleTruck();
    cpSpace *space = doodleTruck->getSpace();
    
    Vec2 s_p = Vec2(doodleTruck->getScaleY(), doodleTruck->getScaleY());
    double mass = TRUCK_MASS;
    
    //body
    Vec2 wd_ht_half = Vec2(128, 64);
    cpBody *body = cpBodyNew(mass, cpMomentForBox(mass, wd_ht_half.x * 2 * doodleTruck->getScaleX(), wd_ht_half.y * 2 * doodleTruck->getScaleY()));
    
    int num = 6;
    cpVect body_verts1[] = {
        cpv(-115.4f * doodleTruck->getScaleY(), -26.0f * doodleTruck->getScaleY()),
        cpv(-114.9f * doodleTruck->getScaleY(), 14.0f * doodleTruck->getScaleY()),
        cpv(68.9f * doodleTruck->getScaleY(), 14.5f * doodleTruck->getScaleY()),
        cpv(124.8f * doodleTruck->getScaleY(), 1.0f * doodleTruck->getScaleY()),
        cpv(125.8f * doodleTruck->getScaleY(), -46.5f * doodleTruck->getScaleY()),
        cpv(111.8f * doodleTruck->getScaleY(), -57.4f * doodleTruck->getScaleY()),
        cpv(40.0f * doodleTruck->getScaleY(), -57.4f * doodleTruck->getScaleY())
    };
    
    cpShape *shape = cpPolyShapeNew(body, num, body_verts1, cpvzero);
    shape->e = TRUCK_BODY_E;
    shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
    shape->data = bodySprite;
    cpSpaceAddShape(space, shape);
    
    num = 5;
    cpVect body_verts2[] = {
        cpv(46.2f * doodleTruck->getScaleY(), 42.3f * doodleTruck->getScaleY()),
        cpv(69.1f * doodleTruck->getScaleY(), 12.0f * doodleTruck->getScaleY()),
        cpv(53.9f * doodleTruck->getScaleY(), 11.3f * doodleTruck->getScaleY()),
        cpv(37.0f * doodleTruck->getScaleY(), 34.9f * doodleTruck->getScaleY()),
        cpv(39.1f * doodleTruck->getScaleY(), 41.6f * doodleTruck->getScaleY())
    };
    
    shape = cpPolyShapeNew(body, num, body_verts2, cpvzero);
    shape->e = TRUCK_BODY_E; shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
    cpSpaceAddShape(space, shape);
    
    body->p.x = bodySprite->getPosition().x;
    body->p.y = bodySprite->getPosition().y;
    cpSpaceAddBody(space, body);
    
    // ------------ driver body------------
    mass = 0.5;
    
    cpBody * driver_body = cpBodyNew(mass, cpMomentForBox(mass, 27 * doodleTruck->getScaleX(), 60 * doodleTruck->getScaleY()));
    
    num = 8;
    cpVect body_verts4[] = {
        cpv(-23.0f, 31.2f),
        cpv(-12.0f, 31.2f),
        cpv(-3.5f, 14.0f),
        cpv(-1.5f, -24.0f),
        cpv(-8.0f, -31.0f),
        cpv(-27.5f, -30.5f),
        cpv(-31.0f, -25.2f),
        cpv(-30.2f, 19.2f)
    };
    
    shape = cpPolyShapeNew(driver_body, num, body_verts4, cpvzero);
    shape->e = 0; shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
    shape->data = driver_Body;
    cpSpaceAddShape(space, shape);
    
    num = 4;
    cpVect body_verts5[] = {
        cpv(-2.7f, 8.3f),
        cpv(17.1f, 8.8f),
        cpv(18.5f, -1.6f),
        cpv(-3.0f, -4.1f)
    };
    
    shape = cpPolyShapeNew(driver_body, num, body_verts5, cpvzero);
    shape->e = 0; shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
   // shape->data = driver_Body;
    cpSpaceAddShape(space, shape);
    
    num = 5;
    cpVect body_verts6[] = {
        cpv(16.9f, 8.5f),
        cpv(26.1f, 13.1f),
        cpv(32.0f, 6.7f),
        cpv(26.8f, -1.4f),
        cpv(18.0f, -0.7f)
    };
    
    shape = cpPolyShapeNew(driver_body, num, body_verts6, cpvzero);
    shape->e = 0; shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
     shape->data = driver_Body;
    cpSpaceAddShape(space, shape);
    
    driver_body->p.x = driver_Body->getPosition().x;
    driver_body->p.y = driver_Body->getPosition().y;
    cpSpaceAddBody(space, driver_body);
    
    // ------- driver-head------------
    mass = 0.3;
    
    cpBody * driver_head = cpBodyNew(mass, cpMomentForCircle(mass, 20 * doodleTruck->getScaleY(), 20 * doodleTruck->getScaleY(), cpvzero));
    
    num = 4;
    cpVect body_verts7[] = {
        cpv(9.9f, -15.6f),
        cpv(8.3f, -24.0f),
        cpv(-6.7f, -23.0f),
        cpv(-6.0f, -11.3f)
    };

    shape = cpPolyShapeNew(driver_head, num, body_verts7, cpvzero);
    shape->e = 0; shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
    shape->data = driver_Head;
    cpSpaceAddShape(space, shape);
    
    num = 7;
    cpVect body_verts8[] = {
        cpv(3.2f, 30.7f),
        cpv(26.5f, 8.0f),
        cpv(19.7f, -12.0f),
        cpv(9.5f, -16.2f),
        cpv(-13.5f, -9.5f),
        cpv(-20.7f, 17.7f),
        cpv(-12.2f, 29.2f)
    };
    
    
    shape = cpPolyShapeNew(driver_head, num, body_verts8, cpvzero);
    shape->e = 0; shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
     shape->data = driver_Body;
    cpSpaceAddShape(space, shape);
    
    driver_head->p.x = driver_Head->getPosition().x;
    driver_head->p.y = driver_Head->getPosition().y;
    cpSpaceAddBody(space, driver_head);
    
  /*
    */
    
    mass = TRUCK_LEFT_WHEELMASS;
    //left wheel
    cpBody * l_wheel = cpBodyNew(mass, cpMomentForCircle(mass, TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(), TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(), cpvzero));
    shape = cpCircleShapeNew(l_wheel, TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(), cpvzero);
    shape->e = TRUCK_WHEEL_E; shape->u = TRUCK_WHEEL_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
    shape->data	= lWheelSprite;
    
    cpSpaceAddShape(space, shape);
    l_wheel->p.x = lWheelSprite->getPosition().x;
    l_wheel->p.y = lWheelSprite->getPosition().y;
    cpSpaceAddBody(space, l_wheel);
    
    mass = TRUCK_RIGHT_WHEELMASS;
    //right wheel
    cpBody * r_wheel = cpBodyNew(mass, cpMomentForCircle(mass, TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(), TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(), cpvzero));
    shape = cpCircleShapeNew(r_wheel, TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(), cpvzero);
    shape->e = TRUCK_WHEEL_E; shape->u = TRUCK_WHEEL_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
    shape->data	= rWheelSprite;
    cpSpaceAddShape(space, shape);
    r_wheel->p.x = rWheelSprite->getPosition().x;
    r_wheel->p.y = rWheelSprite->getPosition().y;
    cpSpaceAddBody(space, r_wheel);
    
    cpVect l_wheel_offset = cpv(-80 * doodleTruck->getScaleY(), -70 * doodleTruck->getScaleY());
    
     cpVect r_wheel_offset = cpv(80 * doodleTruck->getScaleY(), -70 * doodleTruck->getScaleY());
    
    cpSpaceAddConstraint(space, cpGrooveJointNew(body, l_wheel, l_wheel_offset, cpv(l_wheel_offset.x, 0), cpvzero));
    cpSpaceAddConstraint(space, cpGrooveJointNew(body, r_wheel, r_wheel_offset, cpv(r_wheel_offset.x, 0), cpvzero));
    
    cpVect pt_reverse = cpv(1.0, 0);
    
    cpSpaceAddConstraint(space, cpDampedSpringNew(body, l_wheel,
                                                  cpv(l_wheel_offset.x * pt_reverse.x, l_wheel_offset.y * pt_reverse.y),
                                                  cpvzero, fabs(l_wheel_offset.y),
                                                  TRUCK_LEFT_SPRING_STIFFNESS, TRUCK_SPRING_DAMPING));
    
    cpSpaceAddConstraint(space, cpDampedSpringNew(body, r_wheel,
                                                  cpv(r_wheel_offset.x * pt_reverse.x, r_wheel_offset.y * pt_reverse.y),
                                                  cpvzero, fabs(r_wheel_offset.y),
                                                  TRUCK_RIGHT_SPRING_STIFFNESS, TRUCK_SPRING_DAMPING));
    
    
    //cpVect l_wheel_offset = cpv(-80 * doodleTruck->getScaleY(), -60 * doodleTruck->getScaleY());
    
   // cpVect r_wheel_offset = cpv(80 * doodleTruck->getScaleY(), -60 * doodleTruck->getScaleY());
    
   // cpSpaceAddConstraint(space, cpGrooveJointNew(driver_body, driver_head, cpv(-18, 31), cpv(1.5, -25), cpvzero));
    cpSpaceAddConstraint(space, cpSlideJointNew(driver_body, driver_head, cpv(-17.7, 30.7), cpv(1.2, -13.3), 0.3, 1));
//   cpSpaceAddConstraint(space, cpGrooveJointNew(body, driver_body, cpv(0, -5), cpv(0, 35), cpvzero));
    //cpSpaceAddConstraint(space, cpGrooveJointNew(body, driver_body, cpv(10, 5), cpv(15, 5), cpvzero));
    
   
    
   /* cpSpaceAddConstraint(space, cpGrooveJointNew(body, l_wheel, l_wheel_offset, cpv(l_wheel_offset.x, 0), cpvzero));
    cpSpaceAddConstraint(space, cpGrooveJointNew(body, r_wheel, r_wheel_offset, cpv(r_wheel_offset.x, 0), cpvzero));
    */
    
    
    


    
  /*  cpSpaceAddConstraint(space, cpDampedSpringNew(driver_body, driver_head,
                                                  cpv(0, -5), cpv(0, 30),
                                                  fabs(10),
                                                  2000, 3000));
   
    cpSpaceAddConstraint(space, cpRotaryLimitJointNew(body, driver_body, -0.2, 0.3));
    cpSpaceAddConstraint(space, cpRotaryLimitJointNew(driver_body, driver_head, -0.2, 0.3));
    
   
    
    */
    cpConstraint * motor = cpSimpleMotorNew(body, l_wheel, 0);
    doodleTruck->setMotor((cpSimpleMotor *)motor);
    cpSpaceAddConstraint(doodleTruck->getSpace(), motor);
    
    doodleTruck->setBody(body);
    doodleTruck->setLeftW (l_wheel);
    doodleTruck->setRightW(r_wheel);
}

void Truck::setupChipmunk2() {
    
    DoodleTruck * doodleTruck = DoodleTruck::sharedDoodleTruck();
    cpSpace *space = doodleTruck->getSpace();
    
    cpVect s_p = cpv(doodleTruck->getScaleY(), doodleTruck->getScaleY());
    double mass = TRUCK_MASS;
    
    //body
    cpVect wd_ht_half = cpv(247, 91);
    cpBody *body = cpBodyNew(mass, cpMomentForBox(mass,
                                                  wd_ht_half.x * 2 * doodleTruck->getScaleX(),
                                                  wd_ht_half.y * 2 * doodleTruck->getScaleY()));
    
    int num = 4;
    cpVect body_verts1[] = {
        cpv((310 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 2) * s_p.y),
        cpv((382 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 2) * s_p.y),
        cpv((385 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 66) * s_p.y),
        cpv((274 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 66) * s_p.y)
    };
    
    cpShape *shape = cpPolyShapeNew(body, num, body_verts1, cpvzero);
    shape->e = TRUCK_BODY_E; shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
    shape->data = bodySprite;
    cpSpaceAddShape(space, shape);
    
    cpVect body_verts2[] = {
        cpv((274 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 66) * s_p.y),
        cpv((455 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 60) * s_p.y),
        cpv((488 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 155) * s_p.y),
        cpv((260 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 155) * s_p.y)
    };
    
    shape = cpPolyShapeNew(body, num, body_verts2, cpvzero);
    shape->e = TRUCK_BODY_E; shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
    cpSpaceAddShape(space, shape);
    
    cpVect body_verts3[] = {
        cpv((60 - wd_ht_half.x) * s_p.x , (wd_ht_half.y - 100) * s_p.y),
        cpv((265 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 100) * s_p.y),
        cpv((260 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 155) * s_p.y),
        cpv((110 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 155) * s_p.y),
    };
    
    shape = cpPolyShapeNew(body, num, body_verts3, cpvzero);
    shape->e = TRUCK_BODY_E; shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
    cpSpaceAddShape(space, shape);
    
    num = 5;
    cpVect body_verts4[] = {
        cpv((60 - wd_ht_half.x) * s_p.x , (wd_ht_half.y - 100) * s_p.y),
        cpv((0 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 45) * s_p.y),
        cpv((0 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 28) * s_p.y),
        cpv((20 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 28) * s_p.y),
        cpv((80 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 100) * s_p.y)
    };
    
    shape = cpPolyShapeNew(body, num, body_verts4, cpvzero);
    shape->e = TRUCK_BODY_E; shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
    cpSpaceAddShape(space, shape);
    
    body->p = cpv(bodySprite->getPosition().x, bodySprite->getPosition().y);
    cpSpaceAddBody(space, body);
    
    mass = TRUCK_LEFT_WHEELMASS;
    //left wheel
    cpBody * l_wheel = cpBodyNew(mass, cpMomentForCircle(mass,
                                                         TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(),
                                                         TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(),
                                                         cpvzero));
    
    shape = cpCircleShapeNew(l_wheel, TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(), cpvzero);
    shape->e = TRUCK_WHEEL_E; shape->u = TRUCK_WHEEL_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->data	= lWheelSprite;
    
    cpSpaceAddShape(space, shape);
    l_wheel->p = cpv(lWheelSprite->getPosition().x, lWheelSprite->getPosition().y);
    cpSpaceAddBody(space, l_wheel);
    
    mass = TRUCK_RIGHT_WHEELMASS;
    //right wheel
    cpBody * r_wheel = cpBodyNew(mass, cpMomentForCircle(mass,
                                                         TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(),
                                                         TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(),
                                                         cpvzero));
    shape = cpCircleShapeNew(r_wheel, TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(), cpvzero);
    shape->e = TRUCK_WHEEL_E; shape->u = TRUCK_WHEEL_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->data	= rWheelSprite;
    cpSpaceAddShape(space, shape);
    r_wheel->p = cpv(rWheelSprite->getPosition().x, rWheelSprite->getPosition().y);
    cpSpaceAddBody(space, r_wheel);
    
    cpVect l_wheel_offset = cpv(-72 * doodleTruck->getScaleY(), -95 * doodleTruck->getScaleY());
    cpVect r_wheel_offset = cpv(175 * doodleTruck->getScaleY(), -95 * doodleTruck->getScaleY());
    cpSpaceAddConstraint(space, cpGrooveJointNew(body, l_wheel, l_wheel_offset, cpv(l_wheel_offset.x, 0), cpvzero));
    cpSpaceAddConstraint(space, cpGrooveJointNew(body, r_wheel, r_wheel_offset, cpv(r_wheel_offset.x, 0), cpvzero));
    cpVect pt_reverse = cpv(1, 0);
    cpSpaceAddConstraint(space, cpDampedSpringNew(body, l_wheel,
                                                  cpv(l_wheel_offset.x * pt_reverse.x, l_wheel_offset.y * pt_reverse.y),
                                                  cpvzero,
                                                  fabs(l_wheel_offset.y),
                                                  TRUCK_LEFT_SPRING_STIFFNESS,
                                                  TRUCK_SPRING_DAMPING));
    
    cpSpaceAddConstraint(space, cpDampedSpringNew(body, r_wheel,
                                                  cpv(r_wheel_offset.x * pt_reverse.x, r_wheel_offset.y * pt_reverse.y),
                                                  cpvzero,
                                                  fabs(r_wheel_offset.y),
                                                  TRUCK_RIGHT_SPRING_STIFFNESS,
                                                  TRUCK_SPRING_DAMPING));
    
    cpConstraint * motor = cpSimpleMotorNew(body, l_wheel, 0);
    doodleTruck->setMotor((cpSimpleMotor *)motor);
    cpSpaceAddConstraint(doodleTruck->getSpace(), motor);
    
    doodleTruck->setBody(body);
    doodleTruck->setLeftW(l_wheel);
    doodleTruck->setRightW(r_wheel);
}

void Truck::setupChipmunk3() {
    DoodleTruck * doodleTruck = DoodleTruck::sharedDoodleTruck();
    cpSpace *space = doodleTruck->getSpace();
    
    cpVect s_p = cpv(doodleTruck->getScaleY(), doodleTruck->getScaleY());
    double mass = TRUCK_MASS;
    
    //body
    cpVect wd_ht_half = cpv(248, 84);
    cpBody *body = cpBodyNew(mass, cpMomentForBox(mass, wd_ht_half.x * 2 * doodleTruck->getScaleX(), wd_ht_half.y * 2 * doodleTruck->getScaleY()));
    int num = 4;
    cpVect body_verts1[] = {
        cpv((286 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 5) * s_p.y),
        cpv((430 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 5) * s_p.y),
        cpv((430 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 70) * s_p.y),
        cpv((255 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 70) * s_p.y)
    };
    
    cpShape *shape = cpPolyShapeNew(body, num, body_verts1, cpvzero);
    shape->e = TRUCK_BODY_E; shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
    shape->data = bodySprite;
    cpSpaceAddShape(space, shape);
    
    num = 5;
    cpVect body_verts2[] = {
        cpv((255 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 70) * s_p.y),
        cpv((490 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 70) * s_p.y),
        cpv((490 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 165) * s_p.y),
        cpv((455 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 165) * s_p.y),
        cpv((255 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 110) * s_p.y)
    };
    
    shape = cpPolyShapeNew(body, num, body_verts2, cpvzero);
    shape->e = TRUCK_BODY_E; shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
    cpSpaceAddShape(space, shape);
    
    num = 4;
    cpVect body_verts3[] = {
        cpv((255 - wd_ht_half.x) * s_p.x , (wd_ht_half.y - 85) * s_p.y),
        cpv((255 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 130) * s_p.y),
        cpv((70 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 130) * s_p.y),
        cpv((20 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 85) * s_p.y)
    };
    
    shape = cpPolyShapeNew(body, num, body_verts3, cpvzero);
    shape->e = TRUCK_BODY_E; shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
    cpSpaceAddShape(space, shape);
    
    cpVect body_verts4[] = {
        cpv((0 - wd_ht_half.x) * s_p.x , (wd_ht_half.y - 48) * s_p.y),
        cpv((20 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 48) * s_p.y),
        cpv((40 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 85) * s_p.y),
        cpv((20 - wd_ht_half.x) * s_p.x, (wd_ht_half.y - 85) * s_p.y)
    };
    
    shape = cpPolyShapeNew(body, num, body_verts4, cpvzero);
    shape->e = TRUCK_BODY_E; shape->u = TRUCK_BODY_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->collision_type = BODY_COLLISION;
    cpSpaceAddShape(space, shape);
    
    body->p = cpv(bodySprite->getPosition().x, bodySprite->getPosition().y);
    cpSpaceAddBody(space, body);
    
    mass = TRUCK_LEFT_WHEELMASS;
    //left wheel
    cpBody * l_wheel = cpBodyNew(mass, cpMomentForCircle(mass,
                                                         TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(),
                                                         TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(),
                                                         cpvzero));
    shape = cpCircleShapeNew(l_wheel, TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(), cpvzero);
    shape->e = TRUCK_WHEEL_E; shape->u = TRUCK_WHEEL_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->data	= lWheelSprite;
    
    cpSpaceAddShape(space, shape);
    l_wheel->p = cpv(lWheelSprite->getPosition().x, lWheelSprite->getPosition().y);
    cpSpaceAddBody(space, l_wheel);
    
    mass = TRUCK_RIGHT_WHEELMASS;
    //right wheel
    cpBody * r_wheel = cpBodyNew(mass, cpMomentForCircle(mass,
                                                         TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(),
                                                         TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(),
                                                         cpvzero));
    
    shape = cpCircleShapeNew(r_wheel, TRUCK_WHEEL_RADIUS * doodleTruck->getScaleY(), cpvzero);
    shape->e = TRUCK_WHEEL_E; shape->u = TRUCK_WHEEL_U;
    shape->group = BOX2D_TRUCK_GROUP;
    shape->data	= rWheelSprite;
    cpSpaceAddShape(space, shape);
    r_wheel->p = cpv(rWheelSprite->getPosition().x, rWheelSprite->getPosition().y);
    cpSpaceAddBody(space, r_wheel);
    
    cpVect l_wheel_offset = cpv(-100 * doodleTruck->getScaleY(), -50 * doodleTruck->getScaleY());
    cpVect r_wheel_offset = cpv(130 * doodleTruck->getScaleY(), -50 * doodleTruck->getScaleY());
    cpSpaceAddConstraint(space, cpGrooveJointNew(body, l_wheel, l_wheel_offset, cpv(l_wheel_offset.x, 0), cpvzero));
    cpSpaceAddConstraint(space, cpGrooveJointNew(body, r_wheel, r_wheel_offset, cpv(r_wheel_offset.x, 0), cpvzero));
    cpVect pt_reverse = cpv(1, 0);
    
    cpSpaceAddConstraint(space, cpDampedSpringNew(body, l_wheel,
                                                  cpv(l_wheel_offset.x * pt_reverse.x, l_wheel_offset.y * pt_reverse.y),
                                                  cpvzero, fabs(l_wheel_offset.y),
                                                  TRUCK_LEFT_SPRING_STIFFNESS,
                                                  TRUCK_SPRING_DAMPING));
    
    cpSpaceAddConstraint(space, cpDampedSpringNew(body, r_wheel,
                                                  cpv(r_wheel_offset.x * pt_reverse.x, r_wheel_offset.y * pt_reverse.y),
                                                  cpvzero, fabs(r_wheel_offset.y),
                                                  TRUCK_RIGHT_SPRING_STIFFNESS,
                                                  TRUCK_SPRING_DAMPING));
    
    cpConstraint * motor = cpSimpleMotorNew(body, l_wheel, 0);
    doodleTruck->setMotor((cpSimpleMotor *)motor);
    cpSpaceAddConstraint(doodleTruck->getSpace(), motor);
    
    doodleTruck->setBody(body);
    doodleTruck->setLeftW(l_wheel);
    doodleTruck->setRightW(r_wheel);
}

void Truck::setupChipmunk() {
    DoodleTruck * doodleTruck = DoodleTruck::sharedDoodleTruck();
    switch (doodleTruck->getTruckType()) {
        case 0:
            setupChipmunk1();
            break;
        case 1:
            setupChipmunk2();
            break;
        case 2:
            setupChipmunk3();
        default:
            break;
    }
}

