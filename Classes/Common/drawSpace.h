//
//  drawSpace.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__drawSpace__
#define __HillClimb__drawSpace__

#include "chipmunk.h"

typedef struct {
    int drawHash;
    int drawBBs;
    int drawShapes;
    float collisionPointSize;
    float bodyPointSize;
    float lineThickness;
} drawSpaceOptions;

void drawSpace(cpSpace *space, drawSpaceOptions *options);


#endif /* defined(__HillClimb__drawSpace__) */
