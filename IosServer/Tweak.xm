#import "server/HTTPServer.h"
#import "TestMachine.h"
#import "Visualizer.h"
#import <MediaPlayer/MediaPlayer.h>


%hook SpringBoard

-(void)applicationDidFinishLaunching:(id)application {
	NSLog(@"TESTMACHINE: SpringBoard finished launching");

	%orig;

	[TestMachine start:50000];

	// after reboot, start Settings app
	// otherwise, the screen will be locked, even if "Auto-Lock" is set to "never"
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"prefs:"]];


	/*	
	// http://stackoverflow.com/questions/4141403/reroute-iphone-audio-through-speaker-headphone-or-bluetooth
	
	// Display the audio route button (Bluetooth / Speaker / iPhone)
	UIView *mpVolumeViewParentView = [[UIView alloc] initWithFrame:CGRectMake(0, 80, 320, 240)];
	mpVolumeViewParentView.backgroundColor = [UIColor clearColor];
	mpVolumeViewParentView.clipsToBounds = YES;
	
	MPVolumeView *systemVolumeSlider = [[MPVolumeView alloc] initWithFrame:CGRectMake(0, 80, 320, 240)];
	[mpVolumeViewParentView addSubview:systemVolumeSlider];
	[systemVolumeSlider release];
	
	[[[UIApplication sharedApplication] keyWindow] addSubview:mpVolumeViewParentView];
	[mpVolumeViewParentView release];	
	*/
}

%end


static BOOL _lock;
static BOOL _wasActive = FALSE;

%hook UIApplication

+ (id)sharedApplication {
	UIApplication *orig = %orig;
	if (_lock || ![orig class]) {
		return orig;
	}
	_lock = TRUE;

	BOOL active = (orig.applicationState == UIApplicationStateActive);
	if (active != _wasActive) {
		NSString *className = NSStringFromClass([orig class]);
		if ([className isEqual:@"SpringBoard"]) {
			_lock = FALSE;
			return orig;  // handled separately
		}	
		if (active) {
            int port = 50000 + className.hash % 10000;
			
			NSLog(@"TESTMACHINE: %@ became active", className);
			NSLog(@"TESTMACHINE: assigning port number %d", port);
            [Visualizer showMessage:[NSString stringWithFormat:@"port %d", port]];

			[TestMachine start:port];			
		} else {
			NSLog(@"TESTMACHINE: %@ became not active", className);

			[TestMachine stop];
		}
		_wasActive = active;
	}
	_lock = FALSE;
    return orig;
}

%end
