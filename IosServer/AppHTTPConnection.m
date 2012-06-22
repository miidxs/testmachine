#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#import "server/HTTPServer.h"
#import "server/HTTPResponse.h"
#import "AppHTTPConnection.h"
#import "IosDriver.h"
#import "brominet/UIApplication+XMLDescription.h"
#import "NSData+Base64.h"
#import "Visualizer.h"


@implementation AppHTTPConnection

@synthesize multipartData;

/**
 * Returns whether or not the server will accept POSTs.
 * That is, whether the server will accept uploaded data for the given URI.
**/
- (BOOL)supportsPOST:(NSString *)path withSize:(UInt64)contentLength
{
//	NSLog(@"POST:%@", path);
	
	dataStartIndex = 0;
	self.multipartData = [[[NSMutableData alloc] init] autorelease];
	postHeaderOK = FALSE;
	
	return YES;
}

/**
 * This method is called to get a response for a request.
 * You may return any object that adopts the HTTPResponse protocol.
 * The HTTPServer comes with two such classes: HTTPFileResponse and HTTPDataResponse.
 * HTTPFileResponse is a wrapper for an NSFileHandle object, and is the preferred way to send a file response.
 * HTTPDataResopnse is a wrapper for an NSData object, and may be used to send a custom response.
**/
- (NSObject<HTTPResponse> *)httpResponseForURI:(NSString *)path {
	NSMutableString *response = [[NSMutableString alloc] init];
	if ([path isEqual:@"/"]) {
		[Visualizer showMessage:@"(dump screen)"];

		[response appendString:@"<?xml version=\"1.0\"?>"];
		[response appendString:[[UIApplication sharedApplication] xmlDescription]];
	} else if ([path isEqual:@"/rpc"]) {
		NSLog(@"TESTMACHINE: request: %@", [[[NSString alloc] initWithData:multipartData encoding:NSUTF8StringEncoding] autorelease]);	
		
		xmlDoc *doc = xmlReadMemory(multipartData.bytes, multipartData.length, NULL, "UTF-8", 0);
		xmlXPathContext *xpathCtx = xmlXPathNewContext(doc);
		
		xmlXPathObject *methodNameObj = xmlXPathEvalExpression((const xmlChar *)"//methodName/text()", xpathCtx);
		NSString *methodName = [NSString stringWithUTF8String:(const char *)methodNameObj->nodesetval->nodeTab[0]->content];
		[Visualizer showMessage:methodName];
		
		xmlXPathObject *paramsObj = xmlXPathEvalExpression((const xmlChar *)"//param/value//text()", xpathCtx);  // FIXME: force element if text() is empty
		int paramCount = paramsObj->nodesetval ? paramsObj->nodesetval->nodeNr : 0;
		NSString **params = (NSString **)malloc(paramCount * sizeof(NSString *));
		for (int i = 0; i < paramCount; i++) {
			params[i] = [NSString stringWithUTF8String:(const char *)paramsObj->nodesetval->nodeTab[i]->content];
		}
		
		[response appendString:@"<methodResponse>"];
		@try {
		    [response appendString:@"<params>"];
		    [response appendString:@"  <param>"];
		    [response appendString:@"    <value>"];

		    IosDriver *driver = [IosDriver instance];
		    if ([methodName isEqual:@"tap"]) {
				if (paramCount == 1) {
					[response appendFormat:@"      <boolean>%d</boolean>", [driver tap:params[0]]];
				} else {
					[response appendFormat:@"      <boolean>%d</boolean>", [driver tap:params[0] x:params[1].doubleValue y:params[2].doubleValue]];
				}
			} else if ([methodName isEqual:@"swipe"]) {
				[response appendFormat:@"      <boolean>%d</boolean>", [driver swipe:params[0] x1:params[1].doubleValue y1:params[2].doubleValue x2:params[3].doubleValue y2:params[4].doubleValue]];
			} else if ([methodName isEqual:@"setText"]) {
				[response appendFormat:@"      <boolean>%d</boolean>", [driver setText:params[0] text:params[1]]];
			} else if ([methodName isEqual:@"setSwitch"]) {
				[response appendFormat:@"      <boolean>%d</boolean>", [driver setSwitch:params[0] on:[params[1] isEqual:@"1"]]];
			} else if ([methodName isEqual:@"selectPickerViewRow"]) {
				[response appendFormat:@"      <boolean>%d</boolean>", [driver selectPickerViewRow:params[0] rowIndex:params[1].intValue componentIndex:params[2].intValue]];
			} else if ([methodName isEqual:@"scrollToTableViewRow"]) {
				[response appendFormat:@"      <boolean>%d</boolean>", [driver scrollToTableViewRow:params[0] sectionIndex:params[1].intValue rowIndex:params[1].intValue]];
			} else if ([methodName isEqual:@"check"]) {
				[response appendFormat:@"      <boolean>%d</boolean>", [driver check:params[0]]];
			} else if ([methodName isEqual:@"startPlayingSound"]) {
				[driver startPlayingSound:[NSData dataFromBase64String:params[0]]];
			} else if ([methodName isEqual:@"pausePlayingSound"]) {
				[driver pausePlayingSound];
			} else if ([methodName isEqual:@"resumePlayingSound"]) {
				[driver resumePlayingSound];
			} else if ([methodName isEqual:@"openUrl"]) {
				[driver openUrl:params[0]];
			} else if ([methodName isEqual:@"startRecordingSound"]) {
				[driver startRecordingSound:params[0].doubleValue];
			} else if ([methodName isEqual:@"finishRecordingSound"]) {
				[response appendFormat:@"      <base64>%@</base64>", [[driver finishRecordingSound] base64EncodedString]];
			} else if ([methodName isEqual:@"notifyPost"]) {
				[driver notifyPost:params[0] delay:params[1].doubleValue];
			}
		    [response appendString:@"    </value>"];
		    [response appendString:@"  </param>"];
		    [response appendFormat:@"</params>"];
		} @catch (NSException *e) {
			[response setString:@""];
			[response appendString:@"<methodResponse>"];
		    [response appendString:@"<fault>"];
		    [response appendString:@"  <value>"];
		    [response appendString:@"    <struct>"];
		    [response appendString:@"      <member><name>faultCode</name><value><int>-1</int></value></member>"];
		    [response appendFormat:@"      <member><name>faultString</name><value><string>%@</string></value></member>", e];
		    [response appendString:@"    </struct>"];
		    [response appendString:@"  </value>"];
		    [response appendString:@"</fault>"];
		}		
	    [response appendString:@"</methodResponse>"];
		
		free(params);
	    xmlXPathFreeObject(paramsObj);		
	    xmlXPathFreeObject(methodNameObj);		
	    xmlXPathFreeContext(xpathCtx); 
	    xmlFreeDoc(doc);
	}

	NSLog(@"TESTMACHINE: response: %@", response);
	
	NSData *browseData = [response dataUsingEncoding:NSUTF8StringEncoding];
	HTTPDataResponse *r = [[[HTTPDataResponse alloc] initWithData:browseData] autorelease];
	return r;
}

/**
 * This method is called to handle data read from a POST.
 * The given data is part of the POST body.
**/
- (void)processPostDataChunk:(NSData *)postDataChunk
{
	[self.multipartData appendData:postDataChunk];
}

@end
