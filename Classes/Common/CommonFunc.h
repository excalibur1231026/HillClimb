//
//  drawSpace.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__CommonFunc__
#define __HillClimb__CommonFunc__


#if !defined(MIN)
#define MIN(A,B)	({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __a : __b; })
#endif

#if !defined(MAX)
#define MAX(A,B)	({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __b : __a; })
#endif

//general image function
//CGImageRef getImageFromJPEGFile(const char *filename);
//CGImageRef getImageFromPNGFile(const char *filename);

//CGImageRef getScaledImage(CGImageRef imageRef, CGFloat w, CGFloat h);

//app common function
//NSString *	res (NSString *);
//void	getTextImage(NSString *strText, CGImageRef *normal, CGImageRef *active);

//sound
void loadSound(bool flag);
void playDriveSound();
void playStrikeSound();
void playGroundStrikeSound();

void loadMusic(bool	flag);
void playMusic();
void stopMusic();
void replayMusic();

#endif /* defined(__HillClimb__drawSpace__) */
