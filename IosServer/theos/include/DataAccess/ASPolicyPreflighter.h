/**
 * This header is generated by class-dump-z 0.2-1.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/DataAccess.framework/DataAccess
 */

#import <Foundation/NSObject.h>

@class ASAccount, ASTaskManager, ASPolicy, NSString;

@interface ASPolicyPreflighter : NSObject {
  ASAccount* _account;
  NSString* _originalKey;
  NSString* _newKey;
  id _delegate;
  ASPolicy* _policy;
  ASPolicy* _acknowledgedPolicy;
  ASTaskManager* _taskManager;
  id _contextInfo;
  BOOL _invalidated;
}
-(void)setDelegate:(id)delegate;
-(id)delegate;
-(void)setContextInfo:(id)info;
-(id)contextInfo;
-(void)_invalidate;
-(void)invalidate;
// inherited: -(void)dealloc;
-(id)initWithAccount:(id)account policyKey:(id)key;
-(id)account;
-(void)_setPolicy:(id)policy;
-(void)_setAcknowledgedPolicy:(id)policy;
-(id)_acknowledgedPolicy;
-(id)_originalKey;
-(void)provisionTask:(id)task failedWithError:(id)error;
-(void)provisionTask:(id)task wipeRequested:(BOOL)requested policies:(id)policies status:(int)status;
-(void)startPreflight;
-(void)acknowledgePolicyCompliance;
-(void)acknowledgeIntentionToRemoteWipe;
-(void)cancelPendingPreflightRequest;
@end

