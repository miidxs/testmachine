/**
 * This header is generated by class-dump-z 0.2-1.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: (null)
 */

#import "SpringBoard-Structs.h"
#import "SBStatusBarContentView.h"


@interface SBStatusBarBatteryView : SBStatusBarContentView {
  int _batteryCapacity;
  float _curvedCapacity;
  BOOL _batteryCharging;
  BOOL _isOnAC;
  BOOL _showBatteryView;
}
-(void)updateBattery;
-(void)_batteryStatusChanged:(id)changed;
// inherited: -(id)init;
// inherited: -(void)dealloc;
// inherited: -(void)start;
// inherited: -(void)stop;
// inherited: -(int)priority;
-(void)drawRect:(CGRect)rect;
// inherited: -(void)setVisible:(BOOL)visible;
// inherited: -(BOOL)isVisible;
// inherited: -(float)padding;
@end

