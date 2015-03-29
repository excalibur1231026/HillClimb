

#include "Terrain.h"
#include "DoodleTruck.h"
#include "XSprite.h"

Terrain::Terrain() {
    
    _stripes = this->generateStripesSprite();
    
    addXTexture("lowres-terrain-ground.png");
    Texture2D * tex = Director::getInstance()->getTextureCache()->textureForKey("lowres-terrain-ground.png");
    cocos2d::Texture2D::TexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_CLAMP_TO_EDGE};
    tex->setTexParameters(tp);
    
    this->setShaderProgram(ShaderCache::getInstance()->getProgram(kCCShader_PositionTexture));

    _fromKeyPointI = 0;
    _toKeyPointI = 0;
    
    _offsetX = 0;
    
    _hillKeyPoints[0] = Vec2(0, 332);
    _hillKeyPoints[1] = Vec2(90, 332);
    _hillKeyPoints[2] = Vec2(180, 332);
    _hillKeyPoints[3] = Vec2(695, 332);
    _hillKeyPoints[4] = Vec2(858, 354);
    _hillKeyPoints[5] = Vec2(1059, 391);
    _hillKeyPoints[6] = Vec2(1154, 424);
    _hillKeyPoints[7] = Vec2(1258, 434);
    _hillKeyPoints[8] = Vec2(1385, 440);
    _hillKeyPoints[9] = Vec2(1502, 435);
    _hillKeyPoints[10] = Vec2(1564, 434);
    _hillKeyPoints[11] = Vec2(1669, 402);
    _hillKeyPoints[12] = Vec2(1771, 388);
    _hillKeyPoints[13] = Vec2(1858, 387);
    _hillKeyPoints[14] = Vec2(1920, 387);
    _hillKeyPoints[15] = Vec2(2000, 389);
    _hillKeyPoints[16] = Vec2(2095, 348);
    _hillKeyPoints[17] = Vec2(2201, 322);
    _hillKeyPoints[18] = Vec2(2378, 325);
    _hillKeyPoints[19] = Vec2(2818, 409);
    _hillKeyPoints[20] =  Vec2(3061, 388);
    _hillKeyPoints[21] =  Vec2(3153, 407);
    _hillKeyPoints[22] =  Vec2(3295, 479);
    _hillKeyPoints[23] =  Vec2(3403, 490);
    _hillKeyPoints[24] =  Vec2(3465, 475);
    _hillKeyPoints[25] =  Vec2(3619, 420);
    _hillKeyPoints[26] =  Vec2(3788, 392);
    _hillKeyPoints[27] =  Vec2(3896, 346);
    _hillKeyPoints[28] =  Vec2(3983, 325);
    _hillKeyPoints[29] =  Vec2(4043, 324);
    _hillKeyPoints[30] =  Vec2(4168, 282);
    _hillKeyPoints[31] =  Vec2(4320, 252);
    _hillKeyPoints[32] =  Vec2(4420, 239);
    _hillKeyPoints[33] =  Vec2(4501, 249);
    _hillKeyPoints[34] =  Vec2(4719, 315);
    _hillKeyPoints[35] =  Vec2(4852, 377);
    _hillKeyPoints[36] =  Vec2(4950, 408);
    _hillKeyPoints[37] =  Vec2(5050, 418);
    _hillKeyPoints[38] =  Vec2(5226, 425);
    _hillKeyPoints[39] =  Vec2(5401, 371);
    _hillKeyPoints[40] =  Vec2(5505, 383);
    _hillKeyPoints[41] =  Vec2(5574, 381);
    _hillKeyPoints[42] =  Vec2(5720, 372);
    _hillKeyPoints[43] =  Vec2(5884, 364);
    _hillKeyPoints[44] =  Vec2(6087, 407);
    _hillKeyPoints[45] =  Vec2(6254, 412);
    _hillKeyPoints[46] =  Vec2(6453, 363);
    _hillKeyPoints[47] =  Vec2(6679, 390);
    _hillKeyPoints[48] =  Vec2(6955, 374);
    _hillKeyPoints[49] =  Vec2(7089, 376);
    _hillKeyPoints[50] =  Vec2(7221, 365);
    _hillKeyPoints[51] =  Vec2(7436, 419);
    _hillKeyPoints[52] =  Vec2(7578, 406);
    _hillKeyPoints[53] =  Vec2(7755, 375);
    _hillKeyPoints[54] =  Vec2(7986, 370);
    _hillKeyPoints[55] =  Vec2(8070, 392);
    _hillKeyPoints[56] =  Vec2(8259, 369);
    _hillKeyPoints[57] =  Vec2(8441, 385);
    _hillKeyPoints[58] =  Vec2(8611, 377);
    _hillKeyPoints[59] =  Vec2(8682, 358);
    _hillKeyPoints[60] =  Vec2(8863, 410);
    _hillKeyPoints[61] =  Vec2(9087, 403);
    _hillKeyPoints[62] =  Vec2(9205, 367);
    _hillKeyPoints[63] =  Vec2(9480, 387);
    _hillKeyPoints[64] =  Vec2(9663, 381);
    _hillKeyPoints[65] =  Vec2(9723, 364);
    _hillKeyPoints[66] =  Vec2(9916, 426);
    _hillKeyPoints[67] =  Vec2(10211, 424);
    _hillKeyPoints[68] =  Vec2(10434, 370);
    _hillKeyPoints[69] =  Vec2(10509, 384);
    _hillKeyPoints[70] =  Vec2(10582, 381);
    _hillKeyPoints[71] =  Vec2(10697, 371);
    _hillKeyPoints[72] =  Vec2(10912, 364);
    _hillKeyPoints[73] =  Vec2(11090, 408);
    _hillKeyPoints[74] =  Vec2(11256, 416);
    _hillKeyPoints[75] =  Vec2(11458, 366);
    _hillKeyPoints[76] =  Vec2(11563, 380);
    _hillKeyPoints[77] =  Vec2(11737, 382);
    _hillKeyPoints[78] =  Vec2(11998, 355);
    _hillKeyPoints[79] =  Vec2(12254, 317);
    _hillKeyPoints[80] =  Vec2(12430, 307);
    _hillKeyPoints[81] =  Vec2(12490, 289);
    _hillKeyPoints[82] =  Vec2(12589, 287);
    _hillKeyPoints[83] =  Vec2(12852, 241);
    _hillKeyPoints[84] =  Vec2(12844, 254);
    _hillKeyPoints[85] =  Vec2(12821, 273);
    _hillKeyPoints[86] =  Vec2(12833, 278);
    _hillKeyPoints[87] =  Vec2(12833, 278);
    _hillKeyPoints[88] =  Vec2(12830, 286);
    _hillKeyPoints[89] =  Vec2(12830, 286);
    _hillKeyPoints[90] =  Vec2(12819, 293);
    _hillKeyPoints[91] =  Vec2(12806, 326);
    _hillKeyPoints[92] =  Vec2(12778, 283);
    _hillKeyPoints[93] =  Vec2(12695, 292);
    _hillKeyPoints[94] =  Vec2(12688, 341);
    _hillKeyPoints[95] =  Vec2(12710, 529);
    _hillKeyPoints[96] =  Vec2(12984, 566);
    _hillKeyPoints[97] =  Vec2(13238, 527);
    _hillKeyPoints[98] =  Vec2(13243, 353);
    _hillKeyPoints[99] =  Vec2(13214, 302);
    _hillKeyPoints[98] =  Vec2(13183, 294);
    _hillKeyPoints[99] =  Vec2(13139, 317);
    _hillKeyPoints[100] =  Vec2(13128, 346);
    _hillKeyPoints[101] =  Vec2(13114, 344);
    _hillKeyPoints[102] =  Vec2(13097, 293);
    _hillKeyPoints[103] =  Vec2(13074, 256);
    _hillKeyPoints[104] =  Vec2(13056, 253);
    _hillKeyPoints[105] =  Vec2(13061, 242);
    _hillKeyPoints[106] =  Vec2(13143, 253);
    _hillKeyPoints[107] =  Vec2(13216, 273);
    _hillKeyPoints[108] =  Vec2(13315, 284);
    _hillKeyPoints[109] =  Vec2(13390, 300);
    _hillKeyPoints[110] =  Vec2(13539, 286);
    _hillKeyPoints[111] =  Vec2(13701, 297);
    _hillKeyPoints[112] =  Vec2(13810, 315);
    _hillKeyPoints[113] =  Vec2(14012, 384);
    _hillKeyPoints[114] =  Vec2(14130, 423);
    _hillKeyPoints[115] =  Vec2(14229, 442);
    _hillKeyPoints[116] =  Vec2(14346, 430);
    _hillKeyPoints[117] =  Vec2(14466, 441);
    _hillKeyPoints[118] =  Vec2(14502, 419);
    _hillKeyPoints[119] =  Vec2(14528, 439);
    _hillKeyPoints[120] =  Vec2(14706, 423);
    _hillKeyPoints[121] =  Vec2(14832, 431);
    _hillKeyPoints[122] =  Vec2(14900, 420);
    _hillKeyPoints[123] =  Vec2(14900, 196);
    _hillKeyPoints[124] =  Vec2(14997, 196);
    
    resetHillVertices();
}

void Terrain::resetHillVertices() {
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    cocos2d::Size winSize = Director::getInstance()->getWinSize();
    
    static int prevFromKeyPointI = -1;
    static int prevToKeyPointI = -1;
    
    // key points interval for drawing
    
    _fromKeyPointI = 0;
    _toKeyPointI = 0;
    
    while (_hillKeyPoints[_fromKeyPointI].x * doodleTruck->getScaleY() < _offsetX-winSize.width) {
        _fromKeyPointI++;
    }
    while (_hillKeyPoints[_toKeyPointI].x * doodleTruck->getScaleY() < _offsetX + winSize.width) {
        _toKeyPointI++;
    }
    
    
    //_fromKeyPointI = 0;
    //_toKeyPointI = 20;
    
    float minY = 0;
    if (winSize.height > 480) {
        minY = (1136 - 1024)/4;
    }
    
    minY = -100;
    
    if (prevFromKeyPointI != _fromKeyPointI || prevToKeyPointI != _toKeyPointI) {
        
        // vertices for visible area
        _nHillVertices = 0;
        _nBorderVertices = 0;
        Vec2 p0, p1, pt0, pt1;
        
        p0 = Vec2(_hillKeyPoints[_fromKeyPointI].x * doodleTruck->getScaleY()
                  , _hillKeyPoints[_fromKeyPointI].y * doodleTruck->getScaleY());
        
        for (int i = _fromKeyPointI + 1; i < _toKeyPointI + 1; i++) {
            
            p1 = Vec2(_hillKeyPoints[i].x * doodleTruck->getScaleY(),
                      _hillKeyPoints[i].y * doodleTruck->getScaleY());
            
            // triangle strip between p0 and p1
            int hSegments = floorf((p1.x - p0.x) / kHillSegmentWidth);
            float dx = (p1.x - p0.x) / hSegments;
            float da = M_PI / hSegments;
            float ymid = (p0.y + p1.y) / 2;
            float ampl = (p0.y - p1.y) / 2;
            pt0 = p0;
            
            _borderVertices[_nBorderVertices++] = pt0;
            for (int j = 1; j < hSegments + 1; j++) {
                pt1.x = p0.x + j*dx;
                pt1.y = ymid + ampl * cosf(da*j);
                _borderVertices[_nBorderVertices++] = pt1;
                
                _hillVertices[_nHillVertices] = Vec2(pt0.x, 0 + minY);
                _hillTexCoords[_nHillVertices++] = Vec2(pt0.x / 512, 1.0f);
                _hillVertices[_nHillVertices] = Vec2(pt1.x, 0 + minY);
                _hillTexCoords[_nHillVertices++] = Vec2(pt1.x / 512, 1.0f);
                
                _hillVertices[_nHillVertices] = Vec2(pt0.x, pt0.y);
                _hillTexCoords[_nHillVertices++] = Vec2(pt0.x / 512, 0);
                _hillVertices[_nHillVertices] = Vec2(pt1.x, pt1.y);
                _hillTexCoords[_nHillVertices++] = Vec2(pt1.x / 512, 0);
                
                pt0 = pt1;
            }
            
            p0 = p1;
        }
        
        prevFromKeyPointI = _fromKeyPointI;
        prevToKeyPointI = _toKeyPointI;
    }
}

void Terrain::setupChipmunk() {
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    cpSpace * space = doodleTruck->getSpace();
    
    cpBody *staticBody = cpBodyNew(INFINITY, INFINITY);

    
    doodleTruck->setGround_body(staticBody);
    
    double beginY = _hillKeyPoints[2].y;
    
    double minY = beginY;
    
    /*for (int i = 0; i < 125; i++)
        if (_hillKeyPoints[i].y < minY)
            minY = _hillKeyPoints[i].y;
    */
    /*for(int i = 1; i < 124 + 1; ++i) {
        
        cocos2d::Point p0 = _hillKeyPoints[i-1];
        cocos2d::Point p1 = _hillKeyPoints[i];
        int hSegments = floorf((p1.x - p0.x) / kHillSegmentWidth);
        float dx = (p1.x - p0.x) / hSegments;
        float da = M_PI / hSegments;
        float ymid = (p0.y + p1.y) / 2;
        float ampl = (p0.y - p1.y) / 2;
        
        cocos2d::Point pt0, pt1;
        pt0 = p0;
        for (int j = 0; j < hSegments + 1; ++j) {
            
            pt1.x = p0.x + j*dx;
            pt1.y = ymid + ampl * cosf(da*j);
            
            cpVect pt_first = cpv(pt0.x * doodleTruck->getScaleY(),
                                  pt0.y * doodleTruck->getScaleY());
            
            cpVect pt_next = cpv(pt1.x * doodleTruck->getScaleY(),
                                 pt1.y * doodleTruck->getScaleY());
            
            cpShape *shape = cpSegmentShapeNew(staticBody, pt_first, pt_next, 0.0f);
            shape->e = 0.0f; shape->u = GROUND_U;
            shape->collision_type = GROUND_COLLISION;
            cpSpaceAddStaticShape(space, shape);

            
            // ccDrawLine(Vec2(pt0.x * doodleTruck->getScaleY(), pt0.y * doodleTruck->getScaleY()),
            //        Vec2(pt1.x * doodleTruck->getScaleY(), pt1.y * doodleTruck->getScaleY()));
            
            pt0 = pt1;
            
        }
    }*/
    
    for (int i = 0; i < 124 - 1; i++) {
        cpVect pt_first = cpv(_hillKeyPoints[i].x * doodleTruck->getScaleY(),
                              _hillKeyPoints[i].y * doodleTruck->getScaleY());
        
        cpVect pt_next = cpv(_hillKeyPoints[i + 1].x * doodleTruck->getScaleY(),
                             _hillKeyPoints[i + 1].y * doodleTruck->getScaleY());
        
        cpShape *shape = cpSegmentShapeNew(staticBody, pt_first, pt_next, 0.0f);
        shape->e = 0.0f; shape->u = GROUND_U;
        shape->collision_type = GROUND_COLLISION;
        cpSpaceAddStaticShape(space, shape);
    }
}

void Terrain::draw(Renderer *renderer, const Mat4& transform, uint32_t flags) {
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    CC_NODE_DRAW_SETUP();
    
    Texture2D * tex = Director::getInstance()->getTextureCache()->textureForKey("lowres-terrain-ground.png");
    ccGLBindTexture2D(tex->getName());
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords);
    
    ccDrawColor4F(1.0f, 1.0f, 1.0f, 1.0f);
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, _hillVertices);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, _hillTexCoords);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_nHillVertices);
    
    ccDrawColor4F(1.0, 1.0, 1.0, 1.0);
    
    for(int i = _fromKeyPointI; i < _toKeyPointI + 1; ++i) {
    
        cocos2d::Point p0 = _hillKeyPoints[i-1];
        cocos2d::Point p1 = _hillKeyPoints[i];
        int hSegments = floorf((p1.x - p0.x) / kHillSegmentWidth);
        float dx = (p1.x - p0.x) / hSegments;
        float da = M_PI / hSegments;
        float ymid = (p0.y + p1.y) / 2;
        float ampl = (p0.y - p1.y) / 2;
        
        cocos2d::Point pt0, pt1;
        pt0 = p0;
        for (int j = 0; j < hSegments + 1; ++j) {
            
            pt1.x = p0.x + j*dx;
            pt1.y = ymid + ampl * cosf(da*j);
            
            
           // ccDrawLine(Vec2(pt0.x * doodleTruck->getScaleY(), pt0.y * doodleTruck->getScaleY()),
               //        Vec2(pt1.x * doodleTruck->getScaleY(), pt1.y * doodleTruck->getScaleY()));
            
            pt0 = pt1;
            
        }
       // ccDrawLine(_hillKeyPoints[i-1], _hillKeyPoints[i]);
    }
}

void Terrain::setOffsetX(float newOffsetX) {
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    _offsetX = newOffsetX - 286;
    //this->setPosition(Vec2((-_offsetX), 0));
    
    resetHillVertices();
}

Sprite * Terrain::generateStripesSprite() {
    
    Sprite *sprite = Sprite::create("lowres-terrain-ground.png");
    cocos2d::Texture2D::TexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_CLAMP_TO_EDGE};
    sprite->getTexture()->setTexParameters(tp);
    return sprite;
}
