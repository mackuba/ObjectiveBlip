// -------------------------------------------------------
// OBMessage.h
//
// Copyright (c) 2009 Jakub Suder <jakub.suder@gmail.com>
// Licensed under MIT license
// -------------------------------------------------------

/*
  OBMessage - single Blip update (status, directed or private message)
*/

#import <Foundation/Foundation.h>
#import "Constants.h"
#import "OBModel.h"

@class OBUser;

typedef enum { OBStatusMessage, OBDirectedMessage, OBPrivateMessage } OBMessageType;

@interface OBMessage : OBModel {
  // interesting stuff
  NSString *body;
  NSDate *date;
  OBUser *user;
  OBUser *recipient;
  OBMessageType messageType;
  NSArray *pictures;

  // less interesting stuff
  NSString *type;
  NSString *userPath;
  NSString *recipientPath;
  NSString *createdAt;
}

@property (nonatomic, copy) NSString *body;
@property (nonatomic, copy) NSString *type;
@property (nonatomic, copy) NSString *userPath;
@property (nonatomic, copy) NSString *recipientPath;
@property (nonatomic, copy) NSDate *date;
@property (nonatomic, copy) NSString *createdAt;
@property (nonatomic, copy) NSArray *pictures;
@property (nonatomic, retain) OBUser *user;
@property (nonatomic, retain) OBUser *recipient;
@property (nonatomic) OBMessageType messageType;

- (NSString *) url;
- (void) setPictureData: (NSData *) data;

@end
