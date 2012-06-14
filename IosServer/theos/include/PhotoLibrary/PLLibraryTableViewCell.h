/**
 * This header is generated by class-dump-z 0.2-0.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/PhotoLibrary.framework/PhotoLibrary
 */

#import <UIKit/UITableViewCell.h>
#import "PhotoLibrary-Structs.h"

@class UIImage, UILabel;

@interface PLLibraryTableViewCell : UITableViewCell {
	CGRect _posterImageRect;
	UIImage* _posterImage;
	UILabel* _titleTextLabel;
	UILabel* _countLabel;
	BOOL _textNeedsLayout;
}
// inherited: -(id)initWithFrame:(CGRect)frame reuseIdentifier:(id)identifier;
// inherited: -(void)dealloc;
-(void)layoutTextInBounds:(CGRect)bounds;
-(void)setPosterImage:(id)image;
-(void)setText:(id)text photoCount:(int)count;
// inherited: -(void)_drawContentInRect:(CGRect)rect selected:(BOOL)selected;
-(void)drawRect:(CGRect)rect;
@end
