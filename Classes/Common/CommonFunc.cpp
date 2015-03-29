//
//  drawSpace.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "CommonFunc.h"
#import "GameDefine.h"

#pragma mark general image function

/*CGImageRef getImageFromJPEGFile(const char *filename)
{
    CGImageRef image;
    CGDataProviderRef provider;
    CFStringRef path;
    CFURLRef url;
    
    path = CFStringCreateWithCString (NULL, filename, kCFStringEncodingUTF8);
    url = CFURLCreateWithFileSystemPath (NULL, path, kCFURLPOSIXPathStyle, NO);
    CFRelease(path);
    provider = CGDataProviderCreateWithURL (url);
    CFRelease (url);
    image = CGImageCreateWithJPEGDataProvider (provider,
                                               NULL,
                                               true,
                                               kCGRenderingIntentDefault);
    CGDataProviderRelease (provider);
    return image;
}

CGImageRef getImageFromPNGFile(const char *filename)
{
    CGImageRef image;
    CGDataProviderRef provider;
    CFStringRef path;
    CFURLRef url;
    
    NSString * strPath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:filename] ofType:nil];
    
    path = CFStringCreateWithCString (NULL, strPath.UTF8String, kCFStringEncodingUTF8);
    url = CFURLCreateWithFileSystemPath (NULL, path, kCFURLPOSIXPathStyle, NO);
    CFRelease(path);
    provider = CGDataProviderCreateWithURL (url);
    CFRelease (url);
    image = CGImageCreateWithPNGDataProvider (provider,
                                              NULL,
                                              true,
                                              kCGRenderingIntentDefault);
    CGDataProviderRelease (provider);
    return image;
}

CGImageRef getScaledImage(CGImageRef imageRef, CGFloat w, CGFloat h)
{
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef	context = CGBitmapContextCreate(nil, w, h, 8, 0, colorSpace, kCGImageAlphaPremultipliedLast);
    
    UIGraphicsPushContext(context);
    CGContextDrawImage(context, CGRectMake(0, 0, w, h), imageRef);
    UIGraphicsPopContext();
    
    CGImageRef image = CGBitmapContextCreateImage(context);
    
    CGContextRelease(context);
    CGColorSpaceRelease(colorSpace);
    
    return image;
}*/
/*
#pragma mark app common function
NSString *	res (NSString * data)
{
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
    {
        return [data stringByReplacingOccurrencesOfString:@"." withString:@"_iPad."];
    }
    else {
        return data;
    }
}

void	getTextImage(NSString *strText, CGImageRef *normal, CGImageRef *active)
{
    NSString * normal_path = [NSString stringWithFormat:@"%@_nor.png", [strText lowercaseString]];
    NSString * high_path = [NSString stringWithFormat:@"%@_high.png", [strText lowercaseString]];
    
    *normal = getImageFromPNGFile(normal_path.UTF8String);
    *active = getImageFromPNGFile(high_path.UTF8String);
}

#pragma mark SOUND

#import <AudioToolbox/AudioToolbox.h>

SystemSoundID g_driveSound;
SystemSoundID g_strikeSound;
SystemSoundID g_groundStrikeSound;
SystemSoundID g_mainMusic;

BOOL	g_soundFlag = YES;
BOOL	g_musicFlag = YES;

static void MyCompletionCallback(SystemSoundID mySSID, void* myURLRef){
    if (g_musicFlag)
        AudioServicesPlaySystemSound(mySSID);
}

void loadMusic(BOOL flag)
{
    g_musicFlag = flag;
    if (!g_musicFlag)
        return;
    
    NSString * szMainSound = [[NSBundle mainBundle] pathForResource:SND_BG ofType:nil];
    NSURL *urlMainSound = [NSURL fileURLWithPath:szMainSound];
    AudioServicesCreateSystemSoundID( (CFURLRef)urlMainSound, &g_mainMusic);
    
    AudioServicesAddSystemSoundCompletion(g_mainMusic, NULL, NULL, MyCompletionCallback, NULL);
}

void loadSound(BOOL flag)
{
    g_soundFlag = flag;
    if (!g_soundFlag)
        return;
    
    NSString * szDriveSound = [[NSBundle mainBundle] pathForResource:SND_DRIVE ofType:nil];
    NSURL *urlDriveSound = [NSURL fileURLWithPath:szDriveSound];
    AudioServicesCreateSystemSoundID( (CFURLRef)urlDriveSound, &g_driveSound);
    
    NSString * szStrikeSound = [[NSBundle mainBundle] pathForResource:SND_STRIKE ofType:nil];
    NSURL *urlStrikeSound = [NSURL fileURLWithPath:szStrikeSound];
    AudioServicesCreateSystemSoundID( (CFURLRef)urlStrikeSound, &g_strikeSound);
    
    NSString * szGroundStrikeSound = [[NSBundle mainBundle] pathForResource:SND_GROUND_STRIKE ofType:nil];
    NSURL *urlGroundStrikeSound = [NSURL fileURLWithPath:szGroundStrikeSound];
    AudioServicesCreateSystemSoundID( (CFURLRef)urlGroundStrikeSound, &g_groundStrikeSound);
}

void playDriveSound()
{
    if (!g_soundFlag)
        return;
    
    AudioServicesPlaySystemSound(g_driveSound);
}

void playStrikeSound()
{
    if (!g_soundFlag) 
        return;
    
    AudioServicesPlaySystemSound(g_strikeSound);
}

void playGroundStrikeSound()
{
    if (!g_soundFlag) 
        return;
    
    AudioServicesPlaySystemSound(g_groundStrikeSound);
}

void playMusic()
{
    if(!g_musicFlag)
        return;
    AudioServicesPlaySystemSound(g_mainMusic);
}

void replayMusic()
{
    playMusic();
}

void stopMusic()
{
    if (!g_mainMusic) 
        return;
    
    AudioServicesDisposeSystemSoundID(g_mainMusic);
}*/