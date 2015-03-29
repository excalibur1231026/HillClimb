//
//  drawSpace.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__LabelInfo__
#define __HillClimb__LabelInfo__

int		getLimitTime(int mapIndex);
int		getStoneNum(int mapIndex);
int		getPassStoneNum(int mapIndex);
int		getFineStoneNum(int mapIndex);

void	readScore();
int		getRecordedScore(int map_index);
int		getRecordedCount(int map_index);

void	writeScore(int mapIndex, int score, int num);

#endif /* defined(__HillClimb__drawSpace__) */
