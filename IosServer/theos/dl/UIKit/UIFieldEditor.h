/**
 * This header is generated by class-dump-z 0.1-11o.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 */

#import "UIAutoscrollContainer.h"
#import "UIKit-Structs.h"
#import "UIWebDocumentView.h"
#import <Availability2.h>

@class NSString, DOMDocument, DOMHTMLElement, UIView;

#if __IPHONE_OS_VERSION_MAX_ALLOWED < __IPHONE_3_2
__attribute__((visibility("hidden")))
#endif
@interface UIFieldEditor : UIWebDocumentView <UIAutoscrollContainer> {
  DOMDocument* _document;
  DOMHTMLElement* _textElement;
  DOMHTMLElement* _sizeElement;
  NSString* _initialText;
  NSString* _initialStyle;
  UIView* _proxiedView;
@private
  unsigned _changingView : 1;
  unsigned _mouseWasDragged : 1;
  unsigned _disableNotifications : 1;
#if __IPHONE_OS_VERSION_MAX_ALLOWED < __IPHONE_3_2
  unsigned _shouldMaintainFirstResponderWhenEndEditing : 1;
#endif
  unsigned _isResigningFirstResponder : 1;
  unsigned _delegateRespondsToFieldEditorDidChange : 1;
  unsigned _delegateRespondsToShouldInsertText : 1;
  unsigned _delegateRespondsToShouldReplaceWithText : 1;
  unsigned _fieldEditorReentrancyGuard : 1;
  unsigned _reserved : 22;
}
// in a protocol: @property(assign, nonatomic) CGPoint autoscrollContentOffset;
+(id)activeFieldEditor;
+(id)sharedFieldEditor;
+(void)releaseSharedInstance;
// inherited: -(id)initWithFrame:(CGRect)frame;
// inherited: -(void)dealloc;
// inherited: -(void)selectAll;
// inherited: -(BOOL)canResignFirstResponder;
// inherited (N/A on 3.2): -(BOOL)becomeFirstResponder;
// inherited (N/A on 3.2): -(BOOL)resignFirstResponder;
// inherited (N/A on 3.2): -(id)_responderForBecomeFirstResponder;
#if __IPHONE_OS_VERSION_MAX_ALLOWED < __IPHONE_3_2
-(BOOL)shouldChangeSelectionForEvent:(GSEventRef)event;
#endif
// inherited: -(NSRange)selectionRange;
-(void)setSelection:(NSRange)selection;
-(void)revealSelection;
-(void)setTextSelectionBehavior:(int)behavior;
-(unsigned)characterOffsetAtPoint:(CGPoint)point;
// inherited: -(id)textInputTraits;
// inherited: -(BOOL)keyboardInput:(id)input shouldInsertText:(id)text isMarkedText:(BOOL)text3;
// inherited: -(BOOL)keyboardInputShouldDelete:(id)keyboardInput;
// inherited: -(BOOL)keyboardInputChanged:(id)changed;
// inherited: -(void)keyboardInputChangedSelection:(id)selection;
// inherited (N/A on 3.2): -(int)keyboardInput:(id)input positionForAutocorrection:(id)autocorrection;
-(void)becomeFieldEditorForView:(id)view;
#if __IPHONE_OS_VERSION_MAX_ALLOWED < __IPHONE_3_2
-(void)maintainFieldEditorWhenEndEditingForView:(id)view;
#endif
-(void)_setTextElementStyle:(id)style;
-(void)setStyle:(id)style;
-(id)style;
// inherited: -(id)textColorForCaretSelection;
-(void)_setTextElementString:(id)string;
-(void)setText:(id)text andSetCaretSelectionAfterText:(BOOL)text2;
// inherited: -(id)text;
-(void)setCaretColor:(id)color;
-(int)scrollXOffset;
-(int)scrollYOffset;
-(void)setScrollXOffset:(int)offset scrollYOffset:(int)offset2;
-(void)setScrollXOffset:(int)offset scrollYOffset:(int)offset2 adjustForPurpleCaret:(BOOL)purpleCaret;
-(CGSize)contentSize;
-(void)scrollSelectionToVisible:(BOOL)visible;
-(void)scrollToMakeInlineHoleVisible;
-(void)webViewDidChange:(id)webView;
-(BOOL)webView:(id)view shouldChangeSelectedDOMRange:(id)range toDOMRange:(id)domrange affinity:(int)affinity stillSelecting:(BOOL)selecting;
-(BOOL)webView:(id)view shouldInsertText:(id)text replacingDOMRange:(id)range givenAction:(int)action;
-(BOOL)webView:(id)view shouldDeleteDOMRange:(id)range;
-(BOOL)hasMarkedText;
-(id)proxiedView;
// inherited: -(void)setFrame:(CGRect)frame;
// inherited: -(void)mouseDown:(GSEventRef)down;
// inherited: -(void)mouseDragged:(GSEventRef)dragged;
// inherited: -(void)mouseUp:(GSEventRef)up;
// inherited: -(void)touchesCancelled:(id)cancelled withEvent:(id)event;
// inherited (N/A on 3.2): -(BOOL)isProxyFor:(id)aFor;
-(void)resumeWithNotification:(id)notification;
-(id)customOverlayContainer;
// inherited: -(id)automaticallySelectedOverlay;
-(void)setNotificationsDisabled:(BOOL)disabled;
#if __IPHONE_OS_VERSION_MAX_ALLOWED < __IPHONE_3_2
-(id)_parentTextViewForLoupe;
-(BOOL)_usesSingleLineSelectionBehavior;
#endif
-(BOOL)mouseEventsChangeSelection;
// inherited: -(id)selectionView;
// inherited: -(CGRect)selectionClipRect;
-(void)selectionChanged;
-(void)startAutoscroll:(CGPoint)autoscroll;
-(void)updateAutoscroll:(id)autoscroll;
-(void)autoscrollWillNotStart;
// in a protocol: -(CGRect)contentFrameForView:(id)view;
@end

