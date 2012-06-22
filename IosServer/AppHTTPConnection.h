//
//  This class was created by Nonnus,
//  who graciously decided to share it with the CocoaHTTPServer community.
//

#import <Foundation/Foundation.h>
#import "server/HTTPConnection.h"

@interface AppHTTPConnection : HTTPConnection
{
  int dataStartIndex;
  NSMutableData* multipartData;
  BOOL postHeaderOK;
}

@property(nonatomic, retain) NSMutableData* multipartData;

@end
