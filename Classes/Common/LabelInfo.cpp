//
//  LabelInfo.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "LabelInfo.h"
#include "GameDefine.h"

int g_limitTime[] = {
    30,
    45,
    40,
    60,
    50,
    35,
    35,
    30,
    
    30,
    35,
    35,
    50,
    60,
    40,
    45,
    30,
};
int g_stoneNum[] = {
    10,
    2,
    3,
    5,
};

int g_passStoneNum[] =
{
    6,
    1,
    2,
    3,
};

int g_fineStoneNum[] =
{
    9,
    2,
    3,
    4,
};

bool read_flag = false;

int     getLimitTime(int mapIndex)
{
    return g_limitTime[mapIndex];
}

int g_levelScore[MAX_MAP];
int g_levelCount[MAX_MAP];
int		getStoneNum(int mapIndex)
{
    int ix = mapIndex % STONE_KIND_NUM;
    return g_stoneNum[ix];
}

int		getPassStoneNum(int mapIndex)
{
    int ix = mapIndex % STONE_KIND_NUM;
    return g_passStoneNum[ix];
}

int		getFineStoneNum(int mapIndex)
{
    int ix = mapIndex % STONE_KIND_NUM;
    return g_fineStoneNum[ix];
}

void	readScore()
{
   /* memset(g_levelScore, 0, sizeof(g_levelScore));
    memset(g_levelCount, 0, sizeof(g_levelCount));
    
    NSArray *path = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory = [path objectAtIndex:0];
    NSString *szFile = [documentDirectory stringByAppendingPathComponent:SCORE_FILE];
    if (!read_flag) {
        FILE * fr = fopen(szFile.UTF8String, "rb");
        if (!fr)
            return;
        
        fread(g_levelScore, sizeof(g_levelScore), 1, fr);
        fread(g_levelCount, sizeof(g_levelCount), 1, fr);
        
        read_flag = YES;
        fclose(fr);
    }*/
}

int		getRecordedScore(int map_index)
{
    if (!read_flag) {
        readScore();
    }
    return g_levelScore[map_index];
}

int		getRecordedCount(int map_index)
{
    if (!read_flag) {
        readScore();
    }
    return g_levelCount[map_index];
}

void	writeScore(int mapIndex, int score, int count)
{
    /*NSArray *path = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory = [path objectAtIndex:0];
    NSString *szFile = [documentDirectory stringByAppendingPathComponent:SCORE_FILE];
    
    FILE * fw = fopen(szFile.UTF8String, "wb");
    if (!fw)
        return;
    
    if (score > g_levelScore[mapIndex]) 
    {
        g_levelScore[mapIndex] = score;
        g_levelCount[mapIndex] = count;
    }
    fwrite(g_levelScore, sizeof(g_levelScore), 1, fw);
    fwrite(g_levelCount, sizeof(g_levelCount), 1, fw);
    fclose(fw);*/
}
