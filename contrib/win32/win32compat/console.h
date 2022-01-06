/*
 * Author: Microsoft Corp.
 *
 * Copyright (c) 2015 Microsoft Corp.
 * All rights reserved
 *
 * Microsoft openssh win32 port
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* console.h
 * 
 * Common library for Windows Console Screen IO.
 * Contains Windows console related definition so that emulation code can draw
 * on Windows console screen surface.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 */
 
#ifndef __PRAGMA_CONSOLE_h
#define __PRAGMA_CONSOLE_h

#include "libopenssh_defs.h"

#define ANSI_ATTR_RESET			0
#define ANSI_BRIGHT			1
#define ANSI_DIM			2
#define ANSI_UNDERSCORE			4
#define ANSI_BLINK			5
#define ANSI_REVERSE			7
#define ANSI_HIDDEN			8
#define ANSI_NOUNDERSCORE		24
#define ANSI_NOREVERSE			27

#define ANSI_FOREGROUND_BLACK		30
#define ANSI_FOREGROUND_RED		31
#define ANSI_FOREGROUND_GREEN		32
#define ANSI_FOREGROUND_YELLOW		33
#define ANSI_FOREGROUND_BLUE		34
#define ANSI_FOREGROUND_MAGENTA		35
#define ANSI_FOREGROUND_CYAN		36
#define ANSI_FOREGROUND_WHITE		37
#define ANSI_DEFAULT_FOREGROUND		39
#define ANSI_BACKGROUND_BLACK		40
#define ANSI_BACKGROUND_RED		41
#define ANSI_BACKGROUND_GREEN		42
#define ANSI_BACKGROUND_YELLOW		43
#define ANSI_BACKGROUND_BLUE		44
#define ANSI_BACKGROUND_MAGENTA		45
#define ANSI_BACKGROUND_CYAN		46
#define ANSI_BACKGROUND_WHITE		47
#define ANSI_DEFAULT_BACKGROUND		49
#define ANSI_BACKGROUND_BRIGHT		128

#define TAB_LENGTH			4
#define TAB_CHAR			'\t'
#define TAB_SPACE			"    "

#define true TRUE
#define false FALSE
#define bool BOOL

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x4
#endif

#ifndef ENABLE_VIRTUAL_TERMINAL_INPUT
#define ENABLE_VIRTUAL_TERMINAL_INPUT 0x0200
#endif

#ifndef DISABLE_NEWLINE_AUTO_RETURN
#define DISABLE_NEWLINE_AUTO_RETURN 0x8
#endif

typedef void *  SCREEN_HANDLE;

LIBOPENSSH_API void ConEnterRawMode();
LIBOPENSSH_API void ConUnInitWithRestore();
LIBOPENSSH_API void ConExitRawMode();

LIBOPENSSH_API BOOL ConSetScreenRect(int xSize, int ySize);
LIBOPENSSH_API BOOL ConSetScreenSize(int X, int Y);
LIBOPENSSH_API BOOL ConRestoreScreen();
LIBOPENSSH_API void ConSaveScreen();
LIBOPENSSH_API void ConSetAttribute(int *iParam, int iParamCount);
LIBOPENSSH_API int ConScreenSizeX();
LIBOPENSSH_API int ConSetScreenX();
LIBOPENSSH_API int ConScreenSizeY();
LIBOPENSSH_API int ConVisibleWindowWidth();
LIBOPENSSH_API int ConVisibleWindowHeight();
LIBOPENSSH_API int ConSetScreenY();
LIBOPENSSH_API void ConFillToEndOfLine();
LIBOPENSSH_API int ConWriteString(char* pszString, int cbString);
LIBOPENSSH_API BOOL ConWriteChar(CHAR ch);
LIBOPENSSH_API int ConWriteConsole(char *pData, int NumChars);
LIBOPENSSH_API PCHAR ConDisplayData(char* pData, int NumLines);
LIBOPENSSH_API PCHAR ConWriteLine(char* pData);
LIBOPENSSH_API int Con_printf(const char *Format, ...);
LIBOPENSSH_API void ConClearScrollRegion();
LIBOPENSSH_API void ConClearScreen();
LIBOPENSSH_API void ConClearEOScreen();
LIBOPENSSH_API void ConClearBOScreen();
LIBOPENSSH_API void ConClearLine();
LIBOPENSSH_API void ConClearEOLine();
LIBOPENSSH_API void ConClearNFromCursorRight(int n);
LIBOPENSSH_API void ConClearNFromCursorLeft(int n);
LIBOPENSSH_API void ConScrollUpEntireBuffer();
LIBOPENSSH_API void ConScrollDownEntireBuffer();
LIBOPENSSH_API void ConScrollUp(int topline,int botline);
LIBOPENSSH_API void ConScrollDown(int topline,int botline);
LIBOPENSSH_API void ConClearBOLine();
LIBOPENSSH_API BOOL ConChangeCursor(CONSOLE_CURSOR_INFO *pCursorInfo);
LIBOPENSSH_API void ConSetCursorPosition(int x, int y);
LIBOPENSSH_API int ConGetCursorX();
LIBOPENSSH_API int ConGetCursorY();
LIBOPENSSH_API int ConGetBufferHeight();
LIBOPENSSH_API BOOL ConDisplayCursor(BOOL bVisible);
LIBOPENSSH_API void ConMoveCursorPosition(int x, int y);
LIBOPENSSH_API void ConGetRelativeCursorPosition(int *x, int *y);
LIBOPENSSH_API BOOL ConRestoreScreenHandle(SCREEN_HANDLE hScreen);
LIBOPENSSH_API BOOL ConRestoreScreenColors();
LIBOPENSSH_API  SCREEN_HANDLE ConSaveScreenHandle(SCREEN_HANDLE);
LIBOPENSSH_API void ConDeleteScreenHandle(SCREEN_HANDLE hScreen);
LIBOPENSSH_API void ConSaveViewRect_NoPtyHack();
LIBOPENSSH_API void ConRestoreViewRect_NoPtyHack();
LIBOPENSSH_API void ConDeleteChars(int n);
LIBOPENSSH_API void ConSaveWindowsState();
LIBOPENSSH_API void ConMoveVisibleWindow(int offset);
LIBOPENSSH_API int is_cursor_at_lastline_of_visible_window();
LIBOPENSSH_API void ConGetCursorPosition(int *x, int *y);
LIBOPENSSH_API void ConMoveCursorTopOfVisibleWindow();
LIBOPENSSH_API HANDLE get_console_handle(FILE *, DWORD *);
#endif
