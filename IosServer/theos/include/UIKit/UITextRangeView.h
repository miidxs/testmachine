/**
 * This header is generated by class-dump-z 0.1-11o.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 */

#import "UIKit-Structs.h"
#import <UIKit/UIView.h>
#import <Availability2.h>

@class NSArray, UITextSelectionView, NSMutableArray, UISelectionGrabber, UITouch;
@protocol UITextSelectingContainer;

__attribute__((visibility("hidden")))
@interface UITextRangeView : UIView {
  UITextSelectionView* m_selectionView;
  UIView<UITextSelectingContainer>* m_container;
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_3_2
  int m_mode;
#endif
  NSArray* m_rects;
  NSMutableArray* m_rectViews;
  UITouch* m_activeTouch;
  CGRect m_startEdge;
  CGRect m_endEdge;
  CGPoint m_basePoint;
  CGPoint m_extentPoint;
  CGPoint m_initialBasePoint;
  CGPoint m_initialExtentPoint;
  float m_initialDistance;
  CGPoint m_touchOffset;
  double m_firstMovedTime;
  UISelectionGrabber* m_startGrabber;
  UISelectionGrabber* m_endGrabber;
  BOOL m_animateUpdate;
  BOOL m_baseIsStart;
  BOOL m_commandsWereShowing;
  BOOL m_inGesture;
  BOOL m_magnifying;
  BOOL m_scrolling;
  BOOL m_scaling;
  BOOL m_rotating;
}
@property(assign, nonatomic) int mode __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_3_2);
@property(copy, nonatomic) NSArray* rects;
@property(retain, nonatomic) UITouch* activeTouch;
@property(assign, nonatomic) BOOL baseIsStart;
@property(assign, nonatomic) CGRect startEdge;
@property(assign, nonatomic) CGRect endEdge;
@property(assign, nonatomic) CGPoint basePoint;
@property(assign, nonatomic) CGPoint extentPoint;
@property(assign, nonatomic) CGPoint initialBasePoint;
@property(assign, nonatomic) CGPoint initialExtentPoint;
@property(assign, nonatomic) float initialDistance;
@property(assign, nonatomic) CGPoint touchOffset;
@property(assign, nonatomic) double firstMovedTime;
@property(retain, nonatomic) UISelectionGrabber* startGrabber;
@property(retain, nonatomic) UISelectionGrabber* endGrabber;
@property(assign, nonatomic) BOOL animateUpdate;
@property(assign, nonatomic) BOOL commandsWereShowing;
@property(assign, nonatomic) BOOL magnifying;
@property(assign, nonatomic) BOOL inGesture;
@property(assign, nonatomic) BOOL isScrolling;
@property(assign, nonatomic) BOOL scaling;
@property(assign, nonatomic) BOOL rotating;
@property(readonly, assign, nonatomic) BOOL autoscrolled;
@property(readonly, assign, nonatomic) UIView<UITextSelectingContainer>* container;
@property(readonly, assign, nonatomic) UITextSelectionView* selectionView;
-(id)initWithFrame:(CGRect)frame selectionView:(id)view;
-(id)initWithFrame:(CGRect)frame textContainer:(id)container;
-(void)dealloc;
-(void)removeFromSuperview;
-(BOOL)pointInside:(CGPoint)inside withEvent:(id)event;
-(void)touchesBegan:(id)began withEvent:(id)event;
-(void)touchesMoved:(id)moved withEvent:(id)event;
-(void)touchesEnded:(id)ended withEvent:(id)event;
-(void)touchesCancelled:(id)cancelled withEvent:(id)event;
-(void)updateSelectionWithPoint:(CGPoint)point;
-(void)updateSelectionWithContentPoint:(CGPoint)contentPoint;
-(void)updateBaseIsStartWithContentPoint:(CGPoint)contentPoint;
-(void)updateWithMagnifierTerminalPoint:(BOOL)magnifierTerminalPoint;
-(void)selectionAnimationDidStop:(id)selectionAnimation finished:(id)finished;
-(void)setSelectionWithContentBasePoint:(CGPoint)contentBasePoint contentExtentPoint:(CGPoint)point;
-(void)prepareForMagnification;
-(void)doneMagnifying;
-(void)willScroll;
-(void)didScroll;
-(void)scaleWillChange;
-(void)scaleDidChange;
-(void)willRotate;
-(void)didRotate;
-(void)updateDots;
-(void)cancelDelayedActions;
-(BOOL)pointCloserToEnd:(CGPoint)end startEdge:(CGRect)edge endEdge:(CGRect)edge3;
-(void)setTouchOffset:(CGPoint)offset touchPoint:(CGPoint)point;
-(CGPoint)applyTouchOffset:(CGPoint)offset;
-(void)beginMagnifying;
-(void)updateBaseAndExtentPointsFromEdges;
-(void)updateRectViews;
-(void)updateGrabbers;
-(CGPoint)convertExtentPointToMagnifierPoint:(CGPoint)magnifierPoint;
-(CGPoint)convertFromMagnifierPoint:(CGPoint)magnifierPoint;
-(void)setEnclosingScrollViewsEnabled:(BOOL)enabled;
@end

