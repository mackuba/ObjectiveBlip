// -------------------------------------------------------
// OBAccount.h
//
// Copyright (c) 2010 Jakub Suder <jakub.suder@gmail.com>
// Licensed under MIT license
// -------------------------------------------------------

/*
  OBAccount - represents current user's account
*/

#import <Foundation/Foundation.h>

@interface OBAccount : NSObject {
  BOOL loggedIn;
  NSString *username;
  NSString *password;
}

@property (nonatomic, getter=isLoggedIn) BOOL loggedIn;
@property (nonatomic, copy) NSString *username;
@property (nonatomic, copy) NSString *password;

- (BOOL) hasCredentials;

@end
