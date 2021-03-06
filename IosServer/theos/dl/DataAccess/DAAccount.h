/**
 * This header is generated by class-dump-z 0.2-1.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/DataAccess.framework/DataAccess
 */

#import "DataAccess-Structs.h"
#import "AccountCreationProtocol.h"
#import <AccountSettings/BasicAccount.h>
#import "DAAccount.h"

@class NSMutableDictionary, NSData, NSString, NSArray;

@interface DAAccount : BasicAccount <AccountCreationProtocol> {
  int _accountTypes;
  BOOL _hasDirtyBits;
  BOOL _hasInitted;
  BOOL _shouldPromptForPassword;
  BOOL _haveLookedUpPassword;
  NSString* _cachedPassword;
  BOOL _shouldFailAllTasks;
  int _originalAccountTypes;
  int _contactsChangeType;
  int _eventsChangeType;
  NSMutableDictionary* _haveWarnedAboutCertDict;
}
@property(copy) NSData* identityPersist;
@property(assign) BOOL shouldFailAllTasks;
@property(assign) BOOL shouldPromptForPassword;
@property(copy) NSArray* emailAddresses;
@property(copy) NSString* emailAddress;
@property(assign) BOOL useSSL;
@property(copy) NSString* password;
@property(assign) int port;
@property(copy) NSString* host;
@property(copy) NSString* username;
@property(copy) NSString* accountDescription;
@property(readonly, copy) NSString* persistentUUID;
@property(readonly, copy) NSString* tag;
@property(assign, setter=setDAAccountVersion:) int daAccountVersion;
+(id)basicAccountProperties;
+(Class)accountClass;
+(Class)accountClassWithProperties:(id)properties;
+(Class)clientClass;
+(Class)daemonClass;
+(void)vendDaemons;
+(id)defaultProperties;
+(id)newAccountOfClass:(Class)aClass;
// inherited: -(void)dealloc;
// inherited: -(id)initWithProperties:(id)properties;
// inherited: -(id)init;
-(void)resetAccountID;
-(id)accountID;
// inherited: -(id)syncStoreIdentifier;
-(void)_setPersistentUUID:(id)uuid;
-(BOOL)supportsAccountType:(int)type;
-(BOOL)isDisabled;
-(BOOL)enabledForAccountType:(int)accountType;
-(void)setEnabled:(BOOL)enabled forAccountType:(int)accountType changeType:(int)type;
-(BOOL)originallyEnabledForAccountType:(int)accountType;
-(int)accountChangeTypeForAccountType:(int)accountType;
-(id)initProperClassWithProperties:(id)properties;
// in a protocol: -(id)initWithBasicAccount:(id)basicAccount;
-(BOOL)accountBoolPropertyForKey:(id)key;
-(void)setAccountBoolProperty:(BOOL)property forKey:(id)key;
-(int)accountIntPropertyForKey:(id)key;
-(void)setAccountIntProperty:(int)property forKey:(id)key;
-(BOOL)autodiscoverAccountConfigurationWithConsumer:(id)consumer;
-(void)cancelAutodiscovery;
-(void)resumeMonitoringFoldersWithIDs:(id)ids;
-(void)suspendMonitoringFoldersWithIDs:(id)ids;
-(void)stopMonitoringFolderWithID:(id)anId;
-(id)stateString;
-(void)takeValuesFromAccount:(id)account;
-(id)usernameWithoutDomain;
-(void)checkValidityWithConsumer:(id)consumer;
-(void)_removeHostsToTrust;
-(BOOL)_upgradeSelfFromPreKirkwoodWithAccountManager:(id)accountManager;
-(BOOL)upgradeAccountIfNecessaryWithAccountManager:(id)accountManager;
-(void)removePasswordFromKeychain;
-(void)savePasswordInKeychain;
-(void)blowAwayCachedPassword;
-(id)version;
-(void)setVersion:(id)version;
-(BOOL)accountContainsEmailAddress:(id)address;
-(id)urlForKeychain;
-(void)_setProperties:(id)properties;
-(BOOL)hasDirtyBits;
-(void)tearDown;
-(BOOL)monitorFoldersWithIDs:(id)ids;
-(BOOL)monitorFolderWithID:(id)anId;
-(void)stopMonitoringFoldersWithIDs:(id)ids;
-(void)stopMonitoringFolders;
-(id)defaultContainerIdentifierForDataclass:(int)dataclass;
-(void)setP12Data:(id)data password:(id)password;
-(void)saveAccountProperties;
-(id)_exceptionsDict;
-(CFDataRef)exceptionsForDigest:(id)digest;
-(void)setExceptions:(CFDataRef)exceptions forDigest:(id)digest;
-(void)cleanupAccountFiles;
-(void)saveAccountSettings;
-(BOOL)haveWarnedAboutCert:(id)cert;
-(void)setHaveWarnedAboutCert:(id)cert;
-(BOOL)resetCertWarnings;
@end

@interface DAAccount (ASExtension)
-(BOOL)isActiveSyncAccount;
@end

@interface DAAccount (ConcreteAccounts)
+(id)newEASAccount;
+(id)newLDAPAccount;
+(id)newCalDAVAccount;
@end

@interface DAAccount (CertificateErrors)
-(id)localizedCertificateErrorStringForHost:(id)host;
-(BOOL)_userResponseForServerTrustFromHost:(id)host digest:(id)digest;
-(BOOL)shouldAllowTrust:(SecTrust*)trust forHost:(id)host;
@end

@interface DAAccount (EventsSupport)
-(id)defaultEventsFolder;
-(id)eventsFolders;
-(void)synchronizeEventsFolder:(id)folder previousTag:(id)tag actions:(id)actions highestIdContext:(XXStruct_SMhV9B*)context isInitialUberSync:(BOOL)sync isResyncAfterConnectionFailed:(BOOL)failed consumer:(id)consumer;
-(BOOL)sendEmailsForCalEvents:(id)calEvents consumer:(id)consumer;
@end

@interface DAAccount (ContactsSupport)
-(id)defaultContactsFolder;
-(id)contactsFolders;
-(void)synchronizeContactsFolder:(id)folder previousTag:(id)tag actions:(id)actions highestIdContext:(XXStruct_YWGUWB*)context isInitialUberSync:(BOOL)sync isResyncAfterConnectionFailed:(BOOL)failed consumer:(id)consumer;
@end

@interface DAAccount (InvitationSupport)
-(BOOL)reattemptInvitationLinkageForMetaData:(id)metaData inFolderWithId:(id)anId;
@end

@interface DAAccount (MailFolderSupport)
-(id)inboxFolder;
-(id)sentItemsFolder;
-(id)deletedItemsFolder;
@end

@interface DAAccount (Searching)
-(void)performSearchQuery:(id)query consumer:(id)consumer;
-(void)cancelSearchQuery:(id)query;
-(void)cancelAllSearchQueries;
-(BOOL)searchQueriesRunning;
-(int)supportsMailboxSearch;
@end

@interface DAAccount (LDAPExtension)
-(BOOL)isLDAPAccount;
@end

@interface DAAccount (CalDAVExtension)
-(BOOL)isCalDAVAccount;
@end

