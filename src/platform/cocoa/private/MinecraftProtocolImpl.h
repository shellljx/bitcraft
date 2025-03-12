//
// Created by shell on 2025/3/1.
//

#import <Foundation/Foundation.h>

@interface MinecraftProtocolImpl : NSObject
+(MinecraftProtocolImpl*)Make:(NSString*)host;
-(void)connect;
@end
