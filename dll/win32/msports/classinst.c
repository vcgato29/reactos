/*
 * PROJECT:     ReactOS system libraries
 * LICENSE:     GPL - See COPYING in the top level directory
 * FILE:        dlls\win32\msports\classinst.c
 * PURPOSE:     Ports class installer
 * PROGRAMMERS: Copyright 2011 Eric Kohl
 */

#define WIN32_NO_STATUS
#include <windows.h>
#include <cmtypes.h>
#include <stdio.h>
#include <msports.h>
#include <setupapi.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(msports);


typedef enum _PORT_TYPE
{
    UnknownPort,
    ParallelPort,
    SerialPort
} PORT_TYPE;


BOOL
GetBootResourceList(HDEVINFO DeviceInfoSet,
                    PSP_DEVINFO_DATA DeviceInfoData,
                    PCM_RESOURCE_LIST *ppResourceList)
{
    HKEY hDeviceKey = NULL;
    HKEY hConfigKey = NULL;
    LPBYTE lpBuffer = NULL;
    DWORD dwDataSize;
    LONG lError;
    BOOL ret = FALSE;

    *ppResourceList = NULL;

    hDeviceKey = SetupDiCreateDevRegKeyW(DeviceInfoSet,
                                         DeviceInfoData,
                                         DICS_FLAG_GLOBAL,
                                         0,
                                         DIREG_DEV,
                                         NULL,
                                         NULL);
    if (!hDeviceKey)
        return FALSE;

    lError = RegOpenKeyExW(hDeviceKey,
                           L"LogConf",
                           0,
                           KEY_QUERY_VALUE,
                           &hConfigKey);
    if (lError != ERROR_SUCCESS)
        goto done;

    /* Get the configuration data size */
    lError = RegQueryValueExW(hConfigKey,
                              L"BootConfig",
                              NULL,
                              NULL,
                              NULL,
                              &dwDataSize);
    if (lError != ERROR_SUCCESS)
        goto done;

    /* Allocate the buffer */
    lpBuffer = HeapAlloc(GetProcessHeap(), 0, dwDataSize);
    if (lpBuffer == NULL)
        goto done;

    /* Retrieve the configuration data */
    lError = RegQueryValueExW(hConfigKey,
                              L"BootConfig",
                              NULL,
                              NULL,
                             (LPBYTE)lpBuffer,
                              &dwDataSize);
    if (lError == ERROR_SUCCESS)
        ret = TRUE;

done:
    if (ret == FALSE && lpBuffer != NULL)
        HeapFree(GetProcessHeap(), 0, lpBuffer);

    if (hConfigKey)
        RegCloseKey(hConfigKey);

    if (hDeviceKey)
        RegCloseKey(hDeviceKey);

    if (ret == TRUE)
        *ppResourceList = (PCM_RESOURCE_LIST)lpBuffer;

    return ret;
}


DWORD
GetSerialPortNumber(IN HDEVINFO DeviceInfoSet,
                    IN PSP_DEVINFO_DATA DeviceInfoData)
{
    PCM_RESOURCE_LIST lpResourceList = NULL;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR lpResDes;
    ULONG i;
    DWORD dwBaseAddress = 0;
    DWORD dwPortNumber = 0;

    TRACE("GetSerialPortNumber(%p, %p)\n",
          DeviceInfoSet, DeviceInfoData);

    if (GetBootResourceList(DeviceInfoSet,
                            DeviceInfoData,
                            &lpResourceList))
    {
        TRACE("Full resource descriptors: %ul\n", lpResourceList->Count);
        if (lpResourceList->Count > 0)
        {
            TRACE("Partial resource descriptors: %ul\n", lpResourceList->List[0].PartialResourceList.Count);

            for (i = 0; i < lpResourceList->List[0].PartialResourceList.Count; i++)
            {
                lpResDes = &lpResourceList->List[0].PartialResourceList.PartialDescriptors[i];
                TRACE("Type: %u\n", lpResDes->Type);

                switch (lpResDes->Type)
                {
                    case CmResourceTypePort:
                        TRACE("Port: Start: %I64x  Length: %lu\n",
                              lpResDes->u.Port.Start.QuadPart,
                              lpResDes->u.Port.Length);
                        if (lpResDes->u.Port.Start.HighPart == 0)
                            dwBaseAddress = (DWORD)lpResDes->u.Port.Start.LowPart;
                        break;

                    case CmResourceTypeInterrupt:
                        TRACE("Interrupt: Level: %lu  Vector: %lu\n",
                              lpResDes->u.Interrupt.Level,
                              lpResDes->u.Interrupt.Vector);
                        break;
                }
            }
        }

        HeapFree(GetProcessHeap(), 0, lpResourceList);
    }

    switch (dwBaseAddress)
    {
        case 0x3f8:
            dwPortNumber = 1;
            break;

        case 0x2f8:
            dwPortNumber = 2;
            break;

        case 0x3e8:
            dwPortNumber = 3;
            break;

        case 0x2e8:
            dwPortNumber = 4;
            break;
    }

    return dwPortNumber;
}


DWORD
GetParallelPortNumber(IN HDEVINFO DeviceInfoSet,
                      IN PSP_DEVINFO_DATA DeviceInfoData)
{
    PCM_RESOURCE_LIST lpResourceList = NULL;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR lpResDes;
    ULONG i;
    DWORD dwBaseAddress = 0;
    DWORD dwPortNumber = 0;

    TRACE("GetParallelPortNumber(%p, %p)\n",
          DeviceInfoSet, DeviceInfoData);

    if (GetBootResourceList(DeviceInfoSet,
                            DeviceInfoData,
                            &lpResourceList))
    {
        TRACE("Full resource descriptors: %ul\n", lpResourceList->Count);
        if (lpResourceList->Count > 0)
        {
            TRACE("Partial resource descriptors: %ul\n", lpResourceList->List[0].PartialResourceList.Count);

            for (i = 0; i < lpResourceList->List[0].PartialResourceList.Count; i++)
            {
                lpResDes = &lpResourceList->List[0].PartialResourceList.PartialDescriptors[i];
                TRACE("Type: %u\n", lpResDes->Type);

                switch (lpResDes->Type)
                {
                    case CmResourceTypePort:
                        TRACE("Port: Start: %I64x  Length: %lu\n",
                              lpResDes->u.Port.Start.QuadPart,
                              lpResDes->u.Port.Length);
                        if (lpResDes->u.Port.Start.HighPart == 0)
                            dwBaseAddress = (DWORD)lpResDes->u.Port.Start.LowPart;
                        break;

                    case CmResourceTypeInterrupt:
                        TRACE("Interrupt: Level: %lu  Vector: %lu\n",
                              lpResDes->u.Interrupt.Level,
                              lpResDes->u.Interrupt.Vector);
                        break;
                }

            }

        }

        HeapFree(GetProcessHeap(), 0, lpResourceList);
    }

    switch (dwBaseAddress)
    {
        case 0x378:
            dwPortNumber = 1;
            break;

        case 0x278:
            dwPortNumber = 2;
            break;
    }

    return dwPortNumber;
}


static DWORD
InstallSerialPort(IN HDEVINFO DeviceInfoSet,
                  IN PSP_DEVINFO_DATA DeviceInfoData)
{
    WCHAR szDeviceDescription[256];
    WCHAR szFriendlyName[256];
    WCHAR szPortName[5];
    DWORD dwPortNumber;
    HCOMDB hComDB = HCOMDB_INVALID_HANDLE_VALUE;

    TRACE("InstallSerialPort(%p, %p)\n",
          DeviceInfoSet, DeviceInfoData);

    /* Open the com port database */
    ComDBOpen(&hComDB);

    dwPortNumber = GetSerialPortNumber(DeviceInfoSet,
                                       DeviceInfoData);
    if (dwPortNumber != 0)
    {
        swprintf(szPortName, L"COM%u", dwPortNumber);

        ComDBClaimPort(hComDB,
                       dwPortNumber,
                       FALSE,
                       NULL);
    }
    else
    {
        wcscpy(szPortName, L"COMx");
    }

    /* Close the com port database */
    if (hComDB != HCOMDB_INVALID_HANDLE_VALUE)
        ComDBClose(hComDB);

    /* Install the device */
    if (!SetupDiInstallDevice(DeviceInfoSet,
                              DeviceInfoData))
    {
        return GetLastError();
    }

    if (SetupDiGetDeviceRegistryPropertyW(DeviceInfoSet,
                                          DeviceInfoData,
                                          SPDRP_DEVICEDESC,
                                          NULL,
                                          (LPBYTE)szDeviceDescription,
                                          256 * sizeof(WCHAR),
                                          NULL))
    {
        swprintf(szFriendlyName,
                 L"%s (%s)",
                 szDeviceDescription,
                 szPortName);
    }
    else
    {
        swprintf(szFriendlyName,
                 L"Serial Port (%s)",
                 szPortName);
    }

    /* Set the friendly name for the device */
    SetupDiSetDeviceRegistryPropertyW(DeviceInfoSet,
                                      DeviceInfoData,
                                      SPDRP_FRIENDLYNAME,
                                      (LPBYTE)szFriendlyName,
                                      (wcslen(szFriendlyName) + 1) * sizeof(WCHAR));

    return ERROR_SUCCESS;
}


static DWORD
InstallParallelPort(IN HDEVINFO DeviceInfoSet,
                    IN PSP_DEVINFO_DATA DeviceInfoData)
{
    WCHAR szDeviceDescription[256];
    WCHAR szFriendlyName[256];
    WCHAR szPortName[5];
    DWORD dwPortNumber;

    TRACE("InstallParallelPort(%p, %p)\n",
          DeviceInfoSet, DeviceInfoData);

    dwPortNumber = GetParallelPortNumber(DeviceInfoSet,
                                         DeviceInfoData);
    if (dwPortNumber != 0)
    {
        swprintf(szPortName, L"LPT%u", dwPortNumber);
    }
    else
    {
        wcscpy(szPortName, L"LPTx");
    }


    /* Install the device */
    if (!SetupDiInstallDevice(DeviceInfoSet,
                              DeviceInfoData))
    {
        return GetLastError();
    }

    if (SetupDiGetDeviceRegistryPropertyW(DeviceInfoSet,
                                          DeviceInfoData,
                                          SPDRP_DEVICEDESC,
                                          NULL,
                                          (LPBYTE)szDeviceDescription,
                                          256 * sizeof(WCHAR),
                                          NULL))
    {
        swprintf(szFriendlyName,
                 L"%s (%s)",
                 szDeviceDescription,
                 szPortName);
    }
    else
    {
        swprintf(szFriendlyName,
                 L"Serial Port (%s)",
                 szPortName);
    }

    /* Set the friendly name for the device */
    SetupDiSetDeviceRegistryPropertyW(DeviceInfoSet,
                                      DeviceInfoData,
                                      SPDRP_FRIENDLYNAME,
                                      (LPBYTE)szFriendlyName,
                                      (wcslen(szFriendlyName) + 1) * sizeof(WCHAR));

    return ERROR_SUCCESS;
}


VOID
InstallDeviceData(IN HDEVINFO DeviceInfoSet,
                  IN PSP_DEVINFO_DATA DeviceInfoData OPTIONAL)
{
    HKEY hKey = NULL;
    HINF hInf = INVALID_HANDLE_VALUE;
    SP_DRVINFO_DATA DriverInfoData;
    PSP_DRVINFO_DETAIL_DATA DriverInfoDetailData;
    WCHAR InfSectionWithExt[256];
    BYTE buffer[2048];
    DWORD dwRequired;

    TRACE("InstallDeviceData()\n");

    hKey = SetupDiCreateDevRegKeyW(DeviceInfoSet,
                                   DeviceInfoData,
                                   DICS_FLAG_GLOBAL,
                                   0,
                                   DIREG_DRV,
                                   NULL,
                                   NULL);
    if (hKey == NULL)
        goto done;

    DriverInfoData.cbSize = sizeof(SP_DRVINFO_DATA);
    if (!SetupDiGetSelectedDriverW(DeviceInfoSet,
                                   DeviceInfoData,
                                   &DriverInfoData))
    {
        goto done;
    }

    DriverInfoDetailData = (PSP_DRVINFO_DETAIL_DATA)buffer;
    DriverInfoDetailData->cbSize = sizeof(SP_DRVINFO_DETAIL_DATA);
    if (!SetupDiGetDriverInfoDetailW(DeviceInfoSet,
                                     DeviceInfoData,
                                     &DriverInfoData,
                                     DriverInfoDetailData,
                                     2048,
                                     &dwRequired))
    {
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
            goto done;
    }

    TRACE("Inf file name: %S\n", DriverInfoDetailData->InfFileName);

    hInf = SetupOpenInfFileW(DriverInfoDetailData->InfFileName,
                             NULL,
                             INF_STYLE_WIN4,
                             NULL);
    if (hInf == INVALID_HANDLE_VALUE)
        goto done;

    TRACE("Section name: %S\n", DriverInfoDetailData->SectionName);

    SetupDiGetActualSectionToInstallW(hInf,
                                      DriverInfoDetailData->SectionName,
                                      InfSectionWithExt,
                                      256,
                                      NULL,
                                      NULL);

    TRACE("InfSectionWithExt: %S\n", InfSectionWithExt);

    SetupInstallFromInfSectionW(NULL,
                                hInf,
                                InfSectionWithExt,
                                SPINST_REGISTRY,
                                hKey,
                                NULL,
                                0,
                                NULL,
                                NULL,
                                NULL,
                                NULL);

    TRACE("Done\n");

done:;
    if (hKey != NULL)
        RegCloseKey(hKey);

    if (hInf != INVALID_HANDLE_VALUE)
        SetupCloseInfFile(hInf);
}



PORT_TYPE
GetPortType(IN HDEVINFO DeviceInfoSet,
            IN PSP_DEVINFO_DATA DeviceInfoData)
{
    HKEY hKey = NULL;
    DWORD dwSize;
    DWORD dwType = 0;
    BYTE bData = 0;
    PORT_TYPE PortType = UnknownPort;
    LONG lError;

    TRACE("GetPortType()\n");

    hKey = SetupDiCreateDevRegKeyW(DeviceInfoSet,
                                   DeviceInfoData,
                                   DICS_FLAG_GLOBAL,
                                   0,
                                   DIREG_DRV,
                                   NULL,
                                   NULL);
    if (hKey == NULL)
    {
        goto done;
    }

    dwSize = sizeof(BYTE);
    lError = RegQueryValueExW(hKey,
                              L"PortSubClass",
                              NULL,
                              &dwType,
                              &bData,
                              &dwSize);

    TRACE("lError: %ld\n", lError);
    TRACE("dwSize: %lu\n", dwSize);
    TRACE("dwType: %lu\n", dwType);

    if (lError == ERROR_SUCCESS &&
        dwSize == sizeof(BYTE) &&
        dwType == REG_BINARY)
    {
        if (bData == 0)
            PortType = ParallelPort;
        else
            PortType = SerialPort;
    }

done:;
    if (hKey != NULL)
        RegCloseKey(hKey);

    TRACE("GetPortType() returns %u \n", PortType);

    return PortType;
}


static DWORD
InstallPort(IN HDEVINFO DeviceInfoSet,
            IN PSP_DEVINFO_DATA DeviceInfoData)
{
    PORT_TYPE PortType;

    InstallDeviceData(DeviceInfoSet, DeviceInfoData);

    PortType = GetPortType(DeviceInfoSet, DeviceInfoData);
    switch (PortType)
    {
        case ParallelPort:
            return InstallParallelPort(DeviceInfoSet, DeviceInfoData);

        case SerialPort:
            return InstallSerialPort(DeviceInfoSet, DeviceInfoData);

        default:
            return ERROR_DI_DO_DEFAULT;
    }
}


DWORD
WINAPI
PortsClassInstaller(IN DI_FUNCTION InstallFunction,
                    IN HDEVINFO DeviceInfoSet,
                    IN PSP_DEVINFO_DATA DeviceInfoData OPTIONAL)
{
    TRACE("PortsClassInstaller(%lu, %p, %p)\n",
          InstallFunction, DeviceInfoSet, DeviceInfoData);

    switch (InstallFunction)
    {
        case DIF_INSTALLDEVICE:
            return InstallPort(DeviceInfoSet, DeviceInfoData);

        default:
            TRACE("Install function %u ignored\n", InstallFunction);
            return ERROR_DI_DO_DEFAULT;
    }
}

/* EOF */
