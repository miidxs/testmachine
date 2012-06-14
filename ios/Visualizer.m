#import "Visualizer.h"


@implementation Visualizer

+ (void)showMessage:(NSString *)message {
	UIWindow *w = [[UIApplication sharedApplication] keyWindow];
	UILabel *l = [[[UILabel alloc] initWithFrame:CGRectMake(0, w.bounds.size.height - 40, w.bounds.size.width, 40)] autorelease];
	l.text = message;
	l.backgroundColor = [UIColor yellowColor];
	l.textAlignment = UITextAlignmentCenter;
	[w addSubview:l];
    [l performSelector:@selector(removeFromSuperview) withObject:NULL afterDelay:2.0];
}

@end
