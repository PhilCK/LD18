//
//  LD18AppDelegate.h
//  LD18
//
//  Created by Philip Cooper-King on 22/08/2010.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#if (MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_5)
@interface LD18AppDelegate : NSObject
#else
@interface LD18AppDelegate : NSObject <NSApplicationDelegate>
#endif


{
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
