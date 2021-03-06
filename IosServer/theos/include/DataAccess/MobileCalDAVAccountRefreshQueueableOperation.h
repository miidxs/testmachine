/**
 * This header is generated by class-dump-z 0.2-1.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/DataAccess.framework/DataAccess
 */

#import "CalDAVRefreshActorCallback.h"
#import "CalDAVQueueableOperation.h"

@class CalDAVRefreshContext, MobileCalDAVAccountRefreshActor;

@interface MobileCalDAVAccountRefreshQueueableOperation : CalDAVQueueableOperation <CalDAVRefreshActorCallback> {
  MobileCalDAVAccountRefreshActor* _refreshActor;
}
@property(readonly, assign, nonatomic) CalDAVRefreshContext* context;
-(id)initWithQueue:(id)queue context:(id)context;
// inherited: -(void)dealloc;
// inherited: -(id)readableDescription;
// inherited: -(void)performOperation;
// in a protocol: -(oneway void)calDAVRefreshCompletedWithError:(id)error backgroundActor:(id)actor;
// inherited: -(void)finishOperation;
// inherited: -(void)cancel;
@end

