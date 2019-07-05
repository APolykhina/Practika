#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <stdio.h>
#include <ws2tcpip.h>
#include <inaddr.h>
#include <string>
#include <iostream>

using namespace std;

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char **argv) {

	HANDLE hIcmpFile;
	IPAddr ipaddr;
	DWORD dwRetVal = 0;
	char SendData[32] = "";
	LPVOID ReplyBuffer = NULL;
	DWORD ReplySize = 0;
	string IpAddress;
	

	hIcmpFile = IcmpCreateFile();
	if (hIcmpFile == INVALID_HANDLE_VALUE) {
		printf("\tUnable to open handle.\n");
		printf("IcmpCreatefile returned error: %ld\n", GetLastError());
		return 1;
	}

	ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
	ReplyBuffer = (VOID*)malloc(ReplySize);
	if (ReplyBuffer == NULL) {
		printf("\tUnable to allocate memory\n");
		return 1;
	}

	for (int i = 0; i < 255; i++) {
		for (int j = 1; j < 255; j++) {
			IpAddress = "192.168." + to_string(i) + "." + to_string(j);
			inet_pton(AF_INET, IpAddress.c_str(), &ipaddr);
			dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, SendData, sizeof(SendData),
				NULL, ReplyBuffer, ReplySize, 1000);
			if (dwRetVal != 0) {
				cout << IpAddress << endl;
			}
		}
	}

	//if (dwRetVal != 0) {
	//	PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;
	//	struct in_addr ReplyAddr;
	//	ReplyAddr.S_un.S_addr = pEchoReply->Address;
	//	printf("\tSent icmp message to %s\n", argv[1]);
	//	if (dwRetVal > 1) {
	//		printf("\tReceived %ld icmp message responses\n", dwRetVal);
	//		printf("\tInformation from the first response:\n");
	//	}
	//	else {
	//		printf("\tReceived %ld icmp message response\n", dwRetVal);
	//		printf("\tInformation from this response:\n");
	//	}
	//	printf("\t  Received from %s\n", inet_ntop(AF_INET, &ReplyAddr, NULL, NULL));
	//	printf("\t  Status = %ld\n",
	//		pEchoReply->Status);
	//	printf("\t  Roundtrip time = %ld milliseconds\n",
	//		pEchoReply->RoundTripTime);
	//}
	//else {
	//	printf("\tCall to IcmpSendEcho failed.\n");
	//	printf("\tIcmpSendEcho returned error: %ld\n", GetLastError());
	//	return 1;
	//}
	return 0;
}


