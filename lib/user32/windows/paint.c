/*
 *  ReactOS kernel
 *  Copyright (C) 1998, 1999, 2000, 2001 ReactOS Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
/* $Id: paint.c,v 1.16 2003/07/10 21:04:32 chorns Exp $
 *
 * PROJECT:         ReactOS user32.dll
 * FILE:            lib/user32/windows/input.c
 * PURPOSE:         Input
 * PROGRAMMER:      Casper S. Hornstrup (chorns@users.sourceforge.net)
 * UPDATE HISTORY:
 *      09-05-2001  CSH  Created
 */

/* INCLUDES ******************************************************************/

#include <windows.h>
#include <user32.h>
#define NDEBUG
#include <debug.h>

/* FUNCTIONS *****************************************************************/

/*
 * @implemented
 */
HDC
STDCALL
BeginPaint(
  HWND hwnd,
  LPPAINTSTRUCT lpPaint)
{
  return NtUserBeginPaint(hwnd, lpPaint);
}


/*
 * @implemented
 */
WINBOOL
STDCALL
EndPaint(
  HWND hWnd,
  CONST PAINTSTRUCT *lpPaint)
{
  return NtUserEndPaint(hWnd, lpPaint);
}


/*
 * @unimplemented
 */
int
STDCALL
ExcludeUpdateRgn(
  HDC hDC,
  HWND hWnd)
{
  UNIMPLEMENTED;
  return 0;
}


/*
 * @unimplemented
 */
WINBOOL
STDCALL
GetUpdateRect(
  HWND hWnd,
  LPRECT lpRect,
  WINBOOL bErase)
{
  UNIMPLEMENTED;
  return FALSE;
}


/*
 * @implemented
 */
int
STDCALL
GetUpdateRgn(
  HWND hWnd,
  HRGN hRgn,
  WINBOOL bErase)
{
  return NtUserGetUpdateRgn(hWnd, hRgn, bErase);
}


/*
 * @implemented
 */
WINBOOL
STDCALL
InvalidateRect(
  HWND hWnd,
  CONST RECT *lpRect,
  WINBOOL bErase)
{
  return NtUserInvalidateRect( hWnd, lpRect, bErase );
}


/*
 * @implemented
 */
WINBOOL
STDCALL
InvalidateRgn(
  HWND hWnd,
  HRGN hRgn,
  WINBOOL bErase)
{
  return NtUserInvalidateRgn( hWnd, hRgn, bErase );
}


/*
 * @implemented
 */
WINBOOL
STDCALL
RedrawWindow(
  HWND hWnd,
  CONST RECT *lprcUpdate,
  HRGN hrgnUpdate,
  UINT flags)
{
 return NtUserRedrawWindow(hWnd, lprcUpdate, hrgnUpdate, flags);
}


/*
 * @unimplemented
 */
WINBOOL
STDCALL
ScrollDC(
  HDC hDC,
  int dx,
  int dy,
  CONST RECT *lprcScroll,
  CONST RECT *lprcClip,
  HRGN hrgnUpdate,
  LPRECT lprcUpdate)
{
  UNIMPLEMENTED;
  return FALSE;
}


/*
 * @unimplemented
 */
int
STDCALL
SetWindowRgn(
  HWND hWnd,
  HRGN hRgn,
  WINBOOL bRedraw)
{
  UNIMPLEMENTED;
  return 0;
}


/*
 * @unimplemented
 */
WINBOOL
STDCALL
UpdateWindow(
  HWND hWnd)
{
  return NtUserUpdateWindow( hWnd );
}


/*
 * @unimplemented
 */
WINBOOL
STDCALL
ValidateRect(
  HWND hWnd,
  CONST RECT *lpRect)
{
  UNIMPLEMENTED;
  return FALSE;
}


/*
 * @implemented
 */
WINBOOL
STDCALL
ValidateRgn(
  HWND hWnd,
  HRGN hRgn)
{
  return (WINBOOL) NtUserCallTwoParam((DWORD) hWnd,
                                      (DWORD) hRgn,
                                      TWOPARAM_ROUTINE_VALIDATERGN);
}


/*
 * @unimplemented
 */
int
STDCALL
GetWindowRgn(
  HWND hWnd,
  HRGN hRgn)
{
  UNIMPLEMENTED;
  return 0;
}
