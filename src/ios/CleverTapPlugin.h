//
//  CleverTapPlugin.h
//  Copyright (C) 2015 CleverTap
//
//  This code is provided under a comercial License.
//  A copy of this license has been distributed in a file called LICENSE
//  with this source code.
//
//

#import <Cordova/CDVPlugin.h>
#import <CleverTapSDK/CleverTap+ABTesting.h>

static NSString* const CTDidReceiveNotification = @"CTDidReceiveNotification";
static NSString* const CTRemoteNotificationDidRegister = @"CTRemoteNotificationDidRegister";
static NSString* const CTRemoteNotificationRegisterError = @"CTRemoteNotificationRegisterError";
static NSString* const CTHandleOpenURLNotification = @"CTHandleOpenURLNotification";

@interface CleverTapPlugin : CDVPlugin


# pragma mark Developer Options

/** Set CleverTap debug logging
 0 = off, 1 = on;
 */
- (void)setDebugLevel:(CDVInvokedUrlCommand *)command;

# pragma mark launch
/**
 call to be notified of launch Push Notification or Deep Link
*/
-(void)notifyDeviceReady:(CDVInvokedUrlCommand *)command;


# pragma mark enable Personalization API

/** Enable the Personalization API
 must be invoked before calling most Event, Profile, or Session getters, see below
 */
-(void)enablePersonalization:(CDVInvokedUrlCommand *)command;

# pragma mark Offline api

/** Disables/Enables sending events to the server.
 */
-(void)setOffline:(CDVInvokedUrlCommand *)command;

#pragma mark OptOut API

/** Enabling tracking opt out for the currently active user
 */
-(void)setOptOut:(CDVInvokedUrlCommand *)command;

/** Enables the reporting of device network-related information, including IP address.  This reporting is disabled by default.
 */
-(void)enableDeviceNetworkInfoReporting:(CDVInvokedUrlCommand *)command;


#pragma mark Push Notifications

/** Request user push notification permission
 */
-(void)registerPush:(CDVInvokedUrlCommand *)command;

/** Set the user push token
 */
-(void)setPushTokenAsString:(CDVInvokedUrlCommand *)command;
-(void)setPushToken:(NSData*)pushToken;

/** Let CleverTap handle the push notification
 CleverTap will insure your AppDelege OpenUrl: sourceApplication: is called with a deep link, if included in notification
 */
-(void)handleNotification:(id)notification;


/** Let CleverTap handle sending the deep link into the Cordova WebView
 */
-(void)handleDeepLink:(NSURL *)url;

#pragma mark CleverTapInAppNotificationDelegate

/**
   This method gives call back for In App Notification Action
*/
-(void)inAppNotificationDismissedWithExtras:(NSDictionary *)extras andActionExtras:(NSDictionary *)actionExtras ;

/**
   This method gives call back for In App Notification Action
*/
- (void)inAppNotificationButtonTappedWithCustomExtras:(NSDictionary *)customExtras ;

/**
    Call this method to Disable InApp Notification From CleverTap
*/
-(void)disableInAppNotificationDisplay;

#pragma mark Event API

/** Record a Screen View
 */
-(void)recordScreenView:(CDVInvokedUrlCommand *)command;

/** Record an event
 */
-(void)recordEventWithName:(CDVInvokedUrlCommand *)command;

/** Record an event with event properties
 */
-(void)recordEventWithNameAndProps:(CDVInvokedUrlCommand *)command;

/** Record special "Charged" event with event details and array of purchased item objects
 see https://support.clevertap.com/profiles/recording-actions/#user-action-best-practices
 */
-(void)recordChargedEventWithDetailsAndItems:(CDVInvokedUrlCommand *)command;

/** Get event first time recorded in seconds
 requires prior enablePersonalization call
 */
-(void)eventGetFirstTime:(CDVInvokedUrlCommand *)command;

/** Get event last time recorded in seconds
 requires prior enablePersonalization call
 */
-(void)eventGetLastTime:(CDVInvokedUrlCommand *)command;

/** Get num times an event has been recorded
 requires prior enablePersonalization call
 */
-(void)eventGetOccurrences:(CDVInvokedUrlCommand *)command;

/** Get event details summary - first time, last time, occurrences
 requires prior enablePersonalization call
 */
-(void)eventGetDetails:(CDVInvokedUrlCommand *)command;

/** Get history of events recorded with details
 requires prior enablePersonalization call
 */
-(void)getEventHistory:(CDVInvokedUrlCommand *)command;


#pragma mark Profile API

/**
 Get the device location if available.  Calling this will prompt the user location permissions dialog.
 
 Please be sure to include the NSLocationWhenInUseUsageDescription key in your Info.plist.  See https://developer.apple.com/library/ios/documentation/General/Reference/InfoPlistKeyReference/Articles/CocoaKeys.html#//apple_ref/doc/uid/TP40009251-SW26
 
 Uses desired accuracy of kCLLocationAccuracyHundredMeters.
 
 If you need background location updates or finer accuracy please implement your own location handling.  Please see https://developer.apple.com/library/ios/documentation/CoreLocation/Reference/CLLocationManager_Class/index.html for more info.

 Optional.  You can use location to pass it to CleverTap via the setLocation API
 for, among other things, more fine-grained geo-targeting and segmentation purposes.
 */
-(void)getLocation:(CDVInvokedUrlCommand *)command;

/** Set location
 */
-(void)setLocation:(CDVInvokedUrlCommand *)command;

/**
 Creates a separate and distinct user profile identified by one or more of Identity, Email, FBID or GPID values,
 and populated with the key-values included in the profile dictionary.
 
 If your app is used by multiple users, you can use this method to assign them each a unique profile to track them separately.
 
 If instead you wish to assign multiple Identity, Email, FBID and/or GPID values to the same user profile,
 use profileSet rather than this method.
 
 If none of Identity, Email, FBID or GPID is included in the profile dictionary,
 all properties values will be associated with the current user profile.
 
 When initially installed on this device, your app is assigned an "anonymous" profile.
 The first time you identify a user on this device (whether via onUserLogin or profileSet),
 the "anonymous" history on the device will be associated with the newly identified user.
 
 Then, use this method to switch between subsequent separate identified users.
 
 Please note that switching from one identified user to another is a costly operation
 in that the current session for the previous user is automatically closed
 and data relating to the old user removed, and a new session is started
 for the new user and data for that user refreshed via a network call to CleverTap.
 In addition, any global frequency caps are reset as part of the switch.
 
 */
-(void)onUserLogin:(CDVInvokedUrlCommand *)command;

/** Set properties on the CleverTap device user profile
 */
-(void)profileSet:(CDVInvokedUrlCommand *)command;

/** Set facebook graph user object properties on the CleverTap device user profile
 */
-(void)profileSetGraphUser:(CDVInvokedUrlCommand *)command;

/** Set google plus user object properties on the CleverTap device user profile
 */
-(void)profileSetGooglePlusUser:(CDVInvokedUrlCommand *)command;

/** Get property from the CleverTap device user profile
 requires prior enablePersonalization call
 */
-(void)profileGetProperty:(CDVInvokedUrlCommand *)command;

/** Get the CleverTap ID of the User Profile. The CleverTap ID is the unique identifier assigned to the User Profile by CleverTap.
 */
-(void)profileGetCleverTapID:(CDVInvokedUrlCommand *)command;

/** Returns a unique CleverTap identifier suitable for use with install attribution providers.
 */
-(void)profileGetCleverTapAttributionIdentifier:(CDVInvokedUrlCommand *)command;

/** Remove the property specified by key from the user profile.
 */
-(void)profileRemoveValueForKey:(CDVInvokedUrlCommand *)command;

/** Method for setting a multi-value user profile property.
 Any existing value(s) for the key will be overwritten.
 Key must be String.
 Values must be Strings, max 40 bytes.  Longer will be truncated.
 Max 100 values, on reaching 100 cap, oldest value(s) will be removed.
 */
-(void)profileSetMultiValues:(CDVInvokedUrlCommand *)command;

/** Method for adding a unique value to a multi-value profile property (or creating if not already existing).
 If the key currently contains a scalar value, the key will be promoted to a multi-value property
 with the current value cast to a string and the new value(s) added.
 Key must be String.
 Values must be Strings, max 40 bytes. Longer will be truncated.
 Max 100 values, on reaching 100 cap, oldest value(s) will be removed.
 */
-(void)profileAddMultiValue:(CDVInvokedUrlCommand *)command;

/**  Method for adding multiple unique values to a multi-value profile property (or creating if not already existing).
 If the key currently contains a scalar value, the key will be promoted to a multi-value property
 with the current value cast to a string and the new value(s) added.
 Key must be String.
 Values must be Strings, max 40 bytes. Longer will be truncated.
 Max 100 values, on reaching 100 cap, oldest value(s) will be removed.
 */
-(void)profileAddMultiValues:(CDVInvokedUrlCommand *)command;

/**  Method for removing a unique value from a multi-value profile property.
 If the key currently contains a scalar value, prior to performing the remove operation the key will be promoted to a multi-value property with the current value cast to a string.
 If the multi-value property is empty after the remove operation, the key will be removed.
 */
-(void)profileRemoveMultiValue:(CDVInvokedUrlCommand *)command;

/**   Method for removing multiple unique values from a multi-value profile property.
 If the key currently contains a scalar value, prior to performing the remove operation the key will be promoted to a multi-value property with the current value cast to a string.
 If the multi-value property is empty after the remove operation, the key will be removed.
 */
-(void)profileRemoveMultiValues:(CDVInvokedUrlCommand *)command;

#pragma mark Session API

/** Get CleverTap session time in seconds
 */
-(void)sessionGetTimeElapsed:(CDVInvokedUrlCommand *)command;

/** Get total user visits
 requires prior enablePersonalization call
 */
-(void)sessionGetTotalVisits:(CDVInvokedUrlCommand *)command;

/** Get CleverTap session screens viewed count
 */
-(void)sessionGetScreenCount:(CDVInvokedUrlCommand *)command;

/** Get previous user visit time in epoch seconds
 requires prior enablePersonalization call
 */
-(void)sessionGetPreviousVisitTime:(CDVInvokedUrlCommand *)command;

/** Get session referrer utm source, campaign and medium, if applicable
 */
-(void)sessionGetUTMDetails:(CDVInvokedUrlCommand *)command;

/**
 Manually track incoming install referrers.
 Call this to manually track the utm details for an incoming install referrer.
 */
-(void)pushInstallReferrer:(CDVInvokedUrlCommand *)command;

# pragma mark App Inbox

/**
 Initialized the inbox controller.
 Call this method to initialize the inbox controller.
 You must call this method separately for each instance of CleverTap.
 */
-(void)initializeInbox:(CDVInvokedUrlCommand *)command;

/**
 Get the total number of unread inbox messages for the user.
 */
-(void)getInboxMessageUnreadCount:(CDVInvokedUrlCommand *)command;

/**
 Get the total number of inbox messages for the user.
 */
-(void)getInboxMessageCount:(CDVInvokedUrlCommand *)command;

/**
 This method opens the controller to display the inbox messages.
 */
-(void)showInbox:(CDVInvokedUrlCommand *)command;

/**
This method fetches all Inbox Messages
*/
-(void)getAllInboxMessages:(CDVInvokedUrlCommand *)command;

/**
This method fetches all Unread Inbox Messages
*/
-(void)getUnreadInboxMessages:(CDVInvokedUrlCommand *)command;

/**
This method fetches the Message for Given Message Id
*/
-(void)getInboxMessageForID:(CDVInvokedUrlCommand *)command;

/**
This method deletes the Inbox Message for Given Message Id
*/
- (void)deleteInboxMessageForId:(CDVInvokedUrlCommand *)command;

/**
This method Mark a message as Read for Given Message Id
*/
- (void)markReadInboxMessageForId:(CDVInvokedUrlCommand *)command;

/**
This method Marks Inbox Notification Viewed for Given Message Id
*/
-(void)pushInboxNotificationViewedEventForId:(CDVInvokedUrlCommand *)command;

/**
This method Marks Inbox Notification Clicked for Given Message Id
*/
-(void)pushInboxNotificationClickedEventForId:(CDVInvokedUrlCommand *)command;

# pragma mark App Inbox Delegate
/**
This method Gives Callback on Inbox Message Tapped
*/
- (void)messageDidSelect:(CleverTapInboxMessage *_Nonnull)message atIndex:(int)index withButtonIndex:(int)buttonIndex;

/**
This method Gives Callback on Inbox Message Tapped
*/
-(void)messageButtonTappedWithCustomExtras:(NSDictionary *_Nullable)customExtras;

# pragma mark Native Display

/**
This method is called to fetch all Display Units
*/
- (void)getAllDisplayUnits:(CDVInvokedUrlCommand *)command;

/**
This method is called to Fetch Display Unit For ID
*/
- (void)getDisplayUnitForId:(CDVInvokedUrlCommand *)command;

/**
This method is called to record Rendering of Display Unit
*/
- (void)recordDisplayUnitViewedEventForID:(CDVInvokedUrlCommand *)command;

/**
This method is called to record Click on Display Unit
*/
- (void)recordDisplayUnitClickedEventForID:(CDVInvokedUrlCommand *)command;

# pragma mark Native Display Delegate

/**
This method is callback for Display Unit Updates
*/
- (void)displayUnitsUpdated:(NSArray<CleverTapDisplayUnit *>*_Nonnull)displayUnits;

# pragma mark Dynamic Variables

/**
This method enables UI Editor
*/
-(void)setUIEditorConnectionEnabled: (CDVInvokedUrlCommand *)command;

/**
This method registers Boolean Variable
*/
-(void)registerBooleanVariable: (CDVInvokedUrlCommand *)command;

/**
This method registers Double Variable
*/
-(void)registerDoubleVariable: (CDVInvokedUrlCommand *)command;

/**
This method registers Integer Variable
*/
-(void)registerIntegerVariable: (CDVInvokedUrlCommand *)command;

/**
This method registers String Variable
*/
-(void)registerStringVariable: (CDVInvokedUrlCommand *)command;

/**
This method registers List of Boolean Variable
*/
-(void)registerListOfBooleanVariable: (CDVInvokedUrlCommand *)command;

/**
This method registers List of Doubel Variable
*/
-(void)registerListOfDoubleVariable: (CDVInvokedUrlCommand *)command;

/**
This method registers List of Integer Variable
*/
-(void)registerListOfIntegerVariable: (CDVInvokedUrlCommand *)command;

/**
This method registers List of String Variable
*/
-(void)registerListOfStringVariable: (CDVInvokedUrlCommand *)command;

/**
This method registers Dictionary of Boolean Variable
*/
-(void)registerMapOfBooleanVariable: (CDVInvokedUrlCommand *)command;

/**
This method registers Dictionary of Double Variable
*/
-(void)registerMapOfDoubleVariable: (CDVInvokedUrlCommand *)command;

/**
This method registers Dictionary of Integer Variable
*/
-(void)registerMapOfIntegerVariable: (CDVInvokedUrlCommand *)command;

/**
This method registers Dictionary of String Variable
*/
-(void)registerMapOfStringVariable: (CDVInvokedUrlCommand *)command;

/**
This method fetches the Boolean Variable
*/
-(void)getBooleanVariable: (CDVInvokedUrlCommand *)command;

/**
This method fetches the Double Variable
*/
-(void)getDoubleVariable: (CDVInvokedUrlCommand *)command;

/**
This method fetches the Integer Variable
*/
-(void)getIntegerVariable: (CDVInvokedUrlCommand *)command;

/**
This method fetches the String Variable
*/
-(void)getStringVariable: (CDVInvokedUrlCommand *)command;

/**
This method fetches the list of Boolean Variable
*/
-(void)getListOfBooleanVariable: (CDVInvokedUrlCommand *)command;

/**
This method fetches the list of Double Variable
*/
-(void)getListOfDoubleVariable: (CDVInvokedUrlCommand *)command;

/**
This method fetches the list of Integer Variable
*/
-(void)getListOfIntegerVariable: (CDVInvokedUrlCommand *)command;

/**
This method fetches the list of String  Variable
*/
-(void)getListOfStringVariable: (CDVInvokedUrlCommand *)command;

/**
This method fetches the Dictionary of Boolean Variable
*/
-(void)getMapOfBooleanVariable: (CDVInvokedUrlCommand *)command;

/**
This method fetches the Dictionary of Double Variable
*/
-(void)getMapOfDoubleVariable: (CDVInvokedUrlCommand *)command;

/**
This method fetches the Dictionary of Integer Variable
*/
-(void)getMapOfIntegerVariable: (CDVInvokedUrlCommand *)command;

/**
This method fetches the Dictionary of String Variable
*/
-(void)getMapOfStringVariable: (CDVInvokedUrlCommand *)command;

@end

