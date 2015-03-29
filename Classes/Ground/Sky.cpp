

#include "Sky.h"
#include "DoodleTruck.h"
#include "XSprite.h"

Sky::Sky() {
    
    addXTexture("sky-bg-rainbow.png");
    Texture2D * tex = Director::getInstance()->getTextureCache()->textureForKey("sky-bg-rainbow.png");
    cocos2d::Texture2D::TexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_CLAMP_TO_EDGE};
    tex->setTexParameters(tp);
    
    this->setShaderProgram(ShaderCache::getInstance()->getProgram(kCCShader_PositionTexture));
}

void Sky::draw(Renderer *renderer, const Mat4& transform, uint32_t flags) {
    
    cocos2d::Size s = Director::getInstance()->getWinSize();
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    CC_NODE_DRAW_SETUP();
    
    Vec2 _skyVertices[4];
    Vec2 _skyTexCoords[4];
    
    _skyVertices[0] = Vec2(0, 0);
    _skyTexCoords[0] = Vec2(1.0, 1.0f);
    _skyVertices[1] = Vec2(s.width, 0);
    _skyTexCoords[1] = Vec2(1.0f, 1.0f);
    
    _skyVertices[2] = Vec2(0, s.height);
    _skyTexCoords[2] = Vec2(31.0f, 63.0f);
    _skyVertices[3] = Vec2(s.width, s.height);
    _skyTexCoords[3] = Vec2(31.0f, 63.0f);
    
    
    Texture2D * tex = Director::getInstance()->getTextureCache()->textureForKey("sky-bg-rainbow.png");
    GL::bindTexture2D(tex->getName());
    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
    
    ccDrawColor4F(1.0f, 1.0f, 1.0f, 1.0f);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, _skyVertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, _skyTexCoords);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)4);
    
   // ccDrawColor4F(1.0, 1.0, 1.0, 1.0);*/
}