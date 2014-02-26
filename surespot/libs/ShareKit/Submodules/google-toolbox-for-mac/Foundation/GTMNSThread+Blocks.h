//
//  GTMNSThread+Blocks.h
//
//  Copyright 2012 Google Inc.
//
//  Licensed under the Apache License, Version 2.0 (the "License"); you may not
//  use this file except in compliance with the License.  You may obtain a copy
//  of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
//  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
//  License for the specific language governing permissions and limitations under
//  the License.
//
// Based on http://www.informit.com/blogs/blog.aspx?uk=Ask-Big-Nerd-Ranch-Blocks-in-Objective-C

#import <Foundation/Foundation.h>
#import "GTMDefines.h"

// Extension to NSThread to work with blocks.

#if NS_BLOCKS_AVAILABLE

@interface NSThread (GTMBlocksAdditions)

// If self is not the current thread, the block will be called asynchronously
// and this method returns immediately.
// If self is the current thread, the block will be performed immediately, and
// then this method will return.
- (void)gtm_performBlock:(void (^)())block;

- (void)gtm_performWaitingUntilDone:(BOOL)waitDone block:(void (^)())block;
+ (void)gtm_performBlockInBackground:(void (^)())block;
@end

#endif  // NS_BLOCKS_AVAILABLE

// [NSObject performSelector:onThread:...] 10.5 and later, so this makes no
// sense on any earlier SDK.
#if GTM_IPHONE_SDK || (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_5)

// A simple thread that does nothing but handle performBlock and
// performSelector calls.
@interface GTMSimpleWorkerThread : NSThread {
 @private
  CFRunLoopRef runLoop_;
  NSConditionLock *runLock_;
}

// Will stop the thread, blocking till the thread exits.
- (void)stop;

@end

#endif  // GTM_IPHONE_SDK || (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_5)
