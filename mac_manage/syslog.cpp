#include "stdafx.h"
#include "syslog.h"
#include "Winsock2.h"

#define MAX_LOG_BUF	4096
static int log_mask = SDK_LOG_LEVEL_2;



#define DEFAULT_SYSLOG_PORT 514


struct sockaddr_in  m_sockaddr_send_syslog = {0};

char *syslogForwardIp = "127.0.0.1";
SOCKET sock_send = INVALID_SOCKET;

int log_level ( int level )
{
    static const unsigned mask[SDK_LOG_LEVEL_MAX+1] =
    {
        SDK_LOG_LEVEL_0,
        SDK_LOG_LEVEL_1,
        SDK_LOG_LEVEL_2,
        SDK_LOG_LEVEL_3,
        SDK_LOG_LEVEL_4,
        SDK_LOG_LEVEL_5,
        SDK_LOG_LEVEL_6,
        SDK_LOG_LEVEL_7
    };

    if ( level <= SDK_LOG_LEVEL_MAX )
        log_mask = mask[level];
    return 0;
}


int initSyslog()
{
    int err;
    WORD wVersionRequested;
    WSADATA wsaData;
    int nNetTimeout = 200;

    wVersionRequested = MAKEWORD ( 2, 2 );

    err = WSAStartup ( wVersionRequested, &wsaData );
    if ( err != 0 )
    {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        return -1;
    }

    /* Confirm that the WinSock DLL supports 2.2.*/
    /* Note that if the DLL supports versions greater    */
    /* than 2.2 in addition to 2.2, it will still return */
    /* 2.2 in wVersion since that is the version we      */
    /* requested.                                        */

    if ( LOBYTE ( wsaData.wVersion ) != 2 ||
            HIBYTE ( wsaData.wVersion ) != 2 )
    {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        WSACleanup( );
        return -1;
    }

    //syslog信息的socket
    sock_send = socket ( AF_INET, SOCK_DGRAM, 0 );
    if ( sock_send == INVALID_SOCKET )
        goto ERR;


    memset ( &m_sockaddr_send_syslog, 0, sizeof ( m_sockaddr_send_syslog ) );
    m_sockaddr_send_syslog.sin_family = AF_INET;
    m_sockaddr_send_syslog.sin_port = htons ( DEFAULT_SYSLOG_PORT );
    m_sockaddr_send_syslog.sin_addr.S_un.S_addr = inet_addr ( syslogForwardIp );

    return 0;

ERR:
    if ( sock_send != INVALID_SOCKET )
        closesocket ( sock_send );

    return -1;
}

//将TCHAR转为char
//*tchar是TCHAR类型指针，*_char是char类型指针
void TcharToChar (const TCHAR * tchar, char * _char)
{
    int iLength ;//获取字节长度
    iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
    //将tchar值赋给_char 
    WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL); 
}

int debugPrintf ( char* fmt, ... )
{
    va_list vaList;
    char buf[2048];
    char buffer[2048];
    SYSTEMTIME newtime;

    memset ( buf, 0, 2048 );

    va_start ( vaList, fmt );
    vsnprintf ( buf, 2000, fmt, vaList );
    va_end ( vaList );

    GetLocalTime ( &newtime );
    
    sprintf ( buffer, "[%02d - %02d:%02d:%02d.%03d] %s",
              newtime.wDay , newtime.wHour , newtime.wMinute , newtime.wSecond , newtime.wMilliseconds , buf );
    sendto ( sock_send, ( const char* ) buffer, strlen ( buffer ), 0, ( struct sockaddr* ) &m_sockaddr_send_syslog, sizeof ( struct sockaddr ) );

    return 0;
}



static int log_vprintf ( const char *fmt, va_list args )
{
    char buf[MAX_LOG_BUF];
    int ret;

    vsprintf ( buf, fmt, args );

    ret = debugPrintf ( buf );

    return ret;

}

int log_printf_w ( UINT32 mask, const wchar_t *fmt, ... )
{
    va_list args;
    int ret = 0;
    TCHAR wbuffer[2000];
    char  buffer[2000];
    if ( log_mask & mask )
    {
// for WCHAR TO CHAR
#if 1
#define vsnwprintf _vsnwprintf
        va_start ( args, fmt );
        vsnwprintf ( wbuffer, 2000, fmt, args );
        va_end ( args );
        TcharToChar(wbuffer, buffer);
        debugPrintf(buffer);
#else
        va_start ( args, fmt );
        ret = log_vprintf ( fmt, args );
        va_end ( args );
#endif

    }

    return ret;
}
int log_printf ( UINT32 mask, const char *fmt, ... )
{
    va_list args;
    int ret = 0;

    if ( log_mask & mask )
    {
        va_start ( args, fmt );
        ret = log_vprintf ( fmt, args );
        va_end ( args );
    }

    return ret;
}


