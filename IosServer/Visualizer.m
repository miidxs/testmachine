#import "Visualizer.h"


@implementation Visualizer

UILabel *_label = NULL;

NSTimer *_timer = NULL;

+ (void)showMessage:(NSString *)message {
    [Visualizer hideMessage];
    
    UIWindow *w = [[UIApplication sharedApplication] keyWindow];
    _label = [[UILabel alloc] initWithFrame:CGRectMake(0, w.bounds.size.height - 40, w.bounds.size.width, 40)];
    _label.text = message;
    _label.backgroundColor = [UIColor yellowColor];
    _label.textAlignment = UITextAlignmentCenter;
    [w addSubview:_label];

    _timer = [NSTimer scheduledTimerWithTimeInterval:5.0 target:[Visualizer class] selector:@selector(hideMessage) userInfo:NULL repeats:FALSE];
    [_timer retain]; 
}

+ (void)hideMessage {
    if (_timer) {
        [_timer invalidate];
        [_timer release];
        _timer = NULL;        
    }

    if (_label) {    
        [_label removeFromSuperview];
        [_label release];
        _label = NULL;
    }
}

@end
