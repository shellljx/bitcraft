#import "MinecraftProtocol.h"
#import "platform/cocoa/private/MinecraftProtocolImpl.h"

@interface MinecraftProtocol()

@property(nonatomic,strong)MinecraftProtocolImpl* protocol;

@end

@implementation MinecraftProtocol{
}

+(MinecraftProtocol*)Make:(NSString *)host{
    MinecraftProtocolImpl* protocolImp = [MinecraftProtocolImpl Make:host];
    return [[[MinecraftProtocol alloc]initWidthProtocol:protocolImp] autorelease];
}

-(instancetype)initWidthProtocol:(MinecraftProtocolImpl*)value{
    if (self=[super init]) {
        self.protocol = value;
    }
    return self;
}
-(void)connect{
    [_protocol connect];
}

-(void)dealloc {
    if (_protocol) {
        [_protocol release];
        _protocol = nil;
    }
    [super dealloc];
}

@end
