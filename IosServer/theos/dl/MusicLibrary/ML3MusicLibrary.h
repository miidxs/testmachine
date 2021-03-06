/**
 * This header is generated by class-dump-z 0.2a.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/MusicLibrary.framework/MusicLibrary
 */

#import "MusicLibrary-Structs.h"
#import <Foundation/NSObject.h>
#import "ML3MusicLibrary.h"

@class NSThread, NSOperationQueue, NSString;

@interface ML3MusicLibrary : NSObject {
@private
  NSOperationQueue* _backgroundOperationQueue;
  NSThread* _backgroundThread;
  NSString* _path;
  BOOL _enableWrites;
}
@property(readonly, retain) NSOperationQueue* backgroundOperationQueue;
+(void)load;
+(void)initialize;
+(void)mediaFolderPathDidChangeNotification:(id)mediaFolderPath;
+(id)sharedLibrary;
+(id)mainLibraryPath;
+(void)attachAuxiliaryDatabases:(sqlite3*)databases;
+(void)limitCacheSize:(sqlite3*)size;
+(void)ensureIndexExists:(id)exists onHandle:(sqlite3*)handle entityClass:(Class)aClass indexableSQL:(id)sql;
+(void)ensureIndexExists:(id)exists onHandle:(sqlite3*)handle entityClass:(Class)aClass properties:(id)properties;
+(void)ensureSectionAndListIndicesExist:(id)exist onHandle:(sqlite3*)handle entityClass:(Class)aClass filteredProperties:(id)properties sectionProperties:(id)properties5 orderingProperties:(id)properties6 representativeItemProperty:(id)property;
+(void)ensureIndicesExistOnHandle:(sqlite3*)handle;
+(void)ensureSectionColumnsCorrectOnHandle:(sqlite3*)handle;
+(CFDictionaryRef)threadLocalCFMutableDictionaryForKey:(id)key withValueCallbacks:(const XXStruct_MSEYlC*)valueCallbacks;
+(BOOL)statementHasRowAfterStepping:(sqlite3_stmt*)stepping;
+(id)threadLocalSectionCollator;
+(BOOL)executeSQL:(id)sql usingHandle:(sqlite3*)handle;
+(void)registerCollationsOnHandle:(sqlite3*)handle;
+(void)registerFunctionsOnHandle:(sqlite3*)handle;
+(void)registerCustomCallbacksOnHandle:(sqlite3*)handle;
-(id)initWithPath:(id)path enableWrites:(BOOL)writes;
-(void)dealloc;
-(id)entityForClass:(Class)aClass persistentID:(long long)anId;
-(void)_debugLoggingOptionsDidChangeNotification:(id)_debugLoggingOptions;
-(int)openDatabaseHandle:(sqlite3**)handle;
-(BOOL)executeSQL:(id)sql;
-(id)threadLocalDatabaseContext;
-(sqlite3*)threadLocalDatabaseHandle;
-(void)pushThreadLocalDatabaseHandle:(sqlite3*)handle;
-(void)popThreadLocalDatabaseHandle;
-(sqlite3_stmt*)preparedStatementForSQL:(id)sql;
-(void)clearThreadLocalStatementCache;
-(sqlite3_stmt*)threadLocalStatementForSQL:(id)sql;
-(void)performOperationInBackground:(id)background;
@end

@interface ML3MusicLibrary (ML3EntityStorageAdditions)
-(id)threadLocalCollectionForKey:(id)key entityClass:(Class)aClass collectionClass:(Class)aClass3;
-(id)threadLocalPropertyCacheForEntityClass:(Class)entityClass;
-(id)threadLocalPropertyRequestsForEntityClass:(Class)entityClass;
-(id)threadLocalEntityRequestsForEntityClass:(Class)entityClass;
@end

