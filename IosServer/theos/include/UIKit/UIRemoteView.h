/**
 * This header is generated by class-dump-z 0.1-11o.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 */

#import "UIKit-Structs.h"
#import <UIKit/UIView.h>

@class NSString, UIRemoteWindow;

@interface UIRemoteView : UIView {
  NSString* _remoteViewIdentifier;
  UIRemoteWindow* _remoteWindow;
  BOOL _captureAllWindows;
}
-(id)initWithFrame:(CGRect)frame captureAllWindows:(BOOL)windows;
-(void)registerWithIdentifier:(id)identifier;
-(void)dealloc;
-(void)unregister;
-(id)remoteViewIdentifier;
@end

