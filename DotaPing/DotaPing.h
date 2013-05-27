/* DotaPing - Dota 2 Server Ping Check Program For Windows
	Coded By Yi 'Pusungwi' Yeon Jae - 2013 */

#pragma once

#include "resource.h"
#include "DotaPingCore.h"

int sgnPing = PING_DEFAULT_VALUE;
int uswPing = PING_DEFAULT_VALUE;
int usePing = PING_DEFAULT_VALUE;
int shnPing = PING_DEFAULT_VALUE;
int luxPing = PING_DEFAULT_VALUE;
int ausPing = PING_DEFAULT_VALUE;

void refreshAllServerPingValue();
