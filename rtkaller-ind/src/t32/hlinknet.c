/*
 * TRACE32 Remote API
 *
 * Copyright (c) 1998-2017 Lauterbach GmbH
 * All rights reserved
 *
 * Link hlinknet.c and hremote.c with your application.
 *
 * Licensing restrictions apply to this code.
 * Please see documentation (api_remote.pdf) for
 * licensing terms and conditions.
 *
 * $LastChangedRevision: 112948 $
 *
 * formatted with:
 *    indent -kr -c0 -cbi0 -cd0 -cli4 -cp10 -di16 -fc1 -il0 -nsc -ppi2 --line-length120 --no-tabs hlinknet.c
 */


#if defined(T32HOST_UNIX)
# ifndef T32HOST_SOL
#  define _XOPEN_SOURCE 500
# endif
# if defined(T32HOST_LINUX) || defined(T32HOST_MACOSX)
#  ifndef _POSIX_C_SOURCE
#   define _POSIX_C_SOURCE 200112L
#  endif
# endif
# if defined(T32HOST_SOL)
#  define __EXTENSIONS__
#  if defined(T32HOST_SOL_STUDIO12) || (defined(__SunOS_RELEASE) && __SunOS_RELEASE >= 0x051000)
#   ifndef _POSIX_C_SOURCE
#    define _POSIX_C_SOURCE 200112L
#   endif
#  else
#   define _XOPEN_SOURCE 500
#   ifndef _POSIX_C_SOURCE
#    define _POSIX_C_SOURCE 199506L
#   endif
#  endif
# endif
#endif


#include "t32.h"

#if defined(_MSC_VER)
# pragma warning( push )
# pragma warning( disable : 4255 )
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef T32HOST_WIN
# ifndef NOGDI
#  define NOGDI
# endif
# include <winsock2.h>
# include <ws2tcpip.h>
# include <fcntl.h>
typedef int     socklen_t;
#endif

#if defined(T32HOST_UNIX)
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/time.h>
# include <errno.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <sys/select.h>
#endif


#if defined(_MSC_VER)
# pragma warning( pop )
/* disable warning for FD_SET() :-(  */
# pragma warning( disable : 4548)
#endif


#define PCKLEN_MAX 0x4000 /* maximum size of UDP-packet */


#if defined(T32HOST_WIN) || defined(T32HOST_LINUX)
# define RECEIVEADDR (&ReceiveSocketAddress)
static T32_THREADLOCAL struct sockaddr ReceiveSocketAddress;
#else
# define RECEIVEADDR 0
#endif

/* *INDENT-OFF* */
typedef struct LineStruct_s {
	char               NodeName[80]; /* NODE=     */  /* node name of host running T32 SW */
	int                CommSocket;                    /* socket for communication */
	unsigned short     HostPort;     /* HOSTPORT= */  /* Host side port */
	unsigned short     ReceivePort;                   /* Receiver Port */
	unsigned short     TransmitPort; /* PORT=     */  /* Transmitter Port in T32 */
	int                PacketSize;   /* PACKLEN=  */  /* Max. size of UDP-packet data */
	int                PollTimeSec;  /* TIMEOUT=  */
	int                ReceiveToggleBit;
	unsigned char      MessageId;
	int                LineUp;
	unsigned short     ReceiveSeq, TransmitSeq;    /* block-ids */
	unsigned short     LastReceiveSeq, LastTransmitSeq;
	unsigned char     *LastTransmitBuffer;
	int                LastTransmitSize;
	struct sockaddr_in SocketAddress;
} LineStruct;
/* *INDENT-ON* */

#ifdef T32HOST_WIN
extern void     T32_InstallAsyncSelect(HWND hwnd, int msg);
extern void     T32_UnInstallAsyncSelect(HWND hwnd);
#endif

extern void     LINE_SetReceiveToggleBit(int value);
extern int      LINE_GetReceiveToggleBit(void);
extern unsigned char LINE_GetNextMessageId(void);
extern unsigned char LINE_GetMessageId(void);
extern int      LINE_GetLineParamsSize(void);
extern int      LINE_LineConfig(char *in);
extern void     LINE_LineExit(void);
extern int      LINE_LineInit(char *message);
extern int      LINE_LineTransmit(unsigned char *in, int size);
extern int      LINE_LineDriverGetSocket(void);
extern int      LINE_LineReceive(unsigned char *out);
extern int      LINE_ReceiveNotifyMessage(unsigned char *package);
extern int      LINE_LineSync(void);

int T32_NotificationPending(void);
static int Connection(unsigned char *ipaddrused);

extern T32_THREADLOCAL unsigned int LINE_TransmitCounter;
T32_THREADLOCAL unsigned int    LINE_TransmitCounter = 0;

static T32_THREADLOCAL struct timeval LongTime = { 0, 500000 };

static T32_THREADLOCAL int isLineParamsInitialized;
static T32_THREADLOCAL LineStruct LineParams;
static T32_THREADLOCAL LineStruct *pLineParams = NULL;
static void SetToDefaultLineParams(LineStruct * params)
{
	if ((params == &LineParams) && isLineParamsInitialized!=0)
		return;
	memset(params,0,sizeof(LineStruct));
	strcpy(params->NodeName, "localhost");
	params->CommSocket       = -1;
	params->TransmitPort     = 20000;
	params->PacketSize       = 1024;
	params->PollTimeSec      = 5;
	params->ReceiveToggleBit = -1;
	if (params == &LineParams)
		isLineParamsInitialized = 1;
}

static int str2dec(char *in)
{
	int             x = 0;
	while (*in) {
		x *= 10;
		if (*in < '0' || *in > '9')
			return -1;
		x += *in - '0';
		in++;
	}
	return x;
}


void LINE_SetReceiveToggleBit(int value)
{
	if (pLineParams)
		pLineParams->ReceiveToggleBit = value;
}


int LINE_GetReceiveToggleBit(void)
{
	return pLineParams ? pLineParams->ReceiveToggleBit : 0;
}


unsigned char LINE_GetNextMessageId(void)
{
	return pLineParams ? ++pLineParams->MessageId : 0;
}


unsigned char LINE_GetMessageId(void)
{
	return pLineParams ? pLineParams->MessageId : 0;
}


int LINE_GetLineParamsSize(void)
{
	return sizeof(LineStruct);
}

extern void LINE_DefaultLineParams(LineStruct * ParametersOut);
void LINE_DefaultLineParams(LineStruct * ParametersOut)
{
	SetToDefaultLineParams(ParametersOut);
}

extern void LINE_SetLine(LineStruct * params);
void LINE_SetLine(LineStruct * params)
{
	pLineParams = params;
}


/** Configures parameters of the communication lines. Needs to be called separately for each parameter.

	@param input IN
		a string of the "value=key" style (e.g. "NODE=12.23.4.4) for configuring
		a feature of the communication line.
	@return
		1  : OK
		-1 : ERROR
*/
int LINE_LineConfig(char *input)
{
	int             x;
	LineStruct     *line;

	if (pLineParams == NULL) {
		pLineParams = &LineParams;
		SetToDefaultLineParams(pLineParams);
	}
	line = pLineParams;

	if (!strncmp((char *) input, "NODE=", 5)) {
		strcpy(line->NodeName, input + 5);
		return 1;
	}
	if (!strncmp((char *) input, "PORT=", 5)) {
		x = str2dec(input + 5);
		if (x == -1)
			return -1;
		line->TransmitPort = (unsigned short) x;
		return 1;
	}
	if (!strncmp((char *) input, "HOSTPORT=", 9)) {
		x = str2dec(input + 9);
		if (x == -1)
			return -1;
		line->HostPort = (unsigned short) x;
		return 1;
	}
	if (!strncmp((char *) input, "PACKLEN=", 8)) {
		x = str2dec(input + 8);
		if (x == -1)
			return -1;
		line->PacketSize = x;
		return 1;
	}
	if (!strncmp((char *) input, "TIMEOUT=", 8)) {
		x = str2dec(input + 8);
		if (x == -1)
			return -1;
		line->PollTimeSec = x;
		return 1;
	}
	return -1;
}


static void WinsockErrorMessage(char *out)
{
#ifdef T32HOST_WIN
	int             err;
	err = WSAGetLastError();

	switch (err) {
		case WSAHOST_NOT_FOUND:
			strcat(out, " (HOST_NOT_FOUND)");
			break;
		case WSATRY_AGAIN:
			strcat(out, " (TRY_AGAIN)");
			break;
		case WSANO_RECOVERY:
			strcat(out, " (NO_RECOVERY)");
			break;
		case WSANO_DATA:
			strcat(out, " (NO_DATA)");
			break;
		case WSAEINTR:
			strcat(out, " (INTR)");
			break;
		case WSANOTINITIALISED:
			strcat(out, " (NOTINITIALISED)");
			break;
		case WSAENETDOWN:
			strcat(out, " (NETDOWN)");
			break;
		case WSAEAFNOSUPPORT:
			strcat(out, " (WSAEAFNOSUPPORT)");
			break;
		case WSAEINPROGRESS:
			strcat(out, " (INPROGRESS)");
			break;
		case WSAEMFILE:
			strcat(out, " (WSAEMFILE)");
			break;
		case WSAENOBUFS:
			strcat(out, " (WSAENOBUFS)");
			break;
		case WSAEPROTONOSUPPORT:
			strcat(out, " (WSAEPROTONOSUPPORT)");
			break;
		case WSAEPROTOTYPE:
			strcat(out, " (WSAEPROTOTYPE)");
			break;
		case WSAESOCKTNOSUPPORT:
			strcat(out, " (WSAESOCKTNOSUPPORT)");
			break;
	}
#else
	(void)out;  // unused parameter
#endif
}


static int32_t GetInetAddress(char *name, char *message)
{
	int             i1, i2, i3, i4;
	char            ownname[256];
	unsigned int    nbo_own_ip;
	struct addrinfo hints, *ai_result;
	int ai_status;

	if (name == NULL) {
		gethostname(ownname, sizeof(ownname));
		name = ownname;
	}
	i1 = i2 = i3 = i4 = 0;

	if (sscanf(name, "%d.%d.%d.%d", &i1, &i2, &i3, &i4) == 4) {
		if (i1 || i2 || i3 || i4) {
			return (i1 << 24) | (i2 << 16) | (i3 << 8) | (i4);
		}
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	if ((ai_status = getaddrinfo(name, NULL, &hints, &ai_result)) != 0) {
		strcpy(message, "node name (");
		strcat(message, name);
		strcat(message, ") unknown");
		WinsockErrorMessage(message);
		return -1l;
	}

	nbo_own_ip = ((struct sockaddr_in *) ai_result->ai_addr)->sin_addr.s_addr;
	freeaddrinfo(ai_result);
	return ntohl(nbo_own_ip);
}


/**
	Closes communication channel with TRACE32. Needs to be called, otherwise TRACE32 cannot accept new connections.

	@caller
		T32_exit(),
		LINE_LineInit() in case of error
 */
void LINE_LineExit(void)
{
	int             i;
	LineStruct     *line;
	static const char discon[] = { 4, 0, 0, 0, 0, 0, 0, 0, 'T', 'R', 'A', 'C', 'E', '3', '2', 0 };

	if (!pLineParams)
		return;
	line = pLineParams;

	if (!line->LineUp) {
		if (line->CommSocket != -1) {
#ifdef T32HOST_WIN
			closesocket(line->CommSocket);
			WSACleanup();
#endif
#ifdef T32HOST_UNIX
			close(line->CommSocket);
#endif
		}
		return;
	}

	if (line->CommSocket != -1) {

		/* Probably multiple packets for skipping loops reading multiple packets so that one packet gets into the "real" handler." */
		for (i = 0; i < 5; i++)
			sendto(line->CommSocket, discon, 16, 0, (struct sockaddr *) &(line->SocketAddress), sizeof(line->SocketAddress));   /* send EXIT 4 */

#ifdef T32HOST_WIN
		closesocket(line->CommSocket);
#endif
#if defined(T32HOST_UNIX)
		close(line->CommSocket);
#endif
	}
#ifdef T32HOST_WIN
	WSACleanup();
#endif

	line->CommSocket = -1;
	line->LineUp = 0;
}


/**
	Sets up a connection with TRACE32.

	@param message OUT
		a buffer that receives an error message in case of an error; not modified in case of success.
	@return
		0  : OK, using previously established connection
		1  : OK, new connection established
		-1 : ERROR

	@caller only int T32_Init()
*/
int LINE_LineInit(char *message)
{
	int             i, j;
	socklen_t       length;
	int             val;
	unsigned char   dummy_ipaddr[4];
	int32_t         remote_ip;
	int             buflen;
	LineStruct     *line;

	if (pLineParams == NULL) {
		pLineParams = &LineParams;
		SetToDefaultLineParams(pLineParams);
	}
	line = pLineParams;

	if (line->LineUp)   /* OK, connection already exists */
		return 0;

	if (line->CommSocket == -1) {
#ifdef T32HOST_WIN
		WSADATA         wsaData;
		if (WSAStartup(0x0101, &wsaData)) {
			strcpy(message, "TCP/IP not ready, check configuration");
			return -1;
		}
#endif
	}
	if ((remote_ip = GetInetAddress(line->NodeName, message)) == -1l)
		return -1;

	if (line->CommSocket == -1) {
		line->SocketAddress.sin_family = AF_INET;
		line->SocketAddress.sin_addr.s_addr = INADDR_ANY;
		line->SocketAddress.sin_port = line->HostPort;  /* Port can be determined by host */

		if ((line->CommSocket = (int) socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
			strcpy(message, "cannot create socket");
			WinsockErrorMessage(message);
			goto error;
		}
		if ((i = bind(line->CommSocket, (struct sockaddr *) &line->SocketAddress, sizeof(line->SocketAddress))) == -1) {
			strcpy(message, "cannot bind socket");
			WinsockErrorMessage(message);
			goto error;
		}
		length = sizeof(line->SocketAddress);
		if (getsockname(line->CommSocket, (struct sockaddr *) &line->SocketAddress, &length) == -1) {
			strcpy(message, "cannot identify port");
			WinsockErrorMessage(message);
			goto error;
		}
		line->ReceivePort = ntohs(line->SocketAddress.sin_port);

		line->SocketAddress.sin_family = AF_INET;
		line->SocketAddress.sin_addr.s_addr = INADDR_ANY;
		line->SocketAddress.sin_port = htons(line->TransmitPort);
	}
	line->SocketAddress.sin_addr.s_addr = htonl(remote_ip);

	buflen = PCKLEN_MAX;

	val = 0;
	length = sizeof(val);
	getsockopt(line->CommSocket, SOL_SOCKET, SO_RCVBUF, (char *) &val, &length);

	if (val < buflen) {
		val = buflen;
		length = sizeof(val);
		if (setsockopt(line->CommSocket, SOL_SOCKET, SO_RCVBUF, (char *) &val, length) == -1) {
			strcpy(message, "cannot alloc buffer for rcvsocket");
			goto error;
		}
		val = 0;
		length = sizeof(val);
		getsockopt(line->CommSocket, SOL_SOCKET, SO_RCVBUF, (char *) &val, &length);
		if (val < buflen) {
			strcpy(message, "cannot alloc buffer for rcvsocket");
			goto error;
		}
	}

	val = 0;
	length = sizeof(val);
	getsockopt(line->CommSocket, SOL_SOCKET, SO_RCVBUF, (char *) &val, &length);

	if (val > 0 && val < line->PacketSize)
		line->PacketSize = val;

	val = 0;
	length = sizeof(val);
	getsockopt(line->CommSocket, SOL_SOCKET, SO_SNDBUF, (char *) &val, &length);
	if (val < buflen) {
		val = buflen;
		length = sizeof(val);
		if (setsockopt(line->CommSocket, SOL_SOCKET, SO_SNDBUF, (char *) &val, length) == -1) {
			strcpy(message, "cannot alloc buffer for sndsocket");
			goto error;
		}
		val = 0;
		length = sizeof(val);
		getsockopt(line->CommSocket, SOL_SOCKET, SO_SNDBUF, (char *) &val, &length);
		if (val < buflen) {
			strcpy(message, "cannot alloc buffer for sndsocket");
			goto error;
		}
	}

	for (i = 0; i < 10; i++) {
		j = Connection(dummy_ipaddr);

		if (j == 0)
			continue;

		if (j == 1) {
			line->LineUp = 1;
			return 1;   /* OK, new connection established */
		}

		strcpy(message, "TRACE32 access refused");
		goto error;
	}

	strcpy(message, "TRACE32 not responding");

error:
	LINE_LineExit();    /* Close connection if no success */

	/*
		Even in case of error, CommSocket has to be reset, otherwise
		the next connection attempt will fail as WSAStartup() would not
		be called.
	*/

	line->CommSocket = -1;

	return -1;
}


#ifdef T32HOST_WIN

void T32_InstallAsyncSelect(HWND hwnd, int msg)
{
# ifndef DONT_USE_ASYNC
	if (pLineParams)
		WSAAsyncSelect(pLineParams->CommSocket, hwnd, msg, FD_READ);
# endif
}

void T32_UnInstallAsyncSelect(HWND hwnd)
{
# ifndef DONT_USE_ASYNC
	if (pLineParams)
		WSAAsyncSelect(pLineParams->CommSocket, hwnd, 0, 0);
# endif
}

#endif

/**
	Sends a message to T32. Handles segmentation of _message_ into (one
	or multiple) _packages_.

	@param in   : pointer to outgoing message (already includes 5 byte message header)
	@param size : size of message
	@note
		the message must be allocated such that there is space in
		front of the message for adding the packet header
*/

int LINE_LineTransmit(unsigned char *in, int size)
{
	int             packetSize;
	unsigned int    tmpl;
	unsigned int    bytesTransmitted = 0;
	LineStruct     *line;

	if (!pLineParams)
		return 0;
	line = pLineParams;

	LINE_TransmitCounter++;

	line->LastTransmitBuffer = in;
	line->LastTransmitSize = size;
	line->LastTransmitSeq = line->TransmitSeq;
	in -= 4;    /* space for packet header */


	/* Assumed that Host SocketReceivebuffersize is 6000 (see hassist.c) */
	do {
		packetSize = (size > line->PacketSize - 4) ? line->PacketSize - 4 : size;

		/*
			When sending multiple packets, the packet header is written inside the
			message's payload. Original contents needs to be saved/restored
		*/

		SETLONGVAR(tmpl, in[0]);        /* save */

		in[0] = 0x11;   /* transmit data package */
		in[1] = (size > packetSize) ? 1 : 0;    /* more packets follow */
		SETWORDVAR(in[2], line->TransmitSeq);   /* packet sequence ID */

		if (sendto(line->CommSocket, (char *) in, packetSize + 4, 0, (struct sockaddr *) &line->SocketAddress, sizeof(line->SocketAddress)) != packetSize + 4) {        /* send Data Package 0x11 */
			SETLONGVAR(in[0], tmpl);    /* restore buffer */
			return 0;
		}
		bytesTransmitted += packetSize + 4;
		SETLONGVAR(in[0], tmpl);        /* restore buffer */

		line->TransmitSeq++;
		in += packetSize;
		size -= packetSize;
	}
	while (size > 0);   /* more packets required? */

	return line->LastTransmitSize;
}


/**
	Receives a package from the socket, with timeout handling.
	@return number of received bytes or error number (<0)
*/
static int ReceiveWithTimeout(struct timeval *tim, unsigned char *dest, int size)
{
	int             i;
	int             result;
	fd_set          readfds;
	socklen_t       length;
	struct timeval  timeout = *tim;
	LineStruct     *line;

	if (!pLineParams)
		return 0;
	line = pLineParams;

	FD_ZERO(&readfds);
	FD_SET((unsigned int) line->CommSocket, &readfds);

	i = select(FD_SETSIZE, &readfds, (fd_set *) NULL, (fd_set *) NULL, &timeout);

	if (i <= 0) {
		return i;
	}

	length = sizeof(struct sockaddr);
	result = recvfrom(line->CommSocket, (char *) dest, size, 0, (struct sockaddr *) RECEIVEADDR, &length);
	return result;
}


int LINE_LineDriverGetSocket(void)
{
	return pLineParams ? pLineParams->CommSocket : 0;
}


typedef struct t32_notification {
	char            payload[T32_PCKLEN_MAX];
	struct t32_notification *next;
	struct t32_notification *prev;
} T32_NotificationPackage;

/* Queue pending notifications */
T32_NotificationPackage *T32_NotificationHead = NULL;
T32_NotificationPackage *T32_NotificationTail = NULL;

/**
	Receives messages from the socket. Assembles multiple packets into
	a single message.

	@param out
		output buffer for storing payload. Attention: there must
		be some space _before_ the output buffer (4 bytes or more)
		for temporary usage.
	@return
		number of bytes of the message or error number (<0)
*/
int LINE_LineReceive(unsigned char *out)
{
	int             i, flag;
	int             count;
	unsigned short  tmpw;
	unsigned int    tmpl;
	unsigned short  s;
	LineStruct     *line;
	register unsigned char *dest;
	static const unsigned char handshake[] = { 7, 0, 0, 0, 0, 0, 0, 0, 'T', 'R', 'A', 'C', 'E', '3', '2', 0 };

	if (!pLineParams)
		return -1;
	line = pLineParams;

retry:
	dest = out - 4;     /* adjust pointer so we place header BEFORE "out" and thus payload AT "out" */
	count = 0;
	s = line->ReceiveSeq;

	do {
		/*
			multiple packets are merged in-place: backup data that is
			overwritten package aby header
		*/
		SETLONGVAR(tmpl, dest[0]);

		do {
			struct timeval  PollTime = { 0, 0 };
			PollTime.tv_sec = line->PollTimeSec;
			if ((i = ReceiveWithTimeout(&PollTime, dest, line->PacketSize)) <= 0) {
				if (i == -2)
					goto retry;
				return -1;
			}
			/* we got a handshakepackage, ignore it */
			if ((i == 1) && (dest[0] == '+')) {
				goto retry;
			}

			if (i <= 4) {
				return -1;
			}

			/* Detect and enqeue async notification that slipped into a request/reply pair */
			if (dest[0] == T32_API_NOTIFICATION) {
				T32_NotificationPackage *newPackage, *oldHead;

				newPackage = (T32_NotificationPackage *) malloc(sizeof(T32_NotificationPackage));
				if (newPackage == NULL)
					return -1;

				memcpy(newPackage, dest, i);    /* in theory i should always be the package size, at least for ethernet */
				oldHead = T32_NotificationHead;
				newPackage->prev = NULL;
				newPackage->next = oldHead;
				if (oldHead)
					oldHead->prev = newPackage;
				T32_NotificationHead = newPackage;
				if (T32_NotificationTail == NULL) {
					T32_NotificationTail = newPackage;
				}
				goto retry;
			}

			if (dest[0] != T32_API_RECEIVE) {
				return -1;
			}
			SETWORDVAR(tmpw, dest[2]);

			if (tmpw == line->LastReceiveSeq && line->LastTransmitSize) {
				line->TransmitSeq = line->LastTransmitSeq;
				LINE_LineTransmit(line->LastTransmitBuffer, line->LastTransmitSize);
			}
		}
		while (tmpw != line->ReceiveSeq);

		line->ReceiveSeq++;
		flag = dest[1];
		SETLONGVAR(dest[0], tmpl);      /* restore payload overwritten by package header */
		dest += i - 4;
		count += i - 4;

		if (count > LINE_MSIZE) {
			return -1;
		}
		if (flag == 2) {
			if (sendto(line->CommSocket, (const char *) handshake, 16, 0, (struct sockaddr *) &line->SocketAddress, sizeof(line->SocketAddress)) != 16) {     /* send Handshake 7 */
				return -1;
			}
		}
	}
	while (flag);

	line->LastReceiveSeq = s;

	return count;
}


/** Receives notification messages. First checks for a queued
	notification and if none is available polls the socket for new
	notifications. For getting all pending notifications call the
	function until it returns -1.

	@param package output buffer of size T32_PCKLEN_MAX for the package
	@return -1  no notification pending,
		>=0 notificataion type T32_E_BREAK, T32_E_EDIT, T32_E_BREAKPOINTCONFIG

 */
int LINE_ReceiveNotifyMessage(unsigned char *package)
{
	int             len;
	static struct timeval LongTime2 = { 0, 0 };

	/* Check for asynchronous notifications */
	if (T32_NotificationTail) {
		T32_NotificationPackage *prev = T32_NotificationTail->prev;
		if (prev)
			prev->next = NULL;
		memcpy(package, T32_NotificationTail->payload, T32_PCKLEN_MAX);
		free(T32_NotificationTail);
		T32_NotificationTail = prev;
		if (prev == NULL)       /* deleted last message */
			T32_NotificationHead = NULL;
	} else {
		len = ReceiveWithTimeout(&LongTime2, package, T32_PCKLEN_MAX);
		if (len < 2)
			return -1;
	}

	if (package[0] != T32_API_NOTIFICATION)
		return -1;

	return package[1];  /* type of notification: T32_E_BREAK, T32_E_EDIT, T32_E_BREAKPOINTCONFIG  */
}

/** Checks if any notification messages are pending in the queue.

	@return 1   notification pending,
			0   no notification pending

 */
int T32_NotificationPending(void)
{
	return T32_NotificationTail ? 1 : 0;
}

/** Sends sync packets */
int LINE_LineSync(void)
{
	int                i, j;
	unsigned char      packet[PCKLEN_MAX];
	static const char  magicPattern[] = "TRACE32";
	LineStruct        *line;

	if (!pLineParams)
		return -1;
	line = pLineParams;

	j = 0;
	memset(packet, 0, sizeof(packet));

retry:
	packet[0] = T32_API_SYNCREQUEST;
	packet[1] = 0;
	SETWORDVAR(packet[2], line->TransmitSeq);
	packet[4] = 0;
	packet[5] = 0;
	packet[6] = 0;
	packet[7] = 0;
	strcpy((char *) (packet + 8), magicPattern);

	if (sendto(line->CommSocket, (char *) packet, 16 /*size */ , 0, (struct sockaddr *) &line->SocketAddress, sizeof(line->SocketAddress)) == -1) {     /* Send SyncReq 2 */
		return -1;
	}
	while (1) { /* empty queue */
		if (++j > 20) {
			return -1;
		}
		if ((i = ReceiveWithTimeout(&LongTime, packet, PCKLEN_MAX)) <= 0) {
			return -1;
		}
		if (i != 16 || packet[0] != T32_API_SYNCACKN || strcmp((char *) packet + 8, magicPattern)) {
			if (i == 16 && packet[0] == 5)
				goto retry;
			continue;
		}
		break;
	}

	SETWORDVAR(line->ReceiveSeq, packet[2]);
	line->LastReceiveSeq = line->ReceiveSeq - 100;


	packet[0] = T32_API_SYNCBACK;
	packet[1] = 0;
	SETWORDVAR(packet[2], line->TransmitSeq);
	packet[4] = 0;
	packet[5] = 0;
	packet[6] = 0;
	packet[7] = 0;
	strcpy((char *) (packet + 8), magicPattern);

	if (sendto(line->CommSocket, (char *) packet, 16, 0, (struct sockaddr *) &line->SocketAddress, sizeof(line->SocketAddress)) == -1) {        /* Send SyncBack 0x22 */
		return -1;
	}
	return 1;
}


/** Establish a connection with TRACE32.

	@param  ipaddrused OUT
		in some special case returns an IP address;

	@return
		0 : ERROR e.g. in sending or receving packet
		1 : OK
		2 : ?ERROR?
*/
static int Connection(unsigned char *ipaddrused)
{
	int             i;
	unsigned char   buffer[PCKLEN_MAX];
	LineStruct     *line;
	static const char magicPattern[] = "TRACE32";

	if (!pLineParams)
		return 0;
	line = pLineParams;

	memset(buffer, 0, sizeof(buffer));

	buffer[0] = 3;      /* CONNECTREQUEST */
	buffer[1] = 1;      /* protocol version information */;

	line->TransmitSeq = 1;
	SETWORDVAR(buffer[2], line->TransmitSeq);
	SETWORDVAR(buffer[4], line->TransmitPort);
	SETWORDVAR(buffer[6], line->ReceivePort);

	strcpy((char *) (buffer + 8), magicPattern);

	/* send ConnectReq 3 */
	i = sendto(
		line->CommSocket, (char *) buffer, line->PacketSize, 0,
		(struct sockaddr *) &line->SocketAddress, sizeof(line->SocketAddress)
	);
	if (i == -1) {
		return 0;
	}
	i = ReceiveWithTimeout(&LongTime, buffer, line->PacketSize);
	if (i <= 0) {
		return 0;
	}
	if (strcmp((char *) (buffer + 8), magicPattern)) {
		return 0;
	}
	SETWORDVAR(line->ReceiveSeq, buffer[2]);

	if (buffer[0] == 0x53) {    /* POSITIVE CONNECTACKN from Debug Unit ? */
		ipaddrused[0] = 1;
		ipaddrused[1] = 1;
		ipaddrused[2] = 1;
		ipaddrused[3] = 11;
		return 2;
	}

	if (buffer[0] != 0x13) {    /* POSITIVE CONNECTACKN ? */
		if (buffer[0] == 0x23) {        /* NEGATIVE ? */
			ipaddrused[0] = buffer[4];
			ipaddrused[1] = buffer[5];
			ipaddrused[2] = buffer[6];
			ipaddrused[3] = buffer[7];
			return 2;
		}
		return 0;
	}
	line->PacketSize = i;

	return 1;
}


/* .NET helpers: additional functions to interface managed and unmanaged memory */
#ifdef  __cplusplus
extern          "C" void *LINE_AllocNewChannel()
{
	return malloc(sizeof(LineStruct));
}

extern          "C" void LINE_FreeAllocChannel(void *p)
{
	free(p);
}
#endif
