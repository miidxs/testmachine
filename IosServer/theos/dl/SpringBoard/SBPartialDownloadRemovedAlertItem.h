/**
 * This header is generated by class-dump-z 0.2-1.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: (null)
 */

#import <Availability2.h>

#if __IPHONE_OS_VERSION_MAX_ALLOWED < __IPHONE_3_2

#import "SBAlertItem.h"

@interface SBPartialDownloadRemovedAlertItem : SBAlertItem {
  BOOL _allRemoved;
}
-(id)initWithAllDownloadsRemoved:(BOOL)allDownloadsRemoved;
-(void)alertSheet:(id)sheet buttonClicked:(int)clicked;
// inherited: -(void)configure:(BOOL)configure requirePasscodeForActions:(BOOL)actions;
// inherited: -(BOOL)shouldShowInLockScreen;
@end

#endif
