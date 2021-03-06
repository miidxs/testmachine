/**
 * This header is generated by class-dump-z 0.2-1.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: (null)
 */

#import "SpringBoard-Structs.h"
#import "SBIcon.h"

@class NSString, SBApplication;

@interface SBSpotlightIcon : SBIcon {
  SBApplication* _app;
  NSString* _iconPath;
  NSString* _spotlightCategory;
}
+(id)displayIdentifierForSpotlightCategory:(id)spotlightCategory andAppDisplayIdentifier:(id)identifier;
-(id)initWithAppDisplayIdentifier:(id)appDisplayIdentifier spotlightCategory:(id)category iconName:(id)name;
// inherited: -(void)dealloc;
// inherited: -(id)smallIcon;
// inherited: -(void)setIsHidden:(BOOL)hidden animate:(BOOL)animate;
// inherited: -(BOOL)isHidden;
// inherited: -(id)displayIdentifier;
@end

