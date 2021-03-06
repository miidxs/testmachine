/**
 * This header is generated by class-dump-z 0.2-1.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/Message.framework/Message
 */

#import "DAMailboxStreamingContentConsumer.h"
#import "DAMailAccountConsumer.h"
#import "DAMailboxRequestConsumer.h"

@class ActivityMonitor, NSArray, NSMutableData, NSString;

@interface DAMailAccountSyncConsumer : DAMailAccountConsumer <DAMailboxRequestConsumer, DAMailboxStreamingContentConsumer> {
  NSArray* requests;
  NSArray* consumers;
  NSString* tag;
  NSString* accountID;
  BOOL receivedFirstItem;
  BOOL moreAvailable;
  BOOL firstSyncBatch;
  int syncKeyResets;
  int serverErrors;
  id _streamConsumer;
  ActivityMonitor* monitor;
  NSMutableData* bodyData;
}
@property(retain, nonatomic) id streamConsumer;
-(void)reset;
-(void)setTag:(id)tag;
-(id)originalThreadMonitor;
-(id)initWithCurrentTag:(id)currentTag andAccountID:(id)anId;
-(id)actionsConsumer;
-(void)partialResultsForMailbox:(id)mailbox actions:(id)actions responses:(id)responses percentComplete:(double)complete moreAvailable:(BOOL)available;
// in a protocol: -(void)resultsForMailbox:(id)mailbox newTag:(id)tag actions:(id)actions responses:(id)responses percentComplete:(double)complete moreAvailable:(BOOL)available;
// in a protocol: -(BOOL)shouldBeginStreamingForMailMessage:(id)mailMessage format:(int)format;
// in a protocol: -(void)consumeData:(char*)data length:(int)length format:(int)format mailMessage:(id)message;
// in a protocol: -(void)didEndStreamingForMailMessage:(id)mailMessage;
// in a protocol: -(void)actionFailed:(int)failed forTask:(id)task error:(id)error;
// inherited: -(void)dealloc;
@end

