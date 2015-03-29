//
//  RoadManager.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__RoadManager__
#define __HillClimb__RoadManager__

#include <cocos/cocos2d.h>
#include "chipmunk.h"

#define MAX_POINT	512

USING_NS_CC;

class RoadManager {
    
private:
    //Vector<Sprite *>  childSprites;
	
	double					beginY;
	double					endY;
	double					minY;
	
	cpVect				pt_road[MAX_POINT];
	int					pt_num;
	
	int					total_point;
	
    std::string			format_string;
	int					road_height;
	int					road_width;
	int					road_count;
	
	Sprite **			road_sprite;
	Texture2D **		road_texture;
    
public:
    
    RoadManager();
    ~RoadManager();
    
    double getBeginY() {return beginY;}
    double getEndY() {return endY;}
    double getMinY() {return minY;}
    
    int getPointCount() {return total_point;}
  
    void initPoint();
    
    void addVisibleRoad(Layer *parent_layer);
    void setupChipmunk();
    
    cpVect point(int ix);
    int	points();
    
    int getImageNum();
    
};

#endif /* defined(__HillClimb__RoadManager__) */