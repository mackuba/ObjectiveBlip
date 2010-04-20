// -------------------------------------------------------
// OBConnector.h
//
// Copyright (c) 2009 Jakub Suder <jakub.suder@gmail.com>
// Licensed under MIT license
// -------------------------------------------------------

/*
  OBConnector - the central class which manages everything related to Blip connection
*/

#import <Foundation/Foundation.h>

// to enable logging in debug mode, add "-DDEBUG" to "Other C Flags" in the build properties of your target
#define OBLog(...) do { if ([OBConnector loggingEnabled]) NSLog(__VA_ARGS__); } while(0);

@class OBAccount;
@class OBAvatarGroup;
@class OBDashboardMonitor;
@class OBMessage;
@class OBRequest;
@class OBUser;

// these callback methods will be called on objects that created the request
@protocol OBConnectorDelegate
- (void) authenticationSuccessful;
- (void) authenticationFailed;
- (void) messageSent;
- (void) dashboardUpdatedWithMessages: (NSArray *) messages;
- (void) pictureLoaded: (NSData *) data forMessage: (OBMessage *) message;
- (void) requestFailedWithError: (NSError *) error;
@end

@interface OBConnector : NSObject {
  NSInteger lastMessageId;
  NSMutableArray *currentRequests;
  NSMutableArray *avatarGroups;
  NSString *userAgent;
  OBDashboardMonitor *dashboardMonitor;
  OBAccount *account;
  BOOL autoLoadAvatars;
  BOOL autoLoadPictureInfo;
  NSInteger initialDashboardFetch;
}

@property (nonatomic, retain) OBAccount *account;
@property (nonatomic, copy) NSString *userAgent;
@property (nonatomic, readonly) OBDashboardMonitor *dashboardMonitor;
@property (nonatomic) BOOL autoLoadAvatars;
@property (nonatomic) NSInteger initialDashboardFetch;

+ (OBConnector *) sharedConnector;

+ (BOOL) loggingEnabled;
+ (void) setLoggingEnabled: (BOOL) enabled;

- (id) init;
- (id) initWithUsername: (NSString *) username password: (NSString *) password;

- (OBRequest *) authenticateRequest;
- (OBRequest *) dashboardRequest;
- (OBRequest *) sendMessageRequest: (NSString *) message;
- (OBRequest *) loadPictureRequest: (OBMessage *) message;

- (OBRequest *) avatarInfoRequestForUser: (OBUser *) user;
- (OBRequest *) avatarImageRequestForUser: (OBUser *) user toPath: (NSString *) path;

// internal
- (void) avatarGroupLoaded: (OBAvatarGroup *) group;

@end
