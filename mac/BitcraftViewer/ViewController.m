//
//  ViewController.m
//  BitcraftViewer
//
//  Created by shell on 2025/2/28.
//

#import "ViewController.h"
#import <MinecraftProtocol.h>

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSString* host = @"127.0.0.1";
        MinecraftProtocol* protocol = [MinecraftProtocol Make:host];
        [protocol connect];

        sleep(10); // 让当前线程暂停 10 秒
    });
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


@end
