// -------------------------------------------------------
// OBMessage.m
//
// Copyright (c) 2009 Jakub Suder <jakub.suder@gmail.com>
// Licensed under MIT license
// -------------------------------------------------------

#import "OBMessage.h"
#import "OBUser.h"

@implementation OBMessage

@synthesize userPath, recipientPath, body, date, user, recipient, createdAt, messageType, type, pictures;
PSReleaseOnDealloc(userPath, recipientPath, body, date, user, recipient, createdAt, type, pictures);

+ (NSArray *) propertyList {
  return PSArray(@"body", @"userPath", @"createdAt", @"recipientPath", @"type", @"pictures");
}

+ (NSString *) routeName {
  return @"updates";
}

+ (OBMessage *) messageWithBody: (NSString *) text {
  OBMessage *message = [[OBMessage alloc] init];
  message.body = text;
  return [message autorelease];
}

- (id) init {
  self = [super init];
  if (self) {
    pictures = [[NSArray alloc] init];
  }
  return self;
}

- (void) setUserPath: (NSString *) path {
  [userPath release];
  [user release];
  userPath = [path copy];
  NSString *login = [[path componentsSeparatedByString: @"/"] lastObject];
  user = [[OBUser findOrCreateByLogin: login] retain];
}

- (void) setRecipientPath: (NSString *) path {
  [recipientPath release];
  [recipient release];
  recipientPath = [path copy];
  NSString *login = [[path componentsSeparatedByString: @"/"] lastObject];
  recipient = [[OBUser findOrCreateByLogin: login] retain];
}

- (void) setType: (NSString *) typeName {
  [type release];
  type = [typeName copy];
  if ([type isEqual: @"PrivateMessage"]) {
    messageType = OBPrivateMessage;
  } else if ([type isEqual: @"DirectedMessage"]) {
    messageType = OBDirectedMessage;
  } else if ([type isEqual: @"Notice"]) {
    messageType = OBNoticeMessage;
  } else {
    messageType = OBStatusMessage;
  }
}

- (void) setPictureData: (NSData *) data {
  NSDictionary *pictureInfo = [pictures objectAtIndex: 0];
  NSMutableDictionary *updatedInfo = [NSMutableDictionary dictionaryWithDictionary: pictureInfo];
  [updatedInfo setObject: data forKey: @"data"];
  self.pictures = PSArray(updatedInfo);
}

- (BOOL) hasPicture {
  return (pictures.count > 0 && [[pictures objectAtIndex: 0] objectForKey: @"url"] != nil);
}

- (BOOL) hasPictureData {
  return ([self hasPicture] && [[pictures objectAtIndex: 0] objectForKey: @"data"] != nil);
}

- (NSString *) pictureURL {
  return [[pictures objectAtIndex: 0] objectForKey: @"url"];
}

+ (NSSet *) keyPathsForValuesAffectingHasPicture {
  return [NSSet setWithObject: @"pictures"];
}

+ (NSDateFormatter *) timeZoneLessDateFormatter {
  static NSDateFormatter *formatter = nil;
  if (!formatter) {
    formatter = [[NSDateFormatter alloc] init];
    formatter.timeZone = [NSTimeZone timeZoneWithName: @"Europe/Warsaw"];
    formatter.dateFormat = @"yyyy-MM-dd HH:mm:ss";
  }
  return formatter;
}

- (void) setCreatedAt: (NSString *) created {
  [createdAt release];
  [date release];
  createdAt = [created copy];
  date = [[[[self class] timeZoneLessDateFormatter] dateFromString: createdAt] retain];
}

- (NSString *) url {
  return PSFormat(@"%@/s/%@", BLIP_WWW_HOST, self.recordId);
}

- (NSString *) description {
  return PSFormat(@"<OBMessage: user.login=%@, date=%@, body=\"%@\">", user.login, date, body);
}

- (NSString *) encodeToPostData {
  return PSFormat(@"update[body]=%@", [body psStringWithPercentEscapesForFormValues]);
}

@end
