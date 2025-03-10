//
// Created by shell on 2025/3/1.
//

#import <AppKit/AppKit.h>

@interface MinecraftProtocol : NSObject

+(MinecraftProtocol*)Make:(NSString*)host;

-(void)connect;
@end
