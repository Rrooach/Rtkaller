/*
 * TRACE32 Remote API
 *
 * Copyright (c) 1998-2015 Lauterbach GmbH
 * All rights reserved
 *
 * Link hlinknet.c and hremote.c with your application.
 *
 * Licensing restrictions apply to this code.
 * Please see documentation (api_remote.pdf) for
 * licensing terms and conditions.
 *
 * $LastChangedRevision: 116281 $
 *
 * formatted with:
 *    indent -kr -c0 -cbi0 -cd0 -cli4 -cp10 -di16 -fc1 -il0 -nsc -ppi2 --line-length120 --no-tabs hremote.c
 */

/* *INDENT-OFF* */
#ifndef HREMOTE_INCLUDED
#define HREMOTE_INCLUDED

/* Command IDs of the remote API */
enum {
	RAPI_CMD_NOP              = 0x70, /* NOP */
	RAPI_CMD_ATTACH           = 0x71, /* Attach to Device */
	RAPI_CMD_EXECUTE_PRACTICE = 0x72, /* Execute generic Practice command */
	RAPI_CMD_PING             = 0x73, /* Ping */
	RAPI_CMD_DEVICE_SPECIFIC  = 0x74, /* Device-Specific command */
	RAPI_CMD_CMDWINDOW        = 0x75, /* T32_CmdWin: Generic PRACTICE command with remote window */
	RAPI_CMD_GETMSG           = 0x76, /* T32_GetMessage */
	RAPI_CMD_SELECTPRECMD     = 0x77, /* Select Client number precommand. This is only used in PowerView internally. */
	RAPI_CMD_EDITNOTIFY       = 0x78, /* T32_EditNotifyEnable */
	RAPI_CMD_TERMINATE        = 0x79, /* T32_Terminate */
	RAPI_CMD_GETMSGSTRING     = 0x7A, /* T32_GetMessageString */
	RAPI_CMD_INTERCOMV2       = 0x7E, /* Intercom V2 */
	RAPI_CMD_INTERCOM         = 0x7F  /* Intercom */
};

/* Subcommand IDs for device specific commands of the remote API */
enum {
	RAPI_DSCMD_GETSTATE             = 0x10,
	RAPI_DSCMD_RESET                = 0x11,
	RAPI_DSCMD_STATE_SETNOTIFIER    = 0x12,
	RAPI_DSCMD_GETCPUINFO           = 0x13,
	RAPI_DSCMD_EVAL_GETVALUE        = 0x14,
	RAPI_DSCMD_MEMORY_GETMAP        = 0x16,
	RAPI_DSCMD_EVAL_GETSTRING       = 0x17,
	RAPI_DSCMD_EVENT_SETNOTIFIER    = 0x18,
	RAPI_DSCMD_GETLASTERRMSG        = 0x19,
	RAPI_DSCMD_REGISTER_READ        = 0x20,
	RAPI_DSCMD_REGISTER_WRITE       = 0x21,
	RAPI_DSCMD_REGISTER_PC_READ     = 0x22,
	RAPI_DSCMD_REGISTER_READBYNAME  = 0x23,
	RAPI_DSCMD_REGISTER_WRITEBYNAME = 0x24,
	RAPI_DSCMD_REGISTER_OBJ_READ    = 0x25,
	RAPI_DSCMD_REGISTER_OBJ_WRITE   = 0x26,
	RAPI_DSCMD_REGISTER_FPU_READ    = 0x27,
	RAPI_DSCMD_REGISTER_FPU_WRITE   = 0x28,
	RAPI_DSCMD_REGISTERSET_OBJ_READ = 0x29,
	RAPI_DSCMD_REGISTERSET_OBJ_WRITE= 0x2a,
	RAPI_DSCMD_MEMORY_READ          = 0x30,
	RAPI_DSCMD_MEMORY_WRITE         = 0x31,
	RAPI_DSCMD_MEMORY_WRITEPIPE     = 0x32,
	RAPI_DSCMD_MEMORY_TRANSACTION   = 0x33,
	RAPI_DSCMD_MEMORY_ACCESS_SET    = 0x34,
	RAPI_DSCMD_MEMORY_OBJ_READ      = 0x35,
	RAPI_DSCMD_MEMORY_OBJ_WRITE     = 0x36,
	RAPI_DSCMD_ADDRESS_OBJ_QUERY    = 0x37,
	RAPI_DSCMD_BUNDLE_OBJ_TRANSFER  = 0x38,
	RAPI_DSCMD_BREAKPOINT_GET       = 0x40,
	RAPI_DSCMD_BREAKPOINT_SET       = 0x41,
	RAPI_DSCMD_BREAKPOINT_CLEAR     = 0x42,
	RAPI_DSCMD_BREAKPOINT_MCD       = 0x43,
	RAPI_DSCMD_BREAKPOINT_OBJ_READ  = 0x44,
	RAPI_DSCMD_BREAKPOINT_OBJ_WRITE = 0x45,
	RAPI_DSCMD_BREAKPOINT_OBJ_QUERY = 0x46,
	RAPI_DSCMD_STEP_SINGLE          = 0x50,
	RAPI_DSCMD_GO                   = 0x51,
	RAPI_DSCMD_BREAK                = 0x52,
	RAPI_DSCMD_MODE_SET             = 0x53,
	RAPI_DSCMD_STEP_MODE            = 0x54,
	RAPI_DSCMD_SOURCE_GETFILE       = 0x60,
	RAPI_DSCMD_SOURCE_GETSELECTED   = 0x61,
	RAPI_DSCMD_SYMBOL_GET           = 0x62,
	RAPI_DSCMD_TRIGGER_MESSAGE_GET  = 0x63,
	RAPI_DSCMD_BREAKPOINT_LIST      = 0x64,
	RAPI_DSCMD_VARIABLE_READVALUE   = 0x65,
	RAPI_DSCMD_VARIABLE_READSTRING  = 0x66,
	RAPI_DSCMD_SYMBOL_GETBYADDRESS  = 0x67,
	RAPI_DSCMD_SYMBOL_QUERYOBJ      = 0x68,
	RAPI_DSCMD_VARIABLE_WRITEVALUE  = 0x69,
	RAPI_DSCMD_WINDOW_CONTENT       = 0x70,
	RAPI_DSCMD_ANALYZER_STATE       = 0x80,
	RAPI_DSCMD_ANALYZER_READ        = 0x81,
	RAPI_DSCMD_TRACE_STATE          = 0x82,
	RAPI_DSCMD_TRACE_READ           = 0x83,
	RAPI_DSCMD_DAAPI                = 0x92,
	RAPI_DSCMD_DAAPI_HOLD           = 0x93,
	RAPI_DSCMD_API_LOCK             = 0x94,
	RAPI_DSCMD_API_UNLOCK           = 0x95,
	RAPI_DSCMD_FDX_RESOLVE          = 0xA0,
	RAPI_DSCMD_FDX_OPEN             = 0xA1,
	RAPI_DSCMD_FDX_RECEIVEPOLL      = 0xA2,
	RAPI_DSCMD_FDX_RECEIVE          = 0xA3,
	RAPI_DSCMD_FDX_TRANSMITPOLL     = 0xA4,
	RAPI_DSCMD_FDX_TRANSMIT         = 0xA5,
	RAPI_DSCMD_FDX_CLOSE            = 0xA6,
	RAPI_DSCMD_LUA_EXECUTE          = 0xB0,
	RAPI_DSCMD_FLASHFILE_READ       = 0xC0,
	RAPI_DSCMD_FLASHFILE_WRITE      = 0xC1,
	RAPI_DSCMD_FLASHFILE_FLUSH      = 0xC2,
	RAPI_DSCMD_EXTENSION            = 0xFF
};

/* function specific error codes */
#define T32_ERR_FN1 90
#define T32_ERR_FN2 91
#define T32_ERR_FN3 92
#define T32_ERR_FN4 93

#endif /*HREMOTE_INCLUDED */


#ifndef HREMOTE_DEFINITIONS_ONLY
/* *INDENT-ON* */

#include "t32.h"

#if defined(_MSC_VER)
# pragma warning( push )
# pragma warning( disable : 4255 )
#endif

#if defined(T32HOST_SOL) && !defined(__EXTENSIONS__)
/* Make sure we get some prototypes from Solaris headers.  */
# define __EXTENSIONS__
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#ifdef T32HOST_WIN
# include <malloc.h>
# include <windows.h>
#else
# include <sys/time.h>
#endif

#if defined(_MSC_VER)
# pragma warning( pop )
#endif

T32_THREADLOCAL int T32_Errno;

#define MAXRETRY        5

#define EMU_CBMAXDATASIZE 0x3c00

#define LINE_SBLOCK     4096    /* small block mode */

#define T32_MSG_LHANDLE 0x10
#define T32_MSG_LRETRY  0x08

T32_THREADLOCAL unsigned char LINE_OutBuffer[LINE_MSIZE + 256];
T32_THREADLOCAL unsigned char LINE_InBuffer[LINE_MSIZE + 256];

#define T32_OUTBUFFER (LINE_OutBuffer+13+4)
#define T32_INBUFFER  (LINE_InBuffer+13)

/* forward declaration, see hlinknet.c for definition */
typedef struct LineStruct_s LineStruct;

extern int      LINE_LineConfig(char *in);
extern int      LINE_LineInit(char *message);
extern void     LINE_LineExit(void);
extern int      LINE_LineDriverGetSocket(void);
extern int      LINE_LineTransmit(unsigned char *in, int size);
extern int      LINE_LineReceive(unsigned char *out);
extern int      LINE_ReceiveNotifyMessage(unsigned char *package);
extern int      LINE_LineSync(void);
extern int      LINE_GetLineParamsSize(void);
extern void     LINE_DefaultLineParams(LineStruct * ParametersOut);
extern void     LINE_SetLine(LineStruct * params);
extern void     LINE_SetReceiveToggleBit(int value);
extern int      LINE_GetReceiveToggleBit(void);
extern unsigned char LINE_GetNextMessageId(void);
extern unsigned char LINE_GetMessageId(void);

/* prototypes for local helper functions */
int             LINE_Transmit(int len);
int             LINE_Receive(void);
int             LINE_Sync(void);

static const int MaxPacketSize = 2048;


static void T32_ApiCallEpilog(void)
{
#if defined(ENABLE_NOTIFICATION) && defined(ENABLE_AUTONOTIFY)
	T32_CheckStateNotify(0);
#endif
}


/**************************************************************************

  T32_GetApiRevision - Get API revision number

  Parameter:  out  pointer to variable receiving the revision number

  Return:     int  T32_OK

***************************************************************************/
static const char svnRevisionString[] = "$LastChangedRevision: 116281 $";
int T32_GetApiRevision(uint32_t * pRevNum)
{
	*pRevNum = (uint32_t)atoi(svnRevisionString + 22);
	return T32_OK;
}

/**************************************************************************

  API Log to log all API calls

  Enable the code with preprocessor switch ENABLE_APILOG
  Enable the logging by setting the environment variable
	  T32APILOGFILE to the log file path/name

***************************************************************************/

/* #define ENABLE_APILOG 1 */

#define T32APILOG_FENTRY    1
#define T32APILOG_FEXIT     2

#ifdef _WIN32
/* quirks of Windows: */
/* define __func__ (which is C99 standard!) and */
# define __func__  __FUNCTION__
#endif   /* _WIN32 */

#if defined(ENABLE_APILOG)

static T32_THREADLOCAL FILE    *ApiLogFile = NULL;
static T32_THREADLOCAL int      ApiLogEnable = 0;

# ifdef _WIN32
/* implement gettimeofday() */

#  define __func__  __FUNCTION__

/* FILETIME of Jan 1 1970 00:00:00. */
static const unsigned __int64 epoch = 116444736000000000LL;

int gettimeofday(struct timeval *tp, struct timezone *tzp)
{
	FILETIME        file_time;
	SYSTEMTIME      system_time;
	ULARGE_INTEGER  ularge;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	ularge.LowPart = file_time.dwLowDateTime;
	ularge.HighPart = file_time.dwHighDateTime;

	tp->tv_sec = (long) ((ularge.QuadPart - epoch) / 10000000L);
	tp->tv_usec = (long) (system_time.wMilliseconds * 1000);

	return 0;
}
# endif /* _WIN32 */

static int T32_OpenApiLogFile(const char *filename)
{
	ApiLogFile = fopen(filename, "a");
	if (ApiLogFile == NULL)
		return 1;
	ApiLogEnable = 1;
	return 0;
}

static int T32_CloseApiLogFile(void)
{
	ApiLogEnable = 0;
	if (ApiLogFile)
		fclose(ApiLogFile);
	ApiLogFile = NULL;
	return 0;
}

static void T32_ApiLog(const char *func, int entry, const char *argformat, ...)
{
	va_list         args;
	struct timeval  time;
	if (!ApiLogFile || !ApiLogEnable)
		return;
	gettimeofday(&time, 0);
	if (argformat)
		va_start(args, argformat);
	fprintf(ApiLogFile, "/*%d.%6d*/ ", time.tv_sec, time.tv_usec);
	if (entry == T32APILOG_FENTRY) {
		fprintf(ApiLogFile, "%s(", func);
		if (argformat)
			vfprintf(ApiLogFile, argformat, args);
		else
			fprintf(ApiLogFile, "/*void*/");
		fprintf(ApiLogFile, ");\n");
	} else if (entry == T32APILOG_FEXIT) {
		fprintf(ApiLogFile, "//%s()=", func);
		if (argformat)
			vfprintf(ApiLogFile, argformat, args);
		else
			fprintf(ApiLogFile, "<void>");
		fprintf(ApiLogFile, "\n");
	} else
		fprintf(ApiLogFile, "ERROR entry %d in %s\n", entry, func);
	if (argformat)
		va_end(args);
}

#else    /* defined(ENABLE_APILOG) */

/* static int T32_OpenApiLogFile (const char* filename) {return 0;} */
static int T32_CloseApiLogFile(void)
{
	return 0;
}

# define T32_ApiLog(...)

#endif   /* defined(ENABLE_APILOG) */


/**************************************************************************

  T32_GetLineSize - Get sizeof line structure for Multi-Line usage

  Return:       sizeof line structure

  Usage:        void* line = malloc (T32_GetLineSize());

***************************************************************************/
int T32_GetChannelSize(void)
{
	int             size;
	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);
	size = LINE_GetLineParamsSize();
	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", size);
	return size;
}


/**************************************************************************

  T32_GetLineDefaults - Get default parameters for Multi-Line usage

  Parameter:    out  pointer to line receiving the defaults

  Usage:        T32_GetLineDefaults (line);

***************************************************************************/

void T32_GetChannelDefaults(void *ParametersOut)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", ParametersOut);
	LINE_DefaultLineParams((LineStruct *) ParametersOut);
	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, 0);
	return;
}


/**************************************************************************

  T32_SetLine - Set active line for Multi-Line usage

  Parameter:    in  pointer to now active line

  Usage:        T32_SetChannel (line);

***************************************************************************/
void T32_SetChannel(void *ParametersIn)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", ParametersIn);
	LINE_SetLine((LineStruct *) ParametersIn);
	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, 0);
	return;
}


/**************************************************************************

  T32_APILock - create a critical section when multiple clients access to
	one RemoteAPI

  Parameter:  - nTimeoutMS - timeout of lock command in milliseconds
	  0 : lock if RemoteAPI server is not in use or return 123 to
		  indicate that the system is locked already by another client
	  -1: wait infinite time until the system becomes unlocked
		  (you need to increase the TIMEOUT= setting, too)
	   n: wait n ms to get the lock. returns 123 if command was not sucessful

  Return:     return 0 or 123 (system already locked by other client)

***************************************************************************/

int T32_APILock(int nTimeoutMS)
{

	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d", nTimeoutMS);

	T32_OUTBUFFER[0] = 6;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_API_LOCK;
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	T32_OUTBUFFER[4] = (((unsigned int) nTimeoutMS) & 0xFF);
	T32_OUTBUFFER[5] = ((((unsigned int) nTimeoutMS) >> 8) & 0xFF);
	T32_OUTBUFFER[6] = ((((unsigned int) nTimeoutMS) >> 16) & 0xFF);
	T32_OUTBUFFER[7] = ((((unsigned int) nTimeoutMS) >> 24) & 0xFF);

	if (LINE_Transmit(8) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

/**************************************************************************

  T32_APIUnlock - leave critical section when multiple clients access to
	  one RemoteAPI

  Parameter:  -

  Return:     int  0

***************************************************************************/

int T32_APIUnlock(void)
{

	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_API_UNLOCK;
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

/**************************************************************************

  T32_Nop - Sends one NIL message to the system

  Return:     int  0 or Number of Error

***************************************************************************/
int T32_NopEx(int length, int options)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);

	T32_OUTBUFFER[0] = (unsigned char)((length > 0xfd) ? (0) : (length+2));
	T32_OUTBUFFER[1] = RAPI_CMD_NOP;
	T32_OUTBUFFER[2] = (options & 0xff);
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();
	T32_OUTBUFFER[4] = ((length+4) & 0xff);
	T32_OUTBUFFER[5] = (((length+4)>>8) & 0xff);

	if (LINE_Transmit( (length > 0xfd) ? (length+6) : (length+4)) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_Nop(void)
{
	return T32_NopEx(0, 0);
}


/**************************************************************************

  T32_NopFail - Sends one NIL message to the system

  Return:     int  -1 or Number of Error

***************************************************************************/
int T32_NopFail(void)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_NOP;
	T32_OUTBUFFER[2] = 0x00;
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err)
		T32_ApiCallEpilog();
	err = -1;   /* fail! */
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/**************************************************************************

  T32_Ping - Sends one PING message to the system

  Return:     int  0 or Number of Error

***************************************************************************/
int T32_Ping(void)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_PING;
	T32_OUTBUFFER[2] = 0x00;
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/**************************************************************************

  T32_Stop - Stop the currently running PRACTICE program

  Return:   int  0 or Number of Error

  Note:     Former variant used CHAR_FBREAK (0x5000) and an empty T32_Cmd.

***************************************************************************/
int T32_Stop(void)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_EXECUTE_PRACTICE;
	T32_OUTBUFFER[2] = 0x00;    /* PRACTICE stop */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/**************************************************************************

  T32_Terminate - Terminate executable

  Return:     int  0 or Number of Error

***************************************************************************/
int T32_Terminate(int ShellReturnValue)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d", ShellReturnValue);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_TERMINATE;
	T32_OUTBUFFER[2] = (unsigned char) ShellReturnValue;
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/**************************************************************************

  T32_Attach - Attaches control to a device

  Parameter:  in int DeviceSpecifier Number of device (T32_DEV_OS, T32_DEV_ICE, T32_DEV_ICD)

  Return:     int  0 or Number of Error

***************************************************************************/
int T32_Attach(int DeviceSpecifier)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d", DeviceSpecifier);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_ATTACH;
	T32_OUTBUFFER[2] = (unsigned char) DeviceSpecifier;
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/**************************************************************************

  T32_GetState - Return information about the state of TRACE32

  Parameter:  out int * pSystemState Pointer to variable to return the state
	0 System down
	1 System halted
	2 Emulation stopped
	3 Emulation running

  Return:     int  0 or Number of Error

***************************************************************************/
int T32_GetState(int *pSystemState)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pSystemState);

	if (!pSystemState)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		T32_OUTBUFFER[0] = 2;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_GETSTATE; /* T32_GetState: Read Status Information */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();

		if (LINE_Transmit(4) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		*pSystemState = T32_INBUFFER[4];

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	} else {
		if (pSystemState)
			*pSystemState = 0;      /* default in case of error */
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%d", err, pSystemState, *pSystemState);
	return err;
}


/**************************************************************************

  T32_GetCpuInfo - Get information about the used CPU

  Parameter:  out char    **pCPUString     string Pointer to a string decribing the CPU
	  out uint16_t *pFPUType     Pointer to catch the FPU type ( not used, always 0 )
	  out uint16_t *pEndianess  Pointer to catch the Endian mode
		 1  BigEndian
		 0  LittleEndian
	  out uint16_t *pReserved    Pointer to get internal information
			 (for internal use only)

  Return:     int  0 or Number of Error

***************************************************************************/
int T32_GetCpuInfo(char **pCPUString, uint16_t * pFPUType, uint16_t * pEndianess, uint16_t * pReserved)
{
	int             i, err = 0;
	static char     cpu_string[16];

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, p%x, p%x, p%x", pCPUString, pFPUType, pEndianess, pReserved);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_GETCPUINFO;   /* T32_GetCpuInfo: Get CPU information */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		for (i = 0; i < 15; i++)
			cpu_string[i] = (T32_INBUFFER + 4)[i];

		cpu_string[15] = 0;
		*pCPUString = cpu_string;
		*pFPUType = *pEndianess = *pReserved = 0;
		SETWORDVAR(*pFPUType, T32_INBUFFER[22]);
		SETWORDVAR(*pEndianess, T32_INBUFFER[24]);
		SETWORDVAR(*pReserved, T32_INBUFFER[20]);

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%d, p%x=\"%s\"", err, pCPUString, *pCPUString);
	return err;
}


/** Get Data or Program RAM addresses. */
int T32_GetRam(uint32_t * pStartAddress, uint32_t * pEndAddress, uint16_t * pAccess)
{
	int             err = 0;
	uint32_t        t32access;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, p%x, p%x", pStartAddress, pEndAddress, pAccess);

	T32_OUTBUFFER[0] = 8;       /* len */
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_MEMORY_GETMAP;        /* T32_GetRam: Get Memory Mapping */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();
	SETLONGVAR(T32_OUTBUFFER[4], *pStartAddress);
	SETWORDVAR(T32_OUTBUFFER[8], *pAccess);

	if (LINE_Transmit(10) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		SETLONGVAR(*pStartAddress, T32_INBUFFER[4]);
		SETLONGVAR(*pEndAddress, T32_INBUFFER[8]);
		SETLONGVAR(t32access, T32_INBUFFER[12]);

		if (!t32access)
			*pAccess = 0;

		err = T32_INBUFFER[2];
		if (err == T32_ERR_FN1)
			err = T32_ERR_GETRAM_INTERNAL;
		T32_Errno = err;
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%x", err, pStartAddress, *pStartAddress);
	return err;
}


/** Reset CPU Registers. */
int T32_ResetCPU(void)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_RESET;        /* T32_ResetCpu: Reset CPU */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/*  Write Memory.
 *
 *  ADDRESS   memory address
 *  ACCESS    memory access flags
 *  pBuffer   data to be written
 *  SIZE      size of data
 */
int T32_WriteMemory(uint32_t Address, int Access, const uint8_t * pBuffer, int Size)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "0x%x, %d, (uint8_t*) p%x, %d", Address, Access, pBuffer, Size);

	if (Size > MaxPacketSize) {
		err = T32_WriteMemoryPipe(Address, Access, pBuffer, Size);
		if (!err)
			err = T32_WriteMemoryPipe(Address, Access, pBuffer, 0);
		T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
		return err;
	}

	/* Protocol Header */
	T32_OUTBUFFER[0] = 10;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_MEMORY_WRITE;
	T32_OUTBUFFER[3] = LINE_GetNextMessageId(); /* Message ID */

	/* Command specific part */
	SETLONGVAR(T32_OUTBUFFER[4], Address);
	T32_OUTBUFFER[8] = (unsigned char) Access;
	T32_OUTBUFFER[9] = 0;
	T32_OUTBUFFER[10] = (unsigned char) (Size & 0xff);
	T32_OUTBUFFER[11] = (unsigned char) (Size >> 8);

	/* payload */
	memcpy(T32_OUTBUFFER + 12, pBuffer, Size);

	if (LINE_Transmit(12 + ((Size + 1) & (~1))) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/*  Write Memory, Pipelined.
 *
 *  ADDRESS   memory address
 *  ACCESS    memory access flags
 *  pBuffer   data to be written
 *  SIZE      size of data
 */
int T32_WriteMemoryPipe(uint32_t Address, int Access, const uint8_t * pBuffer, int Size)
{
	int             len, err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "0x%x, %d, (uint8_t*) p%x, %d", Address, Access, pBuffer, Size);

	if (Size == 0) {
		T32_OUTBUFFER[0] = 2;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_MEMORY_WRITEPIPE; /* T32_WriteMemoryPipe */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();

		if (LINE_Transmit(4) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;

		if (!err && (LINE_Receive() == -1))
			err = T32_Errno = T32_COM_RECEIVE_FAIL;

		if (!err)
			err = T32_Errno = T32_INBUFFER[2];
	}
	while (!err && (Size > 0)) {
		len = Size;
		if (len > MaxPacketSize)
			len = MaxPacketSize;

		T32_OUTBUFFER[0] = 10;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_MEMORY_WRITEPIPE; /* T32_WriteMemoryPipe */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();

		SETLONGVAR(T32_OUTBUFFER[4], Address);
		T32_OUTBUFFER[8] = (unsigned char) Access;
		T32_OUTBUFFER[9] = 0;
		T32_OUTBUFFER[10] = (unsigned char) (len & 0xff);
		T32_OUTBUFFER[11] = (unsigned char) (len >> 8);

		memcpy(T32_OUTBUFFER + 12, pBuffer, len);

		if (LINE_Transmit(12 + ((len + 1) & (~1))) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;

		if (!err && (LINE_Receive() == -1))
			err = T32_Errno = T32_COM_RECEIVE_FAIL;

		if (!err)
			err = T32_Errno = T32_INBUFFER[2];

		Size -= len;
		Address += len;
		pBuffer += len;
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/* Write Memory, extended version */
int T32_WriteMemoryEx(uint32_t Address, int Segment, int Access, int Attribute, uint8_t * pBuffer, int Size)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "0x%x, %d, %d, %d, (uint8_t*) p%x, %d",
			   Address, Segment, Access, Attribute, pBuffer, Size);

	while (!err && (Size > 0)) {
		int             len, pos;

		len = Size;
		if (len > MaxPacketSize)
			len = MaxPacketSize;

		pos = 0;
		T32_OUTBUFFER[pos++] = 0;
		T32_OUTBUFFER[pos++] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[pos++] = RAPI_DSCMD_MEMORY_TRANSACTION;   /* MCD API transaction list, T32_ReadMemoryEx, T32_WriteMemoryEx */
		T32_OUTBUFFER[pos++] = LINE_GetNextMessageId();

		T32_OUTBUFFER[pos++] = 0x02;    /* LSB of ttype (Ltb.Internal) */
		T32_OUTBUFFER[pos++] = (Segment != -1) ? 0x40 : 0x00;   /* MSB of ttype (Ltb.Internal) */

		SETLONGVAR(T32_OUTBUFFER[pos], Address);
		pos += 4;
		if (Segment != -1) {
			SETLONGVAR(T32_OUTBUFFER[pos], Segment);
			pos += 4;
		}
		SETWORDVAR(T32_OUTBUFFER[pos], Access);
		pos += 2;
		SETLONGVAR(T32_OUTBUFFER[pos], Attribute);
		pos += 4;
		SETWORDVAR(T32_OUTBUFFER[pos], len);
		pos += 2;

		memcpy(T32_OUTBUFFER + pos, pBuffer, len);
		pos += ((len + 1) & (~1));

		T32_OUTBUFFER[pos++] = 0;
		T32_OUTBUFFER[pos++] = 0;

		if (LINE_Transmit(pos) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;

		if (!err && (LINE_Receive() == -1))
			err = T32_Errno = T32_COM_RECEIVE_FAIL;

		if (!err)
			err = T32_Errno = T32_INBUFFER[2];
		if (!err)
			err = T32_Errno = T32_INBUFFER[4];
		Size -= len;
		if (!(Attribute & T32_MEMORY_ATTR_NOINCREMENT))
			Address += len;
		pBuffer += len;
	}
	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/*  Read Memory
 *
 *  ADDRESS   memory address in target memory
 *  ACCESS    memory access specifier
 *  pBuffer   output buffer
 *  SIZE      size of data in bytes
 */
int T32_ReadMemory(uint32_t Address, int Access, uint8_t * pBuffer, int Size)
{
	int             len, err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "0x%x, %d, (uint8_t*) p%x, %d", Address, Access, pBuffer, Size);

	while (!err && (Size > 0)) {
		len = Size;
		if (len > MaxPacketSize)
			len = MaxPacketSize;

		T32_OUTBUFFER[0] = 10;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_MEMORY_READ;      /* T32_ReadMemory */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();

		SETLONGVAR(T32_OUTBUFFER[4], Address);
		T32_OUTBUFFER[8] = (unsigned char) Access;
		T32_OUTBUFFER[9] = 0;
		T32_OUTBUFFER[10] = (unsigned char) (len & 0xff);
		T32_OUTBUFFER[11] = (unsigned char) (len >> 8);

		if (LINE_Transmit(12) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;

		if (!err && (LINE_Receive() == -1))
			err = T32_Errno = T32_COM_RECEIVE_FAIL;

		if (!err) {
			memcpy(pBuffer, T32_INBUFFER + 4, len);
			err = T32_Errno = T32_INBUFFER[2];
		}

		Size -= len;
		Address += len;
		pBuffer += len;
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/* Read Memory, extended version */
int T32_ReadMemoryEx(uint32_t Address, int Segment, int Access, int Attribute, uint8_t * pBuffer, int Size)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY,
			   "0x%x, %d, %d, %d, (uint8_t*) p%x, %d", Address, Segment, Access, Attribute, pBuffer, Size);

	while (!err && (Size > 0)) {
		uint16_t        wAccess, wlen;
		int             len, pos;
		len = Size;
		if (len > MaxPacketSize)
			len = MaxPacketSize;

		pos = 0;
		T32_OUTBUFFER[pos++] = 0;
		T32_OUTBUFFER[pos++] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[pos++] = RAPI_DSCMD_MEMORY_TRANSACTION;   /* MCD API transaction list, T32_ReadMemoryEx, T32_WriteMemoryEx */
		T32_OUTBUFFER[pos++] = LINE_GetNextMessageId();

		T32_OUTBUFFER[pos++] = 0x01;    /* LSB of ttype (LB_Internal) */
		T32_OUTBUFFER[pos++] = (Segment != -1) ? 0x40 : 0x00;   /* MSB of ttype (LB_Internal) */
		SETLONGVAR(T32_OUTBUFFER[pos], Address);
		pos += 4;
		if (Segment != -1) {
			SETLONGVAR(T32_OUTBUFFER[pos], Segment);
			pos += 4;
		}
		wAccess = (uint16_t) Access;
		SETWORDVAR(T32_OUTBUFFER[pos], wAccess);
		pos += 2;
		SETLONGVAR(T32_OUTBUFFER[pos], Attribute);
		pos += 4;
		wlen = (uint16_t) len;
		SETWORDVAR(T32_OUTBUFFER[pos], wlen);
		pos += 2;
		T32_OUTBUFFER[pos++] = 0;
		T32_OUTBUFFER[pos++] = 0;

		if (LINE_Transmit(pos) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;

		if (!err && (LINE_Receive() == -1))
			err = T32_Errno = T32_COM_RECEIVE_FAIL;

		if (!err)
			err = T32_Errno = T32_INBUFFER[2];
		if (!err)
			err = T32_Errno = T32_INBUFFER[4];

		if (!err)
			memcpy(pBuffer, T32_INBUFFER + 8, len);

		Size -= len;
		if (!(Attribute & T32_MEMORY_ATTR_NOINCREMENT))
			Address += len;
		pBuffer += len;
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int  T32_FlashfileReadMemory(uint64_t Addr64, uint8_t *pBuffer, int Size)
{
	int             len, err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "0x%x, (uint8_t*) p%x, %d", (uint32_t)Addr64, pBuffer, Size);

	while (!err && (Size > 0)) {
		len = Size;
		if (len > MaxPacketSize)
			len = MaxPacketSize;

		T32_OUTBUFFER[0] = (10+4);
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_FLASHFILE_READ;      /* T32_FlashfileRead */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();

		SETQUADVAR(T32_OUTBUFFER[4], Addr64);   /* 8byte address */
		T32_OUTBUFFER[8+4] = 0;
		T32_OUTBUFFER[9+4] = 0;
		T32_OUTBUFFER[10+4] = (unsigned char) (len & 0xff);
		T32_OUTBUFFER[11+4] = (unsigned char) (len >> 8);

		if (LINE_Transmit((12+4)) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;

		if (!err && (LINE_Receive() == -1))
			err = T32_Errno = T32_COM_RECEIVE_FAIL;

		if (!err) {
			memcpy(pBuffer, T32_INBUFFER + 4, len);
			err = T32_Errno = T32_INBUFFER[2];
		}

		Size -= len;
		Addr64 += len;
		pBuffer += len;
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int  T32_FlashfileWriteMemory(uint64_t Addr64, const uint8_t *pBuffer, int Size)
{
	int             len,err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "0x%x, (uint8_t*) p%x, %d", (uint32_t)Addr64, pBuffer, Size);

	while (!err && (Size > 0)) {
		len = Size;
		if (len > MaxPacketSize)
			len = MaxPacketSize;

		/* Protocol Header */
		T32_OUTBUFFER[0] = 14;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_FLASHFILE_WRITE;  /* T32_FlashfileWrite */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId(); /* Message ID */

		/* Command specific part */
		SETQUADVAR(T32_OUTBUFFER[4], Addr64);  /* 8byte address */
		T32_OUTBUFFER[12] = 0;
		T32_OUTBUFFER[13] = 0;
		T32_OUTBUFFER[14] = (unsigned char) (len & 0xff);
		T32_OUTBUFFER[15] = (unsigned char) (len >> 8);

		/* payload */
		memcpy(T32_OUTBUFFER + (16), pBuffer, len);

		if (LINE_Transmit( (16) + ((len + 1) & (~1))) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;

		if (!err && (LINE_Receive() == -1))
			err = T32_Errno = T32_COM_RECEIVE_FAIL;

		if (!err)
			err = T32_Errno = T32_INBUFFER[2];

		Size -= len;
		Addr64 += len;
		pBuffer += len;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int  T32_FlashfileFlushMemory( uint64_t Addr64, int Size, uint32_t *pFlushResult )
{

	int             err = 0;
	uint32_t        tmp=0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);

	T32_OUTBUFFER[0] = 14;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_FLASHFILE_FLUSH;      /* T32_FlashfileFlush */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	/* Command specific part */
	SETQUADVAR(T32_OUTBUFFER[4], Addr64);  /* [4:11]  8bytes */
	SETLONGVAR(T32_OUTBUFFER[12], Size);  /* [12:15] 4bytes */

	if (LINE_Transmit(16) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		SETLONGVAR(tmp, T32_INBUFFER[4]);  /* the rest flush blocks */
		*pFlushResult = tmp;
		err = T32_Errno = T32_INBUFFER[2];
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_SetMemoryAccessClass(const char *access)
{
	int             err = 0, len;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\"", access);

	if (!access)
		access = "";

	len = (int) strlen(access);

	if (len + 3 > 0xff)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		T32_OUTBUFFER[0] = (unsigned char) len + 3;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_MEMORY_ACCESS_SET;        /* T32_SetMemoryAccessClass */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		strcpy((char *) (T32_OUTBUFFER + 4), access);

		if (LINE_Transmit((len + 5 + 1) & (~1)) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err)
		err = T32_Errno = T32_INBUFFER[2];

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/* Write Registers.
 *
 * MaskLower32Bit     defines the registers to be set
 * MaskUpper32Bit
 * pBuffer    array of all registers
 */
int T32_WriteRegister(uint32_t MaskLower32Bit, uint32_t MaskUpper32Bit, uint32_t * pBuffer)
{
	int             err = 0, index, i;
	uint32_t        tmp;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "0x%8x, 0x%8x, p%x", MaskLower32Bit, MaskUpper32Bit, pBuffer);

	index = 12;
	tmp = MaskLower32Bit;
	SETLONGVAR(T32_OUTBUFFER[4], tmp);
	tmp = MaskUpper32Bit;
	SETLONGVAR(T32_OUTBUFFER[8], tmp);

	for (i = 0; i < 32; i++) {
		if (MaskLower32Bit & 1l) {
			tmp = *pBuffer;
			SETLONGVAR(T32_OUTBUFFER[index], tmp);
			index += 4;
		}
		pBuffer++;
		MaskLower32Bit >>= 1;
	}

	for (; i < 64; i++) {
		if (MaskUpper32Bit & 1l) {
			tmp = *pBuffer;
			SETLONGVAR(T32_OUTBUFFER[index], tmp);
			index += 4;
		}
		pBuffer++;
		MaskUpper32Bit >>= 1;
	}

	T32_OUTBUFFER[0] = (unsigned char) index;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_REGISTER_WRITE;       /* T32_WriteRegister: Write Registers */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(index) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/* Read Registers.
 *
 * MaskLower32Bit     defines the registers to be read
 * MaskUpper32Bit
 * pBuffer            array of all registers
 */
int T32_ReadRegister(uint32_t MaskLower32Bit, uint32_t MaskUpper32Bit, uint32_t * pBuffer)
{
	int             err = 0, index, i;
	uint32_t        tmp;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "0x%8x, 0x%8x, p%x", MaskLower32Bit, MaskUpper32Bit, pBuffer);

	tmp = MaskLower32Bit;
	SETLONGVAR(T32_OUTBUFFER[4], tmp);
	tmp = MaskUpper32Bit;
	SETLONGVAR(T32_OUTBUFFER[8], tmp);

	T32_OUTBUFFER[0] = 12;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_REGISTER_READ;        /* T32_ReadRegister: Read Registers */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(12) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		index = 4;
		for (i = 0; i < 32; i++) {
			if (MaskLower32Bit & 1l) {
				SETLONGVAR(tmp, T32_INBUFFER[index]);
				index += 4;
				*pBuffer = tmp;
			} else
				*pBuffer = 0x0;
			pBuffer++;
			MaskLower32Bit >>= 1;
		}

		for (; i < 64; i++) {
			if (MaskUpper32Bit & 1l) {
				SETLONGVAR(tmp, T32_INBUFFER[index]);
				index += 4;
				*pBuffer = tmp;
			} else
				*pBuffer = 0x0;
			pBuffer++;
			MaskUpper32Bit >>= 1;
		}

		err = T32_Errno = T32_INBUFFER[2];
	}

	if (!err)
		T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_ReadRegisterByName(const char *RegisterName, uint32_t * pValueLower32Bit, uint32_t * pValueUpper32Bit)
{
	int             err = 0;
	unsigned int    len;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\", 0x%8x, 0x%8x", RegisterName, pValueLower32Bit, pValueUpper32Bit);

	len = (unsigned int) strlen(RegisterName);

	if (len + 3 > 0xff)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		T32_OUTBUFFER[0] = (unsigned char) (len + 3);
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_REGISTER_READBYNAME;      /* T32_ReadRegisterByName */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		strcpy((char *) (T32_OUTBUFFER + 4), RegisterName);

		if (LINE_Transmit((len + 5 + 1) & (~1)) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		SETLONGVAR(*pValueLower32Bit, T32_INBUFFER[4]);
		SETLONGVAR(*pValueUpper32Bit, T32_INBUFFER[8]);

		err = T32_INBUFFER[2];
		switch (err) {
			case T32_ERR_FN1:
				err = T32_ERR_READREGBYNAME_NOTFOUND;
				break;
			case T32_ERR_FN2:
				err = T32_ERR_READREGBYNAME_FAILED;
				break;
		}
		T32_Errno = err;
		T32_ApiCallEpilog();
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_WriteRegisterByName(const char *RegisterName, uint32_t ValueLower32Bit, uint32_t ValueUpper32Bit)
{
	int             err = 0;
	unsigned int    regnamelen;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\", 0x%8x, 0x%8x", RegisterName, ValueLower32Bit, ValueUpper32Bit);

	regnamelen = (unsigned int) strlen(RegisterName);

	if (regnamelen + 3 + 8 > 0xff)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		T32_OUTBUFFER[0] = (unsigned char) (regnamelen + 3 + 8);
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_REGISTER_WRITEBYNAME;     /* T32_WriteRegisterByName */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		SETLONGVAR(T32_OUTBUFFER[4], ValueLower32Bit);
		SETLONGVAR(T32_OUTBUFFER[8], ValueUpper32Bit);
		strcpy((char *) (T32_OUTBUFFER + 12), RegisterName);

		if (LINE_Transmit((regnamelen + 5 + 1 + 8) & (~1)) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_INBUFFER[2];
		switch (err) {
			case T32_ERR_FN1:
				err = T32_ERR_WRITEREGBYNAME_NOTFOUND;
				break;
			case T32_ERR_FN2:
				err = T32_ERR_WRITEREGBYNAME_FAILED;
				break;
		}
		T32_Errno = err;
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_ReadPP(uint32_t * pProgramCounter)
{       /* Returns Program Pointer */
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pProgramCounter);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_REGISTER_PC_READ;     /* T32_ReadPP: Read Program Pointer */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		SETLONGVAR(*pProgramCounter, T32_INBUFFER[4]);

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=0x%x", err, pProgramCounter, *pProgramCounter);
	return err;
}


/* Set/Clear Breakpoints.
 *
 * ADDRESS  memory address
 * Access    memory access flags
 * BPConfiguration   breakpoint type, bit 8 set to clear breakpoints
 * SIZE     size of range
 */
int T32_WriteBreakpoint(uint32_t Address, int Access, int BPConfiguration, int Size)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "0x%8x, 0x%x, 0x%x, %d", Address, Access, BPConfiguration, Size);

	if (Size < 1 || Size > 0xffff)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		T32_OUTBUFFER[0] = 10;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = (BPConfiguration & 0x100) ? 0x42 : 0x41;     /* T32_WriteBreakpoint: Clear/Set Breakpoints */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();

		SETLONGVAR(T32_OUTBUFFER[4], Address);
		T32_OUTBUFFER[8] = (Access & 0xff);
		T32_OUTBUFFER[9] = (BPConfiguration & 0xff);
		SETWORDVAR(T32_OUTBUFFER[10], Size);

		if (LINE_Transmit(12) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_INBUFFER[2];
		if (err == T32_ERR_FN1)
			err = T32_ERR_SETBP_FAILED;
		T32_Errno = err;
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

/* Get Breakpoint/Flag Information.
 *
 * ADDRESS    memory address
 * Access      memory access flags
 * pBPConfiguration     buffer to receive breakpoint information
 * Size        size of range
 */
int T32_ReadBreakpoint(uint32_t Address, int Access, uint16_t * pBPConfiguration, int Size)
{
	int             err = 0, i, len;
	int             outindex = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "0x%8x, 0x%x, p%x, %d", Address, Access, pBPConfiguration, Size);

	while (!err && (Size > 0)) {
		len = Size;
		if (len > MaxPacketSize / 2)
			len = MaxPacketSize / 2;

		T32_OUTBUFFER[0] = 10;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_BREAKPOINT_GET;   /* T32_ReadBreakpoint:  Get Breakpoints */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();

		SETLONGVAR(T32_OUTBUFFER[4], Address);
		T32_OUTBUFFER[8] = (Access & 0xff);
		T32_OUTBUFFER[9] = 0;
		T32_OUTBUFFER[10] = (unsigned char) (len & 0xff);
		T32_OUTBUFFER[11] = (unsigned char) (len >> 8);

		if (LINE_Transmit(12) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;

		if (!err && (LINE_Receive() == -1))
			err = T32_Errno = T32_COM_RECEIVE_FAIL;

		if (!err) {
			for (i = 0; i < len; i++) {
				pBPConfiguration[outindex++] = T32_INBUFFER[4 + 2 * i] | (T32_INBUFFER[4 + 2 * i + 1] << 8);
			}

			err = T32_Errno = T32_INBUFFER[2];
		}

		Size -= len;
		Address += len;
	}
	if (!err)
		T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return 0;
}


int T32_GetBreakpointList(int *pNumberFetched, T32_Breakpoint * pBPSettings, int FetchLimit)
{
	int             err = 0, i, loc;
	uint16_t        wnum;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, p%x, %d", pNumberFetched, pBPSettings, FetchLimit);

	T32_OUTBUFFER[0] = 4;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_BREAKPOINT_LIST;      /* T32_GetBreakpointList */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();
	T32_OUTBUFFER[4] = 0x77;    /* sample payload */
	T32_OUTBUFFER[5] = 0;       /* padding for even byte count */

	if (LINE_Transmit(6) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		SETWORDVAR(wnum, T32_INBUFFER[4]);
		*pNumberFetched = wnum;

		for (i = 0, loc = 6; (i < wnum) && (i < FetchLimit); i++, loc += 13) {
			SETLONGVAR(pBPSettings[i].address, T32_INBUFFER[loc]);
			pBPSettings[i].enabled = T32_INBUFFER[loc + 4] & 0x1;
			SETLONGVAR(pBPSettings[i].type, T32_INBUFFER[loc + 5]);
			SETLONGVAR(pBPSettings[i].auxtype, T32_INBUFFER[loc + 9]);
		}

		err = T32_Errno = T32_INBUFFER[2];
	}

	if (!err)
		T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

/* Single Step. */
int T32_Step(void)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_STEP_SINGLE;  /* T32_Step: Single-Step */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/* Single Step in Mode.
 *
 * MODE 0=ASM, 1=HLL, 2=MIX
 */
int T32_StepMode(int Mode)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d", Mode);

	T32_OUTBUFFER[0] = 4;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_STEP_MODE;    /* T32_StepMode: Step with Options */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();
	T32_OUTBUFFER[4] = (unsigned char) Mode;
	T32_OUTBUFFER[5] = 0;       /* padding for even byte count */

	if (LINE_Transmit(6) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/* Set Mode.
 *
 * Mode 0=ASM, 1=HLL, 2=MIX
 */
int T32_SetMode(int Mode)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d", Mode);

	T32_OUTBUFFER[0] = 4;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_MODE_SET;     /* T32_Mode: Mode-Selection */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();
	T32_OUTBUFFER[4] = (unsigned char) Mode;
	T32_OUTBUFFER[5] = 0;       /* padding for even byte count */

	if (LINE_Transmit(6) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/* Start Realtime execution on target. */
int T32_Go(void)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_GO;   /* T32_Go: Go */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/* Stop Realtime execution on target. */
int T32_Break(void)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_BREAK;        /* T32_Break: Break */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/** T32_Cmd -  Execute a TRACE32 command line

  @param  Command   IN  command line as simple string

  @return 0 : OK, else error

*/
int T32_Cmd(const char *Command)
{
	int     err = 0, len;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\"", Command);

	len = (int) strlen(Command);

	if (len + 7 + 1 > MaxPacketSize)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		if (len + 3 > 0xff) {
			uint16_t        wlen = (uint16_t) (len + 5);
			T32_OUTBUFFER[0] = 0;
			T32_OUTBUFFER[1] = RAPI_CMD_EXECUTE_PRACTICE;
			T32_OUTBUFFER[2] = 0x02;    /* Execute text command */
			T32_OUTBUFFER[3] = LINE_GetNextMessageId();
			SETWORDVAR(T32_OUTBUFFER[4], wlen);
			strcpy((char *) (T32_OUTBUFFER + 6), Command);
			if (LINE_Transmit((len + 7 + 1) & (~1)) == -1)
				return T32_Errno = T32_COM_TRANSMIT_FAIL;
		} else {
			T32_OUTBUFFER[0] = (unsigned char) (len + 3);
			T32_OUTBUFFER[1] = RAPI_CMD_EXECUTE_PRACTICE;
			T32_OUTBUFFER[2] = 0x02;    /* Execute text command */
			T32_OUTBUFFER[3] = LINE_GetNextMessageId();
			strcpy((char *) (T32_OUTBUFFER + 4), Command);
			if (LINE_Transmit((len + 5 + 1) & (~1)) == -1)
				return T32_Errno = T32_COM_TRANSMIT_FAIL;
		}

		if (LINE_Receive() == -1)
			err = T32_Errno = T32_COM_RECEIVE_FAIL;
	}

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/** T32_Cmd_f -  Execute a TRACE32 command line, formatted

  @param  command   IN  command line as string with format specifiers

  @return 0 : OK, else error

*/
int T32_Cmd_f(const char *command, ...)
{
	int     err = 0, len;
	char    buffer[1024];
	va_list args;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\"", command);

	va_start (args, command);
	len = vsnprintf(buffer, sizeof(buffer), command, args);
	buffer[sizeof(buffer)-1] = '\0';
	if (len >= (int)sizeof(buffer))
		err = T32_Errno = T32_ERR_COM_PARA_FAIL;
	if (!err)
		err = T32_Cmd(buffer);

	va_end (args);
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/**
 * @brief Execute a TRACE32 command. If an error occurs the error is returned as a as string.
 *
 * @param pCommand IN command as a simple string
 * @param pBuffer OUT return buffer for the error string
 * @param BufferSize IN return buffer size
 *
 * @return 0 : OK, else error
 */
int T32_ExecuteCommand(const char *pCommand, char* pBuffer, uint32_t BufferSize)
{
	int err = 0, len;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\"", pCommand);

	len = (int) strlen(pCommand) + 2;

	if (len + 10 > MaxPacketSize)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		if (len + 6 > 0xff) {
			uint16_t wlen = (uint16_t) (len + 8);
			T32_OUTBUFFER[0] = 0;
			T32_OUTBUFFER[1] = RAPI_CMD_EXECUTE_PRACTICE;
			T32_OUTBUFFER[2] = 0x04; /* subcommand */
			T32_OUTBUFFER[3] = LINE_GetNextMessageId();
			SETWORDVAR(T32_OUTBUFFER[4], wlen);
			SETLONGVAR(T32_OUTBUFFER[6], BufferSize);
			strcpy((char *) (T32_OUTBUFFER + 10), pCommand);
			if (LINE_Transmit((len + 10) & (~1)) == -1)
				return T32_Errno = T32_COM_TRANSMIT_FAIL;
		} else {
			T32_OUTBUFFER[0] = (unsigned char) (len + 6);
			T32_OUTBUFFER[1] = RAPI_CMD_EXECUTE_PRACTICE;
			T32_OUTBUFFER[2] = 0x04; /* subcommand */
			T32_OUTBUFFER[3] = LINE_GetNextMessageId();
			SETLONGVAR(T32_OUTBUFFER[4], BufferSize);
			strcpy((char *) (T32_OUTBUFFER + 8), pCommand);
			if (LINE_Transmit((len + 8) & (~1)) == -1)
				return T32_Errno = T32_COM_TRANSMIT_FAIL;
		}

		if (LINE_Receive() == -1)
			err = T32_Errno = T32_COM_RECEIVE_FAIL;
	}

	if (!err) {
		uint32_t Size;
		/* T32_INBUFFER[4..7] is not used */
		SETLONGVAR(Size, T32_INBUFFER[8]);
		strncpy(pBuffer, (char *)&T32_INBUFFER[12], BufferSize);
		if (Size<BufferSize)
			pBuffer[Size] = 0;

		switch(T32_INBUFFER[2]) {
		case T32_ERR_FN1:
			err = T32_Errno = T32_ERR_EXECUTECOMMAND_FAIL;
			break;
		default:
			err = T32_Errno = T32_INBUFFER[2];
			break;
		}
		T32_ApiCallEpilog();
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

static int _T32_ExecuteFunction_(uint8_t Subcommand, const char *pExpression, char* pErrorBuffer, uint32_t ErrorBufferSize, void *pResultBuffer, uint32_t ResultBufferSize, uint32_t *pResultType)
{
	int err = 0, len;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\"", pExpression);

	len = (int) strlen(pExpression) + 2;

	if (len + 10 > MaxPacketSize)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		if (len + 6 > 0xff) {
			uint16_t wlen = (uint16_t) (len + 8);
			T32_OUTBUFFER[0] = 0;
			T32_OUTBUFFER[1] = RAPI_CMD_EXECUTE_PRACTICE;
			T32_OUTBUFFER[2] = Subcommand; /* subcommand */
			T32_OUTBUFFER[3] = LINE_GetNextMessageId();
			SETWORDVAR(T32_OUTBUFFER[4], wlen);
			SETLONGVAR(T32_OUTBUFFER[6], ErrorBufferSize);
			strcpy((char *) (T32_OUTBUFFER + 10), pExpression);
			if (LINE_Transmit((len + 10) & (~1)) == -1)
				return T32_Errno = T32_COM_TRANSMIT_FAIL;
		} else {
			T32_OUTBUFFER[0] = (unsigned char) (len + 6);
			T32_OUTBUFFER[1] = RAPI_CMD_EXECUTE_PRACTICE;
			T32_OUTBUFFER[2] = Subcommand; /* subcommand */
			T32_OUTBUFFER[3] = LINE_GetNextMessageId();
			SETLONGVAR(T32_OUTBUFFER[4], ErrorBufferSize);
			strcpy((char *) (T32_OUTBUFFER + 8), pExpression);
			if (LINE_Transmit((len + 8) & (~1)) == -1)
				return T32_Errno = T32_COM_TRANSMIT_FAIL;
		}

		if (LINE_Receive() == -1)
			err = T32_Errno = T32_COM_RECEIVE_FAIL;
	}

	if (!err) {
		uint32_t ResultSize;
		if (pResultType) {
			SETLONGVAR(*pResultType, T32_INBUFFER[4]);
		}
		SETLONGVAR(ResultSize, T32_INBUFFER[8]);

		switch(T32_INBUFFER[2]) {
			case T32_OK: {
				if (ResultSize <= ResultBufferSize) {
					memcpy(pResultBuffer, &T32_INBUFFER[12], ResultSize);
				} else {
					strncpy(pErrorBuffer, "ResultBufferSize insufficient", ErrorBufferSize);
					err = T32_Errno = T32_ERR_EXECUTEFUNCTION_FAIL;
				}
			} break;
			case T32_ERR_FN1: {
				if (ResultSize < ErrorBufferSize) {
					memcpy(pErrorBuffer, &T32_INBUFFER[12], ResultSize);
					pErrorBuffer[ResultSize] = 0;
				} else {
					memcpy(pErrorBuffer, &T32_INBUFFER[12], ErrorBufferSize - 1);
					pErrorBuffer[ErrorBufferSize - 1] = 0;
				}
				err = T32_Errno = T32_ERR_EXECUTEFUNCTION_FAIL;
			} break;
			default: {
				err = T32_Errno = T32_INBUFFER[2];
			} break;
		}
		T32_ApiCallEpilog();
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

/**
 * @brief Execute a TRACE32 function and return result or error as string
 *
 * @param pFunction IN function as a simple string
 * @param pType type of the value in the return buffer
 * @param pBuffer OUT return buffer for the error string
 * @param BufferSize IN return buffer size
 *
 * @return 0 : OK, else error
 */
int T32_ExecuteFunction(const char *pExpression, char* pBuffer, uint32_t BufferSize, uint32_t *pResultType)
{
	return _T32_ExecuteFunction_(0x05, pExpression, pBuffer, BufferSize, pBuffer, BufferSize, pResultType);
}

int T32_ExecuteFunction_Double(const char *pExpression, char* pBuffer, uint32_t BufferSize, double *pResult)
{
	uint8_t pResultBuffer[8];
	int error = _T32_ExecuteFunction_(0x06, pExpression, pBuffer, BufferSize, pResultBuffer, 8, 0);
	if (error != T32_OK)
		return error;
	SETQUADVAR(*pResult, *pResultBuffer);
	return T32_OK;
}

int T32_ExecuteFunction_UInt64(const char *pExpression, char* pBuffer, uint32_t BufferSize, uint64_t *pResult)
{
	uint8_t pResultBuffer[8];
	int error = _T32_ExecuteFunction_(0x07, pExpression, pBuffer, BufferSize, pResultBuffer, 8, 0);
	if (error != T32_OK)
		return error;
	SETQUADVAR(*pResult, *pResultBuffer);
	return T32_OK;
}

/** T32_Printf -  Print to TRACE32 AREA window, formatted

  @param  command   IN  string with format specifiers

  @return 0 : OK, else error

*/
int T32_Printf(const char *str, ...)
{
	int     err = 0, len;
	char    buffer[1024];
	char   *pDelimiter, *pOut = buffer;
	va_list args;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\"", str);

	va_start (args, str);
	len = vsnprintf(buffer, sizeof(buffer), str, args);
	buffer[sizeof(buffer)-1] = '\0';
	if (len >= (int)sizeof(buffer))
		err = T32_Errno = T32_ERR_COM_PARA_FAIL;

	for (pOut = buffer; !err && (pDelimiter = strchr(pOut, '\n'));  pOut = pDelimiter + 1) {
		*pDelimiter = '\0';
		err = T32_Cmd_f("PRINT %%CONTinue \"%s\"", pOut);
		if (!err)
			err = T32_Cmd("PRINT"); /* force new line */
	}
	if (!err && *pOut){
		err = T32_Cmd_f("PRINT %%CONTinue \"%s\"", pOut);
	}

	va_end (args);
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/** T32_GetPracticeState - Return information about the state of PRACTICE.

  @param  pPracticeState OUT Pointer to variable to return the state
	  0 not running
	  1 running

  @return 0 : OK, else error

*/
int T32_GetPracticeState(int *pPracticeState)
{       /* Returns the run-state of PRACTICE */
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pPracticeState);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_EXECUTE_PRACTICE;
	T32_OUTBUFFER[2] = 0x03;    /* API: T32_GetPracticeState() */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		*pPracticeState = T32_INBUFFER[4];
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%d", err, pPracticeState, *pPracticeState);
	return err;
}


/** Execute PRACTICE command with given window handle.
	--- DEPRECATED ---
 */
int T32_CmdWin(uint32_t WindowHandle, const char *Command)
{
	int             err = 0, len;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "0x%x, \"%s\"", WindowHandle, Command);

	len = (int) strlen(Command);
	if (len + 11 + 1 >= MaxPacketSize)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		if (len + 7 >= 0xff) {
			uint16_t        wlen = (uint16_t) (len + 9);
			T32_OUTBUFFER[0] = 0;
			T32_OUTBUFFER[1] = RAPI_CMD_CMDWINDOW;
			T32_OUTBUFFER[2] = 0x02;    /* Execute text command (remote) */
			T32_OUTBUFFER[3] = LINE_GetNextMessageId();
			SETWORDVAR(T32_OUTBUFFER[4], wlen);

			SETLONGVAR(T32_OUTBUFFER[6], WindowHandle);
			strcpy((char *) (T32_OUTBUFFER + 10), Command);

			if (LINE_Transmit((len + 11 + 1) & (~1)) == -1)
				err = T32_Errno = T32_COM_TRANSMIT_FAIL;
		} else {
			T32_OUTBUFFER[0] = (unsigned char) (len + 7);
			T32_OUTBUFFER[1] = RAPI_CMD_CMDWINDOW;
			T32_OUTBUFFER[2] = 0x02;    /* Execute text command (remote) */
			T32_OUTBUFFER[3] = LINE_GetNextMessageId();

			SETLONGVAR(T32_OUTBUFFER[4], WindowHandle);
			strcpy((char *) (T32_OUTBUFFER + 8), Command);

			if (LINE_Transmit((len + 9 + 1) & (~1)) == -1)
				err = T32_Errno = T32_COM_TRANSMIT_FAIL;
		}
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/** Return Evaluation Result.
 */
int T32_EvalGet(uint32_t * pEvaluationResult)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pEvaluationResult);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_EVAL_GETVALUE;        /* T32_EvalGet */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		SETLONGVAR(*pEvaluationResult, T32_INBUFFER[4]);
		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%d", err, pEvaluationResult, *pEvaluationResult);
	return err;
}


int T32_GetMessage(char *AreaMessage, uint16_t * pMessageType)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, p%x", AreaMessage, pMessageType);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_GETMSG;
	T32_OUTBUFFER[2] = 0x00;
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) != 0)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		strcpy(AreaMessage, (char *) T32_INBUFFER + 8);
		{
			uint32_t        MessageType;
			SETLONGVAR(MessageType, T32_INBUFFER[4]);
			*pMessageType = (uint16_t) MessageType;
		}

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%s", err, AreaMessage, AreaMessage);
	return err;
}


int T32_GetMessageString(char* AreaMessage, uint16_t ArraySize, uint16_t *pMessageType, uint16_t *pMessageLen)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, %x, p%x", AreaMessage, ArraySize, pMessageType);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_GETMSGSTRING;
	T32_OUTBUFFER[2] = 0x00;
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();
	SETWORDVAR(T32_OUTBUFFER[4], ArraySize);

	if (LINE_Transmit(6) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		uint32_t    MessageType, MessageLen;
		strncpy (AreaMessage, (char *) T32_INBUFFER + 12, ArraySize-1);
		AreaMessage[ArraySize-1] = 0;
		SETLONGVAR(MessageType, T32_INBUFFER[4]);
		*pMessageType = (uint16_t) MessageType;
		SETLONGVAR(MessageLen, T32_INBUFFER[8]);
		*pMessageLen = (uint16_t) MessageLen;

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%s", err, AreaMessage, AreaMessage);
	return err;
}


int T32_GetTriggerMessage(char *TriggerMessage)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", TriggerMessage);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_TRIGGER_MESSAGE_GET;  /* T32_GetTriggerMessage */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) != 0)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		strcpy(TriggerMessage, (char *) T32_INBUFFER + 4);

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%s", err, TriggerMessage, TriggerMessage);
	return err;
}


int T32_EvalGetString(char *EvaluationString)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", EvaluationString);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_EVAL_GETSTRING;       /* T32_EvalGetString */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) != 0)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		strcpy(EvaluationString, (char *) T32_INBUFFER + 4);

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%s", err, EvaluationString, EvaluationString);
	return err;
}


int T32_GetSymbol(const char *SymbolName, uint32_t * pAddress, uint32_t * pSize, uint32_t * pAccess)
{
	int err = 0, len;

	if (!SymbolName) {
		err = T32_Errno = T32_COM_PARA_FAIL;
		return err;
	}

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\", p%x, p%x, p%x", SymbolName, pAddress, pSize, pAccess);

	len = (int) strlen(SymbolName);

	if (len + 3 > 0xff)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		T32_OUTBUFFER[0] = (unsigned char) (len + 3);
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_SYMBOL_GET;       /* T32_GetSymbol: Get Symbol Address, Size & Class */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		strcpy((char *) (T32_OUTBUFFER + 4), SymbolName);

		if (LINE_Transmit((len + 5 + 1) & (~1)) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		if (pAddress)
			SETLONGVAR(*pAddress, T32_INBUFFER[4]);
		if (pSize)
			SETLONGVAR(*pSize, T32_INBUFFER[8]);
		if (pAccess)
			SETLONGVAR(*pAccess, T32_INBUFFER[12]);

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=0x%x", err, pAddress, *pAddress);
	return err;
}


int T32_GetSource(uint32_t Address, char *SourceFile, uint32_t * pSourceLine)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "0x%x, \"%s\", p%x", Address, SourceFile, pSourceLine);

	T32_OUTBUFFER[0] = 6;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_SOURCE_GETFILE;       /* T32_GetSource: Get Filename & Line */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();
	SETLONGVAR(T32_OUTBUFFER[4], Address);

	if (LINE_Transmit(8) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		strcpy(SourceFile, (char *) T32_INBUFFER + 8);
		*pSourceLine = 0;
		SETLONGVAR(*pSourceLine, T32_INBUFFER[4]);

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%s", err, SourceFile, SourceFile);
	return err;
}


int T32_GetSelectedSource(char *SourceFile, uint32_t * pSourceLine)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\", p%x", SourceFile, pSourceLine);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_SOURCE_GETSELECTED;   /* T32_GetSelectedSource: Get Filename & Line of Selection */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		strcpy(SourceFile, (char *) T32_INBUFFER + 8);
		*pSourceLine = 0;
		SETLONGVAR(*pSourceLine, T32_INBUFFER[4]);

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%s", err, SourceFile, SourceFile);
	return err;
}


int T32_ReadVariableValue(const char *VariableName, uint32_t * pValueLower32Bit, uint32_t * pValueUpper32Bit)
{
	int             err = 0, len;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\", p%x, p%x", VariableName, pValueLower32Bit, pValueUpper32Bit);

	len = (int) strlen(VariableName);

	if (len + 3 > 0xff)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		T32_OUTBUFFER[0] = (unsigned char) (len + 3);
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_VARIABLE_READVALUE;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		strcpy((char *) (T32_OUTBUFFER + 4), VariableName);

		if (LINE_Transmit((len + 5 + 1) & (~1)) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		SETLONGVAR(*pValueLower32Bit, T32_INBUFFER[4]);
		SETLONGVAR(*pValueUpper32Bit, T32_INBUFFER[8]);

		err = T32_INBUFFER[2];
		switch (err) {
			case T32_ERR_FN1:
				err = T32_ERR_READVAR_ALLOC;
				break;
			case T32_ERR_FN2:
				err = T32_ERR_READVAR_ACCESS;
				break;
		}
		T32_Errno = err;

		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=0x%x", err, pValueLower32Bit, *pValueLower32Bit);
	return err;
}


int T32_WriteVariableValue(const char *VariableName, uint32_t ValueLower32Bit, uint32_t ValueUpper32Bit)
{
	int             err = 0, len;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\", %x, %x", VariableName, ValueLower32Bit, ValueUpper32Bit);

	len = (int) strlen(VariableName);

	if (len + 3 + 8 > 0xff)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		T32_OUTBUFFER[0] = (unsigned char) (len + 3 + 8);
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_VARIABLE_WRITEVALUE;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		SETLONGVAR(T32_OUTBUFFER[4], ValueLower32Bit);
		SETLONGVAR(T32_OUTBUFFER[8], ValueUpper32Bit);
		strcpy((char *) (T32_OUTBUFFER + 12), VariableName);

		if (LINE_Transmit((8 + len + 5 + 1) & (~1)) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_INBUFFER[2];
		switch (err) {
			case T32_ERR_FN1:
				err = T32_ERR_READVAR_ALLOC;
				break;
			case T32_ERR_FN2:
				err = T32_ERR_READVAR_ACCESS;
				break;
		}
		T32_Errno = err;

		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_ReadVariableString(const char *VariableName, char *StringFromNumeric, int StringLength)
{
	int             err = 0, len;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\", p%x, %d", VariableName, StringFromNumeric, StringLength);

	len = (int) strlen(VariableName);

	if (len + 3 > 0xff)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		T32_OUTBUFFER[0] = (unsigned char) (len + 3);
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_VARIABLE_READSTRING;      /* T32_ReadVariableString */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		strcpy((char *) (T32_OUTBUFFER + 4), VariableName);

		if (LINE_Transmit((len + 5 + 1) & (~1)) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		len = (int) strlen((char *) T32_INBUFFER + 4);
		if (len >= StringLength)
			len = StringLength - 1;
		strncpy(StringFromNumeric, (char *) T32_INBUFFER + 4, len);
		StringFromNumeric[len] = 0;

		err = T32_INBUFFER[2];
		switch (err) {
			case T32_ERR_FN1:
				err = T32_ERR_READVAR_ALLOC;
				break;
			case T32_ERR_FN2:
				err = T32_ERR_READVAR_ACCESS;
				break;
		}
		T32_Errno = err;

		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%s", err, StringFromNumeric, StringFromNumeric);
	return err;
}

int T32_GetWindowContent(const char *command, char * buffer, uint32_t requested, uint32_t offset, uint32_t print_code)
{
	int             err = 0;
	uint32_t        len;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\", p%x, %d", command, requested, offset);

	len = (int) strlen(command);
	if (len + 3 + 8 > 0xff)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (len + 3 > 0xff)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		T32_OUTBUFFER[0] = (unsigned char) (len + 3 + 12);
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_WINDOW_CONTENT;      /* T32_GetWindowContent */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		SETLONGVAR(T32_OUTBUFFER[4], requested);
		SETLONGVAR(T32_OUTBUFFER[8], offset);
		SETLONGVAR(T32_OUTBUFFER[12], print_code);
		strcpy((char *) (T32_OUTBUFFER + 16), command);

		if (LINE_Transmit((12 + len + 5 + 1) & (~1)) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		SETLONGVAR(len, T32_INBUFFER[4]);
		if (len >= requested)
			len = requested - 1;
		strncpy(buffer, (char *) T32_INBUFFER + 8, len);
		buffer[len] = 0;

		err = T32_INBUFFER[2];
		T32_Errno = err;

		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%s", err, buffer, buffer);
	if (err)
		return -1;
	else
		return len;
}


int T32_GetSymbolFromAddress(char *SymbolName, uint32_t Address, int StringLength)
{
	int             err = 0, len;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, 0x%x, %d", SymbolName, Address, StringLength);

	T32_OUTBUFFER[0] = 10;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_SYMBOL_GETBYADDRESS;  /* T32_GetSymbolFromAddress */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();
	SETLONGVAR(T32_OUTBUFFER[4], Address);
	SETLONGVAR(T32_OUTBUFFER[8], StringLength);

	if (LINE_Transmit(12) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		len = (int) strlen((char *) T32_INBUFFER + 4);
		if (len >= StringLength)
			len = StringLength - 1;
		strncpy(SymbolName, (char *) T32_INBUFFER + 4, len);
		SymbolName[len] = 0;

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%s", err, SymbolName, SymbolName);
	return err;
}


/**************************************************************************

  Trace interface

***************************************************************************/

/* Get Analyzer Status.
 *
 * state Analyzer state
 * size  Size of Tracebuffer
 * min   Min. Record Number
 * max   Max. Record Number
 */
int T32_AnaStatusGet(uint8_t * state, int32_t * size, int32_t * min, int32_t * max)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, p%x, p%x, p%x", state, size, min, max);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_ANALYZER_STATE;       /* T32_AnaStatusGet */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		*state = T32_INBUFFER[4];
		SETLONGVAR(*size, T32_INBUFFER[8]);
		SETLONGVAR(*min, T32_INBUFFER[12]);
		SETLONGVAR(*max, T32_INBUFFER[16]);

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%d", err, state, *state);
	return err;
}


int T32_AnaRecordGet(int32_t record, uint8_t * buffer, int len)
{
	int             err = 0;
	uint32_t        drecord;
	uint16_t        wlen;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d, p%x, %d", record, buffer, len);

	T32_OUTBUFFER[0] = 8;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_ANALYZER_READ;        /* T32_AnaRecordGet */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	drecord = (uint32_t) record;
	wlen = (uint16_t) len;
	SETLONGVAR(T32_OUTBUFFER[4], drecord);
	SETWORDVAR(T32_OUTBUFFER[8], wlen);

	if (LINE_Transmit(10) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		if (!len)
			len = 128;  /* length == 0 means "all data" */

		memcpy(buffer, T32_INBUFFER + 4, len);

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_GetTraceState(int TraceType, int *pTraceState, int32_t * pTraceTotalRecords,
	  int32_t * pCurrentRecordMin, int32_t * pCurrentRecordMax)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d, p%x, p%x, p%x, p%x",
			   TraceType, pTraceState, pTraceTotalRecords, pCurrentRecordMin, pCurrentRecordMax);

	T32_OUTBUFFER[0] = 4;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_TRACE_STATE;  /* T32_GetTraceState */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();
	T32_OUTBUFFER[4] = (unsigned char) TraceType;
	T32_OUTBUFFER[5] = 0;       /* padding for even byte count */

	if (LINE_Transmit(6) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		*pTraceState = T32_INBUFFER[4];
		SETLONGVAR(*pTraceTotalRecords, T32_INBUFFER[8]);
		SETLONGVAR(*pCurrentRecordMin, T32_INBUFFER[12]);
		SETLONGVAR(*pCurrentRecordMax, T32_INBUFFER[16]);

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%d", err, pTraceState, *pTraceState);
	return err;
}


int T32_ReadTrace(int TraceType, int32_t StartRecord, int NumberOfRecords, uint32_t Mask, uint8_t * pBuffer)
{
	int             err = 0, nbytes = 0;
	uint16_t        nrecs;
	uint32_t        drecord, dmask = 0;
	uint32_t        mask2;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d, %d, %d, %8x, p%x",
			   TraceType, StartRecord, NumberOfRecords, Mask, pBuffer);

	if (NumberOfRecords < 0)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		dmask = (uint32_t) Mask;
		nbytes = 0;
		for (mask2 = Mask; mask2; mask2 >>= 1) {
			if (mask2 & 1)
				nbytes += 4;
		}
	}

	while (!err && (NumberOfRecords > 0)) {
		if (NumberOfRecords * nbytes > LINE_SBLOCK)
			nrecs = (uint16_t) (LINE_SBLOCK / nbytes);
		else
			nrecs = (uint16_t) NumberOfRecords;
		drecord = (uint32_t) StartRecord;

		T32_OUTBUFFER[0] = 14;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_TRACE_READ;       /* T32_ReadTrace */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		T32_OUTBUFFER[4] = (unsigned char) TraceType;
		T32_OUTBUFFER[5] = 0;

		SETLONGVAR(T32_OUTBUFFER[6], drecord);
		SETLONGVAR(T32_OUTBUFFER[10], dmask);
		SETWORDVAR(T32_OUTBUFFER[14], nrecs);

		if (LINE_Transmit(16) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;

		if (!err && (LINE_Receive() == -1))
			err = T32_Errno = T32_COM_RECEIVE_FAIL;

		if (!err) {
			memcpy(pBuffer, T32_INBUFFER + 4, nrecs * nbytes);
			err = T32_Errno = T32_INBUFFER[2];
		}

		StartRecord += nrecs;
		NumberOfRecords -= nrecs;
		pBuffer += nrecs * nbytes;
	}

	if (!err)
		T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return 0;
}


int T32_GetLastErrorMessage(char *ErrorMessage, uint32_t * pLastError, uint32_t * pInternal)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, p%x, p%x", ErrorMessage, pLastError, pInternal);

	T32_OUTBUFFER[0] = 2;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_GETLASTERRMSG;
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	if (LINE_Transmit(4) != 0)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		SETLONGVAR(*pLastError, T32_INBUFFER[4]);
		SETLONGVAR(*pInternal, T32_INBUFFER[8]);
		strcpy(ErrorMessage, (char *) T32_INBUFFER + 12);

		err = T32_Errno = T32_INBUFFER[2];
		T32_ApiCallEpilog();
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%s", err, ErrorMessage, ErrorMessage);
	return err;
}


/**************************************************************************

  Object oriented API functions

***************************************************************************/

/**** Object lists: kept for local object administration ****/

typedef union {
	T32_Object *o;
	T32_BufferObj *b;
	T32_AddressObj *a;
	T32_RegisterObj *r;
	T32_RegisterSetObj *rs;
	T32_SymbolObj *s;
	T32_BreakpointObj *bp;
	T32_MemoryBundleObj *mb;
} T32_Object_u;

static T32_THREADLOCAL T32_Object_u T32_BufferObjList       = {NULL};
static T32_THREADLOCAL T32_Object_u T32_AddressObjList      = {NULL};
static T32_THREADLOCAL T32_Object_u T32_RegisterObjList     = {NULL};
static T32_THREADLOCAL T32_Object_u T32_RegisterSetObjList  = {NULL};
static T32_THREADLOCAL T32_Object_u T32_SymbolObjList       = {NULL};
static T32_THREADLOCAL T32_Object_u T32_BreakpointObjList   = {NULL};
static T32_THREADLOCAL T32_Object_u T32_MemoryBundleObjList = {NULL};

static void addToObjList(T32_Object_u *list, void *obj)
{
	T32_Object  **olist = &list->o;
	T32_Object  *walker;
	if (!list || !obj)  /* check parameters */
		return;
	if (!*olist) {
		*olist = (T32_Object*) obj;
		(*olist)->next = NULL;
		return;
	}
	walker = *olist;
	while (walker && walker->next)
		walker = walker->next;
	walker->next = (T32_Object*) obj;
	if (walker->next)
		walker->next->next = NULL;
}

static void rmFromObjList(T32_Object_u *list, void *obj)
{
	T32_Object  **olist = &list->o;
	T32_Object  *walker;
	if (!list || !obj)  /* check parameters */
		return;
	if (*olist == obj) {
		*olist = (*olist)->next;
		return;
	}
	walker = *olist;
	while (walker && walker->next)
	{
		if (walker->next == obj)
		{
			walker->next = ((T32_Object *) obj)->next;
			return;
		}
		walker = walker->next;
	}
}

static int releaseAddressObj(T32_AddressHandle * pHandle)
{
	if (pHandle) {
		T32_Object_u   *list = &T32_AddressObjList;
		rmFromObjList(list, (void *) *pHandle);
		if (*pHandle)
			free(*pHandle);
		*pHandle = NULL;
	}
	return 0;
}

static int releaseSymbolObj(T32_SymbolHandle * pHandle)
{
	if (pHandle) {
		T32_Object_u   *list = &T32_SymbolObjList;
		releaseAddressObj(&(*pHandle)->address);
		rmFromObjList(list, (void *) (*pHandle));
		if (*pHandle)
			free(*pHandle);
		*pHandle = NULL;
	}
	return 0;
}

static int releaseBreakpointObj(T32_BreakpointHandle * pHandle)
{
	if (pHandle) {
		T32_Object_u   *list = &T32_BreakpointObjList;
		releaseAddressObj(&(*pHandle)->address);
		rmFromObjList(list, (void *) (*pHandle));
		if (*pHandle)
			free(*pHandle);
		*pHandle = NULL;
	}
	return 0;
}

static int releaseBufferObj(T32_BufferHandle * pHandle)
{
	if (pHandle) {
		T32_Object_u   *list = &T32_BufferObjList;
		rmFromObjList(list, (void *) *pHandle);
		if (*pHandle) {
			if ((*pHandle)->storage)
				free((*pHandle)->storage);
			free(*pHandle);
		}
		*pHandle = NULL;
	}
	return 0;
}

static int releaseRegisterObj(T32_RegisterHandle * pHandle)
{
	if (pHandle) {
		T32_Object_u   *list = &T32_RegisterObjList;
		rmFromObjList(list, (void *) *pHandle);
		if (*pHandle)
			free(*pHandle);
		*pHandle = NULL;
	}
	return 0;
}

static int releaseRegisterSetObj(T32_RegisterSetHandle * pHandle)
{
	int     i;
	if (pHandle) {
		T32_Object_u   *list = &T32_RegisterSetObjList;
		for (i = 0; i < (*pHandle)->nregs; i++)
			releaseRegisterObj(&((*pHandle)->regs[i]));
		rmFromObjList(list, (void *) (*pHandle));
		if (*pHandle)
			free(*pHandle);
		*pHandle = NULL;
	}
	return 0;
}

static int releaseMemoryBundleObj(T32_MemoryBundleHandle * pHandle)
{
	unsigned i;
	if (pHandle) {
		T32_Object_u *list = &T32_MemoryBundleObjList;
		rmFromObjList(list, (void *) *pHandle);
		if (*pHandle) {
			if ((*pHandle)->chunks) {
				for (i = 0; i < (*pHandle)->used; i++) {
					T32_MemoryChunk *ch = (*pHandle)->chunks[i];
					if (ch) {
						releaseAddressObj(&ch->address);
						releaseBufferObj(&ch->buffer);
						free(ch);
					}
				}
				free((*pHandle)->chunks);
			}
			free(*pHandle);
		}
		*pHandle = NULL;
	}
	return 0;
}

static int releaseAllObjects(void)
{
	/* walk through all objects and free them */

	/* Release memory bundle objects *before* address and buffer objects,
	 * due to embedded address and buffer objects!
	 */
	while (T32_MemoryBundleObjList.mb) {
		T32_MemoryBundleHandle handle = T32_MemoryBundleObjList.mb;
		releaseMemoryBundleObj(&handle);
	}
	/* Release symbol and breakpoint objects *before* address objects,
	 * due to embedded address objects!
	 */
	while (T32_SymbolObjList.s) {
		T32_SymbolHandle handle = T32_SymbolObjList.s;
		releaseSymbolObj(&handle);
	}
	while (T32_BreakpointObjList.bp) {
		T32_BreakpointHandle handle = T32_BreakpointObjList.bp;
		releaseBreakpointObj(&handle);
	}
	while (T32_BufferObjList.b) {
		T32_BufferHandle handle = T32_BufferObjList.b;
		releaseBufferObj(&handle);
	}
	while (T32_AddressObjList.a) {
		T32_AddressHandle handle = T32_AddressObjList.a;
		releaseAddressObj(&handle);
	}
	/* Release RegisterSet objects *before* Register objects,
	 * due to embedded Register objects!
	 */
	while (T32_RegisterSetObjList.rs) {
		T32_RegisterSetHandle handle = T32_RegisterObjList.rs;
		releaseRegisterSetObj(&handle);
	}
	while (T32_RegisterObjList.r) {
		T32_RegisterHandle handle = T32_RegisterObjList.r;
		releaseRegisterObj(&handle);
	}
	return 0;
}



/**** T32_ReleaseAllObjects
	  remove and free all objects requested in the OO API ***/

int T32_ReleaseAllObjects(void)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);

	err = releaseAllObjects();

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/**** Buffer Object: used to keep memory buffers ****/

static int requestBufferObj(T32_BufferHandle * pHandle, const int size)
{
	T32_BufferHandle handle;

	handle = (T32_BufferHandle) malloc(sizeof(T32_BufferObj));
	handle->used = 0;
	handle->storage = (uint8_t *) malloc(size);
	if (!handle->storage) {
		return T32_ERR_MALLOC_FAIL;
	}
	handle->bufsize = size;
	{
		T32_Object_u   *list = &T32_BufferObjList;
		addToObjList(list, (void *) handle);
	}
	*pHandle = handle;

	return T32_OK;
}

static int copyDataFromBufferObj(uint8_t * localbuffer, int lbsize, T32_BufferHandle handle)
{
	if (lbsize >= (int) handle->used)
		memcpy(localbuffer, handle->storage, handle->used);
	else
		memcpy(localbuffer, handle->storage, lbsize);
	return 0;
}

static int copyDataToBufferObj(T32_BufferHandle handle, int size, const uint8_t * localbuffer)
{
	if ((int) handle->bufsize < size)
		T32_ResizeBufferObj(handle, size);

	memcpy(handle->storage, localbuffer, size);
	handle->used = size;
	return 0;
}

static int copyDataToBufferMaskObj(T32_BufferHandle handle, int size, const uint8_t * localbuffer, const uint8_t * localmaskbuffer)
{
	if ((int) handle->bufsize < size * 3)
		T32_ResizeBufferObj(handle, size * 3);

	memcpy(handle->storage + size, localbuffer, size);
	memcpy(handle->storage + size + size, localmaskbuffer, size);
	handle->used = size;
	return 0;
}

int T32_RequestBufferObj(T32_BufferHandle * pHandle, const int size)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, %d", pHandle, size);

	err = requestBufferObj(pHandle, size);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=h%x", 0, pHandle, *pHandle);
	return err;
}

int T32_ResizeBufferObj(T32_BufferHandle handle, const int size)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d", handle, size);
	handle->storage = (uint8_t *) realloc(handle->storage, size);
	handle->bufsize = size;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_ReleaseBufferObj(T32_BufferHandle * pHandle)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pHandle);

	err = releaseBufferObj(pHandle);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_GetBufferObjStoragePointer(uint8_t ** ppointer, T32_BufferHandle handle)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, h%x", ppointer, handle);
	*ppointer = handle->storage;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=0x%x", 0, ppointer, *ppointer);
	return 0;
}

int T32_CopyDataFromBufferObj(uint8_t * localbuffer, int lbsize, T32_BufferHandle handle)
{
	int             err = 0;
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, %d, h%x", localbuffer, lbsize, handle);

	err = copyDataFromBufferObj(localbuffer, lbsize, handle);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return err;
}

int T32_CopyDataToBufferObj(T32_BufferHandle handle, int size, const uint8_t * localbuffer)
{
	int             err = 0;
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d, p%x", handle, size, localbuffer);

	err = copyDataToBufferObj(handle, size, localbuffer);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return err;
}

int T32_CopyDataToMaskedBufferObj(T32_BufferHandle handle, int size, const uint8_t * localbuffer, const uint8_t * localmaskbuffer)
{
	int             err = 0;
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d, p%x, p%x", handle, size, localbuffer, localmaskbuffer);

	if (localmaskbuffer)
		err = copyDataToBufferMaskObj(handle, size, localbuffer, localmaskbuffer);
	else
		err = copyDataToBufferObj(handle, size, localbuffer);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return err;
}


/******** Address Object ********/

static void initAddressObjCommon(T32_AddressHandle handle)
{
	handle->common.type     = T32_ADDRTYPE_COMMON;
	handle->common.access[0]= 0;
	handle->common.width    = 0;
	handle->common.core     = (uint16_t) - 1;
	handle->common.spaceid  = (uint32_t) - 1;
	handle->common.attr     = 0;
	handle->common.sizeofmau        = T32_SIZEOFMAU_NOTSET;
	handle->common.targetsizeofmau  = T32_SIZEOFMAU_NOTSET;
}

static int requestAddressObj(T32_AddressHandle * pHandle)
{
	*pHandle = (T32_AddressHandle) malloc(sizeof(T32_AddressObj));
	initAddressObjCommon(*pHandle);
	{
		T32_Object_u   *list = &T32_AddressObjList;
		addToObjList(list, (void *) (*pHandle));
	}
	return 0;
}

static int copyAddressObj(T32_AddressHandle * pToHandle, T32_AddressHandle fromHandle)
{
	T32_Object     *preserveNext;

	if (*pToHandle == NULL)
		requestAddressObj(pToHandle);
	preserveNext = (*pToHandle)->common.next;
	*(*pToHandle) = *fromHandle;
	(*pToHandle)->common.next = preserveNext;

	return 0;
}

int T32_RequestAddressObj(T32_AddressHandle * pHandle)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pHandle);

	err = requestAddressObj(pHandle);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_RequestAddressObjA32(T32_AddressHandle * pHandle, const uint32_t address)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, 0x%x", pHandle, address);

	*pHandle = (T32_AddressHandle) malloc(sizeof(T32_AddressObj));
	initAddressObjCommon(*pHandle);
	(*pHandle)->common.type = T32_ADDRTYPE_A32;
	(*pHandle)->a32.address = address;
	{
		T32_Object_u   *list = &T32_AddressObjList;
		addToObjList(list, (void *) (*pHandle));
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=h%x", 0, pHandle, *pHandle);
	return 0;
}

int T32_RequestAddressObjA64(T32_AddressHandle * pHandle, const uint64_t address)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, 0x%x", pHandle, address);

	*pHandle = (T32_AddressHandle) malloc(sizeof(T32_AddressObj));
	initAddressObjCommon(*pHandle);
	(*pHandle)->common.type = T32_ADDRTYPE_A64;
	(*pHandle)->a64.address = address;
	{
		T32_Object_u   *list = &T32_AddressObjList;
		addToObjList(list, (void *) (*pHandle));
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_ReleaseAddressObj(T32_AddressHandle * pHandle)
{
	int             err;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pHandle);

	err = releaseAddressObj(pHandle);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_CopyAddressObj(T32_AddressHandle * pToHandle, T32_AddressHandle fromHandle)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, h%x", pToHandle, fromHandle);

	err = copyAddressObj(pToHandle, fromHandle);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_SetAddressObjAddr32(T32_AddressHandle handle, uint32_t address)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, 0x%x", handle, address);

	switch (handle->common.type) {
		case T32_ADDRTYPE_COMMON:
			handle->common.type = T32_ADDRTYPE_A32;
			handle->a32.address = address;
			break;
		case T32_ADDRTYPE_A32:
			handle->a32.address = address;
			break;
		case T32_ADDRTYPE_A64:
			handle->a64.address = (uint64_t) address;
			break;
		default:
			return T32_COM_PARA_FAIL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_GetAddressObjAddr32(T32_AddressHandle handle, uint32_t * pAddress)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", handle, pAddress);

	switch (handle->common.type) {
		case T32_ADDRTYPE_A32:
			*pAddress = handle->a32.address;
			break;
		default:
			return T32_COM_PARA_FAIL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=0x%x", 0, pAddress, *pAddress);
	return 0;
}

int T32_SetAddressObjAddr64(T32_AddressHandle handle, uint64_t address)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, 0x%x", handle, address);

	switch (handle->common.type) {
		case T32_ADDRTYPE_COMMON:
			handle->common.type = T32_ADDRTYPE_A64;
			handle->a64.address = address;
			break;
		case T32_ADDRTYPE_A64:
			handle->a64.address = address;
			break;
		default:
			return T32_COM_PARA_FAIL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_GetAddressObjAddr64(T32_AddressHandle handle, uint64_t * pAddress)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", handle, pAddress);

	switch (handle->common.type) {
		case T32_ADDRTYPE_A32:
			*pAddress = (uint64_t) handle->a32.address;
			break;
		case T32_ADDRTYPE_A64:
			*pAddress = handle->a64.address;
			break;
		default:
			return 1;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=0x%x", 0, pAddress, *pAddress);
	return 0;
}

int T32_SetAddressObjAccessString(T32_AddressHandle handle, const char *accessString)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, \"%s\"", handle, accessString);
	strncpy(handle->common.access, accessString, sizeof(handle->common.access) - 1);
	handle->common.access[sizeof(handle->common.access) - 1] = 0;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_GetAddressObjAccessString(T32_AddressHandle handle, char *accessString, uint8_t maxlen)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x, %d", handle, accessString, maxlen);
	if (strlen(handle->common.access) >= maxlen)
		return T32_COM_PARA_FAIL;
	strncpy(accessString, handle->common.access, maxlen);
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%s", 0, accessString, accessString);
	return 0;
}

int T32_SetAddressObjWidth(T32_AddressHandle handle, uint16_t width)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d", handle, width);
	handle->common.width = width;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_SetAddressObjCore(T32_AddressHandle handle, uint16_t core)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d", handle, core);
	handle->common.core = core;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_SetAddressObjSpaceId(T32_AddressHandle handle, uint32_t spaceid)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d", handle, spaceid);
	handle->common.spaceid = spaceid;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_SetAddressObjAttr(T32_AddressHandle handle, uint32_t attributes)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, 0x%x", handle, attributes);
	handle->common.attr |= attributes;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_SetAddressObjSizeOfMau(T32_AddressHandle handle, T32_SizeOfMauType sizeofmau)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, 0x%x", handle, sizeofmau);
	handle->common.sizeofmau = sizeofmau;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_GetAddressObjSizeOfMau(T32_AddressHandle handle, T32_SizeOfMauType* pSizeOfMau)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", handle, pSizeOfMau);
	*pSizeOfMau = handle->common.sizeofmau;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x", 0, *pSizeOfMau, pSizeOfMau);
	return 0;
}

int T32_GetAddressObjTargetSizeOfMau(T32_AddressHandle handle, T32_SizeOfMauType* pTargetSizeOfMau)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", handle, pTargetSizeOfMau);
	*pTargetSizeOfMau = handle->common.targetsizeofmau;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x", 0, *pTargetSizeOfMau, pTargetSizeOfMau);
	return 0;
}

/******** Register Object ********/

static void initRegisterObjCommon(T32_RegisterHandle handle)
{
	handle->common.type = T32_REGTYPE_COMMON;
	handle->common.id = T32_INVALID_REGID;
	handle->common.name[0] = 0;
	handle->common.core = (uint16_t) - 1;
}

static void requestRegisterObjCommon(T32_RegisterHandle * pHandle, T32_RegisterObjType type)
{
	T32_Object_u   *list = &T32_RegisterObjList;
	*pHandle = (T32_RegisterHandle) malloc(sizeof(T32_RegisterObj));
	initRegisterObjCommon(*pHandle);
	(*pHandle)->common.type = type;
	addToObjList(list, (void *) (*pHandle));
}

static int requestRegisterObjNameCommon(T32_RegisterHandle * pHandle, const char *regName, T32_RegisterObjType type)
{
	int             err = 0;
	T32_Object_u   *list = &T32_RegisterObjList;

	if (strlen(regName) > T32_MAX_REGNAME)
		err = T32_COM_PARA_FAIL;

	if (!err) {
		*pHandle = (T32_RegisterHandle) malloc(sizeof(T32_RegisterObj));
		initRegisterObjCommon(*pHandle);
		(*pHandle)->common.type = type;
		addToObjList(list, (void *) (*pHandle));
		strncpy((*pHandle)->common.name, regName, T32_MAX_REGNAME);
	}

	return err;
}

int T32_RequestRegisterObj(T32_RegisterHandle * pHandle, const T32_RegisterObjType regType)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pHandle);

	requestRegisterObjCommon(pHandle, regType);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_RequestRegisterObjR32(T32_RegisterHandle * pHandle)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pHandle);

	requestRegisterObjCommon(pHandle, T32_REGTYPE_R32);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_RequestRegisterObjR32Name(T32_RegisterHandle * pHandle, const char *regName)
{
	int             err;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, \"%s\"", pHandle, regName);

	err = requestRegisterObjNameCommon(pHandle, regName, T32_REGTYPE_R32);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_RequestRegisterObjR64(T32_RegisterHandle * pHandle)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pHandle);

	requestRegisterObjCommon(pHandle, T32_REGTYPE_R64);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_RequestRegisterObjR64Name(T32_RegisterHandle * pHandle, const char *regName)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, \"%s\"", pHandle, regName);

	err = requestRegisterObjNameCommon(pHandle, regName, T32_REGTYPE_R64);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_RequestRegisterObjR128(T32_RegisterHandle * pHandle)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pHandle);

	requestRegisterObjCommon(pHandle, T32_REGTYPE_R128);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_RequestRegisterObjR128Name(T32_RegisterHandle * pHandle, const char *regName)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, \"%s\"", pHandle, regName);

	err = requestRegisterObjNameCommon(pHandle, regName, T32_REGTYPE_R128);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_RequestRegisterObjR256(T32_RegisterHandle * pHandle)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pHandle);

	requestRegisterObjCommon(pHandle, T32_REGTYPE_R256);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_RequestRegisterObjR256Name(T32_RegisterHandle * pHandle, const char *regName)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, \"%s\"", pHandle, regName);

	err = requestRegisterObjNameCommon(pHandle, regName, T32_REGTYPE_R256);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_RequestRegisterObjR512(T32_RegisterHandle * pHandle)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pHandle);

	requestRegisterObjCommon(pHandle, T32_REGTYPE_R512);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_RequestRegisterObjR512Name(T32_RegisterHandle * pHandle, const char *regName)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, \"%s\"", pHandle, regName);

	err = requestRegisterObjNameCommon(pHandle, regName, T32_REGTYPE_R512);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_ReleaseRegisterObj(T32_RegisterHandle * pHandle)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pHandle);

	err = releaseRegisterObj(pHandle);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_SetRegisterObjValue32(T32_RegisterHandle handle, uint32_t value)
{
	int     err = 0;
	int     i;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%x, %x", handle, value);

	switch (handle->common.type) {
		case T32_REGTYPE_R32:
			handle->r32.value = value;
			break;
		case T32_REGTYPE_R64:
			handle->r64.value = (uint64_t) value;
			break;
		case T32_REGTYPE_R128:
			handle->r128.value[0] = (uint64_t) value;
			handle->r128.value[1] = 0;
			break;
		case T32_REGTYPE_R256:
			handle->r256.value[0] = (uint64_t) value;
			for (i = 1; i < 4; i++)
				handle->r256.value[i] = 0;
			break;
		case T32_REGTYPE_R512:
			handle->r512.value[0] = (uint64_t) value;
			for (i = 1; i < 8; i++)
				handle->r512.value[i] = 0;
			break;
		default:
			err = T32_COM_PARA_FAIL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_GetRegisterObjValue32(T32_RegisterHandle handle, uint32_t * pValue)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%x, p%x", handle, pValue);

	switch (handle->common.type) {
		case T32_REGTYPE_R32:
			*pValue = handle->r32.value;
			break;
		default:
			err = T32_COM_PARA_FAIL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%x", err, pValue, *pValue);
	return err;
}

int T32_SetRegisterObjValue64(T32_RegisterHandle handle, uint64_t value)
{
	int     err = 0;
	int     i;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%x, %x", handle, value);

	switch (handle->common.type) {
		case T32_REGTYPE_R64:
			handle->r64.value = value;
			break;
		case T32_REGTYPE_R128:
			handle->r128.value[0] = value;
			handle->r128.value[1] = 0;
			break;
		case T32_REGTYPE_R256:
			handle->r256.value[0] = value;
			for (i = 1; i < 4; i++)
				handle->r256.value[i] = 0;
			break;
		case T32_REGTYPE_R512:
			handle->r512.value[0] = value;
			for (i = 1; i < 8; i++)
				handle->r512.value[i] = 0;
			break;
		default:
			err = T32_COM_PARA_FAIL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_GetRegisterObjValue64(T32_RegisterHandle handle, uint64_t * pValue)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%x, p%x", handle, pValue);

	switch (handle->common.type) {
		case T32_REGTYPE_R32:
			*pValue = (uint64_t) handle->r32.value;
			break;
		case T32_REGTYPE_R64:
			*pValue = handle->r64.value;
			break;
		default:
			err = T32_COM_PARA_FAIL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%x", err, pValue, *pValue);
	return err;
}

static void setUint64ArrayFromByteArray (uint64_t *vArray, uint8_t* bArray, int vNum, int bNum)
{
	int     bindex, vindex, shift;

	for (vindex = 0; vindex < vNum; vindex++)
		vArray[vindex] = 0;
	bindex = vindex = shift = 0;
	while (bindex < bNum) {
		vArray[vindex] |= ((uint64_t) bArray[bindex]) << shift;
		bindex++;
		shift += 8;
		if ((bindex % 8) == 0) {
			vindex++;
			shift = 0;
		}
		if (vindex >= vNum)
			break;
	}
}

int T32_SetRegisterObjValueArray(T32_RegisterHandle handle, uint8_t * pArray, uint8_t maxlen)
{
	int     err = 0;
	int     i;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%x", handle);

	switch (handle->common.type) {
		case T32_REGTYPE_R32:
			handle->r32.value = 0;
			for (i = 0; (i < 4) && (i < maxlen); i++)
				handle->r32.value |= ((uint32_t) pArray[i]) << (i * 8);
			break;
		case T32_REGTYPE_R64:
			handle->r64.value = 0;
			for (i = 0; (i < 8) && (i < maxlen); i++)
				handle->r64.value |= ((uint64_t) pArray[i]) << (i * 8);
			break;
		case T32_REGTYPE_R128:
			setUint64ArrayFromByteArray (handle->r128.value, pArray, 2, maxlen);
			break;
		case T32_REGTYPE_R256:
			setUint64ArrayFromByteArray (handle->r256.value, pArray, 4, maxlen);
			break;
		case T32_REGTYPE_R512:
			setUint64ArrayFromByteArray (handle->r512.value, pArray, 8, maxlen);
			break;
		default:
			err = T32_COM_PARA_FAIL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

static void setByteArrayFromUint64Array (uint8_t* bArray, uint64_t* vArray, int bNum, int vNum)
{
	int     bindex, vindex, shift;

	for (bindex = 0; bindex < bNum; bindex++)
		bArray[bindex] = 0;
	bindex = vindex = shift = 0;
	while (bindex < bNum) {
		bArray[bindex] = (uint8_t) ((vArray[vindex] >> shift) & 0xff);
		bindex++;
		shift += 8;
		if ((bindex % 8) == 0) {
			vindex++;
			shift = 0;
		}
		if (vindex >= vNum)
			break;
	}
}

int T32_GetRegisterObjValueArray(T32_RegisterHandle handle, uint8_t * pArray, uint8_t maxlen)
{
	int     err = 0;
	int     i;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%x", handle);

	switch (handle->common.type) {
		case T32_REGTYPE_R32:
			for (i = 0; (i < 4) && (i < maxlen); i++)
				pArray[i] = (uint8_t) ((handle->r32.value >> (i * 8)) & 0xff);
			for (; i < maxlen; i++)
				pArray[i] = 0;
			break;
		case T32_REGTYPE_R64:
			for (i = 0; (i < 8) && (i < maxlen); i++)
				pArray[i] = (uint8_t) ((handle->r64.value >> (i * 8)) & 0xff);
			for (; i < maxlen; i++)
				pArray[i] = 0;
			break;
		case T32_REGTYPE_R128:
			setByteArrayFromUint64Array (pArray, handle->r128.value, maxlen, 2);
			break;
		case T32_REGTYPE_R256:
			setByteArrayFromUint64Array (pArray, handle->r256.value, maxlen, 4);
			break;
		case T32_REGTYPE_R512:
			setByteArrayFromUint64Array (pArray, handle->r512.value, maxlen, 8);
			break;
		default:
			err = T32_COM_PARA_FAIL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_SetRegisterObjName(T32_RegisterHandle handle, const char *name)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, \"%s\"", handle, name);

	if (strlen(name) > T32_MAX_REGNAME)
		err = T32_COM_PARA_FAIL;
	if (!err) {
		strncpy(handle->common.name, name, T32_MAX_REGNAME);
		handle->common.id = T32_INVALID_REGID;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_GetRegisterObjName(T32_RegisterHandle handle, char *name, uint8_t maxlen)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x, %d", handle, name, maxlen);

	if (strlen(handle->common.name) >= maxlen)
		err = T32_COM_PARA_FAIL;
	if (!err)
		strncpy(name, handle->common.name, maxlen);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%s", err, name, name);
	return err;
}

int T32_SetRegisterObjId(T32_RegisterHandle handle, uint32_t id)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d", handle, id);

	handle->common.id = id;
	handle->common.name[0] = 0; /* invalidate register name */

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_GetRegisterObjId(T32_RegisterHandle handle, uint32_t * pId)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", handle, pId);
	*pId = handle->common.id;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=%d", 0, pId, *pId);
	return 0;
}

int T32_SetRegisterObjCore(T32_RegisterHandle handle, uint16_t core)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d", handle, core);
	handle->common.core = core;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_GetRegisterObjCore(T32_RegisterHandle handle, uint16_t *pCore)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d", handle, core);
	*pCore = handle->common.core;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

/******** RegisterSet Object ********/

static int requestRegisterSetObj (T32_RegisterSetHandle *pHandle, int numRegisters, T32_RegisterObjType regType)
{
	int             i;
	T32_Object_u   *list = &T32_RegisterSetObjList;

	*pHandle = (T32_RegisterSetHandle) malloc(sizeof(T32_RegisterSetObj) + numRegisters * sizeof(T32_RegisterHandle));
	(*pHandle)->nregs = numRegisters;
	for (i = 0; i < numRegisters; i++)
		requestRegisterObjCommon(&((*pHandle)->regs[i]), regType);
	addToObjList(list, (void *) (*pHandle));

	return 0;
}

int T32_RequestRegisterSetObj (T32_RegisterSetHandle *pHandle, int numRegisters, T32_RegisterObjType regType)
{
	int     err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, %d, %d", pHandle, numRegisters, regType);

	// parameter check
	if (numRegisters > T32_MAX_REGISTERS)
		err = T32_ERR_COM_PARA_FAIL;

	if (!err)
		err = requestRegisterSetObj (pHandle, numRegisters, regType);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);

	return err;
}

int T32_RequestRegisterSetObjR32 (T32_RegisterSetHandle *pHandle, int numRegisters)
{
	int     err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, %d", pHandle, numRegisters);

	// parameter check
	if (numRegisters > T32_MAX_REGISTERS)
		err = T32_ERR_COM_PARA_FAIL;

	if (!err)
		err = requestRegisterSetObj (pHandle, numRegisters, T32_REGTYPE_R32);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);

	return err;
}

int T32_RequestRegisterSetObjR64 (T32_RegisterSetHandle *pHandle, int numRegisters)
{
	int     err = 0;
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, %d", pHandle, numRegisters);
	err = requestRegisterSetObj (pHandle, numRegisters, T32_REGTYPE_R64);
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_ReleaseRegisterSetObj (T32_RegisterSetHandle *pHandle)
{
	int     err = 0;
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pHandle);
	err = releaseRegisterSetObj (pHandle);
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_SetRegisterSetObjNames (T32_RegisterSetHandle handle, const char **names, int numNames)
{
	int err = 0;
	int i;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x", handle);

	// parameter check
	if (handle->nregs < numNames)
		err = T32_ERR_COM_PARA_FAIL;

	if (!err)
		for (i = 0; i < numNames; i++) {
			err = T32_SetRegisterObjName (handle->regs[i], names[i]);
			if (err)
				break;
		}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_SetRegisterSetObjValues32   (T32_RegisterSetHandle handle, const uint32_t *values, int numValues)
{
	int err = 0;
	int i;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x", handle);

	// parameter check
	if (handle->nregs < numValues)
		err = T32_ERR_COM_PARA_FAIL;

	if (!err)
		for (i = 0; i < numValues; i++) {
			err = T32_SetRegisterObjValue32 (handle->regs[i], values[i]);
			if (err)
				break;
		}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_GetRegisterSetObjValues32   (T32_RegisterSetHandle handle, uint32_t *values, int numValues)
{
	int err = 0;
	int i;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x", handle);

	// parameter check
	if (handle->nregs < numValues)
		err = T32_ERR_COM_PARA_FAIL;

	if (!err)
		for (i = 0; i < numValues; i++) {
			err = T32_GetRegisterObjValue32 (handle->regs[i], &values[i]);
			if (err)
				break;
		}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/******** Symbol Object ********/

static void initSymbolObj(T32_SymbolHandle symHandle)
{
	symHandle->name2 = NULL;
	symHandle->path2 = NULL;
	symHandle->address = NULL;
}

int T32_RequestSymbolObj(T32_SymbolHandle *pSymHandle)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pSymHandle);

	*pSymHandle = (T32_SymbolHandle) malloc(sizeof(T32_SymbolObj));
	initSymbolObj(*pSymHandle);
	requestAddressObj(&((*pSymHandle)->address));
	{
		T32_Object_u   *list = &T32_SymbolObjList;
		addToObjList(list, (void *) (*pSymHandle));
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_RequestSymbolObjName(T32_SymbolHandle *pSymHandle, const char *symName)
{
	int err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, \"%s\"", pSymHandle, symName);

	err = T32_RequestSymbolObj(pSymHandle);
	if (!err) {
		err = T32_SetSymbolObjName(*pSymHandle, symName);
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_RequestSymbolObjAddr(T32_SymbolHandle *pSymHandle, const T32_AddressHandle addrHandle)
{
	int err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, h%x", pSymHandle, addrHandle);

	err = T32_RequestSymbolObj(pSymHandle);
	if (!err) {
		err = T32_SetSymbolObjAddress(*pSymHandle, addrHandle);
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_ReleaseSymbolObj(T32_SymbolHandle *pSymHandle)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pSymHandle);

	err = releaseSymbolObj(pSymHandle);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_SetSymbolObjName(T32_SymbolHandle symHandle, const char *name)
{
	int err = 0;
	size_t nameLen = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, \"%s\"", symHandle, name);

	/* unset old name */
	if (symHandle->name2) {
		free(symHandle->name2);
		symHandle->name2 = NULL;
	}
	/* set new name */
	if (name) {
		nameLen = strlen(name);
		if (nameLen >= 0x8000)
			return T32_COM_PARA_FAIL;
		/* set name */
		symHandle->name2 = malloc((nameLen + 1) * sizeof(char));
		if (symHandle->name2)
			memcpy(symHandle->name2, name, nameLen + 1);
		else
			err = T32_ERR_MALLOC_FAIL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_GetSymbolObjName(T32_SymbolHandle symHandle, char *name, uint8_t maxlen)
{
	int err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x, %d", symHandle, name, maxlen);

	if (symHandle->name2) {
		const size_t symNameLen = strlen(symHandle->name2);
		if (symNameLen < maxlen) {
			memcpy(name, symHandle->name2, symNameLen);
			name[symNameLen] = 0;
		} else
			err = T32_COM_PARA_FAIL;
	} else {
		if (maxlen < 1)
			err = T32_COM_PARA_FAIL;
		else
			name[0] = 0;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_GetSymbolObjNamePtr(T32_SymbolHandle symHandle, char **symName)
{
	int err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", symHandle, symName);

	if (symHandle->name2) {
		if (symName)
			*symName = symHandle->name2;
		else
			err = T32_ERR_COM_PARA_FAIL;
	} else if (symName) {
		*symName = NULL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_SetSymbolObjPath(T32_SymbolHandle symHandle, const char *path)
{
	int err = 0;
	size_t pathLen = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, \"%s\"", symHandle, path);

	/* unset old path */
	if (symHandle->path2) {
		free(symHandle->path2);
		symHandle->path2 = NULL;
	}
	/* set new path */
	if (path) {
		pathLen = strlen(path);
		if (pathLen >= 0x8000)
			return T32_COM_PARA_FAIL;
		/* set path */
		symHandle->path2 = malloc((pathLen + 1) * sizeof(char));
		if (symHandle->path2)
			memcpy(symHandle->path2, path, pathLen + 1);
		else
			err = T32_ERR_MALLOC_FAIL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_GetSymbolObjPath(T32_SymbolHandle symHandle, char *symPath, uint16_t symPathSize16, uint16_t *symPathLen16)
{
	int err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x, %d, p%x", symHandle, symPath, symPathSize16, symPathLen16);

	if (symHandle->path2) {
		const size_t symPathLen = strlen(symHandle->path2);
		if (symPath && (symPathLen < symPathSize16)) {
			memcpy(symPath, symHandle->path2, symPathLen);
			symPath[symPathLen] = 0;
			if (symPathLen16)
				*symPathLen16 = (uint16_t) symPathLen;
		} else
			err = T32_ERR_COM_PARA_FAIL;
	} else {
		if (symPath && symPathSize16)
			symPath[0] = 0;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_GetSymbolObjPathPtr(T32_SymbolHandle symHandle, char **symPath)
{
	int err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", symHandle, symPath);

	if (symHandle->path2) {
		if (symPath)
			*symPath = symHandle->path2;
		else
			err = T32_ERR_COM_PARA_FAIL;
	} else if (symPath) {
		*symPath = NULL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_SetSymbolObjAddress(T32_SymbolHandle symHandle, T32_AddressHandle addrHandle)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, h%x", symHandle, addrHandle);

	copyAddressObj(&(symHandle->address), addrHandle);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_GetSymbolObjAddress(T32_SymbolHandle symHandle, T32_AddressHandle * pAddrHandle)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", symHandle, pAddrHandle);

	copyAddressObj(pAddrHandle, symHandle->address);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_GetSymbolObjSize(T32_SymbolHandle symHandle, uint64_t* pSize)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", symHandle, pSize);

	*pSize = symHandle->size;

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}


/******** Breakpoint Object ********/

static void initBreakpointObj(T32_BreakpointHandle handle)
{
	handle->address = NULL;
	handle->size = 0;
	handle->types = 0;
	handle->impl = 0;
	handle->action = 0;
	handle->disabled = 0;
}

int T32_RequestBreakpointObj(T32_BreakpointHandle * pHandle)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pHandle);

	*pHandle = (T32_BreakpointHandle) malloc(sizeof(T32_BreakpointObj));
	initBreakpointObj(*pHandle);
	requestAddressObj(&((*pHandle)->address));
	{
		T32_Object_u   *list = &T32_BreakpointObjList;
		addToObjList(list, (void *) (*pHandle));
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_RequestBreakpointObjAddr(T32_BreakpointHandle * pBpHandle, const T32_AddressHandle addrHandle)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, h%x", pBpHandle, addrHandle);

	*pBpHandle = (T32_BreakpointHandle) malloc(sizeof(T32_BreakpointObj));
	initBreakpointObj(*pBpHandle);
	requestAddressObj(&((*pBpHandle)->address));
	{
		T32_Object_u   *list = &T32_BreakpointObjList;
		addToObjList(list, (void *) (*pBpHandle));
	}
	copyAddressObj((&(*pBpHandle)->address), addrHandle);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, p%x=h%x", 0, pBpHandle, *pBpHandle);
	return 0;
}

int T32_ReleaseBreakpointObj(T32_BreakpointHandle * pHandle)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pHandle);

	err = releaseBreakpointObj(pHandle);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_SetBreakpointObjType(T32_BreakpointHandle handle, uint32_t type)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d", handle, type);
	handle->types = type;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_GetBreakpointObjType(T32_BreakpointHandle handle, uint32_t * pType)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", handle, pType);
	*pType = handle->types;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_SetBreakpointObjImpl(T32_BreakpointHandle handle, uint32_t impl)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d", handle, impl);
	handle->impl = impl;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_GetBreakpointObjImpl(T32_BreakpointHandle handle, uint32_t * pImpl)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", handle, pImpl);
	*pImpl = handle->impl;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_SetBreakpointObjAction(T32_BreakpointHandle handle, uint32_t act)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d", handle, act);
	handle->action = act;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_GetBreakpointObjAction(T32_BreakpointHandle handle, uint32_t* pAct)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", handle, pAct);
	*pAct = handle->action;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_SetBreakpointObjAddress(T32_BreakpointHandle bpHandle, T32_AddressHandle addrHandle)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, h%x", bpHandle, addrHandle);
	copyAddressObj(&(bpHandle->address), addrHandle);
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_GetBreakpointObjAddress(T32_BreakpointHandle bpHandle, T32_AddressHandle * pAddrHandle)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", bpHandle, pAddrHandle);
	copyAddressObj(pAddrHandle, bpHandle->address);
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_SetBreakpointObjEnable(T32_BreakpointHandle handle, uint8_t enable)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d", handle, enable);
	if (enable)
		handle->disabled = 0;
	else
		handle->disabled = 1;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}

int T32_GetBreakpointObjEnable(T32_BreakpointHandle handle, uint8_t * pEnable)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", handle, pEnable);
	*pEnable = handle->disabled ? 0 : 1;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}


/******** Memory Bundle Object ********/

static int addToBundleObjAddrLengthByteArray(T32_MemoryBundleHandle bundleHandle, const T32_AddressHandle addrHandle, const T32_Length length, uint8_t *localbuffer, uint8_t *localmaskbuffer)
{
	T32_BufferHandle bh = NULL;
	T32_AddressHandle ah = NULL;
	T32_MemoryChunk *ch;

	if (bundleHandle->used >= bundleHandle->size) {
		T32_Size newsize = bundleHandle->size ?  bundleHandle->size*2 : 1;
		bundleHandle->chunks = (T32_MemoryChunk**) realloc(bundleHandle->chunks, newsize*sizeof(T32_MemoryChunk*));
		bundleHandle->size = newsize;
	}

	requestBufferObj(&bh, length);
	requestAddressObj(&ah);
	copyAddressObj(&ah, addrHandle);

	ch = (T32_MemoryChunk*) malloc(sizeof(T32_MemoryChunk));
	ch->synched = T32_BUFFER_NOTSYNCHED;
	ch->buffer = bh;
	ch->address = ah;
	if (localbuffer == NULL)
		ch->read = 1;
	else if (localmaskbuffer == NULL)
		ch->read = 0;
	else
		ch->read = 2;

	if (localbuffer) {
		if (localmaskbuffer)
			copyDataToBufferMaskObj(bh, length, localbuffer, localmaskbuffer);
		else
			copyDataToBufferObj(bh, length, localbuffer);
	}

	bundleHandle->chunks[bundleHandle->used++] = ch;

	return 0;
}

int T32_RequestMemoryBundleObj(T32_MemoryBundleHandle *pHandle, const int initial_size)
{
	T32_MemoryBundleHandle handle;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, %d", pHandle, initial_size);

	handle = (T32_MemoryBundleHandle) malloc(sizeof(T32_MemoryBundleObj));
	handle->chunks = (T32_MemoryChunk**) malloc(sizeof(T32_MemoryChunk*)*initial_size);
	handle->size = initial_size;
	handle->used = 0;
	{
		T32_Object_u *list = &T32_MemoryBundleObjList;
		addToObjList(list, (void *) handle);
	}
	*pHandle = handle;

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, h%x", 0, *pHandle);
	return 0;
}

int T32_ReleaseMemoryBundleObj(T32_MemoryBundleHandle *pHandle)
{
	int err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pHandle);

	err = releaseMemoryBundleObj(pHandle);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_GetBundleObjSize(T32_MemoryBundleHandle bundleHandle, T32_Size *size)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x", bundleHandle, size);

	*size = bundleHandle->used;

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, %d", 0, *size);
	return 0;
}

int T32_GetBundleObjSyncStatusByIndex(T32_MemoryBundleHandle bundleHandle, T32_BufferSynchStatus *pSyncStatus, T32_Index index)
{
	int err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, p%x, %d", bundleHandle, pSyncStatus, index);

	if (index < bundleHandle->used) {
		*pSyncStatus = bundleHandle->chunks[index]->synched;
	}
	else {
		*pSyncStatus = T32_BUFFER_ERROR;
		err = T32_COM_PARA_FAIL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, %d", err, *pSyncStatus);

	return err;
}

int T32_CopyDataFromBundleObjByIndex (uint8_t *localbuffer, int lbsize, T32_MemoryBundleHandle bundleHandle, T32_Index index)
{
	int err = 0;
	T32_BufferHandle bh;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x, %d, h%x, %d", localbuffer, lbsize, bundleHandle, index);

	if (index < bundleHandle->used) {
		bh = bundleHandle->chunks[index]->buffer;
		copyDataFromBufferObj(localbuffer, lbsize, bh);
	}
	else {
		err = T32_COM_PARA_FAIL;
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d, h%x", err, bh);
	return err;
}

int T32_AddToBundleObjAddrLength(T32_MemoryBundleHandle bundleHandle, const T32_AddressHandle addrHandle, const T32_Length length)
{
	int err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, h%x, %d", bundleHandle, addrHandle, length);

	err = addToBundleObjAddrLengthByteArray(bundleHandle, addrHandle, length, NULL, NULL);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);

	return err;
}

int T32_AddToBundleObjAddrLengthByteArray(T32_MemoryBundleHandle bundleHandle, const T32_AddressHandle addrHandle, const T32_Length length, uint8_t *localbuffer)
{
	int err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, h%x, %d, p%x", bundleHandle, addrHandle, length, localbuffer);

	err = addToBundleObjAddrLengthByteArray(bundleHandle, addrHandle, length, localbuffer, NULL);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);

	return err;
}

int T32_AddToBundleObjAddrLengthByteArrayMaskArray(T32_MemoryBundleHandle bundleHandle, const T32_AddressHandle addrHandle, const T32_Length length, uint8_t *localbuffer, uint8_t *localmaskbuffer)
{
	int err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, h%x, %d, p%x, p%x", bundleHandle, addrHandle, length, localbuffer, localmaskbuffer);

	err = addToBundleObjAddrLengthByteArray(bundleHandle, addrHandle, length, localbuffer, localmaskbuffer);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);

	return err;
}


/******** Access memory ********/

static int streamAddressParams(const T32_AddressHandle addressHandle, int offset, int index)
{
	uint16_t        tmp_ui16;
	uint32_t        tmp_ui32;
	uint64_t        tmp_ui64;

	SETWORDVAR(T32_OUTBUFFER[index], addressHandle->common.type);
	index += 2;
	switch (addressHandle->common.type) {
		case T32_ADDRTYPE_A32:
			tmp_ui32 = addressHandle->a32.address + offset;
			SETLONGVAR(T32_OUTBUFFER[index], tmp_ui32);
			index += 4;
			break;
		case T32_ADDRTYPE_A64:
			tmp_ui64 = addressHandle->a64.address + offset;
			SETQUADVAR(T32_OUTBUFFER[index], tmp_ui64);
			index += 8;
			break;
		default:
			T32_Errno = T32_COM_PARA_FAIL;
			return T32_Errno;
	}
	if (*(addressHandle->common.access)) {
		int             len = (int) strlen(addressHandle->common.access) + 1;	/* +1 for zero termination */
		if (len & 1)
			len++;	/* align to 16bit */
		tmp_ui16 = 0x4341;	/* "AC" */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		SETWORDVAR(T32_OUTBUFFER[index + 2], len);
		strcpy((char *) T32_OUTBUFFER + index + 4, addressHandle->common.access);
		T32_OUTBUFFER[index + 4 + len - 1] = 0;
		index = index + 4 + len;
	}
	if (addressHandle->common.width) {
		tmp_ui16 = 0x4957;      /* "WI" */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		SETWORDVAR(T32_OUTBUFFER[index + 2], addressHandle->common.width);
		index += 4;
	}
	if (addressHandle->common.core != (uint16_t) - 1) {
		tmp_ui16 = 0x4f43;      /* "CO" */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		SETWORDVAR(T32_OUTBUFFER[index + 2], addressHandle->common.core);
		index += 4;
	}
	if (addressHandle->common.spaceid != (uint32_t) - 1) {
		tmp_ui16 = 0x4953;      /* "SI" */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		SETLONGVAR(T32_OUTBUFFER[index + 2], addressHandle->common.spaceid);
		index += 6;
	}
	if (addressHandle->common.attr) {
		tmp_ui16 = 0x4a41;      /* "AT" */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		SETLONGVAR(T32_OUTBUFFER[index + 2], addressHandle->common.attr);
		index += 6;
	}
	if (addressHandle->common.sizeofmau) {
		tmp_ui16 = 0x554d;      /* "MU" */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		SETWORDVAR(T32_OUTBUFFER[index + 2], addressHandle->common.sizeofmau);
		index += 4;
	}
	tmp_ui16 = 0x5858;  /* "XX" = end marker */
	SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
	return index + 2;
}

static int extractAddressParams(const T32_AddressHandle addressHandle, int index)
{
	uint16_t        parId;
	SETWORDVAR(addressHandle->common.type, T32_INBUFFER[index]);        /* address type */
	index += 2;
	switch (addressHandle->common.type) {
		case T32_ADDRTYPE_A32:
			SETLONGVAR(addressHandle->a32.address, T32_INBUFFER[index]);
			SETWORDVAR(parId, T32_INBUFFER[index + 4]);
			index += 6;
			break;
		case T32_ADDRTYPE_A64:
			SETQUADVAR(addressHandle->a64.address, T32_INBUFFER[index]);
			SETWORDVAR(parId, T32_INBUFFER[index + 8]);
			index += 10;
			break;
		default:
			T32_Errno = T32_COM_PARA_FAIL;
			return T32_Errno;
	}
	if (parId == 0x4341) {      /* access class */
		uint16_t        aclen;
		int             slen;
		SETWORDVAR(aclen, T32_INBUFFER[index]);
		strncpy(addressHandle->common.access, (char *) (T32_INBUFFER + index + 2), sizeof(addressHandle->common.access) - 1);
		addressHandle->common.access[sizeof(addressHandle->common.access) - 1] = 0;
		slen = (int) strlen(addressHandle->common.access);
		if (addressHandle->common.access[slen - 1] == ':')
			addressHandle->common.access[slen - 1] = 0; /* strip colon */

		addressHandle->common.access[15] = 0;
		SETWORDVAR(parId, T32_INBUFFER[index + aclen + 2]);
		index = index + aclen + 4;
	}
	if (parId == 0x4957) {      /* access width */
		SETWORDVAR(addressHandle->common.width, T32_INBUFFER[index]);
		SETWORDVAR(parId, T32_INBUFFER[index + 2]);
		index += 4;
	}
	if (parId == 0x4f43) {      /* core id */
		SETWORDVAR(addressHandle->common.core, T32_INBUFFER[index]);
		SETWORDVAR(parId, T32_INBUFFER[index + 2]);
		index += 4;
	}
	if (parId == 0x4953) {      /* space id */
		SETLONGVAR(addressHandle->common.spaceid, T32_INBUFFER[index]);
		SETWORDVAR(parId, T32_INBUFFER[index + 4]);
		index += 6;
	}
	if (parId == 0x4953) {      /* attributes */
		SETLONGVAR(addressHandle->common.attr, T32_INBUFFER[index]);
		SETWORDVAR(parId, T32_INBUFFER[index + 4]);
		index += 6;
	}
	if (parId == 0x554d) {      /* size of MAU */
		SETWORDVAR(addressHandle->common.sizeofmau, T32_INBUFFER[index]);
		SETWORDVAR(parId, T32_INBUFFER[index + 2]);
		index += 4;
	}
	if (parId == 0x5554) {      /* target size of MAU */
		SETWORDVAR(addressHandle->common.targetsizeofmau, T32_INBUFFER[index]);
		SETWORDVAR(parId, T32_INBUFFER[index + 2]);
		index += 4;
	}
	while (parId != 0x5858) {   /* end marker */
		SETWORDVAR(parId, T32_INBUFFER[index]);
		index += 2;
	}
	return index;
}


int T32_QueryAddressObjMmuTranslation(T32_AddressHandle handle, uint16_t translation)
{
	int             err = 0, msgsize;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d", handle, translation);

	if (!handle)
		err = T32_COM_PARA_FAIL;

	if (!err) {
		/* send address parameters to T32 */

		T32_OUTBUFFER[0] = 2;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_ADDRESS_OBJ_QUERY;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		T32_OUTBUFFER[4] = 0;   /* id: MMU translation */
		T32_OUTBUFFER[5] = 0;
		SETWORDVAR(T32_OUTBUFFER[8], translation);
		msgsize = streamAddressParams(handle, 0, 10);
		SETWORDVAR(T32_OUTBUFFER[6], msgsize);

		if (LINE_Transmit(msgsize) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err)
		err = T32_INBUFFER[2];

	if (!err) {
		extractAddressParams(handle, 4);
	} else {
		switch (err) {
			case T32_ERR_FN1:
				err = T32_ERR_MMUTRANSLATION_FAIL;
				break;
		}
		T32_Errno = err;
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_QueryAddressObjTargetSizeOfMau(T32_AddressHandle handle)
{
	int     err = 0, msgsize;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x", handle);

	if (!handle)
		err = T32_COM_PARA_FAIL;

	if (!err) {
		/* send address parameters to T32 */

		T32_OUTBUFFER[0] = 2;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_ADDRESS_OBJ_QUERY;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		T32_OUTBUFFER[4] = 1;   /* id: target size of MAU */
		T32_OUTBUFFER[5] = 0;
		T32_OUTBUFFER[6] = 0;   /* parameter of ADDRESS_OBJ_QUERY */
		T32_OUTBUFFER[7] = 0;
		msgsize = streamAddressParams(handle, 0, 10);
		SETWORDVAR(T32_OUTBUFFER[6], msgsize);

		if (LINE_Transmit(msgsize) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		extractAddressParams(handle, 4);
		err = T32_Errno = T32_INBUFFER[2];
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_ReadMemoryObj(T32_BufferHandle bufferHandle, const T32_AddressHandle addressHandle, const T32_Length length)
{
	int             err = 0;
	T32_Length      bytesToRcv = 0, bytesReceived = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, h%x, %d", bufferHandle, addressHandle, length);

	if (!bufferHandle || !addressHandle || !length)
		err = T32_COM_PARA_FAIL;

	if (!err) {
		if (bufferHandle->bufsize < length)
			T32_ResizeBufferObj(bufferHandle, length);

		T32_Errno = 0;
		bytesToRcv = length;
		bytesReceived = 0;
		bufferHandle->used = 0;
	}

	while (!err && (bytesToRcv > 0)) {
		T32_Length      packetsize;
		int             msgsize;

		/* check for multiple messages */

		if (bytesToRcv > (T32_Length) MaxPacketSize)
			packetsize = MaxPacketSize;
		else
			packetsize = bytesToRcv;

		/* send address parameters to T32 */

		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_MEMORY_OBJ_READ;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		SETWORDVAR(T32_OUTBUFFER[4], packetsize);

		msgsize = streamAddressParams(addressHandle, bytesReceived, 6);
		if (T32_Errno)
			err = T32_Errno;

		if (!err) {
			T32_OUTBUFFER[0] = (unsigned char) msgsize;

			if (LINE_Transmit(msgsize) == -1)
				err = T32_Errno = T32_COM_TRANSMIT_FAIL;
		}

		/* receive memory buffer */

		if (!err && (LINE_Receive() == -1))
			err = T32_Errno = T32_COM_RECEIVE_FAIL;

		/* copy data into buffer */

		if (!err) {
			memcpy(bufferHandle->storage + bytesReceived, T32_INBUFFER + 4, packetsize);
			bufferHandle->used += packetsize;
			err = T32_INBUFFER[2];
			if (err == T32_ERR_FN1)
				err = T32_ERR_READMEMOBJ_PARAFAIL;
			T32_Errno = err;
		}

		/* check for multiple messages */

		bytesToRcv -= packetsize;
		bytesReceived += packetsize;
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_WriteMemoryObj(T32_BufferHandle bufferHandle, const T32_AddressHandle addressHandle, const T32_Length length)
{
	int             err = 0;
	T32_Length      bytesToSend = 0, bytesSent = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, h%x, %d", bufferHandle, addressHandle, length);

	if (!bufferHandle || !addressHandle || !length)
		err = T32_COM_PARA_FAIL;

	if (!err && length > bufferHandle->used)
		err = T32_COM_PARA_FAIL;

	if (!err) {
		T32_Errno = 0;
		bytesToSend = length;
		bytesSent = 0;
	}

	while (!err && (bytesToSend > 0)) {
		T32_Length      packetsize;
		int             hdrsize;

		/* check for multiple messages */

		if (bytesToSend > (T32_Length) MaxPacketSize)
			packetsize = MaxPacketSize;
		else
			packetsize = bytesToSend;

		/* send address parameters to T32 */

		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_MEMORY_OBJ_WRITE;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		SETWORDVAR(T32_OUTBUFFER[4], packetsize);

		hdrsize = streamAddressParams(addressHandle, bytesSent, 6);
		if (T32_Errno)
			err = T32_Errno;

		if (!err) {
			T32_OUTBUFFER[0] = (unsigned char) hdrsize; /* header size */

			memcpy(T32_OUTBUFFER + hdrsize, bufferHandle->storage + bytesSent, packetsize);

			if (LINE_Transmit(hdrsize + ((packetsize + 1) & (~1))) == -1)
				err = T32_Errno = T32_COM_TRANSMIT_FAIL;
		}

		if (!err && (LINE_Receive() == -1))
			err = T32_Errno = T32_COM_RECEIVE_FAIL;

		if (!err) {
			err = T32_INBUFFER[2];
			if (err == T32_ERR_FN1)
				err = T32_ERR_WRITEMEMOBJ_PARAFAIL;
			T32_Errno = err;
		}

		/* check for multiple messages */

		bytesToSend -= packetsize;
		bytesSent += packetsize;
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

int T32_TransferMemoryBundleObj(T32_MemoryBundleHandle bundles)
{
	int err;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x", bundles);

	err = T32_Errno = 0;

	if (!bundles)
		err = T32_COM_PARA_FAIL;

	if (!err) {
		// check if total data size to receive exceeds buffer size
		unsigned i, index;
		index = 4;
		for (i = 0; i < bundles->used; i++) {
			index += 2;
			if (bundles->chunks[i]->read)
				index += (uint16_t) bundles->chunks[i]->buffer->bufsize;
			bundles->chunks[i]->synched = T32_BUFFER_ERROR;
		}

		if (index > EMU_CBMAXDATASIZE) {
			err = T32_ERR_TRANSFERMEMOBJ_PARAFAIL;
		}
		// check if total data size to send exceeds buffer size is done below
	}

	if (!err) {
		unsigned i, index;
		uint16_t tmp_ui16;

		T32_OUTBUFFER[0] = 0;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_BUNDLE_OBJ_TRANSFER;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		tmp_ui16 = (uint16_t)(bundles->used);
		SETWORDVAR(T32_OUTBUFFER[6], tmp_ui16);
		index = 8;

		for (i = 0; i < bundles->used && !err; i++) {
			unsigned bufsize = (bundles->chunks[i]->read == 0 || bundles->chunks[i]->read == 2) ? bundles->chunks[i]->buffer->used : bundles->chunks[i]->buffer->bufsize;
			tmp_ui16 = (bundles->chunks[i]->read <= 2) ? (uint16_t) bundles->chunks[i]->read : 1;
			SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
			index += 2;
			tmp_ui16 = (uint16_t)bufsize;
			SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
			index += 2;
			index = streamAddressParams(bundles->chunks[i]->address, 0, index);
			if (T32_Errno)
				err = T32_Errno;
			if (bundles->chunks[i]->read == 0) {
				memcpy(T32_OUTBUFFER + index, bundles->chunks[i]->buffer->storage, bufsize);
				index += (bufsize + 1) & (~1);  //16 bit alignment
			} else if (bundles->chunks[i]->read == 2) {
				memcpy(T32_OUTBUFFER + index, bundles->chunks[i]->buffer->storage + bufsize, bufsize * 2);
				index += (bufsize * 2 + 1) & (~1);  //16 bit alignment
			}
		}

		tmp_ui16 = 0x5858;  /* "XX" = end marker */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		index += 2;
		tmp_ui16 = (uint16_t)index;
		SETWORDVAR(T32_OUTBUFFER[4], tmp_ui16);

		// total data to send exceeds buffer size
		if (index > EMU_CBMAXDATASIZE) {
			err = T32_ERR_TRANSFERMEMOBJ_PARAFAIL;
		}

		if (!err) {
			if (LINE_Transmit(index) == -1)
				err = T32_Errno = T32_COM_TRANSMIT_FAIL;
		}
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		err = T32_INBUFFER[2];
		if (err == T32_ERR_FN1)
			err = T32_ERR_TRANSFERMEMOBJ_PARAFAIL;
		if (err == T32_ERR_FN2)
			err = T32_ERR_TRANSFERMEMOBJ_TRANSFERFAIL;
	}

	if (!err) {
		unsigned        i, index;

		index = 4;

		for (i = 0; i < bundles->used; i++) {
			uint16_t        ok;
			SETWORDVAR(ok, T32_INBUFFER[index]);
			index += 2;
			if (bundles->chunks[i]->read == 0) {
				bundles->chunks[i]->synched = ok ? T32_BUFFER_WRITTEN : T32_BUFFER_ERROR;
			} else if (bundles->chunks[i]->read == 2) {
				unsigned        bufsize = bundles->chunks[i]->buffer->used;
				bundles->chunks[i]->synched = ok ? T32_BUFFER_READ : T32_BUFFER_ERROR;
				if (ok) {
					memcpy(bundles->chunks[i]->buffer->storage, T32_INBUFFER + index, bufsize);
					index += bufsize;
				}
			} else {
				unsigned        bufsize = bundles->chunks[i]->buffer->bufsize;
				bundles->chunks[i]->synched = ok ? T32_BUFFER_READ : T32_BUFFER_ERROR;
				if (ok) {
					memcpy(bundles->chunks[i]->buffer->storage, T32_INBUFFER + index, bufsize);
					bundles->chunks[i]->buffer->used = bufsize;
					index += bufsize;
				}
			}
			if (!ok) {
				err = T32_ERR_TRANSFERMEMOBJ_TRANSFERFAIL;
			}
		}
	}

	T32_Errno = err;

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

/****** Access Registers ******/

static int streamRegisterParams(const T32_RegisterHandle registerHandle, int index)
{
	uint16_t        tmp_ui16;

	SETWORDVAR(T32_OUTBUFFER[index], registerHandle->common.type);
	index += 2;
	{
		tmp_ui16 = 0x4944;      /* "ID" */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		SETLONGVAR(T32_OUTBUFFER[index + 2], registerHandle->common.id);
		index += 6;
	}
	{
		int             len = (int) strlen(registerHandle->common.name) + 1;    /* +1 for zero termination */
		if (len & 1)
			len++;      /* align to 16bit */
		tmp_ui16 = 0x4d4e;      /* "NM" */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		SETWORDVAR(T32_OUTBUFFER[index + 2], len);
		strcpy((char *) T32_OUTBUFFER + index + 4, registerHandle->common.name);
		index = index + 4 + len;
	}
	if (registerHandle->common.core != (uint16_t) - 1) {
		tmp_ui16 = 0x4f43;      /* "CO" */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		SETWORDVAR(T32_OUTBUFFER[index + 2], registerHandle->common.core);
		index += 4;
	}
	tmp_ui16 = 0x5858;  /* "XX" = end marker */
	SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
	return index + 2;
}

static int streamRegisterValue(const T32_RegisterHandle registerHandle, int index)
{
	int i;

	if (registerHandle->common.type == T32_REGTYPE_R32) {
		SETLONGVAR(T32_OUTBUFFER[index], registerHandle->r32.value);
		index = index + 4;
	} else if (registerHandle->common.type == T32_REGTYPE_R64) {
		SETQUADVAR(T32_OUTBUFFER[index], registerHandle->r64.value);
		index = index + 8;
	} else if (registerHandle->common.type == T32_REGTYPE_R128) {
		for (i = 0; i < 2; i++)
			SETQUADVAR(T32_OUTBUFFER[index + i*8], registerHandle->r128.value[i]);
		index = index + 16;
	} else if (registerHandle->common.type == T32_REGTYPE_R256) {
		for (i = 0; i < 4; i++)
			SETQUADVAR(T32_OUTBUFFER[index + i*8], registerHandle->r256.value[i]);
		index = index + 32;
	} else if (registerHandle->common.type == T32_REGTYPE_R512) {
		for (i = 0; i < 8; i++)
			SETQUADVAR(T32_OUTBUFFER[index + i*8], registerHandle->r512.value[i]);
		index = index + 64;
	} else
		T32_Errno = T32_COM_PARA_FAIL;
	return index;
}

static int extractRegisterParams(const T32_RegisterHandle registerHandle, int index)
{
	uint16_t    regType, parId;
	int         i;

	SETWORDVAR(regType, T32_INBUFFER[index]);   /* register type */
	SETWORDVAR(parId, T32_INBUFFER[index + 2]);
	index += 4;
	if (parId == 0x4944) {      /* reg id */
		SETLONGVAR(registerHandle->common.id, T32_INBUFFER[index]);
		SETWORDVAR(parId, T32_INBUFFER[index + 4]);
		index += 6;
	}
	if (parId == 0x4d4e) {      /* reg name */
		int             len = (int) strlen((char *) (T32_INBUFFER + index)) + 1;        /* +1 for zero termination */
		if (len & 1)
			len++;      /* align to 16bit */
		strcpy(registerHandle->common.name, (char *) (T32_INBUFFER + index));
		SETWORDVAR(parId, T32_INBUFFER[index + 4]);
		index = index + len + 2;
	}
	if (parId == 0x414c) {      /* value */
		if (regType == T32_REGTYPE_R32) {
			if (registerHandle->common.type != T32_REGTYPE_R32) {
				T32_Errno = T32_COM_PARA_FAIL;
				return index;
			}
			SETLONGVAR(registerHandle->r32.value, T32_INBUFFER[index]);
			index += 4;
		} else if (regType == T32_REGTYPE_R64) {
			if (registerHandle->common.type != T32_REGTYPE_R64) {
				T32_Errno = T32_COM_PARA_FAIL;
				return index;
			}
			SETQUADVAR(registerHandle->r64.value, T32_INBUFFER[index]);
			index += 8;
		} else if (regType == T32_REGTYPE_R128) {
			if (registerHandle->common.type != T32_REGTYPE_R128) {
				T32_Errno = T32_COM_PARA_FAIL;
				return index;
			}
			for (i = 0; i < 2; i++)
				SETQUADVAR(registerHandle->r128.value[i], T32_INBUFFER[index + i*8]);
			index += 16;
		} else if (regType == T32_REGTYPE_R256) {
			if (registerHandle->common.type != T32_REGTYPE_R256) {
				T32_Errno = T32_COM_PARA_FAIL;
				return index;
			}
			for (i = 0; i < 4; i++)
				SETQUADVAR(registerHandle->r256.value[i], T32_INBUFFER[index + i*8]);
			index += 32;
		} else if (regType == T32_REGTYPE_R512) {
			if (registerHandle->common.type != T32_REGTYPE_R512) {
				T32_Errno = T32_COM_PARA_FAIL;
				return index;
			}
			for (i = 0; i < 8; i++)
				SETQUADVAR(registerHandle->r512.value[i], T32_INBUFFER[index + i*8]);
			index += 64;
		} else {
			T32_Errno = T32_COM_PARA_FAIL;
			return index;
		}
		SETWORDVAR(parId, T32_INBUFFER[index]);
		/* check here(!) for XX ending, old versions didn't send this */
		if (parId == 0x5858)
			index +=2;
	}
	return index;
}


int T32_ReadRegisterObj(T32_RegisterHandle registerHandle)
{
	int     err, msgsize;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x", registerHandle);
	err = T32_Errno = 0;

	if (!registerHandle)
		err = T32_COM_PARA_FAIL;

	if (!err) {
		/* send register parameters to T32 */

		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_REGISTER_OBJ_READ;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		msgsize = streamRegisterParams(registerHandle, 4);
		T32_OUTBUFFER[0] = (unsigned char) msgsize;

		if (LINE_Transmit(msgsize) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		extractRegisterParams(registerHandle, 4);
		err = T32_Errno;
	}

	if (!err) {
		err = T32_INBUFFER[2];
		switch (err) {
			case T32_ERR_FN1:
				err = T32_ERR_READREGOBJ_PARAFAIL;
				break;
			case T32_ERR_FN2:
				err = T32_ERR_READREGOBJ_MAXCORE;
				break;
			case T32_ERR_FN3:
				err = T32_ERR_READREGOBJ_NOTFOUND;
				break;
		}
		T32_Errno = err;
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_WriteRegisterObj(T32_RegisterHandle registerHandle)
{
	int     err, index;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x", registerHandle);
	err = T32_Errno = 0;
	index = 0;

	if (!registerHandle)
		err = T32_COM_PARA_FAIL;

	if (!err) {
		/* send register parameters to T32 */

		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_REGISTER_OBJ_WRITE;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		index = streamRegisterParams(registerHandle, 4);
		index = streamRegisterValue(registerHandle, index);
		err = T32_Errno;
	}

	if (!err) {
		T32_OUTBUFFER[0] = (unsigned char) index;

		if (LINE_Transmit(index) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		extractRegisterParams(registerHandle, 4);
		err = T32_Errno;
	}

	if (!err) {
		err = T32_INBUFFER[2];
		switch (err) {
			case T32_ERR_FN1:
				err = T32_ERR_WRITEREGOBJ_PARAFAIL;
				break;
			case T32_ERR_FN2:
				err = T32_ERR_WRITEREGOBJ_MAXCORE;
				break;
			case T32_ERR_FN3:
				err = T32_ERR_WRITEREGOBJ_NOTFOUND;
				break;
			case T32_ERR_FN4:
				err = T32_ERR_WRITEREGOBJ_FAILED;
				break;
		}
		T32_Errno = err;
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_ReadRegisterSetObj(T32_RegisterSetHandle regSetHandle)
{
	int         err = 0, index = 0;
	int         i;
	uint16_t    numRegs, tmp_ui16;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x", regSetHandle);

	if (!regSetHandle || (regSetHandle->nregs > T32_MAX_REGISTERS))
		err = T32_COM_PARA_FAIL;

	if (!err) {
		/* send register set parameters to T32 */

		T32_OUTBUFFER[0] = 0;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_REGISTERSET_OBJ_READ;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		SETWORDVAR(T32_OUTBUFFER[6], regSetHandle->nregs);
		index = 8;
		for (i = 0; i < regSetHandle->nregs; i++)
			index = streamRegisterParams(regSetHandle->regs[i], index);
		tmp_ui16 = 0x5858;  /* "XX" = end marker */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		index += 2;
		SETWORDVAR(T32_OUTBUFFER[4], index);

		if (LINE_Transmit(index-4) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		SETWORDVAR(numRegs, T32_INBUFFER[4]);
		if (numRegs != regSetHandle->nregs)
			err = T32_Errno = T32_ERR_READREGSETOBJ_NUMREGS;
	}
	if (!err) {
		index = 6;
		for (i = 0; i < regSetHandle->nregs; i++) {
			index = extractRegisterParams(regSetHandle->regs[i], index);
			err = T32_Errno;
			if (err)
				break;
		}
		/* we ignore the ending "XX" marker for now */
	}

	if (!err) {
		err = T32_INBUFFER[2];
		switch (err) {
			case T32_ERR_FN1:
				err = T32_ERR_READREGSETOBJ_PARAFAIL;
				break;
			case T32_ERR_FN2:
				err = T32_ERR_READREGOBJ_MAXCORE;
				break;
			case T32_ERR_FN3:
				err = T32_ERR_READREGOBJ_NOTFOUND;
				break;
		}
		T32_Errno = err;
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_WriteRegisterSetObj(T32_RegisterSetHandle regSetHandle)
{
	int         err, index;
	int         i;
	uint16_t    numRegs, tmp_ui16;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x", regSetHandle);
	err = T32_Errno = 0;

	if (!regSetHandle || (regSetHandle->nregs > T32_MAX_REGISTERS))
		err = T32_COM_PARA_FAIL;

	if (!err) {
		/* send register set parameters to T32 */

		T32_OUTBUFFER[0] = 0;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_REGISTERSET_OBJ_WRITE;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		SETWORDVAR(T32_OUTBUFFER[6], regSetHandle->nregs);
		index = 8;
		for (i = 0; i < regSetHandle->nregs; i++) {
			index = streamRegisterParams(regSetHandle->regs[i], index);
			index = streamRegisterValue(regSetHandle->regs[i], index);
		}
		tmp_ui16 = 0x5858;  /* "XX" = end marker */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		index += 2;
		SETWORDVAR(T32_OUTBUFFER[4], index);

		if (LINE_Transmit(index-4) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		SETWORDVAR(numRegs, T32_INBUFFER[4]);
		if (numRegs != regSetHandle->nregs)
			err = T32_Errno = T32_ERR_READREGSETOBJ_NUMREGS;
	}
	if (!err) {
		index = 6;
		for (i = 0; i < regSetHandle->nregs; i++) {
			index = extractRegisterParams(regSetHandle->regs[i], index);
			err = T32_Errno;
			if (err)
				break;
		}
		/* we ignore the ending "XX" marker for now */
	}

	if (!err) {
		err = T32_INBUFFER[2];
		switch (err) {
			case T32_ERR_FN1:
				err = T32_ERR_WRITEREGOBJ_PARAFAIL;
				break;
			case T32_ERR_FN2:
				err = T32_ERR_WRITEREGOBJ_MAXCORE;
				break;
			case T32_ERR_FN3:
				err = T32_ERR_WRITEREGOBJ_NOTFOUND;
				break;
			case T32_ERR_FN4:
				err = T32_ERR_WRITEREGOBJ_FAILED;
				break;
		}
		T32_Errno = err;
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/******** Access Symbols ********/

static int streamSymbolParams(const T32_SymbolHandle symHandle, int index)
{
	uint16_t tmp_ui16;

	/* symbol address */
	if (symHandle->address->common.type != T32_ADDRTYPE_COMMON) {
		tmp_ui16 = 0x4441; /* "AD" */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		index += 2;
		index = streamAddressParams(symHandle->address, 0, index);
	}

	/* symbol name */
	if (symHandle->name2 && symHandle->name2[0]) {
		size_t nameLen = strlen(symHandle->name2);
		size_t nameLen0A;
		if (nameLen > 64)
			nameLen = 64;
		/* nameLen0A: nameLen with zero termination and aligned to 16bit */
		nameLen0A = (nameLen & 1) ? nameLen + 1 : nameLen + 2;
		tmp_ui16 = 0x4d4e; /* "NM" */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		index +=2;
		SETWORDVAR(T32_OUTBUFFER[index], nameLen0A);
		index += 2;
		memcpy(T32_OUTBUFFER + index, symHandle->name2, nameLen);
		T32_OUTBUFFER[index + nameLen] = 0;
		index += (int)nameLen0A;
	}

	// symbol path (legacy, reserved, do not use)
	// tmp_ui16 = 0x5450; /* "PT" */

	/* symbol name extension */
	if (symHandle->name2 && symHandle->name2[0]) {
		size_t nameLen = strlen(symHandle->name2);
		size_t nameLen0A;
		if (nameLen > 64) {
			nameLen -= 64;
			/* nameLen0A: nameLen with zero termination and aligned to 16bit */
			nameLen0A = (nameLen & 1) ? nameLen + 1 : nameLen + 2;
			if (nameLen0A > 0xFFFE)
				return -1;
			tmp_ui16 = 0x454e; /* "NE" */
			SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
			index +=2;
			SETWORDVAR(T32_OUTBUFFER[index], nameLen0A);
			index += 2;
			memcpy(T32_OUTBUFFER + index, symHandle->name2 + 64, nameLen);
			T32_OUTBUFFER[index + nameLen] = 0;
			index += (int)nameLen0A;
		}
	}

	/* symbol path replacement */
	if (symHandle->path2 && symHandle->path2[0]) {
		size_t pathLen = strlen(symHandle->path2);
		size_t pathLen0A;
		/* pathLen0A: pathLen with zero termination and aligned to 16bit */
		pathLen0A = (pathLen & 1) ? pathLen + 1 : pathLen + 2;
		tmp_ui16 = 0x5250; /* "PR" */
		SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
		index +=2;
		SETWORDVAR(T32_OUTBUFFER[index], pathLen0A);
		index += 2;
		memcpy(T32_OUTBUFFER + index, symHandle->path2, pathLen);
		T32_OUTBUFFER[index + pathLen] = 0;
		index += (int)pathLen0A;
	}

	tmp_ui16 = 0x5858;  /* "XX" = end marker */
	SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
	index += 2;

	return index;
}


static int extractSymbolParams(const T32_SymbolHandle symHandle, int index)
{
	uint16_t parId;
	char *symName = NULL;
	size_t symNameLen = 0;
	char *symNameExt = NULL;
	size_t symNameExtLen = 0;
	char *symPath = NULL;
	size_t symPathLen = 0;

	if (symHandle->name2) {
		free(symHandle->name2);
		symHandle->name2 = NULL;
	}

	if (symHandle->path2) {
		free(symHandle->path2);
		symHandle->path2 = NULL;
	}

	SETWORDVAR(parId, T32_INBUFFER[index]);
	index += 2;

	/* AD: symbol address */
	if (parId == 0x4441) {
		index = extractAddressParams(symHandle->address, index);
		SETWORDVAR(parId, T32_INBUFFER[index]);
		index += 2;
	}

	/* NM: symbol name */
	if (parId == 0x4d4e) {
		uint16_t fieldLen;
		SETWORDVAR(fieldLen, T32_INBUFFER[index]);
		index +=2;
		symName = (char *) T32_INBUFFER + index;
		symNameLen = strlen(symName);
		if (symNameLen >= fieldLen)
			return T32_ERR_COM_RECEIVE_FAIL;
		index += fieldLen;
		SETWORDVAR(parId, T32_INBUFFER[index]);
		index +=2;
	}

	/* symbol path (legacy, reserved, do not use) */
	if (parId == 0x5450) /* PT */ {
		uint16_t fieldLen;
		SETWORDVAR(fieldLen, T32_INBUFFER[index]);
		/* NOP */
		SETWORDVAR(parId, T32_INBUFFER[index + 2 + fieldLen]);
		index = index + 2 + fieldLen + 2;
	}

	/* symbol size */
	if (parId == 0x5a53) /* "SZ" */ {
		SETQUADVAR(symHandle->size, T32_INBUFFER[index]);
		SETWORDVAR(parId, T32_INBUFFER[index + 8]);
		index += 10;
	}

	/* symbol name extension*/
	if (parId == 0x454e) /* "NE */ {
		uint16_t fieldLen;
		SETWORDVAR(fieldLen, T32_INBUFFER[index]);
		index +=2;
		symNameExt = (char *) T32_INBUFFER + index;
		symNameExtLen = strlen(symNameExt);
		if (symNameExtLen >= fieldLen)
			return T32_ERR_COM_RECEIVE_FAIL;
		index += fieldLen;
		SETWORDVAR(parId, T32_INBUFFER[index]);
		index +=2;
	}

	/* symbol path replacement */
	if (parId == 0x5250) /* PR */ {
		uint16_t fieldLen;
		SETWORDVAR(fieldLen, T32_INBUFFER[index]);
		index +=2;
		symPath = (char *) T32_INBUFFER + index;
		symPathLen = strlen(symPath);
		if (symPathLen >= fieldLen)
			return T32_ERR_COM_RECEIVE_FAIL;
		index += fieldLen;
		SETWORDVAR(parId, T32_INBUFFER[index]);
		index +=2;
	}

	/* check here(!) for XX ending, old versions may not have sent this */
	/* if (parId == 0x5858)
		index +=2; */

	if ((symName && symNameLen) || (symNameExt && symNameExtLen)) {
		symHandle->name2 = malloc((symNameLen + symNameExtLen + 1) * sizeof(char));
		if (symHandle->name2) {
			memcpy(symHandle->name2, symName, symNameLen);
			memcpy(symHandle->name2 + symNameLen, symNameExt, symNameExtLen);
			symHandle->name2[symNameLen + symNameExtLen] = 0;
		}
	}

	if (symPath && symPathLen) {
		symHandle->path2 = malloc((symPathLen + 1) * sizeof(char));
		if (symHandle->path2) {
			memcpy(symHandle->path2, symPath, symPathLen);
			symHandle->path2[symPathLen] = 0;
		}
	}

	return 0;
}


int T32_QuerySymbolObj(T32_SymbolHandle symbolHandle)
{
	int             err = 0, msgsize;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x", symbolHandle);

	if (!symbolHandle)
		err = T32_COM_PARA_FAIL;

	if (!err) {
		/* send symbol parameters to T32 */

		T32_OUTBUFFER[0] = 2;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_SYMBOL_QUERYOBJ;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		msgsize = streamSymbolParams(symbolHandle, 6);
		if (msgsize < 0)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
		else {
			SETWORDVAR(T32_OUTBUFFER[4], msgsize);
			if (LINE_Transmit(msgsize) == -1)
				err = T32_Errno = T32_COM_TRANSMIT_FAIL;
		}
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err)
		err = T32_Errno = extractSymbolParams(symbolHandle, 4);

	if (!err)
		err = T32_Errno = T32_INBUFFER[2];

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/******** Access breakpoints ********/

static int streamBreakpointParams(const T32_BreakpointHandle bpHandle, int index)
{
	int             startindex = index;
	uint16_t        tmp_ui16;

	tmp_ui16 = 0x6868;  /* "xx", ptr to XX */
	SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
	index += 4;

	tmp_ui16 = 0x4441;  /* "AD" */
	SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
	index += 2;
	index = streamAddressParams(bpHandle->address, 0, index);

	tmp_ui16 = 0x5a53;  /* "SZ" */
	SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
	SETQUADVAR(T32_OUTBUFFER[index + 2], bpHandle->size);
	index += 10;

	tmp_ui16 = 0x5954;  /* "TY" */
	SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
	SETLONGVAR(T32_OUTBUFFER[index + 2], bpHandle->types);
	index += 6;

	tmp_ui16 = 0x4d49;  /* "IM" */
	SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
	SETLONGVAR(T32_OUTBUFFER[index + 2], bpHandle->impl);
	index += 6;

	tmp_ui16 = 0x4143;  /* "AC" */
	SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
	SETLONGVAR(T32_OUTBUFFER[index + 2], bpHandle->action);
	index += 6;

	tmp_ui16 = 0x4e45;  /* "EN" */
	SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);
	tmp_ui16 = bpHandle->disabled ? 0 : 1;
	SETWORDVAR(T32_OUTBUFFER[index + 2], tmp_ui16);
	index += 4;

	tmp_ui16 = 0x5858;  /* "XX" = end marker */
	SETWORDVAR(T32_OUTBUFFER[index], tmp_ui16);

	tmp_ui16 = (uint16_t) (index - startindex);
	SETWORDVAR(T32_OUTBUFFER[startindex + 2], tmp_ui16);

	return index + 2;
}


static int extractBreakpointParams(T32_BreakpointHandle bpHandle, int index)
{
	uint16_t        parId, tmp_ui16;
	uint16_t        xxindex = 0;
	int             startindex = index;
	SETWORDVAR(parId, T32_INBUFFER[index]);
	index += 2;
	if (parId == 0x6a6a) {
		bpHandle->types = 0;
		bpHandle->impl = 0;
		return 2;
	}
	if (parId == 0x6868) {      /* ptr to XX */
		SETWORDVAR(xxindex, T32_INBUFFER[index]);
		SETWORDVAR(parId, T32_INBUFFER[index + 2]);
		index += 4;
	}
	if (parId == 0x4441) {      /* address */
		index = extractAddressParams(bpHandle->address, index);
		SETWORDVAR(parId, T32_INBUFFER[index]);
		index += 2;
	}
	if (parId == 0x5a53) {      /* size */
		SETQUADVAR(bpHandle->size, T32_INBUFFER[index]);
		SETWORDVAR(parId, T32_INBUFFER[index + 8]);
		index += 10;
	}
	if (parId == 0x5954) {      /* type */
		SETLONGVAR(bpHandle->types, T32_INBUFFER[index]);
		SETWORDVAR(parId, T32_INBUFFER[index + 4]);
		index += 6;
	}
	if ((parId == 0x4d44) || (parId == 0x4d49)) {       /* implementation ("DM": legacy 2014-07) */
		SETLONGVAR(bpHandle->impl, T32_INBUFFER[index]);
		SETWORDVAR(parId, T32_INBUFFER[index + 4]);
		index += 6;
	}
	if (parId == 0x4143) {      /* action */
		SETLONGVAR(bpHandle->action, T32_INBUFFER[index]);
		SETWORDVAR(parId, T32_INBUFFER[index + 4]);
		index += 6;
	}
	if (parId == 0x4e45) {      /* enable */
		SETWORDVAR(tmp_ui16, T32_INBUFFER[index]);
		bpHandle->disabled = tmp_ui16 ? 0 : 1;
		SETWORDVAR(parId, T32_INBUFFER[index + 4]);
		index += 4;
	}
	if (xxindex)
		index = startindex + xxindex;
	/* SETWORDVAR(parId, T32_INBUFFER[index+4]); // should be "XX" */

	return index + 2;
}


int T32_ReadBreakpointObj(T32_BreakpointHandle bpHandle)
{
	int             err = 0, msgsize;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x", bpHandle);

	if (!bpHandle)
		err = T32_COM_PARA_FAIL;

	if (!err) {
		/* send breakpoint address to T32 */

		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_BREAKPOINT_OBJ_READ;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		T32_OUTBUFFER[4] = 0;   /* by address */
		msgsize = streamAddressParams(bpHandle->address, 0, 6);
		T32_OUTBUFFER[0] = (unsigned char) msgsize;

		if (LINE_Transmit(msgsize) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		extractBreakpointParams(bpHandle, 4);
		err = T32_INBUFFER[2];
		switch (err) {
			case T32_ERR_FN1:
				err = T32_ERR_READBPOBJ_PARAFAIL;
				break;
			case T32_ERR_FN2:
				err = T32_ERR_READBPOBJ_NOTFOUND;
				break;
		}
		T32_Errno = err;
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_ReadBreakpointObjByIndex(T32_BreakpointHandle bpHandle, uint32_t index)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d", bpHandle, index);

	if (!bpHandle)
		err = T32_COM_PARA_FAIL;

	if (!err) {
		/* send breakpoint index to T32 */

		T32_OUTBUFFER[0] = 8;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_BREAKPOINT_OBJ_READ;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		T32_OUTBUFFER[4] = 1;   /* by index */
		SETLONGVAR(T32_OUTBUFFER[6], index);

		if (LINE_Transmit(10) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		extractBreakpointParams(bpHandle, 4);
		err = T32_INBUFFER[2];
		switch (err) {
			case T32_ERR_FN1:
				err = T32_ERR_READBPOBJ_PARAFAIL;
				break;
			case T32_ERR_FN2:
				err = T32_ERR_READBPOBJ_NOTFOUND;
				break;
		}
		T32_Errno = err;
	}


	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_WriteBreakpointObj(T32_BreakpointHandle bpHandle, int set)
{
	int             err = 0, msgsize;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "h%x, %d", bpHandle, set);

	if (!bpHandle)
		err = T32_COM_PARA_FAIL;

	if (!err) {
		/* send breakpoint parameters to T32 */

		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_BREAKPOINT_OBJ_WRITE;
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		T32_OUTBUFFER[4] = (unsigned char) set;
		T32_OUTBUFFER[5] = 0;
		msgsize = streamBreakpointParams(bpHandle, 6);
		T32_OUTBUFFER[0] = (unsigned char) msgsize;

		if (LINE_Transmit(msgsize) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		extractBreakpointParams(bpHandle, 4);
		err = T32_INBUFFER[2];
		switch (err) {
			case T32_ERR_FN1:
				err = T32_ERR_SETBP_FAILED;
				break;
			case T32_ERR_FN2:
				err = T32_ERR_WRITEBPOBJ_FAILED;
				break;
			case T32_ERR_FN3:
				err = T32_ERR_WRITEBPOBJ_ADDRESS;
				break;
			case T32_ERR_FN4:
				err = T32_ERR_WRITEBPOBJ_ACTION;
				break;
		}
		T32_Errno = err;
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


int T32_QueryBreakpointObjCount(uint32_t * pCount)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "p%x", pCount);

	T32_OUTBUFFER[0] = 4;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_BREAKPOINT_OBJ_QUERY;
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();
	T32_OUTBUFFER[4] = 0;       /* id: count */
	T32_OUTBUFFER[5] = 0;

	if (LINE_Transmit(6) == -1)
		err = T32_Errno = T32_COM_TRANSMIT_FAIL;

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		/* SETWORDVAR(id, T32_INBUFFER[4]); */
		SETLONGVAR(*pCount, T32_INBUFFER[6]);
		err = T32_Errno = T32_INBUFFER[2];
	}

	T32_ApiCallEpilog();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/**************************************************************************

  T32_Fdx* - Fast Data Exchange

***************************************************************************/

int T32_Fdx_Open(const char *Name, const char *Mode)
{
	unsigned int    len, lenm;
	int             result = 0;
	uint32_t        id;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%s, %s", Name, Mode);

	len = (unsigned int) strlen(Name);
	lenm = (unsigned int) strlen(Mode);
	T32_OUTBUFFER[0] = (unsigned char) (2 + len + 1 + lenm + 1);
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_FDX_OPEN;     /* T32_FdxOpen */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	strcpy((char *) (T32_OUTBUFFER + 4), Name);
	strcpy((char *) (T32_OUTBUFFER + 4 + len + 1), Mode);

	if (LINE_Transmit((len + lenm + 6 + 1) & (~1)) == -1) {
		T32_Errno = T32_COM_TRANSMIT_FAIL;
		result = -1;
		goto returnlabel;
	}

	if (LINE_Receive() == -1) {
		T32_Errno = T32_COM_RECEIVE_FAIL;
		result = -1;
		goto returnlabel;
	}

	if ((T32_Errno = T32_INBUFFER[2]) != 0) {
		result = -1;
		goto returnlabel;
	}

	SETLONGVAR(id, T32_INBUFFER[4]);
	result = (int) id;
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", result);
	return result;
}

int T32_Fdx_Close(int Channel)
{
	uint32_t        id;
	int             result = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d", Channel);

	id = (uint32_t) Channel;
	T32_OUTBUFFER[0] = 6;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_FDX_CLOSE;    /* T32_FdxClose */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	SETLONGVAR(T32_OUTBUFFER[4], id);

	if (LINE_Transmit(8) == -1) {
		T32_Errno = T32_COM_TRANSMIT_FAIL;
		result = -1;
		goto returnlabel;
	}
	if (LINE_Receive() == -1) {
		T32_Errno = T32_COM_RECEIVE_FAIL;
		result = -1;
		goto returnlabel;
	}
	if ((T32_Errno = T32_INBUFFER[2]) != 0) {
		result = -1;
		goto returnlabel;
	}
	result = 0;
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", result);
	return result;
}


int T32_Fdx_Resolve(const char *Name)
{
	unsigned int    len;
	uint32_t        id;
	int             result = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%s", Name);

	len = (unsigned int) strlen(Name);
	T32_OUTBUFFER[0] = (unsigned char) (3 + len);
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_FDX_RESOLVE;  /* T32_FdxResolve */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	strcpy((char *) (T32_OUTBUFFER + 4), Name);

	if (LINE_Transmit((len + 5 + 1) & (~1)) == -1) {
		T32_Errno = T32_COM_TRANSMIT_FAIL;
		result = -1;
		goto returnlabel;
	}

	if (LINE_Receive() == -1) {
		T32_Errno = T32_COM_RECEIVE_FAIL;
		result = -1;
		goto returnlabel;
	}

	if ((T32_Errno = T32_INBUFFER[2]) != 0) {
		result = -1;
		goto returnlabel;
	}

	SETLONGVAR(id, T32_INBUFFER[4]);
	result = (int) id;
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", result);
	return result;
}


int T32_Fdx_ReceivePoll(int Channel, void *pData, int Width, int MaxSize)
{
	int             size, len;
	uint32_t        id;
	int             result = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d, (void*) p%x, %d, %d", Channel, pData, Width, MaxSize);

	id = (uint32_t) Channel;
	if (Width <= 0 || Width > 16) {
		T32_Errno = T32_COM_PARA_FAIL;
		result = -1;
		goto returnlabel;
	}
	if (MaxSize <= 0) {
		T32_Errno = T32_COM_PARA_FAIL;
		result = -1;
		goto returnlabel;
	}
	MaxSize *= Width;
	if (MaxSize > LINE_SBLOCK)
		MaxSize = LINE_SBLOCK;

	T32_OUTBUFFER[0] = 6;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_FDX_RECEIVEPOLL;      /* T32_FdxReceivePoll */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	SETLONGVAR(T32_OUTBUFFER[4], id);

	T32_OUTBUFFER[8] = (unsigned char) Width;

#if defined(T32HOST_BE)
	T32_OUTBUFFER[8] |= 0x80;
#endif

	T32_OUTBUFFER[9] = 0;

	if (LINE_Transmit(10) == -1) {
		T32_Errno = T32_COM_TRANSMIT_FAIL;
		result = -1;
		goto returnlabel;
	}
	if ((len = LINE_Receive()) == -1) {
		T32_Errno = T32_COM_RECEIVE_FAIL;
		result = -1;
		goto returnlabel;
	}
	if ((T32_Errno = T32_INBUFFER[2]) != 0) {
		result = -1;
		goto returnlabel;
	}
	len -= 4;
	if (len < 0) {
		T32_Errno = T32_COM_SEQ_FAIL;
		result = -1;
		goto returnlabel;
	}
	size = (len > MaxSize) ? MaxSize : len;

	if (size > 0)
		memcpy(pData, T32_INBUFFER + 4, size);

	if (Width <= 1) {
		result = size;
		goto returnlabel;
	}
	result = size / Width;
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", result);
	return result;
}


int T32_Fdx_Receive(int Channel, void *pData, int Width, int MaxSize)
{
	int             size, len, paramWidth;
	uint32_t        id;
	int             result = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d, (void*) p%x, %d, %d", Channel, pData, Width, MaxSize);

	paramWidth = Width;
	Width &= 0x3F;
	if (Width <= 0 || Width > 16) {
		T32_Errno = T32_COM_PARA_FAIL;
		result = -1;
		goto returnlabel;
	}
	if (MaxSize <= 0) {
		T32_Errno = T32_COM_PARA_FAIL;
		result = -1;
		goto returnlabel;
	}
	MaxSize *= Width;
	if (MaxSize > LINE_SBLOCK)
		MaxSize = LINE_SBLOCK;

	do {
		id = (uint32_t) Channel;
		T32_OUTBUFFER[0] = 6;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_FDX_RECEIVE;      /* T32_FdxReceive */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();

		SETLONGVAR(T32_OUTBUFFER[4], id);

		T32_OUTBUFFER[8] = (unsigned char) paramWidth;
#if defined(T32HOST_BE)
		T32_OUTBUFFER[8] |= 0x80;
#endif

		T32_OUTBUFFER[9] = 0;

		if (LINE_Transmit(10) == -1) {
			T32_Errno = T32_COM_TRANSMIT_FAIL;
			result = -1;
			goto returnlabel;
		}
		if ((len = LINE_Receive()) == -1) {
			T32_Errno = T32_COM_RECEIVE_FAIL;
			result = -1;
			goto returnlabel;
		}
		if ((T32_Errno = T32_INBUFFER[2]) != 0) {
			result = -1;
			goto returnlabel;
		}
		len -= 4;
		if (len < 0) {
			T32_Errno = T32_COM_SEQ_FAIL;
			result = -1;
			goto returnlabel;
		}
		size = (len > MaxSize) ? MaxSize : len;

	} while (size <= 0);

	memcpy(pData, T32_INBUFFER + 4, size);

	if (Width <= 1) {
		result = size;
		goto returnlabel;
	}
	result = size / Width;
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", result);
	return result;
}


int T32_Fdx_SendPoll(int Channel, void *pData, int Width, int Size)
{
	int             bsize;
	uint32_t        id;
	int             result = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d, (void*) p%x, %d, %d", Channel, pData, Width, Size);

	if (Width <= 0 || Width > 16) {
		T32_Errno = T32_COM_PARA_FAIL;
		result = -1;
		goto returnlabel;
	}
	bsize = Size * Width;
	if (bsize > LINE_SBLOCK || bsize <= 0) {
		T32_Errno = T32_COM_PARA_FAIL;
		result = -1;
		goto returnlabel;
	}
	id = (uint32_t) Channel;
	T32_OUTBUFFER[0] = 0;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_FDX_TRANSMITPOLL;     /* T32_FdxTransmitPoll */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();

	SETLONGVAR(T32_OUTBUFFER[4], id);

#if defined(T32HOST_BE)
	Width |= 0x80;
#endif

	T32_OUTBUFFER[8] = (unsigned char) Width;
	T32_OUTBUFFER[9] = 0;
	T32_OUTBUFFER[10] = (10 + bsize) & 0xff;
	T32_OUTBUFFER[11] = ((10 + bsize) >> 8) & 0xff;
	memcpy(T32_OUTBUFFER + 12, pData, bsize);

	if (LINE_Transmit((bsize + 12 + 1) & (~1)) == -1) {
		T32_Errno = T32_COM_TRANSMIT_FAIL;
		result = -1;
		goto returnlabel;
	}
	if (LINE_Receive() == -1) {
		T32_Errno = T32_COM_RECEIVE_FAIL;
		result = -1;
		goto returnlabel;
	}
	if (T32_INBUFFER[2] == 1) {
		result = 0;
		goto returnlabel;
	}
	if ((T32_Errno = T32_INBUFFER[2]) != 0) {
		result = -1;
		goto returnlabel;
	}
	result = Size;
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", result);
	return result;
}


int T32_Fdx_Send(int Channel, void *pData, int Width, int Size)
{
	int             bsize;
	uint32_t        id;
	int             result = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d, (void*) p%x, %d, %d", Channel, pData, Width, Size);

	if (Width <= 0 || Width > 16) {
		T32_Errno = T32_COM_PARA_FAIL;
		result = -1;
		goto returnlabel;
	}
	bsize = Size * Width;
	if (bsize > LINE_SBLOCK || bsize <= 0) {
		T32_Errno = T32_COM_PARA_FAIL;
		result = -1;
		goto returnlabel;
	}
	id = (uint32_t) Channel;

	do {
		T32_OUTBUFFER[0] = 0;
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_FDX_TRANSMIT;     /* T32_FdxTransmit */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		SETLONGVAR(T32_OUTBUFFER[4], id);

#if defined(T32HOST_BE)
		Width |= 0x80;
#endif

		T32_OUTBUFFER[8] = (unsigned char) Width;
		T32_OUTBUFFER[9] = 0;
		T32_OUTBUFFER[10] = (10 + bsize) & 0xff;
		T32_OUTBUFFER[11] = ((10 + bsize) >> 8) & 0xff;
		memcpy(T32_OUTBUFFER + 12, pData, bsize);

		if (LINE_Transmit((bsize + 12 + 1) & (~1)) == -1) {
			T32_Errno = T32_COM_TRANSMIT_FAIL;
			result = -1;
			goto returnlabel;
		}
		if (LINE_Receive() == -1) {
			T32_Errno = T32_COM_RECEIVE_FAIL;
			result = -1;
			goto returnlabel;
		}
	} while (T32_INBUFFER[2] == 1);

	if ((T32_Errno = T32_INBUFFER[2]) != 0) {
		result = -1;
		goto returnlabel;
	}
	result = Size;
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", result);
	return result;
}




/**************************************************************************

  T32_TapAccess* - Low level JTAG access functions

***************************************************************************/

typedef enum {
	T32_PARAM_TYPE_UINT8,
	T32_PARAM_TYPE_UINT16,
	T32_PARAM_TYPE_UINT32,
	T32_PARAM_TYPE_UINT64,
} T32_Param_Type;

typedef struct tapAccessHeader {
	struct tapAccessHeader *next;
	int             cmd;
	int             numberofbits;   /**< data to write to target*/
	int             numberofinbits; /**< data to read from target*/
	T32_Param_Type  inbittype;      /**< data to read from target*/
	uint8_t        *pinbits;        /**< data to read from target*/
	unsigned char   outbits[1];     /**< additional data appended to that structure !*/
} tapAccessHeader;


typedef struct tapAccessHandle {
	struct tapAccessHeader *first;
	struct tapAccessHeader *current;
} tapAccessHandle;


/* internal API */
extern int T32_BundledAccess(int cmd, T32_BUNDLEDACCESS_HANDLE connection, int numberofbits,
		const uint8_t * poutbits, uint8_t * pinbits, int numberofinbits, T32_Param_Type inbittype);

int T32_BundledAccess(int cmd, T32_BUNDLEDACCESS_HANDLE connection, int numberofbits,
	const uint8_t * poutbits, uint8_t * pinbits, int numberofinbits, T32_Param_Type inbittype)
{
	int             size, len;
	unsigned char  *ptr;
	int             indatasize;

	ptr = T32_OUTBUFFER + 6;
	indatasize = (numberofinbits + 7) / 8;

	if (numberofbits >= 0) {
		if (poutbits || pinbits) {
			cmd |= 2;
		}
		if (pinbits) {
			cmd |= 1;
		}
		if (numberofbits < 0x0f) {
			*ptr++ = (unsigned char) ((cmd << 4) | numberofbits);
		} else if (numberofbits < 0xff) {
			*ptr++ = (unsigned char) ((cmd << 4) | 0x0f);
			*ptr++ = (unsigned char) numberofbits;
		} else {
			*ptr++ = (unsigned char) ((cmd << 4) | 0x0f);
			*ptr++ = 0xff;
			ptr[0] = (numberofbits & 0xff);
			ptr[1] = ((numberofbits >> 8) & 0xff);
			ptr[2] = ((numberofbits >> 16) & 0xff);
			ptr[3] = ((numberofbits >> 24) & 0xff);
			ptr += 4;
		}

		size = (numberofbits + 7) / 8;
		if (size && (cmd & 2)) {
			if (poutbits)
				memcpy(ptr, poutbits, size);
			else
				memset(ptr, 0x0, size);
			ptr += size;
		}
	}

	if (connection != T32_TAPACCESS_HOLD)
		*ptr++ = 0;

	size = (int) (ptr - (T32_OUTBUFFER + 6));
	if (indatasize > size)
		return T32_Errno = T32_COM_PARA_FAIL;   /* can't receive more bytes than send */

	T32_OUTBUFFER[0] = 0;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = (connection == T32_TAPACCESS_HOLD) ? 0x93 : 0x92;        /* T32_JtagDebugLock/T32_JtagDebug */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();
	T32_OUTBUFFER[4] = (4 + size) & 0xff;
	T32_OUTBUFFER[5] = ((4 + size) >> 8) & 0xff;

	if (LINE_Transmit(6 + ((size + 1) & (~1))) == -1)
		return T32_Errno = T32_COM_TRANSMIT_FAIL;

	if ((len = LINE_Receive()) == -1)
		return T32_Errno = T32_COM_RECEIVE_FAIL;

	T32_Errno = T32_INBUFFER[2];

	if (pinbits && len >= indatasize + 4) {
		int             i;
		uint8_t        *src = T32_INBUFFER + 4;
		if (inbittype == T32_PARAM_TYPE_UINT8) {
			memcpy(pinbits, src, indatasize);
		} else if (inbittype == T32_PARAM_TYPE_UINT16) {
			for (i = 0; i < indatasize; i += 2)
				*(uint16_t *) (void *) (pinbits + i) = ((uint16_t) src[i]) + (((uint16_t) src[i + 1]) << 8);
		} else if (inbittype == T32_PARAM_TYPE_UINT32) {
			for (i = 0; i < indatasize; i += 4)
				*(uint32_t *) (void *) (pinbits + i) =
					((uint32_t) src[i]) + (((uint32_t) src[i + 1]) << 8) + (((uint32_t) src[i + 2]) << 16) +
					(((uint32_t) src[i + 3]) << 24);
		} else if (inbittype == T32_PARAM_TYPE_UINT64) {
			for (i = 0; i < indatasize; i += 8)
				*(uint64_t *) (void *) (pinbits + i) =
					((uint64_t) src[i]) + (((uint64_t) src[i + 1]) << 8) + (((uint64_t) src[i + 2]) << 16) +
					(((uint64_t) src[i + 3]) << 24) + (((uint64_t) src[i + 4]) << 32) +
					(((uint64_t) src[i + 5]) << 40) + (((uint64_t) src[i + 6]) << 48) + (((uint64_t) src[i + 7]) << 56);
		}
	}
	return T32_Errno;
}


/* internal API */
extern int T32_BundledAccessStore(int cmd, T32_BUNDLEDACCESS_HANDLE connection, int numberofbits,
		  const uint8_t * poutbits, uint8_t * pinbits, int numberofinbits, T32_Param_Type inbittype);

int T32_BundledAccessStore(int cmd, T32_BUNDLEDACCESS_HANDLE connection, int numberofbits,
	   const uint8_t * poutbits, uint8_t * pinbits, int numberofinbits, T32_Param_Type inbittype)
{
	tapAccessHandle *taphandle;
	tapAccessHeader *tapptr;
	int             size;

	taphandle = (tapAccessHandle *) connection;

	size = (numberofbits + 7) / 8;
	tapptr = (tapAccessHeader *) malloc(sizeof(tapAccessHeader) + size);
	if (!tapptr) {
		T32_Errno = T32_MALLOC_FAIL;
		return T32_Errno;
	}

	if (poutbits || pinbits) {
		if (poutbits)
			memcpy(tapptr->outbits, poutbits, size);
		else
			memset(tapptr->outbits, 0x0, size);
		cmd |= 2;
	}
	if (pinbits) {
		cmd |= 1;
	}

	tapptr->next = NULL;
	tapptr->cmd = cmd;
	tapptr->numberofbits = numberofbits;
	tapptr->pinbits = pinbits;
	tapptr->numberofinbits = numberofinbits;
	tapptr->inbittype = inbittype;

	if (taphandle->current)
		taphandle->current->next = tapptr;
	else
		taphandle->first = tapptr;
	taphandle->current = tapptr;

	T32_Errno = 0;
	return T32_Errno;
}


T32_BUNDLEDACCESS_HANDLE T32_BundledAccessAlloc(void)
{
	tapAccessHandle *taphandle;

	T32_ApiLog(__func__, T32APILOG_FENTRY, NULL);

	taphandle = (tapAccessHandle *) malloc(sizeof(tapAccessHandle));
	if (!taphandle) {
		T32_Errno = T32_MALLOC_FAIL;
		return NULL;
	}

	taphandle->first = NULL;
	taphandle->current = NULL;

	T32_Errno = 0;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "(void*) p%x", taphandle);
	return taphandle;
}


static int BundledAccessSend(T32_BUNDLEDACCESS_HANDLE connection, int size, uint8_t ** bitptr,
	 int *bitsizesenddata, int *bitsizereceivedata, T32_Param_Type * bitreceivetype, int npairs)
{
	int             i, len;
	unsigned char  *ptr;

	T32_OUTBUFFER[0] = 0;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = (connection == T32_TAPACCESS_HOLD) ? 0x93 : 0x92;        /* T32_JtagDebugLock/T32_JtagDebug */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();
	T32_OUTBUFFER[4] = (4 + size) & 0xff;
	T32_OUTBUFFER[5] = ((4 + size) >> 8) & 0xff;

	if (LINE_Transmit(6 + ((size + 1) & (~1))) == -1)
		return T32_Errno = T32_COM_TRANSMIT_FAIL;

	if ((len = LINE_Receive()) == -1)
		return T32_Errno = T32_COM_RECEIVE_FAIL;

	T32_Errno = T32_INBUFFER[2];

	ptr = T32_INBUFFER + 4;
	for (i = 0; i < npairs; i++) {
		if (bitptr[i]) {
			int             bytesize = (bitsizereceivedata[i] + 7) / 8;
			if (bitreceivetype[i] == T32_PARAM_TYPE_UINT8)
				memcpy(bitptr[i], ptr, bytesize);
			else if (bitreceivetype[i] == T32_PARAM_TYPE_UINT16) {
				int             j;
				int             l = bytesize / 2;
				for (j = 0; j < l; ++j) {
					uint16_t        nValue = (uint16_t) ptr[j * 2] + ((uint16_t) ptr[j * 2 + 1] << 8);
					*((uint16_t *) (void *) (bitptr[i] + j * 2)) = nValue;
				}
			} else if (bitreceivetype[i] == T32_PARAM_TYPE_UINT32) {
				int             j;
				int             l = bytesize / 4;
				for (j = 0; j < l; ++j) {
					uint32_t        nValue =
						(uint32_t) ptr[j * 4] + ((uint32_t) ptr[j * 4 + 1] << 8) + ((uint32_t) ptr[j * 4 + 2] << 16) +
						((uint32_t) ptr[j * 4 + 3] << 24);
					*((uint32_t *) (void *) (bitptr[i] + j * 4)) = nValue;
				}
			} else if (bitreceivetype[i] == T32_PARAM_TYPE_UINT64) {
				int             j;
				int             l = bytesize / 8;
				for (j = 0; j < l; ++j) {
					uint64_t        nValue =
						((uint64_t) ptr[j * 8 + 0]) + ((uint64_t) ptr[j * 8 + 1] << 8) +
						((uint64_t) ptr[j * 8 + 2] << 16) + ((uint64_t) ptr[j * 8 + 3] << 24)
						+ ((uint64_t) ptr[j * 8 + 4] << 32) + ((uint64_t) ptr[j * 8 + 5] << 40) +
						((uint64_t) ptr[j * 8 + 6] << 48) + ((uint64_t) ptr[j * 8 + 7] << 56);
					*((uint64_t *) (void *) (bitptr[i] + j * 8)) = nValue;
				}
			}
			ptr += (bitsizesenddata[i] + 7) / 8;
		}
	}

	return T32_Errno;
}


int T32_BundledAccessExecute(T32_BUNDLEDACCESS_HANDLE Handle, T32_BUNDLEDACCESS_HANDLE SequenceHandle)
{
	unsigned char  *ptr;
	int             datasize, size, maxsize, n, cmd, numberofbits;
	tapAccessHandle *taphandle;
	tapAccessHeader *tapptr;
	unsigned char  *bitptr[2048];
	int             bitsizessend[2048];
	int             bitsizesreceive[2048];
	T32_Param_Type  bitreceivetype[2048];
	int             result = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, (void*) p%x", Handle, SequenceHandle);

	if (!(Handle > T32_TAPACCESS_HOLD)) {
		result = T32_Errno = T32_COM_PARA_FAIL;
		goto returnlabel;
	}

	taphandle = (tapAccessHandle *) Handle;

	ptr = T32_OUTBUFFER + T32_TAPACCESSSEND_HEADERSIZE;
	tapptr = taphandle->first;
	datasize = 0;
	n = 0;
	maxsize = EMU_CBMAXDATASIZE;

	while (tapptr) {
		cmd = tapptr->cmd;
		numberofbits = tapptr->numberofbits;
		size = (numberofbits + 7) / 8;

		if ((datasize >= maxsize) || (datasize + size > maxsize) || (n >= 2048)) {
			if (BundledAccessSend(T32_TAPACCESS_HOLD,
						  (int) (ptr - (T32_OUTBUFFER + T32_TAPACCESSSEND_HEADERSIZE)),
						  bitptr, bitsizessend, bitsizesreceive, bitreceivetype, n)
				&& (T32_Errno != 67) /*user signal event */ ) {
				result = T32_Errno;
				goto returnlabel;
			}
			ptr = T32_OUTBUFFER + T32_TAPACCESSSEND_HEADERSIZE;
			datasize = 0;
			n = 0;
		}
		if (numberofbits < 0x0f) {
			*ptr++ = (unsigned char) ((cmd << 4) | numberofbits);
			datasize++;
		} else if (numberofbits < 0xff) {
			*ptr++ = (unsigned char) ((cmd << 4) | 0x0f);
			*ptr++ = (unsigned char) numberofbits;
			datasize += 2;
		} else {
			*ptr++ = (unsigned char) ((cmd << 4) | 0x0f);
			*ptr++ = 0xff;
			ptr[0] = (numberofbits & 0xff);
			ptr[1] = ((numberofbits >> 8) & 0xff);
			ptr[2] = ((numberofbits >> 16) & 0xff);
			ptr[3] = ((numberofbits >> 24) & 0xff);
			ptr += 4;
			datasize += T32_TAPACCESSSEND_HEADERSIZE;
		}

		if (size && (cmd & 2)) {
			memcpy(ptr, tapptr->outbits, size);
			ptr += size;
		}
		bitptr[n] = tapptr->pinbits;
		bitsizessend[n] = tapptr->numberofbits;
		bitsizesreceive[n] = tapptr->numberofinbits;
		bitreceivetype[n] = tapptr->inbittype;
		n++;

		datasize += size;
		tapptr = tapptr->next;
	}

	if (SequenceHandle != T32_TAPACCESS_HOLD)
		*ptr++ = 0;

	result = BundledAccessSend(SequenceHandle, (int) (ptr - (T32_OUTBUFFER + T32_TAPACCESSSEND_HEADERSIZE)),
					   bitptr, bitsizessend, bitsizesreceive, bitreceivetype, n);
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", result);
	return result;
}


int T32_BundledAccessFree(T32_BUNDLEDACCESS_HANDLE Handle)
{
	tapAccessHandle *taphandle;
	tapAccessHeader *tapptr;
	tapAccessHeader *tapptrnext;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x", Handle);

	taphandle = (tapAccessHandle *) Handle;

	tapptr = taphandle->first;
	while (tapptr) {
		tapptrnext = tapptr->next;
		free(tapptr);
		tapptr = tapptrnext;
	}

	free(taphandle);

	T32_Errno = 0;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "0");
	return 0;
}


int T32_TAPAccessSetInfo2(T32_BUNDLEDACCESS_HANDLE Handle, int irpre, int irpost,
	  int drpre, int drpost, int tristate, int tapstate, int tcklevel, int reserved)
{
	unsigned char   outbits[20];
	int             result;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %d, %d, %d, %d, %d, %d, %d, %d", Handle, irpre, irpost,
			   drpre, drpost, tristate, tapstate, reserved);

	outbits[0] = irpre & 0xff;
	outbits[1] = (irpre >> 8) & 0xff;
	outbits[2] = (irpre >> 16) & 0xff;
	outbits[3] = (irpre >> 24) & 0xff;
	outbits[4] = irpost & 0xff;
	outbits[5] = (irpost >> 8) & 0xff;
	outbits[6] = (irpost >> 16) & 0xff;
	outbits[7] = (irpost >> 24) & 0xff;
	outbits[8] = drpre & 0xff;
	outbits[9] = (drpre >> 8) & 0xff;
	outbits[10] = (drpre >> 16) & 0xff;
	outbits[11] = (drpre >> 24) & 0xff;
	outbits[12] = drpost & 0xff;
	outbits[13] = (drpost >> 8) & 0xff;
	outbits[14] = (drpost >> 16) & 0xff;
	outbits[15] = (drpost >> 24) & 0xff;
	outbits[16] = (unsigned char) tristate;
	outbits[17] = (unsigned char) tapstate;
	outbits[18] = (unsigned char) tcklevel;
	outbits[19] = (unsigned char) reserved;

	if (Handle > T32_TAPACCESS_HOLD)
		result = T32_BundledAccessStore(0, Handle, 160, outbits, NULL, 0, T32_PARAM_TYPE_UINT8);
	else
		result = T32_BundledAccess(0, Handle, 160, outbits, NULL, 0, T32_PARAM_TYPE_UINT8);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", result);
	return result;
}


int T32_TAPAccessSetInfo(int irpre, int irpost, int drpre, int drpost,
	 int tristate, int tapstate, int tcklevel, int reserved)
{
	return T32_TAPAccessSetInfo2(T32_TAPACCESS_RELEASE, irpre, irpost, drpre, drpost,
		 tristate, tapstate, tcklevel, reserved);
}


int T32_DirectAccessGetInfo(T32_BUNDLEDACCESS_HANDLE Handle, int nInstanceType, unsigned int nInstance,
	int nInfoID, T32_Param * value)
{
	unsigned char   outbits[255];
	unsigned char   inbits[16];
	int             lenbytes;
	int             res;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %d, %u, %d, (T32_Param*) p%x", Handle, nInstanceType,
			   nInstance, nInfoID, value);

	outbits[0] = 0xff;
	outbits[1] = 0xff;
	outbits[2] = 0xff;
	outbits[3] = 0xff;
	lenbytes = 4;

	outbits[lenbytes++] = nInstanceType & 0xff;
	outbits[lenbytes++] = nInstance & 0xff;
	outbits[lenbytes++] = (nInstance >> 8) & 0xff;
	outbits[lenbytes++] = nInfoID & 0xff;
	outbits[lenbytes++] = (nInfoID >> 8) & 0xff;

	if (Handle > T32_TAPACCESS_HOLD) {
		res =
			T32_BundledAccessStore(0, Handle, lenbytes * 8, outbits, (uint8_t *) (void *) value, 4 * 8,
				   T32_PARAM_TYPE_UINT32);
	} else {
		res = T32_BundledAccess(0, Handle, lenbytes * 8, outbits, inbits, 4 * 8, T32_PARAM_TYPE_UINT8);
		value->uint32 =
			(uint32_t) inbits[0] + ((uint32_t) inbits[1] << 8) + ((uint32_t) inbits[2] << 16) +
			((uint32_t) inbits[3] << 24);
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}

#define T32_DIRECTACCESS_RESET_CONFIG_ALL_UINT32                                              4

int T32_DirectAccessResetAll(T32_BUNDLEDACCESS_HANDLE Handle)
{
	return T32_DirectAccessSetInfo(Handle, 0, 0, T32_DIRECTACCESS_RESET_CONFIG_ALL_UINT32, T32_ParamFromUint32(1));
}

int T32_DirectAccessSetInfo(T32_BUNDLEDACCESS_HANDLE Handle, int nInstanceType, unsigned int nInstance,
	int nInfoID, T32_Param value)
{
	unsigned char   outbits[255];
	int             lenbytes;
	int             result;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %d, %u, %d, %u", Handle, nInstanceType, nInstance, nInfoID,
			   value.uint32);

	outbits[0] = 0xff;
	outbits[1] = 0xff;
	outbits[2] = 0xff;
	outbits[3] = 0xff;
	lenbytes = 4;

	outbits[lenbytes++] = nInstanceType & 0xff;
	outbits[lenbytes++] = nInstance & 0xff;
	outbits[lenbytes++] = (nInstance >> 8) & 0xff;
	outbits[lenbytes++] = nInfoID & 0xff;
	outbits[lenbytes++] = (nInfoID >> 8) & 0xff;

	/* _UINT32 */
	outbits[lenbytes++] = value.uint32 & 0xff;
	outbits[lenbytes++] = (value.uint32 >> 8) & 0xff;
	outbits[lenbytes++] = (value.uint32 >> 16) & 0xff;
	outbits[lenbytes++] = (value.uint32 >> 24) & 0xff;

	if (Handle > T32_TAPACCESS_HOLD)
		result = T32_BundledAccessStore(0, Handle, lenbytes * 8, outbits, NULL, 0, T32_PARAM_TYPE_UINT32);
	else
		result = T32_BundledAccess(0, Handle, lenbytes * 8, outbits, NULL, 0, T32_PARAM_TYPE_UINT32);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", result);
	return result;
}


int T32_TAPAccessJTAGResetWithTMS(T32_BUNDLEDACCESS_HANDLE Handle, unsigned int nTapInstance)
{
	unsigned char   outbits[255];
	int             lenbytes = 0;
	int             result;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %u", Handle, nTapInstance);

	outbits[lenbytes++] = 0x91;
	outbits[lenbytes++] = T32_DIRECTACCESS_INSTANCETYPE_TAP;
	outbits[lenbytes++] = nTapInstance & 0xFF;
	outbits[lenbytes++] = (nTapInstance >> 8) & 0xff;
	outbits[lenbytes++] = 0;    /* command */
	if (Handle > T32_TAPACCESS_HOLD)
		result = T32_BundledAccessStore(12, Handle, lenbytes * 8, outbits, NULL, 0, T32_PARAM_TYPE_UINT32);
	else
		result = T32_BundledAccess(12, Handle, lenbytes * 8, outbits, NULL, 0, T32_PARAM_TYPE_UINT32);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", result);
	return result;
}


int T32_TAPAccessJTAGResetWithTRST(T32_BUNDLEDACCESS_HANDLE Handle, unsigned int nTapInstance,
	   int32_t nTRSTAssertTimeUS, int32_t nDelayAfterTRSTReleaseUS)
{
	unsigned char   outbits[255];
	int             lenbytes = 0;
	int             result;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %u, %d, %d", Handle, nTapInstance, nTRSTAssertTimeUS,
			   nDelayAfterTRSTReleaseUS);

	outbits[lenbytes++] = 0x91;
	outbits[lenbytes++] = T32_DIRECTACCESS_INSTANCETYPE_TAP;
	outbits[lenbytes++] = nTapInstance & 0xFF;
	outbits[lenbytes++] = (nTapInstance >> 8) & 0xff;
	outbits[lenbytes++] = 1;    /* command */
	outbits[lenbytes++] = nTRSTAssertTimeUS & 0xFF;
	outbits[lenbytes++] = (nTRSTAssertTimeUS >> 8) & 0xFF;
	outbits[lenbytes++] = (nTRSTAssertTimeUS >> 16) & 0xFF;
	outbits[lenbytes++] = (nTRSTAssertTimeUS >> 24) & 0xFF;
	outbits[lenbytes++] = nDelayAfterTRSTReleaseUS & 0xFF;
	outbits[lenbytes++] = (nDelayAfterTRSTReleaseUS >> 8) & 0xFF;
	outbits[lenbytes++] = (nDelayAfterTRSTReleaseUS >> 16) & 0xFF;
	outbits[lenbytes++] = (nDelayAfterTRSTReleaseUS >> 24) & 0xFF;
	if (Handle > T32_TAPACCESS_HOLD)
		result = T32_BundledAccessStore(12, Handle, lenbytes * 8, outbits, NULL, 0, T32_PARAM_TYPE_UINT32);
	else
		result = T32_BundledAccess(12, Handle, lenbytes * 8, outbits, NULL, 0, T32_PARAM_TYPE_UINT32);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", result);
	return result;
}

#define T32_DIRECTACCESS_TAP_SET_PATTERN_RESERVED 125

int T32_TAPAccessSetShiftPattern(T32_BUNDLEDACCESS_HANDLE Handle, unsigned int nTapInstance,
	 uint32_t nReturnIRCount, uint32_t nReturnDRCount,
	 uint32_t nGotoIRCount, uint32_t nGotoDRCount,
	 uint32_t nReturnIR, uint32_t nReturnDR,
	 uint32_t nGotoIR, uint32_t nGotoDR, unsigned int nPattern)
{
	unsigned char   outbits[255];
	int             lenbytes = 0;
	int             result;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u", Handle,
			   nTapInstance, nReturnIRCount, nReturnDRCount, nGotoIRCount, nGotoDRCount, nReturnIR, nReturnDR,
			   nGotoIR, nGotoDR, nPattern);

	outbits[0] = 0xff;
	outbits[1] = 0xff;
	outbits[2] = 0xff;
	outbits[3] = 0xff;
	lenbytes = 4;

	outbits[lenbytes++] = T32_DIRECTACCESS_INSTANCETYPE_TAP & 0xff;
	outbits[lenbytes++] = nTapInstance & 0xff;
	outbits[lenbytes++] = (nTapInstance >> 8) & 0xff;
	outbits[lenbytes++] = T32_DIRECTACCESS_TAP_SET_PATTERN_RESERVED & 0xff;
	outbits[lenbytes++] = (T32_DIRECTACCESS_TAP_SET_PATTERN_RESERVED >> 8) & 0xff;

	outbits[lenbytes++] = nPattern & 0xFF;
	outbits[lenbytes++] = (nPattern >> 8) & 0xFF;
	outbits[lenbytes++] = (nPattern >> 16) & 0xFF;
	outbits[lenbytes++] = (nPattern >> 24) & 0xFF;
	outbits[lenbytes++] = nReturnIRCount & 0xFF;
	outbits[lenbytes++] = (nReturnIRCount >> 8) & 0xFF;
	outbits[lenbytes++] = (nReturnIRCount >> 16) & 0xFF;
	outbits[lenbytes++] = (nReturnIRCount >> 24) & 0xFF;
	outbits[lenbytes++] = nReturnDRCount & 0xFF;
	outbits[lenbytes++] = (nReturnDRCount >> 8) & 0xFF;
	outbits[lenbytes++] = (nReturnDRCount >> 16) & 0xFF;
	outbits[lenbytes++] = (nReturnDRCount >> 24) & 0xFF;
	outbits[lenbytes++] = nGotoIRCount & 0xFF;
	outbits[lenbytes++] = (nGotoIRCount >> 8) & 0xFF;
	outbits[lenbytes++] = (nGotoIRCount >> 16) & 0xFF;
	outbits[lenbytes++] = (nGotoIRCount >> 24) & 0xFF;
	outbits[lenbytes++] = nGotoDRCount & 0xFF;
	outbits[lenbytes++] = (nGotoDRCount >> 8) & 0xFF;
	outbits[lenbytes++] = (nGotoDRCount >> 16) & 0xFF;
	outbits[lenbytes++] = (nGotoDRCount >> 24) & 0xFF;
	outbits[lenbytes++] = nReturnIR & 0xFF;
	outbits[lenbytes++] = (nReturnIR >> 8) & 0xFF;
	outbits[lenbytes++] = (nReturnIR >> 16) & 0xFF;
	outbits[lenbytes++] = (nReturnIR >> 24) & 0xFF;
	outbits[lenbytes++] = nReturnDR & 0xFF;
	outbits[lenbytes++] = (nReturnDR >> 8) & 0xFF;
	outbits[lenbytes++] = (nReturnDR >> 16) & 0xFF;
	outbits[lenbytes++] = (nReturnDR >> 24) & 0xFF;
	outbits[lenbytes++] = nGotoIR & 0xFF;
	outbits[lenbytes++] = (nGotoIR >> 8) & 0xFF;
	outbits[lenbytes++] = (nGotoIR >> 16) & 0xFF;
	outbits[lenbytes++] = (nGotoIR >> 24) & 0xFF;
	outbits[lenbytes++] = nGotoDR & 0xFF;
	outbits[lenbytes++] = (nGotoDR >> 8) & 0xFF;
	outbits[lenbytes++] = (nGotoDR >> 16) & 0xFF;
	outbits[lenbytes++] = (nGotoDR >> 24) & 0xFF;

	if (Handle > T32_TAPACCESS_HOLD)
		result = T32_BundledAccessStore(0, Handle, lenbytes * 8, outbits, NULL, 0, T32_PARAM_TYPE_UINT32);
	else
		result = T32_BundledAccess(0, Handle, lenbytes * 8, outbits, NULL, 0, T32_PARAM_TYPE_UINT32);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", result);
	return result;
}

int T32_DirectAccessGetTimestamp(T32_BUNDLEDACCESS_HANDLE Handle, int Format, uint64_t * result)
{
	unsigned char   outbits[8];
	int             lenbytes = 0;
	int             res;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %d, (uint64_t*) p%x", Handle, Format, result);

	outbits[lenbytes++] = 0x92;
	outbits[lenbytes++] = 0x0;
	outbits[lenbytes++] = Format & 0xFF;
	outbits[lenbytes++] = (Format >> 8) & 0xff;
	outbits[lenbytes++] = (Format >> 16) & 0xff;
	outbits[lenbytes++] = (Format >> 24) & 0xff;
	outbits[lenbytes++] = 0;
	outbits[lenbytes++] = 0;

	if (Handle > T32_TAPACCESS_HOLD) {
		res = T32_BundledAccessStore(12, Handle, lenbytes * 8, outbits, (uint8_t *) (void *) result, 8 * 8,
				 T32_PARAM_TYPE_UINT64);
	} else {
		res = T32_BundledAccess(12, Handle, lenbytes * 8, outbits, (uint8_t *) (void *) result, 8 * 8,
			T32_PARAM_TYPE_UINT64);
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}

int T32_I2CAccess(T32_BUNDLEDACCESS_HANDLE Handle, unsigned int nInstance, uint32_t nAction,
	  uint32_t nDeviceID, const uint8_t * pCommandData, unsigned int nCommandByteLength,
	  uint8_t * pData, unsigned int nDataByteLength)
{
	unsigned char   outbits[EMU_CBMAXDATASIZE];
	unsigned int    nReadBytes = 0;
	unsigned int    lenbytes = 0;
	int             res = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %u, %d, %u, (uint8_t*) p%x, %u, (uint8_t*) p%x, %u",
			   Handle, nInstance, nAction, nDeviceID, pCommandData, nCommandByteLength, pData, nDataByteLength);

	outbits[lenbytes++] = 0x91;
	outbits[lenbytes++] = (unsigned char) T32_DIRECTACCESS_INSTANCETYPE_I2C;
	outbits[lenbytes++] = nInstance & 0xFF;
	outbits[lenbytes++] = (nInstance >> 8) & 0xff;

	outbits[lenbytes++] = 0;    /* command */

	outbits[lenbytes++] = nAction & 0xFF;
	outbits[lenbytes++] = (nAction >> 8) & 0xFF;
	outbits[lenbytes++] = (nAction >> (8 * 2)) & 0xFF;
	outbits[lenbytes++] = (nAction >> (8 * 3)) & 0xFF;
	outbits[lenbytes++] = nDeviceID & 0xFF;
	outbits[lenbytes++] = (nDeviceID >> 8) & 0xFF;
	outbits[lenbytes++] = (nDeviceID >> (8 * 2)) & 0xFF;
	outbits[lenbytes++] = (nDeviceID >> (8 * 3)) & 0xFF;
	outbits[lenbytes++] = nCommandByteLength & 0xFF;
	outbits[lenbytes++] = (nCommandByteLength >> 8) & 0xFF;
	outbits[lenbytes++] = nDataByteLength & 0xFF;
	outbits[lenbytes++] = (nDataByteLength >> 8) & 0xFF;

	if (nCommandByteLength) {
		if (!pCommandData) {
			res = T32_Errno = T32_COM_PARA_FAIL;
			goto returnlabel;
		}
		if (nCommandByteLength + lenbytes > EMU_CBMAXDATASIZE) {
			res = T32_Errno = T32_COM_PARA_FAIL;
			goto returnlabel;
		}
		memcpy(outbits + lenbytes, pCommandData, nCommandByteLength);
		lenbytes += nCommandByteLength;
	}

	if ((nAction & 0xFF) == T32_I2CACCESS_ACTION_WRITE && nDataByteLength) {
		if (!pData) {
			res = T32_Errno = T32_COM_PARA_FAIL;
			goto returnlabel;
		}
		if (nDataByteLength + lenbytes > EMU_CBMAXDATASIZE) {
			res = T32_Errno = T32_COM_PARA_FAIL;
			goto returnlabel;
		}
		memcpy(outbits + lenbytes, pData, nDataByteLength);
		lenbytes += nDataByteLength;
	}

	if ((nAction & 0xFF) != T32_I2CACCESS_ACTION_WRITE && nDataByteLength) {
		if (!pData) {
			res = T32_Errno = T32_COM_PARA_FAIL;
			goto returnlabel;
		}
		if (nDataByteLength > EMU_CBMAXDATASIZE) {
			res = T32_Errno = T32_COM_PARA_FAIL;
			goto returnlabel;
		}
		if (nDataByteLength > lenbytes)
			lenbytes = nDataByteLength;
		nReadBytes = nDataByteLength;
	}

	if (Handle > T32_TAPACCESS_HOLD) {
		res = T32_BundledAccessStore(12, Handle, lenbytes * 8, outbits, (nReadBytes) ? (pData) : NULL, nReadBytes * 8,
					 T32_PARAM_TYPE_UINT8);
	} else {
		res = T32_BundledAccess(12, Handle, lenbytes * 8, outbits, (nReadBytes) ? (pData) : (uint8_t *) NULL,
				nReadBytes * 8, T32_PARAM_TYPE_UINT8);
	}
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}

int T32_I2CRawAccess(T32_BUNDLEDACCESS_HANDLE Handle, unsigned int nInstance, const uint32_t * send, uint32_t * recv, int len)
{
	uint8_t         outbits[EMU_CBMAXDATASIZE];
	uint32_t        lenbytes = 0;
	int             res = 0;
	int             i;
	uint32_t        d;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %u, (uint32_t*) p%x, (uint32_t*) p%x, %d", Handle,
			   nInstance, send, recv, len);

	if (len > (EMU_CBMAXDATASIZE - 0x20) / 4) {
		res = T32_COM_PARA_FAIL;
		goto returnlabel;
	}
	outbits[lenbytes++] = 0x91;
	outbits[lenbytes++] = (unsigned char) T32_DIRECTACCESS_INSTANCETYPE_I2C;
	outbits[lenbytes++] = nInstance & 0xFF;
	outbits[lenbytes++] = (nInstance >> 8) & 0xff;

	outbits[lenbytes++] = 1;    /* command */

	outbits[lenbytes++] = (uint8_t) (len >> 0);
	outbits[lenbytes++] = (uint8_t) (len >> 8);
	outbits[lenbytes++] = (uint8_t) (len >> 16);
	outbits[lenbytes++] = (uint8_t) (len >> 24);
	for (i = 0; i < len; i++) {
		d = send[i];
		outbits[lenbytes++] = (uint8_t) (d >> 0);
		outbits[lenbytes++] = (uint8_t) (d >> 8);
		outbits[lenbytes++] = (uint8_t) (d >> 16);
		outbits[lenbytes++] = (uint8_t) (d >> 24);
	}

	if (Handle > T32_TAPACCESS_HOLD) {
		res = T32_BundledAccessStore(12, Handle, lenbytes * 8, outbits, (uint8_t *) recv, lenbytes * 8,
					 T32_PARAM_TYPE_UINT32);
	} else {
		res = T32_BundledAccess(12, Handle, lenbytes * 8, outbits, (uint8_t *) recv, lenbytes * 8,
				T32_PARAM_TYPE_UINT32);
	}
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}


int T32_DirectAccessUserSignal(T32_BUNDLEDACCESS_HANDLE Handle, int NumberOfAccesses,
	   const uint32_t * pOutAccesses, uint32_t * pInAccesses)
{
	unsigned char   outbits[EMU_CBMAXDATASIZE];
	int             lenbytes = 0;
	int             i;
	int             res = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %d, (uint32_t*) p%x, (uint32_t*) p%x", Handle,
			   NumberOfAccesses, pOutAccesses, pInAccesses);

	outbits[lenbytes++] = 0x93;
	outbits[lenbytes++] = 0x0;
	outbits[lenbytes++] = NumberOfAccesses & 0xFF;
	outbits[lenbytes++] = (NumberOfAccesses >> 8) & 0xff;
	outbits[lenbytes++] = (NumberOfAccesses >> 16) & 0xff;
	outbits[lenbytes++] = (NumberOfAccesses >> 24) & 0xff;
	for (i = 0; i < NumberOfAccesses; ++i) {
		outbits[lenbytes++] = pOutAccesses[i] & 0xFF;
		outbits[lenbytes++] = (pOutAccesses[i] >> 8) & 0xFF;
		outbits[lenbytes++] = (pOutAccesses[i] >> 16) & 0xff;
		outbits[lenbytes++] = (pOutAccesses[i] >> 24) & 0xff;
	}
	if (Handle > T32_TAPACCESS_HOLD) {
		res = T32_BundledAccessStore(12, Handle, lenbytes * 8, outbits, (uint8_t *) (void *) pInAccesses,
					 (pInAccesses) ? (NumberOfAccesses * 4 * 8) : 0, T32_PARAM_TYPE_UINT32);
	} else {
		res = T32_BundledAccess(12, Handle, lenbytes * 8, outbits, (uint8_t *) (void *) pInAccesses,
				(pInAccesses) ? (NumberOfAccesses * 4 * 8) : 0, T32_PARAM_TYPE_UINT32);
	}
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}

int T32_DAPAccessInitSWD(T32_BUNDLEDACCESS_HANDLE Handle, unsigned int nDapInstance)
{
	unsigned char   outbits[255];
	int             lenbytes = 0;
	int             res;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %u", Handle, nDapInstance);

	outbits[lenbytes++] = 0x91;
	outbits[lenbytes++] = T32_DIRECTACCESS_INSTANCETYPE_DAP;
	outbits[lenbytes++] = nDapInstance & 0xFF;
	outbits[lenbytes++] = (nDapInstance >> 8) & 0xff;
	outbits[lenbytes++] = 2;    /* command */
	if (Handle > T32_TAPACCESS_HOLD)
		res = T32_BundledAccessStore(12, Handle, lenbytes * 8, outbits, NULL, 0, T32_PARAM_TYPE_UINT32);
	else
		res = T32_BundledAccess(12, Handle, lenbytes * 8, outbits, NULL, 0, T32_PARAM_TYPE_UINT8);

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}

int T32_DAPAccessScan(T32_BUNDLEDACCESS_HANDLE Handle, unsigned int nDapInstance,
	  int nRegisterSet /*T32_DAPACCESS_REGISTERSET_ */ ,
	  int nRW /*T32_DAPACCESS_RW_ */ ,
	  uint32_t nRegisterAddress, uint32_t nDataIn, uint32_t * pDataOut)
{
	unsigned char   outbits[255];
	unsigned char   inbits[4];
	int             lenbytes = 0;
	int             res;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %u, %d, %d, %u, %u, (uint32_t*) p%x", Handle, nDapInstance,
			   nRegisterSet, nRW, nRegisterAddress, nDataIn, pDataOut);

	outbits[lenbytes++] = 0x91;
	outbits[lenbytes++] = T32_DIRECTACCESS_INSTANCETYPE_DAP;
	outbits[lenbytes++] = nDapInstance & 0xFF;
	outbits[lenbytes++] = (nDapInstance >> 8) & 0xff;
	outbits[lenbytes++] = (pDataOut) ? 1 : 0;   /* command */
	outbits[lenbytes++] = nRegisterSet & 0xFF;
	outbits[lenbytes++] = nRW & 0xFF;
	outbits[lenbytes++] = nRegisterAddress & 0xFF;
	outbits[lenbytes++] = (nRegisterAddress >> 8) & 0xFF;
	outbits[lenbytes++] = (nRegisterAddress >> 16) & 0xFF;
	outbits[lenbytes++] = (nRegisterAddress >> 24) & 0xFF;
	outbits[lenbytes++] = nDataIn & 0xFF;
	outbits[lenbytes++] = (nDataIn >> 8) & 0xFF;
	outbits[lenbytes++] = (nDataIn >> 16) & 0xFF;
	outbits[lenbytes++] = (nDataIn >> 24) & 0xFF;

	if (Handle > T32_TAPACCESS_HOLD) {
		res = T32_BundledAccessStore(12, Handle, lenbytes * 8, outbits, (uint8_t *) (void *) pDataOut,
						 (pDataOut) ? 4 * 8 : 0, T32_PARAM_TYPE_UINT32);
	} else {
		res = T32_BundledAccess(12, Handle, lenbytes * 8, outbits, (pDataOut) ? inbits : NULL, (pDataOut) ? 4 * 8 : 0,
					T32_PARAM_TYPE_UINT8);
		if (pDataOut)
			*pDataOut = (uint32_t) inbits[0] + ((uint32_t) inbits[1] << 8)
				+ ((uint32_t) inbits[2] << 16) + ((uint32_t) inbits[3] << 24);
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}


int T32_DAPAPAccessReadWrite(T32_BUNDLEDACCESS_HANDLE Handle, int nAPType /*T32_DIRECTACCESS_INSTANCETYPE */ ,
	 unsigned int nInstance, int nRW /*T32_DAPAPACCESS_RW_ */ ,
	 uint64_t nAddress, uint8_t * pData, unsigned int nByteWidth,
	 unsigned int nByteSize, int bNonIncrement, uint32_t nFlags)
{
	unsigned char   outbits[EMU_CBMAXDATASIZE];
	int             lenbytes = 0;
	int             res;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %d, %u, %d, %llu, (uint8_t*) p%x, %u, %u, %d, %u", Handle,
			   nAPType, nInstance, nRW, nAddress, pData, nByteWidth, nByteSize, bNonIncrement, nFlags);

	if (!nByteSize || !pData) {
		res = 0;
		goto returnlabel;
	}
	outbits[lenbytes++] = 0x91;
	outbits[lenbytes++] = (unsigned char) nAPType;
	outbits[lenbytes++] = nInstance & 0xFF;
	outbits[lenbytes++] = (nInstance >> 8) & 0xff;
	if (nRW == T32_DAPAPACCESS_RW_READ)
		outbits[lenbytes++] = 0;        /* command */
	else
		outbits[lenbytes++] = 1;        /* command */
	outbits[lenbytes++] = nAddress & 0xFF;
	outbits[lenbytes++] = (nAddress >> 8) & 0xFF;
	outbits[lenbytes++] = (nAddress >> (8 * 2)) & 0xFF;
	outbits[lenbytes++] = (nAddress >> (8 * 3)) & 0xFF;
	outbits[lenbytes++] = (nAddress >> (8 * 4)) & 0xFF;
	outbits[lenbytes++] = (nAddress >> (8 * 5)) & 0xFF;
	outbits[lenbytes++] = (nAddress >> (8 * 6)) & 0xFF;
	outbits[lenbytes++] = (nAddress >> (8 * 7)) & 0xFF;
	outbits[lenbytes++] = nByteWidth & 0xFF;
	outbits[lenbytes++] = nByteSize & 0xFF;
	outbits[lenbytes++] = (nByteSize >> 8) & 0xFF;
	outbits[lenbytes++] = (bNonIncrement) ? 1 : 0;
	outbits[lenbytes++] = nFlags & 0xFF;
	outbits[lenbytes++] = (nFlags >> 8) & 0xFF;
	outbits[lenbytes++] = (nFlags >> (8 * 2)) & 0xFF;
	outbits[lenbytes++] = (nFlags >> (8 * 3)) & 0xFF;
	if (nByteSize + lenbytes > EMU_CBMAXDATASIZE) {
		res = T32_Errno = T32_COM_PARA_FAIL;
		goto returnlabel;
	}
	if (nRW == T32_DAPAPACCESS_RW_WRITE)
		memcpy(outbits + lenbytes, pData, nByteSize);
	else
		memset(outbits + lenbytes, 0xAA, nByteSize);
	lenbytes += nByteSize;
	if (Handle > T32_TAPACCESS_HOLD) {
		res = T32_BundledAccessStore(12, Handle, lenbytes * 8, outbits,
					 (nRW == T32_DAPAPACCESS_RW_READ) ? pData : NULL,
					 (nRW == T32_DAPAPACCESS_RW_READ) ? nByteSize * 8 : 0, T32_PARAM_TYPE_UINT8);
	} else {
		res = T32_BundledAccess(12, Handle, lenbytes * 8, outbits,
				(nRW == T32_DAPAPACCESS_RW_READ) ? pData : NULL,
				(nRW == T32_DAPAPACCESS_RW_READ) ? nByteSize * 8 : 0, T32_PARAM_TYPE_UINT8);
	}
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}

T32_Param T32_ParamFromUint32(uint32_t value)
{
	T32_Param       res;
	res.uint32 = value;
	return res;
}

#define SHIFTRAW_OPTION_INTERNAL_TMS     0x0001
#define SHIFTRAW_OPTION_INTERNAL_TDI     0x0002
#define SHIFTRAW_OPTION_INTERNAL_TDO     0x0004
#define SHIFTRAW_OPTION_INTERNAL_ALL     0x0007


int T32_TAPAccessShiftRaw(T32_BUNDLEDACCESS_HANDLE Handle, int NumberOfBits,
	  const uint8_t * pTMSBits, const uint8_t * pTDIBits, uint8_t * pTDOBits, int Options)
{
	int             usedbytes = 0;
	unsigned char  *poutbuffer;
	unsigned char  *poutptr;
	int             nDataByteSize = 0;
	int             res = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %d, (uint8_t*) p%x, (uint8_t*) p%x, (uint8_t*) p%x, %d",
			   Handle, NumberOfBits, pTMSBits, pTDIBits, pTDOBits, Options);

	if (!NumberOfBits) {
		res = T32_Errno = 0;
		goto returnlabel;
	}

	nDataByteSize = (NumberOfBits + 7) / 8;

	/* allocate twice the size - if TMS and TDI are given we need the double buffer size */
	poutbuffer = (unsigned char *) malloc(nDataByteSize * 2 + 10);
	if (poutbuffer == NULL) {
		res = T32_MALLOC_FAIL;
		goto returnlabel;
	}

	poutptr = poutbuffer;

	poutbuffer[0] = 0x90;       /* EMUMCI CMD Special Shift - see targetsystemtools.cpp */
	poutbuffer[1] = 0x00;       /* EMUMCI CMD Special Shift sub function 0x0 */

	/* setup options */
	Options &= ~SHIFTRAW_OPTION_INTERNAL_ALL;
	if (pTMSBits)
		Options |= SHIFTRAW_OPTION_INTERNAL_TMS;
	if (pTDIBits)
		Options |= SHIFTRAW_OPTION_INTERNAL_TDI;
	if (pTDOBits)
		Options |= SHIFTRAW_OPTION_INTERNAL_TDO;

	poutbuffer[2] = Options & 0xFF;
	poutbuffer[3] = (Options >> 8) & 0xFF;
	/* store bitlength */
	poutbuffer[4] = NumberOfBits & 0xff;
	poutbuffer[5] = (NumberOfBits >> 8) & 0xff;
	poutbuffer[6] = (NumberOfBits >> 16) & 0xff;
	poutbuffer[7] = (NumberOfBits >> 24) & 0xff;
	usedbytes += 8;
	poutptr = poutbuffer + 8;

	if (pTMSBits) {
		memcpy(poutptr, pTMSBits, nDataByteSize);
		poutptr += nDataByteSize;
		usedbytes += nDataByteSize;
	}
	if (pTDIBits) {
		memcpy(poutptr, pTDIBits, nDataByteSize);
		poutptr += nDataByteSize;
		usedbytes += nDataByteSize;
	}
	if (pTDOBits && !pTMSBits && !pTDIBits)
		usedbytes += nDataByteSize;

	if (usedbytes > EMU_CBMAXDATASIZE) {
		free(poutbuffer);
		res = T32_Errno = T32_COM_PARA_FAIL;
		goto returnlabel;
	}

	if (Handle > T32_TAPACCESS_HOLD) {
		T32_Errno = T32_BundledAccessStore(12, Handle, usedbytes * 8, poutbuffer,
					   pTDOBits, ((pTDOBits) ? NumberOfBits : 0), T32_PARAM_TYPE_UINT8);
	} else {
		T32_Errno = T32_BundledAccess(12, Handle, usedbytes * 8, poutbuffer, pTDOBits, ((pTDOBits) ? NumberOfBits : 0),
				  T32_PARAM_TYPE_UINT8);
	}
	free(poutbuffer);
	res = T32_Errno;
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}


int T32_TAPAccessShiftIR(T32_BUNDLEDACCESS_HANDLE Handle, int NumberOfBits, const uint8_t * pOutBits, uint8_t * pInBits)
{
	int             res = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %d, (uint8_t*) p%x, (uint8_t*) p%x", Handle, NumberOfBits,
			   pOutBits, pInBits);
	if (NumberOfBits > T32_TAPACCESS_MAXBITS) {
		res = T32_Errno = T32_COM_PARA_FAIL;
		goto returnlabel;
	}
	if (Handle > T32_TAPACCESS_HOLD)
		res = T32_BundledAccessStore(4, Handle, NumberOfBits, pOutBits, pInBits, NumberOfBits, T32_PARAM_TYPE_UINT8);
	else
		res = T32_BundledAccess(4, Handle, NumberOfBits, pOutBits, pInBits, NumberOfBits, T32_PARAM_TYPE_UINT8);
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}


int T32_TAPAccessShiftDR(T32_BUNDLEDACCESS_HANDLE Handle, int NumberOfBits, const uint8_t * pOutBits, uint8_t * pInBits)
{
	int             res = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %d, (uint8_t*) p%x, (uint8_t*) p%x", Handle, NumberOfBits,
			   pOutBits, pInBits);
	if (NumberOfBits > T32_TAPACCESS_MAXBITS) {
		res = T32_Errno = T32_COM_PARA_FAIL;
		goto returnlabel;
	}
	if (Handle > T32_TAPACCESS_HOLD)
		res = T32_BundledAccessStore(8, Handle, NumberOfBits, pOutBits, pInBits, NumberOfBits, T32_PARAM_TYPE_UINT8);
	else
		res = T32_BundledAccess(8, Handle, NumberOfBits, pOutBits, pInBits, NumberOfBits, T32_PARAM_TYPE_UINT8);
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}


int T32_TAPAccessDirect(T32_BUNDLEDACCESS_HANDLE Handle, int NumberOfBytes, const uint8_t * pOutBytes, uint8_t * pInBytes)
{
	int             res = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, %d, (uint8_t*) p%x, (uint8_t*) p%x", Handle, NumberOfBytes,
			   pOutBytes, pInBytes);
	if (pOutBytes == NULL && pInBytes == NULL) {
		res = T32_Errno = T32_COM_PARA_FAIL;
		goto returnlabel;
	}
	if (NumberOfBytes > EMU_CBMAXDATASIZE) {
		res = T32_Errno = T32_COM_PARA_FAIL;
		goto returnlabel;
	}
	if (Handle > T32_TAPACCESS_HOLD) {
		res = T32_BundledAccessStore(12, Handle, NumberOfBytes * 8, pOutBytes, pInBytes,
					 (pInBytes) ? (NumberOfBytes * 8) : 0, T32_PARAM_TYPE_UINT8);
	} else {
		res = T32_BundledAccess(12, Handle, NumberOfBytes * 8, pOutBytes, pInBytes,
				(pInBytes) ? (NumberOfBytes * 8) : 0, T32_PARAM_TYPE_UINT8);
	}
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}


int T32_DirectAccessRelease(void)
{
	int             res;
	T32_ApiLog(__func__, T32APILOG_FENTRY, NULL);
	res = T32_BundledAccess(0, T32_TAPACCESS_RELEASE, -1, NULL, NULL, 0, T32_PARAM_TYPE_UINT8);
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}

/* Lua execution API */
/*
 * mode: bit 0: 0-> do not execute the lua script, 1->execute the lua script
 *       bit 1: 0-> do not replace the script if exist, 1->replace the script if exist
 *              bit 2: 0-> do not try to load the script to the target (executes only if it exists already), 1->load the script to target
 */
int T32_ExecuteLua(const char *filename, int mode, const uint8_t * inputBuf, int inputBufLen, uint8_t * outputBuf,
	   int outputBufLen)
{
	unsigned char  *ptr;
	int             filenameLen, inputsize;
	int             retlen;
	uint8_t        *retval;
	int             res = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(char*) p%x, %d, (uint8_t*) p%x, %d, (uint8_t*) p%x, %d", filename, mode,
			   inputBuf, inputBufLen, outputBuf, outputBufLen);

	filenameLen = (int) strlen(filename);

	T32_OUTBUFFER[0] = 0;
	T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
	T32_OUTBUFFER[2] = RAPI_DSCMD_LUA_EXECUTE;  /* T32 Lua */
	T32_OUTBUFFER[3] = LINE_GetNextMessageId();
	T32_OUTBUFFER[4] = filenameLen & 0xff;
	T32_OUTBUFFER[5] = (filenameLen >> 8) & 0xff;
	T32_OUTBUFFER[6] = inputBufLen & 0xff;
	T32_OUTBUFFER[7] = (inputBufLen >> 8) & 0xff;
	T32_OUTBUFFER[8] = outputBufLen & 0xff;
	T32_OUTBUFFER[9] = (outputBufLen >> 8) & 0xff;
	T32_OUTBUFFER[10] = mode & 0xff;

	ptr = T32_OUTBUFFER + 12;
	inputsize = 12 + filenameLen + inputBufLen;

	if (filenameLen > 512 || inputsize > EMU_CBMAXDATASIZE) {
		res = T32_Errno = T32_COM_PARA_FAIL;
		goto returnlabel;
	}
	retval = T32_INBUFFER + 4;
	if (outputBufLen + (retval - T32_INBUFFER) > EMU_CBMAXDATASIZE) {
		res = T32_Errno = T32_COM_PARA_FAIL;
		goto returnlabel;
	}
	memcpy(ptr, filename, filenameLen);
	ptr += filenameLen;
	if (inputBuf)
		memcpy(ptr, inputBuf, inputBufLen);

	if (LINE_Transmit(inputsize) == -1) {
		res = T32_Errno = T32_COM_TRANSMIT_FAIL;
		goto returnlabel;
	}

	if ((retlen = LINE_Receive()) == -1) {
		res = T32_Errno = T32_COM_RECEIVE_FAIL;
		goto returnlabel;
	}

	T32_Errno = T32_INBUFFER[2];
	if (outputBuf)
		memcpy(outputBuf, retval, outputBufLen);
	res = T32_OK;
returnlabel:
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}

/* Execute Lua with given label in the context of direct access API */
/*
 * mode: bit 0: 0-> do not execute the lua script, 1->execute the lua script
 *       bit 1: 0-> do not replace the script if exist, 1->replace the script if exist
 *              bit 2: 0-> do not try to load the script to the target (executes only if it exists already), 1->load the script to target
 */
T32EXTERN int T32_DirectAccessExecuteLua(T32_BUNDLEDACCESS_HANDLE Handle, const char *filename, int mode,
	 const uint8_t * inputBuf, int inputBufLen, uint8_t * outputBuf,
	 int outputBufLen)
{
	unsigned char   outbits[EMU_CBMAXDATASIZE];
	int             lenbytes = 0;
	FILE           *fp = NULL;
	int             res = 0;
	int             filenamelen, filesize = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "(void*) p%x, (char*) p%x, %d, (uint8_t*) p%x, %d, (uint8_t*) p%x, %d",
			   Handle, filename, mode, inputBuf, inputBufLen, outputBuf, outputBufLen);

	outbits[lenbytes++] = 0x94; /* command */
	outbits[lenbytes++] = (unsigned char) mode; /* subcommand */
	filenamelen = (int) strlen(filename);
	outbits[lenbytes++] = filenamelen & 0xFF;
	outbits[lenbytes++] = (filenamelen >> 8) & 0xFF;
	outbits[lenbytes++] = (filenamelen >> 16) & 0xff;
	outbits[lenbytes++] = (filenamelen >> 24) & 0xff;
	outbits[lenbytes++] = inputBufLen & 0xFF;
	outbits[lenbytes++] = (inputBufLen >> 8) & 0xFF;
	outbits[lenbytes++] = (inputBufLen >> 16) & 0xff;
	outbits[lenbytes++] = (inputBufLen >> 24) & 0xff;
	if (mode & 0x4) {
		fp = fopen(filename, "rb");
		if (fp != NULL) {
			fseek(fp, 0L, SEEK_END);
			filesize = ftell(fp);
		} else {
			filesize = 0;
		}
		outbits[lenbytes++] = filesize & 0xFF;
		outbits[lenbytes++] = (filesize >> 8) & 0xFF;
		outbits[lenbytes++] = (filesize >> 16) & 0xff;
		outbits[lenbytes++] = (filesize >> 24) & 0xff;
	}
	if (filenamelen > 0 && (lenbytes + filenamelen < EMU_CBMAXDATASIZE) && filename)
		memcpy(&outbits[lenbytes], filename, filenamelen);
	lenbytes += filenamelen;
	if (inputBuf && (lenbytes + inputBufLen < EMU_CBMAXDATASIZE))
		memcpy(&outbits[lenbytes], inputBuf, inputBufLen);
	lenbytes += inputBufLen;
	if (mode & 0x4 && fp && (lenbytes + filesize < EMU_CBMAXDATASIZE)) {
		fseek(fp, 0L, SEEK_SET);
		fread(&outbits[lenbytes], 1, filesize, fp);
		lenbytes += filesize;
	}
	if (fp)
		fclose(fp);
	if (Handle > T32_TAPACCESS_HOLD)
		res = T32_BundledAccessStore(12, Handle, lenbytes * 8, outbits, outputBuf, outputBufLen, T32_PARAM_TYPE_UINT8);
	else
		res = T32_BundledAccess(12, Handle, lenbytes * 8, outbits, outputBuf, outputBufLen, T32_PARAM_TYPE_UINT8);
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", res);
	return res;
}

int T32_Config(const char *String1, const char *String2)
{
	int             err = 0;
	char            configline[256];
	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\", \"%s\"", String1, String2);
	strcpy(configline, String1);
	strcat(configline, String2);
	if (LINE_LineConfig(configline) == -1)
		err = -1;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

/** Exit all drivers. */
int T32_Exit(void)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);
	LINE_LineExit();
	releaseAllObjects();
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	T32_CloseApiLogFile();
	return 0;
}

#ifdef ENABLE_NOTIFICATION

typedef struct T32_NotificationEvent_s {
	struct T32_NotificationEvent_s *next;       /* event list */
	T32_NotificationCallback_t function;        /* notification function */
	char            name[1];    /* event name */
} T32_NotificationEvent_t;

static T32_THREADLOCAL T32_NotificationEvent_t *eventlist = NULL;


/** T32_Notify StateEnable - enables notifications regarding state changes in T32.

	Register callback function to get event notifications for state changes in T32 or target.

   @param eventNr: T32_E_BREAK,
		   T32_E_EDIT,
		   T32_E_BREAKPOINTCONFIG

   @param  func    callback function connected to this event

   @return 0 : OK, else error number

   @note currently there is not way to deregister events.
 */
static T32_THREADLOCAL int T32_EventMask = 0;
static T32_THREADLOCAL T32_NotificationCallback_t notificationCallback[T32_MAX_EVENTS];
int T32_NotifyStateEnable(int EventNumber, T32_NotificationCallback_t pFunction)
{
	int             err = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d, p%x", EventNumber, pFunction);

	if (EventNumber >= T32_MAX_EVENTS)
		err = T32_Errno = T32_MAX_EVENT_FAIL;

	if (!err) {
		T32_EventMask |= 1 << EventNumber;

		if (EventNumber == T32_E_EDIT) {
			/* device independent -> win/main.c */
			T32_OUTBUFFER[0] = 4;
			T32_OUTBUFFER[1] = RAPI_CMD_EDITNOTIFY;
			T32_OUTBUFFER[2] = 0x0;
			T32_OUTBUFFER[3] = LINE_GetNextMessageId();
			T32_OUTBUFFER[4] = 0x01;    /* bit 0 set == enable */
			T32_OUTBUFFER[5] = 0x00;    /* high byte */
		} else {
			/* device dependent -> debug/comemu12.c */
			T32_OUTBUFFER[0] = 4;
			T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
			T32_OUTBUFFER[2] = RAPI_DSCMD_STATE_SETNOTIFIER; /* -> T32_NotifyStateEnable */
			T32_OUTBUFFER[3] = LINE_GetNextMessageId();
			T32_OUTBUFFER[4] = T32_EventMask;
			T32_OUTBUFFER[5] = 0;       /* padding for even byte count */
		}

		if (LINE_Transmit(6) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	notificationCallback[EventNumber] = pFunction;      /* update pointer in case of success only */

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}

/** T32_CheckStateNotify -  Check socket for all pending notification
	messages and invoke callback functions if required for each of them.

	@param  ParameterOfCallbackFunction Parameter to give to the Event Callback

	@return int  OK=0 or Number of Error (<0)
*/
typedef void    (*T32_NotificationCallback_i_t) (int);
typedef void    (*T32_NotificationCallback_iqq_t) (int, uint64_t, uint64_t);
typedef void    (*T32_NotificationCallback_iicp_t) (int, int, unsigned char *);
typedef void    (*T32_NotificationCallback_iqqq_t) (int, uint64_t, uint64_t, uint64_t);

int T32_CheckStateNotify(unsigned ParameterOfCallbackFunction)
{
	unsigned char                   package[T32_PCKLEN_MAX];
	int                             notifyid;
	static T32_THREADLOCAL int      inFunction = 0;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "%d", ParameterOfCallbackFunction);

	/* notification handler may cause another notification -
	   block against recursive call */

	if (inFunction) {
		T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
		return 0;
	}
	inFunction = 1;

	/* Check if there is a pending notification message */
	notifyid = LINE_ReceiveNotifyMessage(package);

	/* process all received notifications */
	while (notifyid != -1) {
		switch (notifyid) {
		case T32_E_BREAK:
			if (notificationCallback[T32_E_BREAK]) {
				int             off = 16;
				uint32_t        low, high;
				uint64_t        pc, reason;
				SETLONGVAR(low, package[off]);
				SETLONGVAR(high, package[off + 4]);
				pc = ((uint64_t) low) | (((uint64_t) high) << 32);
				SETLONGVAR(low, package[off + 8]);
				SETLONGVAR(high, package[off + 12]);
				reason = ((uint64_t) low) | (((uint64_t) high) << 32);
				((T32_NotificationCallback_iqq_t) notificationCallback[T32_E_BREAK]) (ParameterOfCallbackFunction, pc, reason);
			}
			break;

		case T32_E_EDIT:
			if (notificationCallback[T32_E_EDIT]) {
				int             off = 16;
				uint32_t        lineNr;
				unsigned char  *fileName = package + 20;
				SETLONGVAR(lineNr, package[off]);
				((T32_NotificationCallback_iicp_t) notificationCallback[T32_E_EDIT]) (ParameterOfCallbackFunction, (int) lineNr, fileName);
			}
			break;


		case T32_E_BREAKPOINTCONFIG:
			if (notificationCallback[T32_E_BREAKPOINTCONFIG]) {
				((T32_NotificationCallback_i_t) notificationCallback[T32_E_BREAKPOINTCONFIG]) (ParameterOfCallbackFunction);
			}
			break;

		case T32_E_ONEVENT:
			{
				T32_NotificationEvent_t *event_c = eventlist;
				char           *event = (char *) package + 16;
				while (event_c) {
					if (!strcmp(event_c->name, event)) {
						(event_c->function) (ParameterOfCallbackFunction);
						break;
					}
					event_c = event_c->next;
				}
			}
			break;

		case T32_E_RTSTRIGGER:
			if (notificationCallback[T32_E_RTSTRIGGER]) {
				int             off = 16;
				uint32_t        low, high;
				uint64_t        time, code, param;
				SETLONGVAR(low, package[off]);
				SETLONGVAR(high, package[off + 4]);
				time = ((uint64_t) low) | (((uint64_t) high) << 32);
				SETLONGVAR(low, package[off + 8]);
				SETLONGVAR(high, package[off + 12]);
				code = ((uint64_t) low) | (((uint64_t) high) << 32);
				SETLONGVAR(low, package[off + 16]);
				SETLONGVAR(high, package[off + 20]);
				param = ((uint64_t) low) | (((uint64_t) high) << 32);
				((T32_NotificationCallback_iqqq_t) notificationCallback[T32_E_RTSTRIGGER]) (ParameterOfCallbackFunction, time, code, param);
			}
			break;

		case T32_E_ERROR:
			if (notificationCallback[T32_E_ERROR]) {
				int             off = 16;
				int             code =  package[off];
				unsigned char  *message = package + 20;
				((T32_NotificationCallback_iicp_t) notificationCallback[T32_E_ERROR]) (ParameterOfCallbackFunction, code, message);
			}
			break;
		}

		notifyid = LINE_ReceiveNotifyMessage(package);
	}

	inFunction = 0;
	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", 0);
	return 0;
}


/** T32_NotifyEventEnable - enables notifications regarding ON events in TRACE32.

	Register callback function to get event notifications for ON events in TRACE32 or target.
	See also "ON" command in TRACE32 general command reference.

   @param  event    event name as available with the "ON" command
   @param  func     callback function connected to this event, NULL for unregister
   @return 0 : OK, else error number

   @note currently there is not way to deregister events.
 */
int T32_NotifyEventEnable(const char *event, T32_NotificationCallback_t pFunction)
{
	int             err = 0, len;

	T32_ApiLog(__func__, T32APILOG_FENTRY, "\"%s\", p%x", event, pFunction);

	len = (int) strlen(event);
	if ((len + 6) > 0xff)
		err = T32_Errno = T32_COM_PARA_FAIL;

	if (!err) {
		T32_OUTBUFFER[0] = (unsigned char) (len + 6);
		T32_OUTBUFFER[1] = RAPI_CMD_DEVICE_SPECIFIC;
		T32_OUTBUFFER[2] = RAPI_DSCMD_EVENT_SETNOTIFIER;        /* -> T32_NotifyEventEnable */
		T32_OUTBUFFER[3] = LINE_GetNextMessageId();
		if (pFunction)
			T32_OUTBUFFER[4] = 1;
		else
			T32_OUTBUFFER[4] = 0;
		T32_OUTBUFFER[5] = 0;
		strcpy((char *) (T32_OUTBUFFER + 6), event);
		T32_OUTBUFFER[6 + len] = 0;

		if (LINE_Transmit((6 + len + 1 + 1) & (~1)) == -1)
			err = T32_Errno = T32_COM_TRANSMIT_FAIL;
	}

	if (!err && (LINE_Receive() == -1))
		err = T32_Errno = T32_COM_RECEIVE_FAIL;

	if (!err) {
		T32_NotificationEvent_t *event_c = eventlist;
		T32_NotificationEvent_t *event_p = NULL;
		while (event_c) {
			if (!strcmp(event_c->name, event)) {
				if (pFunction) {
					event_c->function = pFunction;
				} else {
					if (event_p)
						event_p->next = event_c->next;
					else
						eventlist = event_c->next;
					free(event_c);
				}
				break;
			}
			event_p = event_c;
			event_c = event_c->next;
		}
		if (!event_c) {
			event_c = malloc(sizeof(T32_NotificationEvent_t) + strlen(event));
			event_c->function = pFunction;
			strcpy(event_c->name, event);
			event_c->next = NULL;
			if (!eventlist)
				eventlist = event_c;
			else
				event_p->next = event_c;
		}
	}

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


#endif   /*ENABLE_NOTIFICATION */


int T32_Init(void)
{
	int             err = 0;
	char            errorline[256];

#if defined(ENABLE_APILOG)
	{
		char            envvar[4000] = "";

# ifdef _WIN32
		GetEnvironmentVariable("T32APILOGFILE", envvar, 4000);
# else
		{
			char           *envptr = NULL;
			envptr = getenv("T32APILOGFILE");
			if (envptr)
				strcpy(envvar, envptr);
		}
# endif

		if (envvar[0])
			T32_OpenApiLogFile(envvar);
	}
#endif

	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);

	if (LINE_LineInit(errorline) == -1)
		err = -1;

	if (!err) {
		LINE_SetReceiveToggleBit(-1);

		if (LINE_Sync() == -1)
			err = -1;
	}
#ifdef ENABLE_NOTIFICATION
	{
		int             i;
		for (i = 0; i < T32_MAX_EVENTS; i++)
			notificationCallback[i] = 0;
	}
#endif   /*ENABLE_NOTIFICATION */

	T32_ApiLog(__func__, T32APILOG_FEXIT, "%d", err);
	return err;
}


/** Get socket handle of TRACE32 remote connection.

	@param t32soc int pointer (for socket handle)
*/

void T32_GetSocketHandle(int *t32soc)
{
	T32_ApiLog(__func__, T32APILOG_FENTRY, 0);
	*t32soc = LINE_LineDriverGetSocket();
	T32_ApiLog(__func__, T32APILOG_FEXIT, 0);
}


/**************************************************************************

 network layer
 transport layer

***************************************************************************/

/** Sends message with payload contained in T32_OUTBUFFER[0...len-1].
	Adds the (empty) message header and calls LINE_LineTransmit.
 */
int LINE_Transmit(int len)
{
	int             LastTransmitLen = 0;

	if (len)
		LastTransmitLen = len + 4 + 1;

	T32_OUTBUFFER[-5] = 0;      /* message header */

	T32_OUTBUFFER[-4] = 0;
	T32_OUTBUFFER[-3] = 0;
	T32_OUTBUFFER[-2] = 0;
	T32_OUTBUFFER[-1] = 0;

	if (LINE_LineTransmit(T32_OUTBUFFER - 5, LastTransmitLen) == -1) {
		T32_Errno = T32_COM_TRANSMIT_FAIL;
		return -1;
	}
	return 0;
}


int LINE_Receive(void)
{
	int             len;
	int             retry;

	for (retry = 0; retry < MAXRETRY; retry++) {
		len = LINE_LineReceive(T32_INBUFFER - 1);
		if (len == -1) {
			T32_Errno = T32_COM_RECEIVE_FAIL;
			return -1;
		}
		if (T32_INBUFFER[2] == 0xfe) {
			retry = 0;
			LINE_SetReceiveToggleBit(-1);
			continue;
		}
		if (T32_INBUFFER[3] != LINE_GetMessageId())
			continue;

		if (T32_INBUFFER[-1] & T32_MSG_LRETRY) {
			if (LINE_GetReceiveToggleBit() == (! !(T32_INBUFFER[-1] & T32_MSG_LHANDLE))) {
				if (LINE_Transmit(0) == -1)
					LINE_Sync();
				continue;
			}
		}
		LINE_SetReceiveToggleBit(! !(T32_INBUFFER[-1] & T32_MSG_LHANDLE));

		return len - 1;
	}

	T32_Errno = T32_COM_RECEIVE_FAIL;
	return -1;
}


int LINE_Sync(void)
{
	int             retry = MAXRETRY;
	while (--retry > 0) {
		if (LINE_LineSync() != -1)
			return 0;
	}
	return -1;
}


/* *INDENT-OFF* */
#endif   /* !(HREMOTE_DEFINITIONS_ONLY) */

