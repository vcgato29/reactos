/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS kernel
 * FILE:            ntoskrnl/nt/event.c
 * PURPOSE:         Named event support
 * PROGRAMMER:      Philip Susi and David Welch
 * UPDATE HISTORY:
 *                  Created 22/05/98
 */

/* INCLUDES *****************************************************************/

#include <ddk/ntddk.h>
#include <internal/ob.h>

#define NDEBUG
#include <internal/debug.h>

/* GLOBALS *******************************************************************/

POBJECT_TYPE EXPORTED ExEventObjectType = NULL;

/* FUNCTIONS *****************************************************************/

NTSTATUS NtpCreateEvent(PVOID ObjectBody,
			PVOID Parent,
			PWSTR RemainingPath,
			POBJECT_ATTRIBUTES ObjectAttributes)
{
   
   DPRINT("NtpCreateDevice(ObjectBody %x, Parent %x, RemainingPath %S)\n",
	  ObjectBody, Parent, RemainingPath);
   
   if (RemainingPath != NULL && wcschr(RemainingPath+1, '\\') != NULL)
     {
	return(STATUS_UNSUCCESSFUL);
     }
   
   if (Parent != NULL && RemainingPath != NULL)
     {
	ObAddEntryDirectory(Parent, ObjectBody, RemainingPath+1);
     }
   return(STATUS_SUCCESS);
}

VOID NtInitializeEventImplementation(VOID)
{
   ANSI_STRING AnsiName;
   
   ExEventObjectType = ExAllocatePool(NonPagedPool,sizeof(OBJECT_TYPE));
   
   RtlInitAnsiString(&AnsiName,"Event");
   RtlAnsiStringToUnicodeString(&ExEventObjectType->TypeName,&AnsiName,TRUE);
   
   ExEventObjectType->MaxObjects = ULONG_MAX;
   ExEventObjectType->MaxHandles = ULONG_MAX;
   ExEventObjectType->TotalObjects = 0;
   ExEventObjectType->TotalHandles = 0;
   ExEventObjectType->PagedPoolCharge = 0;
   ExEventObjectType->NonpagedPoolCharge = sizeof(KEVENT);
   ExEventObjectType->Dump = NULL;
   ExEventObjectType->Open = NULL;
   ExEventObjectType->Close = NULL;
   ExEventObjectType->Delete = NULL;
   ExEventObjectType->Parse = NULL;
   ExEventObjectType->Security = NULL;
   ExEventObjectType->QueryName = NULL;
   ExEventObjectType->OkayToClose = NULL;
   ExEventObjectType->Create = NtpCreateEvent;
}

NTSTATUS STDCALL NtClearEvent (IN HANDLE EventHandle)
{
   PKEVENT Event;
   NTSTATUS Status;
   
   Status = ObReferenceObjectByHandle(EventHandle,
				      EVENT_MODIFY_STATE,
				      ExEventObjectType,
				      UserMode,
				      (PVOID*)&Event,
				      NULL);
   if (Status != STATUS_SUCCESS)
     {
	return(Status);
     }
   KeClearEvent(Event);
   ObDereferenceObject(Event);
   return(STATUS_SUCCESS);
}


NTSTATUS STDCALL NtCreateEvent (OUT PHANDLE			EventHandle,
				IN ACCESS_MASK		DesiredAccess,
				IN POBJECT_ATTRIBUTES	ObjectAttributes,
				IN BOOLEAN			ManualReset,
				IN BOOLEAN	InitialState)
{
   PKEVENT Event;

   DPRINT("NtCreateEvent()\n");
   Event = ObCreateObject(EventHandle,
			  DesiredAccess,
			  ObjectAttributes,
			  ExEventObjectType);
   KeInitializeEvent(Event, 
		     ManualReset ? NotificationEvent : SynchronizationEvent, 
		     InitialState );
   ObDereferenceObject(Event);
   return(STATUS_SUCCESS);
}


NTSTATUS STDCALL NtOpenEvent (OUT PHANDLE			EventHandle,
			      IN ACCESS_MASK		DesiredAccess,
			      IN POBJECT_ATTRIBUTES	ObjectAttributes)
{
   NTSTATUS Status;
   PKEVENT Event;

   Status = ObReferenceObjectByName(ObjectAttributes->ObjectName,
				    ObjectAttributes->Attributes,
				    NULL,
				    DesiredAccess,
				    ExEventObjectType,
				    UserMode,
				    NULL,
				    (PVOID*)&Event);
   if (Status != STATUS_SUCCESS)
     {
	return(Status);
     }

   Status = ObCreateHandle(PsGetCurrentProcess(),
			   Event,
			   DesiredAccess,
			   FALSE,
			   EventHandle);
   ObDereferenceObject(Event);
   
   return(STATUS_SUCCESS);
}


NTSTATUS STDCALL NtPulseEvent(IN	HANDLE	EventHandle,
			      IN	PULONG	PulseCount	OPTIONAL)
{
   UNIMPLEMENTED;
}


NTSTATUS STDCALL NtQueryEvent (IN	HANDLE	EventHandle,
			       IN	CINT	EventInformationClass,
			       OUT	PVOID	EventInformation,
			       IN	ULONG	EventInformationLength,
			       OUT	PULONG	ReturnLength)
{
   UNIMPLEMENTED;
}


NTSTATUS STDCALL NtResetEvent(HANDLE	EventHandle,
			      PULONG	NumberOfWaitingThreads	OPTIONAL)
{
   PKEVENT Event;
   NTSTATUS Status;
   
   DPRINT("NtResetEvent(EventHandle %x)\n", EventHandle);
   
   Status = ObReferenceObjectByHandle(EventHandle,
				      EVENT_MODIFY_STATE,
				      ExEventObjectType,
				      UserMode,
				      (PVOID*)&Event,
				      NULL);
   if (Status != STATUS_SUCCESS)
     {
	return(Status);
     }
   KeResetEvent(Event);
   ObDereferenceObject(Event);
   return(STATUS_SUCCESS);
}


NTSTATUS STDCALL NtSetEvent(IN	HANDLE	EventHandle,
			    PULONG NumberOfThreadsReleased)
{
   PKEVENT Event;
   NTSTATUS Status;
   
   DPRINT("NtSetEvent(EventHandle %x)\n", EventHandle);
   
   Status = ObReferenceObjectByHandle(EventHandle,
				      EVENT_MODIFY_STATE,
				      ExEventObjectType,
				      UserMode,
				      (PVOID*)&Event,
				      NULL);
   if (Status != STATUS_SUCCESS)
     {
	return(Status);
     }
   KeSetEvent(Event,IO_NO_INCREMENT,FALSE);
      
   
   ObDereferenceObject(Event);
   return(STATUS_SUCCESS);
}
