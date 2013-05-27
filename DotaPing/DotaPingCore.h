/* DotaPing - Dota 2 Server Ping Check Program For Windows
	Coded By Yi 'Pusungwi' Yeon Jae - 2013 */

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define PING_ERROR_VALUE -1
#define PING_DEFAULT_VALUE 9999

#include <winsock2.h>
#include <IPHlpApi.h>
#include <IcmpAPI.h>
#include <stdio.h>

void getOwnIPAddress();
void ping(char *destination);

int getPingStatus(char *targetUrl);

int getPingValueFromSingapore();
int getPingValueFromLuxemburg();
int getPingValueFromAustrailia();
int getPingValueFromUSWest();
int getPingValueFromUSEast();
int getPingValueFromShanghai();
int getPingValueFromDestination(char *destination);
