#import "server/HTTPServer.h"
#import "AppHTTPConnection.h"
#import "TestMachine.h"
#import "Visualizer.h"


static HTTPServer *_server;


@implementation TestMachine

+ (void)start:(int)port {
	_server = [HTTPServer new];
	[_server setName:[NSString stringWithFormat:@"testmachine2%d", port]];
	[_server setType:@"_http._tcp."];
	[_server setConnectionClass:[AppHTTPConnection class]];
	[_server setPort:port];
	
	NSString *message;
	NSError* error = NULL;
	if([_server start:&error]) {
		message = [NSString stringWithFormat:@"server started on port %d", port];
	} else {
		message = [NSString stringWithFormat:@"start server failed %@", error];
	}
	NSLog(@"TESTMACHINE: %@", message);
	//[Visualizer showMessage:message];  // stalls
}

+ (void)stop {
	NSLog(@"TESTMACHINE: stopping server");
	[_server stop];
	[_server release];
}

@end
