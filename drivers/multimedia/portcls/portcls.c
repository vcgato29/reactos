/*
 *  ReactOS PortCls Driver
 *  Copyright (C) 2005 ReactOS Team
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA 
 *
 *  COPYRIGHT:        See COPYING in the top level directory
 *  PROJECT:          ReactOS Sound System
 *  PURPOSE:          Audio Port Class Functions
 *  FILE:             drivers/multimedia/portcls/portcls.c
 *  PROGRAMMERS:
 *
 *  REVISION HISTORY:
 *       21 November 2005   Created James Tabor
 */
#include "portcls.h"


#define NDEBUG
#include <debug.h>


NTSTATUS STDCALL
DriverEntry(PDRIVER_OBJECT DriverObject,
            PUNICODE_STRING RegistryPath)
{
    return STATUS_SUCCESS;
}

/*
 * @implemented
 */
ULONG STDCALL
DllInitialize(ULONG Unknown)
{
    return 0;
}

/*
 * @implemented
 */
ULONG STDCALL
DllUnload(VOID)
{
    return 0;
}


/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcAddAdapterDevice(
 ULONG DriverObject,
 ULONG PhysicalDeviceObject,
 ULONG StartDevice,
 ULONG MaxObjects,
 ULONG DeviceExtensionSize
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcAddContentHandlers(
 ULONG  ContentId,
 ULONG  paHandlers,
 ULONG  NumHandlers
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcCompleteIrp(
 ULONG  DeviceObject,
 ULONG  Irp,
 ULONG  Status
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcCompletePendingPropertyRequest(
 ULONG PropertyRequest,
 ULONG NtStatus
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL 
PcCreateContentMixed(
 ULONG paContentId,
 ULONG cContentId,
 ULONG pMixedContentId
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcDestroyContent(
 ULONG ContentId
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcDispatchIrp(
 ULONG DeviceObject,
 ULONG Irp
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcForwardContentToDeviceObject(
 ULONG ContentId,
 ULONG Reserved,
 ULONG DrmForward
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL 
PcForwardContentToFileObject(
 ULONG ContentId,
 ULONG FileObject
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL 
PcForwardContentToInterface(
 ULONG ContentId,
 ULONG Unknown,
 ULONG NumMethods
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcForwardIrpSynchronous(
 ULONG DeviceObject,
 ULONG Irp 
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL 
PcGetContentRights(
 ULONG ContentId,
 ULONG DrmRights
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcGetDeviceProperty(
 ULONG DeviceObject,
 ULONG DeviceProperty,
 ULONG BufferLength,
 ULONG PropertyBuffer,
 ULONG ResultLength
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @implemented
 */
ULONGLONG STDCALL
PcGetTimeInterval(
  ULONGLONG  Timei
)
{
    LARGE_INTEGER CurrentTime;
    
    KeQuerySystemTime( &CurrentTime);

    return (Timei - CurrentTime.QuadPart);
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcInitializeAdapterDriver(
 ULONG DriverObject,
 ULONG RegistryPathName,
 ULONG AddDevice
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcNewDmaChannel(
 ULONG OutDmaChannel,
 ULONG Unknown,
 ULONG PoolType,
 ULONG DeviceDescription,
 ULONG DeviceObject
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcNewInterruptSync(
 ULONG OutInterruptSync,
 ULONG Unknown,
 ULONG ResourceList,
 ULONG ResourceIndex,
 ULONG Mode
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcNewMiniport(
 ULONG OutMiniport,
 ULONG ClassId
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcNewPort(
 ULONG OutPort,
 ULONG ClassId
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcNewRegistryKey(
 ULONG OutRegistryKey,
 ULONG Unknown,
 ULONG RegistryKeyType,
 ULONG DesiredAccess,
 ULONG DeviceObject,
 ULONG SubDevice,
 ULONG ObjectAttributes,
 ULONG CreateOptions,
 ULONG Disposition
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcNewResourceList(
 ULONG OutResourceList,
 ULONG Unknown,
 ULONG PoolType,
 ULONG TranslatedResources,
 ULONG UntranslatedResources
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcNewResourceSublist(
 ULONG OutResourceList,
 ULONG Unknown,
 ULONG PoolType,
 ULONG ParentList,
 ULONG MaximumEntries
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcNewServiceGroup(
 ULONG OutServiceGroup,
 ULONG Unknown
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcRegisterAdapterPowerManagement(
 ULONG Unknown,
 ULONG pvContext
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcRegisterIoTimeout(
 ULONG pDeviceObject,
 ULONG pTimerRoutine,
 ULONG pContext
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcRegisterPhysicalConnection(
 ULONG DeviceObject,
 ULONG FromUnknown,
 ULONG FromPin,
 ULONG ToUnknown,
 ULONG ToPin
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcRegisterPhysicalConnectionFromExternal(
 ULONG DeviceObject,
 ULONG FromString,
 ULONG FromPin,
 ULONG ToUnknown,
 ULONG ToPin
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcRegisterPhysicalConnectionToExternal(
 ULONG DeviceObject,
 ULONG FromUnknown,
 ULONG FromPin,
 ULONG ToString,
 ULONG ToPin
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcRegisterSubdevice(
 ULONG DeviceObject,
 ULONG SubdevName,
 ULONG Unknown
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcRequestNewPowerState(
 ULONG pDeviceObject,
 ULONG RequestedNewState
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

/*
 * @unimplemented
 */
NTSTATUS STDCALL
PcUnregisterIoTimeout(
 ULONG pDeviceObject,
 ULONG pTimerRoutine,
 ULONG pContext
)
{
 UNIMPLEMENTED;
 return STATUS_UNSUCCESSFUL;
}

