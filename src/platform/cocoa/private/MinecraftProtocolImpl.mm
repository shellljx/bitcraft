#import "MinecraftProtocolImpl.h"
#include "base/protocol/MinecraftProtocol.h"

@interface MinecraftProtocolImpl ()

@property(nonatomic) std::shared_ptr<bitcraft::MinecraftProtocol> protocol;

@end

@implementation MinecraftProtocolImpl {
}

+ (MinecraftProtocolImpl*)Make:(NSString*)host{
    auto data = bitcraft::MinecraftProtocol::Make("127.0.0.1", 25565, "1");
    MinecraftProtocolImpl* protocol = [[[MinecraftProtocolImpl alloc] initWithMinecraftProtocol:data]autorelease];
    return protocol;
}

-(instancetype) initWithMinecraftProtocol:(std::shared_ptr<bitcraft::MinecraftProtocol>)value {
    if (self = [super init]) {
        _protocol = value;
    }
    return self;
}

-(void)connect {
    _protocol->connect();
}
@end
