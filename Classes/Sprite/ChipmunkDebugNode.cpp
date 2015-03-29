//
// desc: ChipmunkDebugNode.cpp
//

//
// includes
//
#include "ChipmunkDebugNode.h"

// cocos2d namespace
USING_NS_CC;

ChipmunkDebugNode *ChipmunkDebugNode::create(cpSpace *space)
{
    ChipmunkDebugNode *chipmunkDebugNode = new ChipmunkDebugNode();
    if (chipmunkDebugNode && chipmunkDebugNode->init(space)) {
        chipmunkDebugNode->autorelease();
        return chipmunkDebugNode;
    }
    
    // else cleanup
    delete chipmunkDebugNode;
    return NULL;
}

void ChipmunkDebugNode::DrawShape(cpShape* shape, void *data)
{
    if (!shape) {
        return;
    }
    
    glLineWidth(5.0f);
    DrawPrimitives::setDrawColor4F(0.5f, 0.5f, 0.5f, 1.0f);
    
    if (shape->klass_private->type == CP_CIRCLE_SHAPE) {
        cpCircleShape *circle = (cpCircleShape *)shape;
        cpVect center = cpvadd(shape->body->p, cpvrotate(circle->c, shape->body->rot));
        DrawPrimitives::drawCircle(Point(center.x, center.y), circle->r, shape->body->a, 20, true);
        return;
    }
    
    if (shape->klass_private->type == CP_POLY_SHAPE) {
        cpPolyShape *poly = (cpPolyShape *)shape;
        
        // convert chipmunk points to coco points
        Point *pointArray = new Point[poly->numVerts];
        for (int i=0; i < poly->numVerts; i++) {
            pointArray[i] = Point(poly->tVerts[i].x, poly->tVerts[i].y);
        }
        
        DrawPrimitives::drawPoly(pointArray, poly->numVerts, true);
        delete [] pointArray;
        return;
    }
    
    if (shape->klass_private->type == CP_SEGMENT_SHAPE) {
        cpSegmentShape* segment = (cpSegmentShape*)shape;
        DrawPrimitives::drawLine(Point(segment->ta.x, segment->ta.y),
                                 Point(segment->tb.x, segment->tb.y));
        return;
    }
    
    cpSegmentShape *segment = (cpSegmentShape *)shape;
    DrawPrimitives::drawLine(Point(segment->ta.x, segment->ta.y),
                             Point(segment->tb.x, segment->tb.y));
}

//
// descP init
//
bool ChipmunkDebugNode::init(cpSpace *space)
{
    if (!Node::init()) {
        return false;
    }
    
    // init variables
    _space = space;
    
    return true;
}

//
// desc: override draw
//
void ChipmunkDebugNode::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    cpSpaceEachShape(_space, &DrawShape, this);
}