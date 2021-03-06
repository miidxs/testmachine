/**
 * This header is generated by class-dump-z 0.1-11o.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 */

#import <Foundation/NSObject.h>

@class NSIndexSet;

@interface UIGroupDeletionItem : NSObject {
  unsigned _lastIndex;
  int _group;
  NSIndexSet* _indexes;
}
-(id)initWithGroup:(int)group;
-(id)initWithGroup:(int)group andIndexes:(id)indexes;
-(id)initWithIndexes:(id)indexes inGroup:(int)group;
-(void)dealloc;
-(int)group;
-(id)indexes;
-(unsigned)lastIndex;
-(void)setLastIndex:(unsigned)index;
@end

