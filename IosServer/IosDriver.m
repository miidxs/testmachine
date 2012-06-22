//
//  This class was created by Nonnus,
//  who graciously decided to share it with the CocoaHTTPServer community.
//

#import <AudioToolbox/AudioToolbox.h>
#import "brominet/UIApplication+XMLDescription.h"
#import "brominet/XPathQuery.h"
#import "IosDriver.h"
#import "KIF/Additions/UIView-KIFAdditions.h"
#import "HTTPResponse.h"
#import <notify.h>


static IosDriver* _instance = NULL;


@implementation IosDriver

+ (IosDriver *)instance {
	if (_instance == NULL) {
		_instance = [[IosDriver alloc] init];
	}
	return _instance;
}

- (id)init {
	self = [super init];
	if (self) {

	}
	return self;
}

- (void)dealloc {
	if (_player) {
		[_player release];
	}
	if (_recorder) {
		[_recorder dealloc];
	}
	
	[super dealloc];
}

// copied from ScriptRunner.m
//
//viewsForXPath:
//
//Generates an XML document from the current view tree and runs the specified
//XPath query on the document. If the resulting nodes contain "address" values
//then these values are interrogated to determine if they are UIViews. All
//UIViews found in this way are returned in the array.
//
- (NSArray *)viewsForXPath:(NSString *)xpath
{
	//printf("XML \n%s\n\n", [[[[UIApplication sharedApplication] keyWindow] xmlDescription] cStringUsingEncoding:NSUTF8StringEncoding]);
	NSData *resultData =
	[[[UIApplication sharedApplication] xmlDescription] dataUsingEncoding: NSUTF8StringEncoding];
	
	NSArray *queryResults = PerformXMLXPathQuery(resultData, xpath);
	//printf("%s", [queryResults.description UTF8String]);
	NSMutableArray *views =
	[NSMutableArray arrayWithCapacity:[queryResults count]];
	for (NSDictionary *result in queryResults)
	{
		int i;
		int count = [[result objectForKey:@"nodeChildArray"] count];
		for (i = 0; i < count; i++)
		{
			NSDictionary *childNode = [[result objectForKey:@"nodeChildArray"] objectAtIndex:i];
			if ([[childNode objectForKey:@"nodeName"] isEqualToString:@"address"] )
			{
				UIView *view =
				(UIView *)[[childNode objectForKey:@"nodeContent"] integerValue];
				NSAssert([view isKindOfClass:[UIView class]],
						 @"XPath selected memory address did not contain a UIView");
				[views addObject:view];
				break;
			}
		}
	}
	return views;
}

- (UIView *)findView:(NSString *)xpath {
	NSArray *views = [self viewsForXPath:xpath];
	if (views.count == 0) {
		return NULL;
	}
	if (views.count > 1) {
		[NSException raise:@"TestMachine" format:@"expression selected %d nodes, exactely 1 is required", [views count]];
	}
	return [views objectAtIndex:0];
}

- (BOOL)tap:(NSString *)xpath {
	UIView *view = [self findView:xpath];
	if (view) {
		[view tap];
		return TRUE;
	}
	return FALSE;
}

- (BOOL)tap:(NSString *)xpath x:(double)x y:(double)y {
	UIView *view = [self findView:xpath];
	if (view) {
		[view tapAtPoint:CGPointMake(x, y)];
		return TRUE;
	}
	return FALSE;
}

- (BOOL)swipe:(NSString *)xpath x1:(double)x1 y1:(double)y1 x2:(double)x2 y2:(double)y2 {	
	UIView *view = [self findView:xpath];
	if (view) {
		[view dragFromPoint:CGPointMake(x1, y1) toPoint:CGPointMake(x2, y2)];
		return TRUE;
	}
	return FALSE;
}

- (BOOL)setText:(NSString *)xpath text:(NSString *)text {
	UIView *view = [self findView:xpath];	
	if (view) {
		[view performSelector:@selector(setText:) withObject:text];
		return TRUE;
	}
	return FALSE;
}

- (BOOL)setSwitch:(NSString *)xpath on:(BOOL)on {
	UISwitch *switchView = (UISwitch *)[self findView:xpath];
	if (switchView) {
		if (switchView.on == on) {
			return TRUE;
		} 
		[switchView tap];

		[NSThread sleepForTimeInterval:0.5];
		
		if (switchView.on != on) {
			[NSException raise:@"TestMachine" format:@"switch is sill %@", switchView.on ? "on" : "off"];
		}

		return TRUE;
	}
	return FALSE;
}

- (BOOL)selectPickerViewRow:(NSString *)xpath rowIndex:(int)rowIndex componentIndex:(int)componentIndex {
	UIPickerView *pickerView = (UIPickerView *)[self findView:xpath];
	if (pickerView) {
		[pickerView selectRow:rowIndex inComponent:componentIndex animated:TRUE];
		return TRUE;
	}
	return FALSE;
}

- (BOOL)scrollToTableViewRow:(NSString *)xpath sectionIndex:(int)sectionIndex rowIndex:(int)rowIndex {
	UITableView *tableView = (UITableView *)[self findView:xpath];
	if (tableView) {
		unsigned int indexes[2];
		indexes[0] = sectionIndex;
		indexes[1] = rowIndex;
		NSIndexPath *indexPath = [NSIndexPath indexPathWithIndexes:indexes length:2];
		
		[tableView scrollToRowAtIndexPath:indexPath atScrollPosition:UITableViewScrollPositionTop animated:TRUE];
		
		return TRUE;
	}
	return FALSE;
}

- (BOOL)check:(NSString *)xpath {
	UIView *view = [self findView:xpath];
	if (view) {
		return TRUE;
	}
	return FALSE;
}

- (void)startPlayingSound:(NSData *)data {
	if (_player) {
		[_player release];
		_player = NULL;
	}

	NSError *error;
	_player = [[AVAudioPlayer alloc] initWithData:data error:&error];
	if (!_player) {
		[NSException raise:@"TestMachine" format:@"%@", error.localizedDescription];		
	}
    [_player play];
}

- (void)pausePlayingSound {
	[_player pause];
}

- (void)resumePlayingSound {
	[_player play];
}

- (void)openUrl:(NSString *)url {
	if (![[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]]) {
		[NSException raise:@"TestMachine" format:@"command failed"];		
	}
}

- (void)startRecordingSound:(double)sampleRate {
	NSString *destinationString = [NSTemporaryDirectory() stringByAppendingPathComponent:@"testmachine.wav"];
	NSURL *destinationURL = [NSURL fileURLWithPath: destinationString];
	
	NSDictionary *settings = [NSDictionary dictionaryWithObjectsAndKeys:
	                          [NSNumber numberWithFloat: (float)sampleRate],       AVSampleRateKey,
	                          [NSNumber numberWithInt: kAudioFormatLinearPCM],     AVFormatIDKey,
	                          [NSNumber numberWithInt: 1],                         AVNumberOfChannelsKey,
	                          [NSNumber numberWithInt: AVAudioQualityMax],         AVEncoderAudioQualityKey,
	                          nil];
	
	NSError *error;
	_recorder = [[AVAudioRecorder alloc] initWithURL:destinationURL settings:settings error:&error];
	if (!_recorder) {
		[NSException raise:@"TestMachine" format:@"%@", error.localizedDescription];		
	}
	[_recorder record];
}

- (NSData *)finishRecordingSound {
	[_recorder stop];
	[_recorder release];

	// http://stackoverflow.com/questions/4506106/avaudiorecorder-avaudioplayer-not-always-playing-sound
	UInt32 sessionCategory = kAudioSessionCategory_PlayAndRecord;
	AudioSessionSetProperty(kAudioSessionProperty_AudioCategory, sizeof(sessionCategory), &sessionCategory);
	AudioSessionSetActive(true);
	
	return [NSData dataWithContentsOfFile:[NSTemporaryDirectory() stringByAppendingPathComponent:@"testmachine.wav"]];
}

- (void)notifyPostNow:(NSString *)name {
	notify_post([name UTF8String]);
}

- (void)notifyPost:(NSString *)name delay:(double)delay {
	[self performSelector:@selector(notifyPostNow:) withObject:name afterDelay:delay];
}

@end
