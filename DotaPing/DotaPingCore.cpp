/* DotaPing - Dota 2 Server Ping Check Program For Windows
	Coded By Yi 'Pusungwi' Yeon Jae - 2013 */

#include "stdafx.h"
#include "DotaPingCore.h"

using namespace std;

char *d2ServerIPSingapore[] = {"sgp-1.valve.net", "sgp-2.valve.net", "103.28.54.1", "103.28.55.1", "103.10.124.1"};
char *d2ServerIPUSWest[] = {"192.69.96.1", "192.69.96.2", "192.69.96.3", "192.69.96.91", "192.69.96.90"};
char *d2ServerIPUSEast[] = {"208.78.164.1", "208.78.165.1"};
char *d2ServerIPAus[] = {"103.10.125.1", "103.10.125.2"};
char *d2ServerIPShanghai[] = {"58.125.52.1", "58.125.52.2"};
char *d2ServerIPLux[] = {"146.66.153.1", "146.66.153.2"}; 

void getOwnIPAddress() {
	MIB_IPADDRTABLE  *pIPAddrTable;
	DWORD            dwSize = 0;
	DWORD            dwRetVal;

	pIPAddrTable = (MIB_IPADDRTABLE*)malloc( sizeof(MIB_IPADDRTABLE) );

	if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER) {
		free( pIPAddrTable );
		pIPAddrTable = (MIB_IPADDRTABLE *)malloc( dwSize );
	}

	if ( (dwRetVal = GetIpAddrTable( pIPAddrTable, &dwSize, 0 )) != NO_ERROR ) { 
		printf("GetIpAddrTable call failed with %d\n", dwRetVal);
	}	

	printf("IP Address:         %ld\n", pIPAddrTable->table[0].dwAddr);
	printf("IP Mask:            %ld\n", pIPAddrTable->table[0].dwMask);
	printf("IF Index:           %ld\n", pIPAddrTable->table[0].dwIndex);
	printf("Broadcast Addr:     %ld\n", pIPAddrTable->table[0].dwBCastAddr);
	printf("Re-assembly size:   %ld\n", pIPAddrTable->table[0].dwReasmSize);

	if (pIPAddrTable)
        free(pIPAddrTable);
}

int getPingValueFromSingapore() {
	int tmpValue = getPingValueFromDestination(d2ServerIPSingapore[0]);
	return tmpValue;
}

int getPingValueFromLuxemburg() {
	int tmpValue = getPingValueFromDestination(d2ServerIPLux[0]);
	return tmpValue;
}

int getPingValueFromAustrailia() {
	int tmpValue = getPingValueFromDestination(d2ServerIPAus[0]);
	return tmpValue;
}

int getPingValueFromUSWest() {
	int tmpValue = getPingValueFromDestination(d2ServerIPUSWest[0]);
	return tmpValue;
}
int getPingValueFromUSEast() {
	int tmpValue = getPingValueFromDestination(d2ServerIPUSEast[0]);
	return tmpValue;
}

int getPingValueFromShanghai() {
	int tmpValue = getPingValueFromDestination(d2ServerIPShanghai[0]);
	return tmpValue;
}

int getPingValueFromDestination(char *destination) {
	int resultMS = PING_DEFAULT_VALUE;
	WSADATA wsaData;
    WSAStartup(0x0202, &wsaData);

    hostent* remoteHost;
    remoteHost = gethostbyname(destination);
    if (WSAGetLastError() != 0)
    {
        WSACleanup();
		return PING_ERROR_VALUE;
    }

    HANDLE hIcmpFile = IcmpCreateFile();
    if (hIcmpFile==INVALID_HANDLE_VALUE)
    {
        WSACleanup();
		return PING_ERROR_VALUE;
    }

    IPAddr* ipaddr = reinterpret_cast< IPAddr* >
        (remoteHost->h_addr_list[0]);
    LPVOID ReplyBuffer = (VOID*) malloc(sizeof(ICMP_ECHO_REPLY));

	if (IcmpSendEcho(hIcmpFile, *ipaddr, 0, 0, NULL, ReplyBuffer, sizeof(ICMP_ECHO_REPLY), 1000)==0) {
		return PING_ERROR_VALUE;
	}
    else {
		PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;
        in_addr ipreplied;
		ipreplied.S_un.S_addr=pEchoReply->Address;
		resultMS = (int)pEchoReply->RoundTripTime;
	}

    free(ReplyBuffer);
    IcmpCloseHandle(hIcmpFile);
    WSACleanup();

	return resultMS;
}

void ping(char *destination)
{
    WSADATA wsaData;
    WSAStartup(0x0202, &wsaData);

    hostent* remoteHost;
    remoteHost = gethostbyname(destination);
    if (WSAGetLastError() != 0)
    {
        WSACleanup();
        return;
    }

    HANDLE hIcmpFile = IcmpCreateFile();
    if (hIcmpFile==INVALID_HANDLE_VALUE)
    {
        WSACleanup();
        return;
    }

    IPAddr* ipaddr = reinterpret_cast< IPAddr* >
        (remoteHost->h_addr_list[0]);

	/*
    cout << "Pinging " << destination << " ["
        << inet_ntoa(*reinterpret_cast< in_addr* >(ipaddr)) 
        << "]\n" << endl;
	*/
    LPVOID ReplyBuffer = (VOID*) malloc(sizeof(ICMP_ECHO_REPLY));

    for (int i=0; i<3; i++)
    {
        if (IcmpSendEcho(hIcmpFile, *ipaddr,
            0,0,NULL, ReplyBuffer,sizeof(ICMP_ECHO_REPLY),1000)==0)
        {
			/*
            cout << "IcmpSendEcho failed with error code: " 
                << GetLastError() << endl;
			*/
			
		}
        else
        {
            PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;
            in_addr ipreplied;
            ipreplied.S_un.S_addr=pEchoReply->Address;
			printf("pinging...");
			printf("ping : %d ms", pEchoReply->RoundTripTime);
			/*
            cout << "Reply from " << inet_ntoa(ipreplied)
                << ": bytes=" << pEchoReply->DataSize
                << " time=" << pEchoReply->RoundTripTime << "ms" << endl;
			*/
		}
        Sleep(500);
    }

    free(ReplyBuffer);
    IcmpCloseHandle(hIcmpFile);
    WSACleanup();
}

int getPingStatus(char *targetUrl) {
	// return ping
	// if return 9999. timeout.
	// if returning -1. error.
	return 0;
}