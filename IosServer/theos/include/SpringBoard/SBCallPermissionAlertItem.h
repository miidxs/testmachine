/**
 * This header is generated by class-dump-z 0.2-1.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: (null)
 */

#import "SBAlertItem.h"

@class NSURL;

@interface SBCallPermissionAlertItem : SBAlertItem {
  NSURL* _url;
}
-(id)initWithURL:(id)url;
// inherited: -(void)dealloc;
-(void)alertSheet:(id)sheet buttonClicked:(int)clicked;
// inherited: -(void)configure:(BOOL)configure requirePasscodeForActions:(BOOL)actions;
// inherited: -(BOOL)shouldShowInLockScreen;
// inherited: -(BOOL)dismissOnLock;
// inherited: -(BOOL)allowMenuButtonDismissal;
@end

