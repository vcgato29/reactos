#ifdef UNICODE
#undef UNICODE
#endif

#undef WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ddk/ntddk.h>
#include <win32k/kapi.h>


/*
 * @implemented
 */
HPEN
STDCALL
CreatePen(INT PenStyle, INT Width, COLORREF Color)
{
   return NtGdiCreatePen(PenStyle, Width, Color);
}


/*
 * @implemented
 */
HPEN
STDCALL
CreatePenIndirect(CONST LOGPEN *lgpn)
{
   return NtGdiCreatePenIndirect((CONST PLOGPEN)lgpn);
}
