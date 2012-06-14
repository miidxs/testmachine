#import "server/HTTPServer.h"
#import "TestMachine.h"
#import <MediaPlayer/MediaPlayer.h>


%hook SpringBoard

-(void)applicationDidFinishLaunching:(id)application {
	NSLog(@"TESTMACHINE: SpringBoard finished launching");

	%orig;

	[TestMachine start:50000];

	// after reboot, start Settings app
	// otherwise, the screen will be locked, even if "Auto-Lock" is set to "never"
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"prefs:"]];
}

%end


static BOOL _wasActive = FALSE;

static UIView *mpVolumeViewParentView;

%hook UIApplication

+ (id)sharedApplication {
	UIApplication *orig = %orig;
	if (![orig class]) {
		return orig;
	}

	BOOL active = (orig.applicationState == UIApplicationStateActive);
	if (active != _wasActive) {
		NSString *className = NSStringFromClass([orig class]);
		if ([className isEqual:@"SpringBoard"]) {
			return orig;  // handled separately
		}
		
		if (active) {
			NSLog(@"TESTMACHINE: %@ became active", className);
			
			int port = 50000 + className.hash % 10000;
			NSLog(@"TESTMACHINE: assigning port number %d", port);

			[TestMachine start:port];
			
			if ([className isEqual:@"MediaApplication"]) {
				// http://stackoverflow.com/questions/4141403/reroute-iphone-audio-through-speaker-headphone-or-bluetooth
				
				// Display the audio route button (Bluetooth / Speaker / iPhone)
				mpVolumeViewParentView = [[UIView alloc] initWithFrame:CGRectMake(0, 240, 320, 240)];
				mpVolumeViewParentView.backgroundColor = [UIColor clearColor];
				mpVolumeViewParentView.clipsToBounds = YES;
				
				MPVolumeView *systemVolumeSlider = [[MPVolumeView alloc] initWithFrame:CGRectMake(0, 0, 320, 240)];
				[mpVolumeViewParentView addSubview:systemVolumeSlider];
				[systemVolumeSlider release];
				
				[[[UIApplication sharedApplication] keyWindow] addSubview:mpVolumeViewParentView];
				[mpVolumeViewParentView release];
			}
		} else {
			NSLog(@"TESTMACHINE: %@ became not active", className);

			[TestMachine stop];
			
			if ([className isEqual:@"MediaApplication"]) {
				[mpVolumeViewParentView removeFromSuperview];
			}
		}
		_wasActive = active;
	}
	
    return orig;
}

%end
