#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@interface IosDriver : NSObject {
	AVAudioPlayer *_player;
	AVAudioRecorder *_recorder;
}

+ (IosDriver *)instance;

- (id)init;

// Taps the element specified by the XPath expression at its center, if the element is present.
// Returns FALSE, if the element was not present, TRUE if it was present and the operation succeded.
// Throws an exception if the operation failed.
- (BOOL)tap:(NSString *)xpath;

// Taps the element specified by the XPath expression at the specified coordinates, if the element is present.
// Returns FALSE, if the element was not present, TRUE if it was present and the operation succeded.
// Throws an exception if the operation failed.
- (BOOL)tap:(NSString *)xpath x:(double)x y:(double)y;

// Performs a swipe on the element specified by the XPath expression, if the element is present.
// Returns FALSE, if the element was not present, TRUE if it was present and the operation succeded.
// Throws an exception if the operation failed.
- (BOOL)swipe:(NSString *)xpath x1:(double)x1 y1:(double)y1 x2:(double)x2 y2:(double)y2;

// Sets the text value of the element specified by the XPath expression, if the element is present.
// Returns FALSE, if the element was not present, TRUE if it was present and the operation succeded.
// Throws an exception if the operation failed.
- (BOOL)setText:(NSString *)xpath text:(NSString *)text;

// Sets the switch specified by the XPath expression, if the element is present.
// Returns FALSE, if the element was not present, TRUE if it was present and the operation succeded.
// Throws an exception if the operation failed.
- (BOOL)setSwitch:(NSString *)xpath on:(BOOL)on;

// Sets a component of the picker view specified by the XPath expression, if the element is present.
// Returns FALSE, if the element was not present, TRUE if it was present and the operation succeded.
// Throws an exception if the operation failed.
- (BOOL)selectPickerViewRow:(NSString *)xpath rowIndex:(int)rowIndex componentIndex:(int)componentIndex;

// Scrolls to the specified row in a section of the table view specified by the XPath expression, if the element is present.
// Returns FALSE, if the element was not present, TRUE if it was present and the operation succeded.
// Throws an exception if the operation failed.
- (BOOL)scrollToTableViewRow:(NSString *)xpath sectionIndex:(int)sectionIndex rowIndex:(int)rowIndex;

// Checks if the element specified by the XPath expression is present.
// Returns FALSE, if the element was not present, TRUE if it was present.
- (BOOL)check:(NSString *)xpath;

// Starts playing sound.
// The sound is specified as a raw byte array.
- (void)startPlayingSound:(NSData *)data;

// Pauses playing the sound.
- (void)pausePlayingSound;

// Resumes playing the sound.
- (void)resumePlayingSound;

// Opens another application and jumps to the specified module by calling UIApplication:openURL:.
// The exact URL format is not documented, but examples can be found in the internet.
- (void)openUrl:(NSString *)url;

// Starts recording sound in WAV file.
- (void)startRecordingSound:(double)sampleRate;

// Finishes recording sound.
// Return the sound as a raw byte array.
- (NSData *)finishRecordingSound;

// Calls an SBSettings command after a specified delay.
// The purpose of the delay is to allow the call to return when invoking the reboot command.
// The command must be installed on the phone. See http://stackoverflow.com/questions/6419678/iphone-reboot-programmatically.
- (void)notifyPost:(NSString *)name delay:(double)delay;

@end
