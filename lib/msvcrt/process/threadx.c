/* $Id: threadx.c,v 1.5 2003/11/14 17:13:31 weiden Exp $
 *
 */
#include <windows.h>
#include <msvcrt/errno.h>
#include <msvcrt/process.h>
#include <msvcrt/internal/file.h>


/*
 * @unimplemented
 */
unsigned long _beginthreadex(
    void* security,
    unsigned stack_size,
    unsigned (__stdcall *start_address)(void*),
    void* arglist,
    unsigned initflag,
    unsigned* thrdaddr)
{
  HANDLE NewThread;

  /*
   * Just call the API function. Any CRT specific processing is done in
   * DllMain DLL_THREAD_ATTACH
   */
  NewThread = CreateThread ( security, stack_size,
    (LPTHREAD_START_ROUTINE)start_address,
    arglist, initflag, (PULONG)thrdaddr );
  if (NULL == NewThread)
    {
    /* FIXME map GetLastError() to errno */
    __set_errno ( ENOSYS );
    }

  return (unsigned long) NewThread;
}


/*
 * @implemented
 */
void _endthreadex(unsigned retval)
{
  /*
   * Just call the API function. Any CRT specific processing is done in
   * DllMain DLL_THREAD_DETACH
   */
  ExitThread(retval);
}

/* EOF */
