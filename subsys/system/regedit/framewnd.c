/*
 * Regedit frame window
 *
 * Copyright (C) 2002 Robert Dickenson <robd@reactos.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include <commdlg.h>
#include <cderr.h>
#include <stdlib.h>
#include <stdio.h>
#include <shellapi.h>
#include <objsel.h>
#include <objbase.h>

#include "main.h"
#include "regproc.h"

/********************************************************************************
 * Global and Local Variables:
 */

static BOOL bInMenuLoop = FALSE;        /* Tells us if we are in the menu loop */

/*******************************************************************************
 * Local module support methods
 */

static void resize_frame_rect(HWND hWnd, PRECT prect)
{
    RECT rt;
    /*
    	if (IsWindowVisible(hToolBar)) {
    		SendMessage(hToolBar, WM_SIZE, 0, 0);
    		GetClientRect(hToolBar, &rt);
    		prect->top = rt.bottom+3;
    		prect->bottom -= rt.bottom+3;
    	}
     */
    if (IsWindowVisible(hStatusBar)) {
        SetupStatusBar(hWnd, TRUE);
        GetClientRect(hStatusBar, &rt);
        prect->bottom -= rt.bottom;
    }
    MoveWindow(g_pChildWnd->hWnd, prect->left, prect->top, prect->right, prect->bottom, TRUE);
}

static void resize_frame_client(HWND hWnd)
{
    RECT rect;

    GetClientRect(hWnd, &rect);
    resize_frame_rect(hWnd, &rect);
}

/********************************************************************************/

static void OnEnterMenuLoop(HWND hWnd)
{
    int nParts;

    /* Update the status bar pane sizes */
    nParts = -1;
    SendMessage(hStatusBar, SB_SETPARTS, 1, (LPARAM)&nParts);
    bInMenuLoop = TRUE;
    SendMessage(hStatusBar, SB_SETTEXT, (WPARAM)0, (LPARAM)_T(""));
}

static void OnExitMenuLoop(HWND hWnd)
{
    bInMenuLoop = FALSE;
    /* Update the status bar pane sizes*/
    SetupStatusBar(hWnd, TRUE);
    UpdateStatusBar();
}

static void OnMenuSelect(HWND hWnd, UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
    TCHAR str[100];

    _tcscpy(str, _T(""));
    if (nFlags & MF_POPUP) {
        if (hSysMenu != GetMenu(hWnd)) {
            if (nItemID == 2) nItemID = 5;
        }
    }
    if (LoadString(hInst, nItemID, str, 100)) {
        /* load appropriate string*/
        LPTSTR lpsz = str;
        /* first newline terminates actual string*/
        lpsz = _tcschr(lpsz, '\n');
        if (lpsz != NULL)
            *lpsz = '\0';
    }
    SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)str);
}

void SetupStatusBar(HWND hWnd, BOOL bResize)
{
    RECT  rc;
    int nParts;
    GetClientRect(hWnd, &rc);
    nParts = rc.right;
    /*    nParts = -1;*/
    if (bResize)
        SendMessage(hStatusBar, WM_SIZE, 0, 0);
    SendMessage(hStatusBar, SB_SETPARTS, 1, (LPARAM)&nParts);
}

void UpdateStatusBar(void)
{
    TCHAR text[260];
    DWORD size;

    size = sizeof(text)/sizeof(TCHAR);
    GetComputerName(text, &size);
    SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)text);
}

static void toggle_child(HWND hWnd, UINT cmd, HWND hchild)
{
    BOOL vis = IsWindowVisible(hchild);
    HMENU hMenuView = GetSubMenu(hMenuFrame, ID_VIEW_MENU);

    CheckMenuItem(hMenuView, cmd, vis?MF_BYCOMMAND:MF_BYCOMMAND|MF_CHECKED);
    ShowWindow(hchild, vis?SW_HIDE:SW_SHOW);
    resize_frame_client(hWnd);
}

static BOOL CheckCommDlgError(HWND hWnd)
{
    DWORD dwErrorCode = CommDlgExtendedError();
    switch (dwErrorCode) {
    case CDERR_DIALOGFAILURE:
        break;
    case CDERR_FINDRESFAILURE:
        break;
    case CDERR_NOHINSTANCE:
        break;
    case CDERR_INITIALIZATION:
        break;
    case CDERR_NOHOOK:
        break;
    case CDERR_LOCKRESFAILURE:
        break;
    case CDERR_NOTEMPLATE:
        break;
    case CDERR_LOADRESFAILURE:
        break;
    case CDERR_STRUCTSIZE:
        break;
    case CDERR_LOADSTRFAILURE:
        break;
    case FNERR_BUFFERTOOSMALL:
        break;
    case CDERR_MEMALLOCFAILURE:
        break;
    case FNERR_INVALIDFILENAME:
        break;
    case CDERR_MEMLOCKFAILURE:
        break;
    case FNERR_SUBCLASSFAILURE:
        break;
    default:
        break;
    }
    return TRUE;
}

#define MAX_CUSTOM_FILTER_SIZE 50
TCHAR CustomFilterBuffer[MAX_CUSTOM_FILTER_SIZE];
TCHAR FileNameBuffer[_MAX_PATH];
TCHAR FileTitleBuffer[_MAX_PATH];

typedef struct
{
  UINT DisplayID;
  UINT FilterID;
} FILTERPAIR, *PFILTERPAIR;

void
BuildFilterStrings(TCHAR *Filter, PFILTERPAIR Pairs, int PairCount)
{
  int i, c;

  c = 0;
  for(i = 0; i < PairCount; i++)
  {
    c += LoadString(hInst, Pairs[i].DisplayID, &Filter[c], 255 * sizeof(TCHAR));
    Filter[++c] = '\0';
    c += LoadString(hInst, Pairs[i].FilterID, &Filter[c], 255 * sizeof(TCHAR));
    Filter[++c] = '\0';
  }
  Filter[++c] = '\0';
}

static BOOL InitOpenFileName(HWND hWnd, OPENFILENAME* pofn)
{
    FILTERPAIR FilterPairs[3];
    static TCHAR Filter[1024];

    memset(pofn, 0, sizeof(OPENFILENAME));
    pofn->lStructSize = sizeof(OPENFILENAME);
    pofn->hwndOwner = hWnd;
    pofn->hInstance = hInst;

    /* create filter string */
    FilterPairs[0].DisplayID = IDS_FLT_REGFILES;
    FilterPairs[0].FilterID = IDS_FLT_REGFILES_FLT;
    FilterPairs[1].DisplayID = IDS_FLT_REGEDIT4;
    FilterPairs[1].FilterID = IDS_FLT_REGEDIT4_FLT;
    FilterPairs[2].DisplayID = IDS_FLT_ALLFILES;
    FilterPairs[2].FilterID = IDS_FLT_ALLFILES_FLT;
    BuildFilterStrings(Filter, FilterPairs, sizeof(FilterPairs) / sizeof(FILTERPAIR));

    pofn->lpstrFilter = Filter;
    pofn->lpstrCustomFilter = CustomFilterBuffer;
    pofn->nMaxCustFilter = MAX_CUSTOM_FILTER_SIZE;
    pofn->nFilterIndex = 0;
    pofn->lpstrFile = FileNameBuffer;
    pofn->nMaxFile = _MAX_PATH;
    pofn->lpstrFileTitle = FileTitleBuffer;
    pofn->nMaxFileTitle = _MAX_PATH;
    /*    pofn->lpstrInitialDir = _T("");*/
    /*    pofn->lpstrTitle = _T("Import Registry File");*/
    /*    pofn->Flags = OFN_ENABLETEMPLATE + OFN_EXPLORER + OFN_ENABLESIZING;*/
    pofn->Flags = OFN_HIDEREADONLY;
    /*    pofn->nFileOffset = ;*/
    /*    pofn->nFileExtension = ;*/
    /*    pofn->lpstrDefExt = _T("");*/
    /*    pofn->lCustData = ;*/
    /*    pofn->lpfnHook = ImportRegistryFile_OFNHookProc;*/
    /*    pofn->lpTemplateName = _T("ID_DLG_IMPORT_REGFILE");*/
    /*    pofn->lpTemplateName = MAKEINTRESOURCE(IDD_DIALOG1);*/
    /*    pofn->FlagsEx = ;*/
    return TRUE;
}

static BOOL ImportRegistryFile(HWND hWnd)
{
    OPENFILENAME ofn;
    TCHAR Caption[128];

    InitOpenFileName(hWnd, &ofn);
    LoadString(hInst, IDS_IMPORT_REG_FILE, Caption, sizeof(Caption)/sizeof(TCHAR));
    ofn.lpstrTitle = Caption;
    /*    ofn.lCustData = ;*/
    if (GetOpenFileName(&ofn)) {
        /* FIXME - convert to ascii */
	if (!import_registry_file((LPSTR)ofn.lpstrFile)) {
            /*printf("Can't open file \"%s\"\n", ofn.lpstrFile);*/
            return FALSE;
        }
#if 0
        get_file_name(&s, filename, MAX_PATH);
        if (!filename[0]) {
            printf("No file name is specified\n%s", usage);
            return FALSE;
            /*exit(1);*/
        }
        while (filename[0]) {
            if (!import_registry_file(filename)) {
                perror("");
                printf("Can't open file \"%s\"\n", filename);
                return FALSE;
                /*exit(1);*/
            }
            get_file_name(&s, filename, MAX_PATH);
        }
#endif

    } else {
        CheckCommDlgError(hWnd);
    }
    return TRUE;
}


static UINT_PTR CALLBACK ExportRegistryFile_OFNHookProc(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    HWND hControl;
    UINT_PTR iResult = 0;

	switch(uiMsg) {
	case WM_INITDIALOG:
        hControl = GetDlgItem(hdlg, IDC_EXPORT_ALL);
        if (hControl)
		{
            EnableWindow(hControl, FALSE);
            SendMessage(hControl, BM_SETCHECK, BST_CHECKED, 0);
		}

        hControl = GetDlgItem(hdlg, IDC_EXPORT_BRANCH);
        if (hControl)
		{
            EnableWindow(hControl, FALSE);
            SendMessage(hControl, BM_SETCHECK, BST_UNCHECKED, 0);
		}

        hControl = GetDlgItem(hdlg, IDC_EXPORT_BRANCH_TEXT);
        if (hControl)
		{
            EnableWindow(hControl, FALSE);
		}
		break;
    }
    return iResult;
}

static BOOL ExportRegistryFile(HWND hWnd)
{
    OPENFILENAME ofn;
    TCHAR ExportKeyPath[_MAX_PATH];
    TCHAR Caption[128];

    ExportKeyPath[0] = _T('\0');
    InitOpenFileName(hWnd, &ofn);
    LoadString(hInst, IDS_EXPORT_REG_FILE, Caption, sizeof(Caption)/sizeof(TCHAR));
    ofn.lpstrTitle = Caption;
    /*    ofn.lCustData = ;*/
    ofn.Flags = OFN_ENABLETEMPLATE | OFN_EXPLORER | OFN_ENABLEHOOK;
    ofn.lpfnHook = ExportRegistryFile_OFNHookProc;
    ofn.lpTemplateName = MAKEINTRESOURCE(IDD_EXPORTRANGE);
    if (GetSaveFileName(&ofn)) {
        BOOL result;
        /* FIXME - convert strings to ascii! */
        result = export_registry_key((CHAR*)ofn.lpstrFile, (CHAR*)ExportKeyPath);
        /*result = export_registry_key(ofn.lpstrFile, NULL);*/
        /*if (!export_registry_key(ofn.lpstrFile, NULL)) {*/
        if (!result) {
            /*printf("Can't open file \"%s\"\n", ofn.lpstrFile);*/
            return FALSE;
        }
#if 0
        TCHAR filename[MAX_PATH];
        filename[0] = '\0';
        get_file_name(&s, filename, MAX_PATH);
        if (!filename[0]) {
            printf("No file name is specified\n%s", usage);
            return FALSE;
            /*exit(1);*/
        }
        if (s[0]) {
            TCHAR reg_key_name[KEY_MAX_LEN];
            get_file_name(&s, reg_key_name, KEY_MAX_LEN);
            export_registry_key((CHAR)filename, reg_key_name);
        } else {
            export_registry_key(filename, NULL);
        }
#endif

    } else {
        CheckCommDlgError(hWnd);
    }
    return TRUE;
}

BOOL PrintRegistryHive(HWND hWnd, LPTSTR path)
{
#if 1
    PRINTDLG pd;

    ZeroMemory(&pd, sizeof(PRINTDLG));
    pd.lStructSize = sizeof(PRINTDLG);
    pd.hwndOwner   = hWnd;
    pd.hDevMode    = NULL;     /* Don't forget to free or store hDevMode*/
    pd.hDevNames   = NULL;     /* Don't forget to free or store hDevNames*/
    pd.Flags       = PD_USEDEVMODECOPIESANDCOLLATE | PD_RETURNDC;
    pd.nCopies     = 1;
    pd.nFromPage   = 0xFFFF;
    pd.nToPage     = 0xFFFF;
    pd.nMinPage    = 1;
    pd.nMaxPage    = 0xFFFF;
    if (PrintDlg(&pd)) {
        /* GDI calls to render output. */
        DeleteDC(pd.hDC); /* Delete DC when done.*/
    }
#else
    HRESULT hResult;
    PRINTDLGEX pd;

    hResult = PrintDlgEx(&pd);
    if (hResult == S_OK) {
        switch (pd.dwResultAction) {
        case PD_RESULT_APPLY:
            /*The user clicked the Apply button and later clicked the Cancel button. This indicates that the user wants to apply the changes made in the property sheet, but does not yet want to print. The PRINTDLGEX structure contains the information specified by the user at the time the Apply button was clicked. */
            break;
        case PD_RESULT_CANCEL:
            /*The user clicked the Cancel button. The information in the PRINTDLGEX structure is unchanged. */
            break;
        case PD_RESULT_PRINT:
            /*The user clicked the Print button. The PRINTDLGEX structure contains the information specified by the user. */
            break;
        default:
            break;
        }
    } else {
        switch (hResult) {
        case E_OUTOFMEMORY:
            /*Insufficient memory. */
            break;
        case E_INVALIDARG:
            /* One or more arguments are invalid. */
            break;
        case E_POINTER:
            /*Invalid pointer. */
            break;
        case E_HANDLE:
            /*Invalid handle. */
            break;
        case E_FAIL:
            /*Unspecified error. */
            break;
        default:
            break;
        }
        return FALSE;
    }
#endif
    return TRUE;
}

static BOOL CopyKeyName(HWND hWnd, LPCTSTR keyName)
{
    BOOL result;

    result = OpenClipboard(hWnd);
    if (result) {
        result = EmptyClipboard();
        if (result) {

            /*HANDLE hClipData;*/
            /*hClipData = SetClipboardData(UINT uFormat, HANDLE hMem);*/

        } else {
            /* error emptying clipboard*/
            /* DWORD dwError = GetLastError(); */
            ;
        }
        if (!CloseClipboard()) {
            /* error closing clipboard*/
            /* DWORD dwError = GetLastError(); */
            ;
        }
    } else {
        /* error opening clipboard*/
        /* DWORD dwError = GetLastError(); */
        ;
    }
    return result;
}

static BOOL CreateNewValue(HKEY hRootKey, LPCTSTR pszKeyPath, DWORD dwType)
{
    TCHAR szNewValueFormat[128];
    TCHAR szNewValue[128];
    int iIndex = 1;
    BYTE data[128];
    DWORD dwExistingType, cbData;
    LONG lResult;
    HKEY hKey;
    LVFINDINFO lvfi;

    if (RegOpenKey(hRootKey, pszKeyPath, &hKey) != ERROR_SUCCESS)
        return FALSE;    

    LoadString(hInst, IDS_NEW_VALUE, szNewValueFormat, sizeof(szNewValueFormat)
        / sizeof(szNewValueFormat[0]));

    do
    {
        _sntprintf(szNewValue, sizeof(szNewValue) / sizeof(szNewValue[0]),
            szNewValueFormat, iIndex++);

        cbData = sizeof(data);
        lResult = RegQueryValueEx(hKey, szNewValue, NULL, &dwExistingType, data, &cbData);
    }
    while(lResult == ERROR_SUCCESS);

    switch(dwType) {
    case REG_DWORD:
        cbData = sizeof(DWORD);
        break;
    case REG_SZ:
    case REG_EXPAND_SZ:
        cbData = sizeof(TCHAR);
        break;
    case REG_MULTI_SZ:
        cbData = sizeof(TCHAR) * 2;
        break;
    case REG_QWORD:
        cbData = sizeof(DWORD) * 2;
        break;
    default:
        cbData = 0;
        break;
    }
    memset(data, 0, cbData);
    lResult = RegSetValueEx(hKey, szNewValue, 0, dwType, data, cbData);
    if (lResult != ERROR_SUCCESS)
        return FALSE;

    RefreshListView(g_pChildWnd->hListWnd, hRootKey, pszKeyPath);

    /* locate the newly added value, and get ready to rename it */
    memset(&lvfi, 0, sizeof(lvfi));
    lvfi.flags = LVFI_STRING;
    lvfi.psz = szNewValue;
    iIndex = ListView_FindItem(g_pChildWnd->hListWnd, -1, &lvfi);
    if (iIndex >= 0)
        ListView_EditLabel(g_pChildWnd->hListWnd, iIndex);

    return TRUE;
}

static HRESULT
InitializeRemoteRegistryPicker(OUT IDsObjectPicker **pDsObjectPicker)
{
    HRESULT hRet;

    *pDsObjectPicker = NULL;

    hRet = CoCreateInstance(&CLSID_DsObjectPicker,
                            NULL,
                            CLSCTX_INPROC_SERVER,
                            &IID_IDsObjectPicker,
                            (LPVOID*)pDsObjectPicker);
    if (SUCCEEDED(hRet))
    {
        DSOP_INIT_INFO InitInfo;
        DSOP_SCOPE_INIT_INFO Scopes[] =
        {
            {
                sizeof(DSOP_SCOPE_INIT_INFO),
                DSOP_SCOPE_TYPE_USER_ENTERED_UPLEVEL_SCOPE | DSOP_SCOPE_TYPE_USER_ENTERED_DOWNLEVEL_SCOPE |
                    DSOP_SCOPE_TYPE_GLOBAL_CATALOG | DSOP_SCOPE_TYPE_EXTERNAL_UPLEVEL_DOMAIN |
                    DSOP_SCOPE_TYPE_EXTERNAL_DOWNLEVEL_DOMAIN | DSOP_SCOPE_TYPE_WORKGROUP |
                    DSOP_SCOPE_TYPE_UPLEVEL_JOINED_DOMAIN | DSOP_SCOPE_TYPE_DOWNLEVEL_JOINED_DOMAIN,
                0,
                {
                    {
                        DSOP_FILTER_COMPUTERS,
                        0,
                        0
                    },
                    DSOP_DOWNLEVEL_FILTER_COMPUTERS
                },
                NULL,
                NULL,
                S_OK
            },
        };

        InitInfo.cbSize = sizeof(InitInfo);
        InitInfo.pwzTargetComputer = NULL;
        InitInfo.cDsScopeInfos = sizeof(Scopes) / sizeof(Scopes[0]);
        InitInfo.aDsScopeInfos = Scopes;
        InitInfo.flOptions = DSOP_SCOPE_TYPE_TARGET_COMPUTER;
        InitInfo.cAttributesToFetch = 0;
        InitInfo.apwzAttributeNames = NULL;

        hRet = (*pDsObjectPicker)->lpVtbl->Initialize(*pDsObjectPicker,
                                                      &InitInfo);

        if (FAILED(hRet))
        {
            /* delete the object picker in case initialization failed! */
            (*pDsObjectPicker)->lpVtbl->Release(*pDsObjectPicker);
        }
    }

    return hRet;
}

static HRESULT
InvokeRemoteRegistryPickerDialog(IN IDsObjectPicker *pDsObjectPicker,
                                 IN HWND hwndParent  OPTIONAL,
                                 OUT LPWSTR lpBuffer,
                                 IN UINT uSize)
{
    IDataObject *pdo = NULL;
    HRESULT hRet;

    hRet = pDsObjectPicker->lpVtbl->InvokeDialog(pDsObjectPicker,
                                                 hwndParent,
                                                 &pdo);
    if (hRet == S_OK)
    {
        STGMEDIUM stm;
        FORMATETC fe;

        fe.cfFormat = RegisterClipboardFormat(CFSTR_DSOP_DS_SELECTION_LIST);
        fe.ptd = NULL;
        fe.dwAspect = DVASPECT_CONTENT;
        fe.lindex = -1;
        fe.tymed = TYMED_HGLOBAL;

        hRet = pdo->lpVtbl->GetData(pdo,
                                    &fe,
                                    &stm);
        if (SUCCEEDED(hRet))
        {
            PDS_SELECTION_LIST SelectionList = (PDS_SELECTION_LIST)GlobalLock(stm.hGlobal);
            if (SelectionList != NULL)
            {
                if (SelectionList->cItems == 1)
                {
                    UINT nlen = wcslen(SelectionList->aDsSelection[0].pwzName);
                    if (nlen >= uSize)
                    {
                        nlen = uSize - 1;
                    }

                    memcpy(lpBuffer,
                           SelectionList->aDsSelection[0].pwzName,
                           nlen * sizeof(WCHAR));
                    lpBuffer[nlen] = L'\0';
                }

                GlobalUnlock(stm.hGlobal);
            }

            ReleaseStgMedium(&stm);
        }

        pdo->lpVtbl->Release(pdo);
    }

    return hRet;
}

static VOID
FreeObjectPicker(IN IDsObjectPicker *pDsObjectPicker)
{
    pDsObjectPicker->lpVtbl->Release(pDsObjectPicker);
}

/*******************************************************************************
 *
 *  FUNCTION: _CmdWndProc(HWND, unsigned, WORD, LONG)
 *
 *  PURPOSE:  Processes WM_COMMAND messages for the main frame window.
 *
 */
static BOOL _CmdWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HKEY hKeyRoot = 0, hKey = 0;
    LPCTSTR keyPath;
    LPCTSTR valueName;
    BOOL result = TRUE;
    REGSAM regsam = KEY_READ;
    LONG lRet;
    int item;

    switch (LOWORD(wParam)) {
    case ID_REGISTRY_IMPORTREGISTRYFILE:
        ImportRegistryFile(hWnd);
        return TRUE;
    case ID_REGISTRY_EXPORTREGISTRYFILE:
        ExportRegistryFile(hWnd);
        return TRUE;
    case ID_REGISTRY_CONNECTNETWORKREGISTRY:
    {
        IDsObjectPicker *ObjectPicker;
        WCHAR szComputerName[MAX_COMPUTERNAME_LENGTH + 1];
        HRESULT hRet;
        
        hRet = CoInitialize(NULL);
        if (SUCCEEDED(hRet))
        {
            hRet = InitializeRemoteRegistryPicker(&ObjectPicker);
            if (SUCCEEDED(hRet))
            {
                hRet = InvokeRemoteRegistryPickerDialog(ObjectPicker,
                                                        hWnd,
                                                        szComputerName,
                                                        sizeof(szComputerName) / sizeof(szComputerName[0]));
                if (hRet == S_OK)
                {
                    /* FIXME - connect to the registry */
                }

                FreeObjectPicker(ObjectPicker);
            }

            CoUninitialize();
        }

        return TRUE;
    }
    case ID_REGISTRY_DISCONNECTNETWORKREGISTRY:
        return TRUE;
    case ID_REGISTRY_PRINT:
        PrintRegistryHive(hWnd, _T(""));
        return TRUE;
    case ID_REGISTRY_EXIT:
        DestroyWindow(hWnd);
        return TRUE;
    case ID_VIEW_STATUSBAR:
        toggle_child(hWnd, LOWORD(wParam), hStatusBar);
        return TRUE;
    case ID_HELP_HELPTOPICS:
        WinHelp(hWnd, _T("regedit"), HELP_FINDER, 0);
        return TRUE;
    case ID_HELP_ABOUT:
        ShowAboutBox(hWnd);
        return TRUE;
    case ID_VIEW_SPLIT:
    {
        RECT rt;
        POINT pt, pts;
        GetClientRect(g_pChildWnd->hWnd, &rt);
        pt.x = rt.left + g_pChildWnd->nSplitPos;
        pt.y = (rt.bottom / 2);
        pts = pt;
        if(ClientToScreen(g_pChildWnd->hWnd, &pts))
        {
          SetCursorPos(pts.x, pts.y);
          SetCursor(LoadCursor(0, IDC_SIZEWE));
          SendMessage(g_pChildWnd->hWnd, WM_LBUTTONDOWN, 0, MAKELPARAM(pt.x, pt.y));
        }
        return TRUE;
    }
    case ID_EDIT_RENAME:
    case ID_EDIT_MODIFY:
    case ID_EDIT_MODIFY_BIN:
    case ID_EDIT_DELETE:
        regsam |= KEY_WRITE;
        break;
    }

    keyPath = GetItemPath(g_pChildWnd->hTreeWnd, 0, &hKeyRoot);
    valueName = GetValueName(g_pChildWnd->hListWnd, -1);
    if (keyPath) {
        lRet = RegOpenKeyEx(hKeyRoot, keyPath, 0, regsam, &hKey);
        if (lRet != ERROR_SUCCESS) hKey = 0;
    }

     switch (LOWORD(wParam)) {
    case ID_EDIT_MODIFY:
        if (valueName && ModifyValue(hWnd, hKey, valueName, FALSE))
            RefreshListView(g_pChildWnd->hListWnd, hKeyRoot, keyPath);
        break;
    case ID_EDIT_MODIFY_BIN:
        if (valueName && ModifyValue(hWnd, hKey, valueName, TRUE))
            RefreshListView(g_pChildWnd->hListWnd, hKeyRoot, keyPath);
        break;
    case ID_EDIT_RENAME:
        if(ListView_GetSelectedCount(g_pChildWnd->hListWnd) == 1)
        {
          item = ListView_GetNextItem(g_pChildWnd->hListWnd, -1, LVNI_SELECTED);
          if(item > -1)
          {
            ListView_EditLabel(g_pChildWnd->hListWnd, item);
          }
        }
        break;
    case ID_EDIT_DELETE:
    {
        UINT nSelected = ListView_GetSelectedCount(g_pChildWnd->hListWnd);
        if(nSelected >= 1)
        {
          TCHAR msg[128], caption[128];
          LoadString(hInst, IDS_QUERY_DELETE_CONFIRM, caption, sizeof(caption)/sizeof(TCHAR));
          LoadString(hInst, (nSelected == 1 ? IDS_QUERY_DELETE_ONE : IDS_QUERY_DELETE_MORE), msg, sizeof(msg)/sizeof(TCHAR));
          if(MessageBox(g_pChildWnd->hWnd, msg, caption, MB_ICONQUESTION | MB_YESNO) == IDYES)
          {
            int ni, errs;

	    item = -1;
	    errs = 0;
            while((ni = ListView_GetNextItem(g_pChildWnd->hListWnd, item, LVNI_SELECTED)) > -1)
            {
              valueName = GetValueName(g_pChildWnd->hListWnd, item);
              if(RegDeleteValue(hKey, valueName) != ERROR_SUCCESS)
              {
                errs++;
              }
	      item = ni;
            }

            RefreshListView(g_pChildWnd->hListWnd, hKeyRoot, keyPath);
            if(errs > 0)
            {
              LoadString(hInst, IDS_ERR_DELVAL_CAPTION, caption, sizeof(caption)/sizeof(TCHAR));
              LoadString(hInst, IDS_ERR_DELETEVALUE, msg, sizeof(msg)/sizeof(TCHAR));
              MessageBox(g_pChildWnd->hWnd, msg, caption, MB_ICONSTOP);
            }
          }
        }
	break;
    case ID_EDIT_NEW_STRINGVALUE:
        CreateNewValue(hKeyRoot, keyPath, REG_SZ);
        break;
    case ID_EDIT_NEW_BINARYVALUE:
        CreateNewValue(hKeyRoot, keyPath, REG_BINARY);
        break;
    case ID_EDIT_NEW_DWORDVALUE:
        CreateNewValue(hKeyRoot, keyPath, REG_DWORD);
        break;
    }
    case ID_EDIT_COPYKEYNAME:
        CopyKeyName(hWnd, _T(""));
        break;
    case ID_EDIT_PERMISSIONS:
        if(keyPath != NULL && _tcslen(keyPath) > 0)
        {
          RegKeyEditPermissions(hWnd, hKey, NULL, keyPath);
        }
        else
        {
          MessageBeep(MB_ICONASTERISK);
        }
        break;
    case ID_REGISTRY_PRINTERSETUP:
        /*PRINTDLG pd;*/
        /*PrintDlg(&pd);*/
        /*PAGESETUPDLG psd;*/
        /*PageSetupDlg(&psd);*/
        break;
    case ID_REGISTRY_OPENLOCAL:
        break;

    case ID_VIEW_REFRESH:
        RefreshTreeView(g_pChildWnd->hTreeWnd);
        /*RefreshListView(g_pChildWnd->hListWnd, hKeyRoot, keyPath, NULL); */
        break;
   /*case ID_OPTIONS_TOOLBAR:*/
   /*	toggle_child(hWnd, LOWORD(wParam), hToolBar);*/
   /*    break;*/
    case ID_EDIT_NEW_KEY:
        CreateNewKey(g_pChildWnd->hTreeWnd, TreeView_GetSelection(g_pChildWnd->hTreeWnd));
        break;
    default:
        result = FALSE;
    }

    if(hKey)
      RegCloseKey(hKey);
    return result;
}

/********************************************************************************
 *
 *  FUNCTION: FrameWndProc(HWND, unsigned, WORD, LONG)
 *
 *  PURPOSE:  Processes messages for the main frame window.
 *
 *  WM_COMMAND  - process the application menu
 *  WM_DESTROY  - post a quit message and return
 *
 */

LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_CREATE:
        CreateWindowEx(0, szChildClass, NULL, WS_CHILD | WS_VISIBLE,
                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                       hWnd, (HMENU)0, hInst, 0);
        break;
    case WM_COMMAND:
        if (!_CmdWndProc(hWnd, message, wParam, lParam))
            return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    case WM_ACTIVATE:
        if (LOWORD(hWnd)) 
            SetFocus(g_pChildWnd->hWnd);
        break;
    case WM_SIZE:
        resize_frame_client(hWnd);
        break;
    case WM_TIMER:
        break;
    case WM_ENTERMENULOOP:
        OnEnterMenuLoop(hWnd);
        break;
    case WM_EXITMENULOOP:
        OnExitMenuLoop(hWnd);
        break;
    case WM_MENUSELECT:
        OnMenuSelect(hWnd, LOWORD(wParam), HIWORD(wParam), (HMENU)lParam);
        break;
    case WM_DESTROY:
        WinHelp(hWnd, _T("regedit"), HELP_QUIT, 0);
        PostQuitMessage(0);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
