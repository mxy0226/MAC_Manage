#ifndef __SYSLOG_H__
#define __SYSLOG_H__
#pragma once

#include "stdafx.h"
#include <yvals.h>

#define SDK_FORCE			(1<<0)
#define SDK_ERR				(1<<1)
#define SDK_STD_ERR			(1<<2)
#define SDK_INFO			(1<<3)
#define SDK_DBG				(1<<4)
#define SDK_FUNC			(1<<5)

#define SDK_OUT_BIT			16
#define SDK_FORCE_OUT		(SDK_FORCE<<SDK_OUT_BIT)
#define SDK_ERR_OUT			(SDK_ERR<<SDK_OUT_BIT)
#define SDK_STD_ERR_OUT		(SDK_STD_ERR<<SDK_OUT_BIT)
#define SDK_INFO_OUT		(SDK_INFO<<SDK_OUT_BIT)
#define SDK_DBG_OUT			(SDK_DBG<<SDK_OUT_BIT)
#define SDK_FUNC_OUT		(SDK_FUNC<<SDK_OUT_BIT)

#define SDK_LOG_LEVEL_0		(SDK_FORCE|SDK_FORCE_OUT|SDK_ERR|SDK_STD_ERR)
#define SDK_LOG_LEVEL_1		(SDK_LOG_LEVEL_0|SDK_INFO)
#define SDK_LOG_LEVEL_2		(SDK_LOG_LEVEL_1|SDK_DBG)
#define SDK_LOG_LEVEL_3		(SDK_LOG_LEVEL_2|SDK_FUNC)
#define SDK_LOG_LEVEL_4		(SDK_LOG_LEVEL_3|SDK_ERR_OUT|SDK_STD_ERR_OUT)
#define SDK_LOG_LEVEL_5		(SDK_LOG_LEVEL_4|SDK_INFO_OUT)
#define SDK_LOG_LEVEL_6		(SDK_LOG_LEVEL_5|SDK_DBG_OUT)
#define SDK_LOG_LEVEL_7		(SDK_LOG_LEVEL_6|SDK_FUNC_OUT)
#define SDK_LOG_LEVEL_MAX	7

#define xprintf_w(mask, fmt, ...)	do {\
        if ((mask) & SDK_ERR)\
            log_printf_w(mask, L"#ERROR: in %s\n\t:" fmt L"\n",\
                       __FUNCTIONW__ , ##  __VA_ARGS__);\
        else if ((mask) & SDK_STD_ERR)\
            log_printf_w(mask, L"#ERROR: in %s, err=%d\n\t:" fmt L"\n",\
                       __FUNCTIONW__ , GetLastError(), ##  __VA_ARGS__);\
        else if ((mask) & SDK_INFO)\
            log_printf_w(mask, L"#INFO: %s(%d) " fmt L"\n" , __FUNCTIONW__  , __LINE__, ##  __VA_ARGS__);\
        else  if ((mask) & SDK_DBG)\
            log_printf_w(mask, L"#DBG: %s(%d) " fmt L"\n" , __FUNCTIONW__  , __LINE__, ##  __VA_ARGS__);\
        else\
            log_printf_w(mask, L"#FUNC: " fmt L"\n" , ##  __VA_ARGS__);\
    } while (0)

#define xprintf(mask, fmt, ...)	do {\
        if ((mask) & SDK_ERR)\
            log_printf(mask, "#ERROR: in %s\n\t:" fmt"\n",\
                       __FUNCTION__, ##  __VA_ARGS__);\
        else if ((mask) & SDK_STD_ERR)\
            log_printf(mask, "#ERROR: in %s, err=%d\n\t:" fmt"\n",\
                       __FUNCTION__, GetLastError(), ##  __VA_ARGS__);\
        else if ((mask) & SDK_INFO)\
            log_printf(mask, "#INFO: %s(%d) " fmt "\n" , __FUNCTION__ , __LINE__, ##  __VA_ARGS__);\
        else  if ((mask) & SDK_DBG)\
            log_printf(mask, "#DBG: %s(%d) " fmt "\n" , __FUNCTION__ , __LINE__, ##  __VA_ARGS__);\
        else\
            log_printf(mask, "#FUNC: " fmt "\n" , ##  __VA_ARGS__);\
    } while (0)

int initSyslog();
int log_level ( int level );
int log_printf_w ( UINT32 mask, const wchar_t *fmt, ... );
int log_printf ( UINT32 mask, const char *fmt, ... );
void log_printf_hex ( UINT32 mask, void *buf, int len );
#endif
