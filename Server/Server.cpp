// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Server.h"
#include "afxsock.h"
#include <cctype>
#include <cstring>
#include <cstdio>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: code your application's behavior here.
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
			//Space to Code
			//Khai báo sử dụng socket trong window
			// Khơi tao thư viện 

			if (AfxSocketInit() == FALSE) {
				cout << "Không khởi tạo được thư viện";
					return FALSE;
			}
			//Tạo socket cho server, lấy port là 1234, giao thức TCP
			//  1 // 2 //   Khởi tạo socket với port và Lắng nghe kết nối từ client
			//chọn port 12345
			CSocket ServerSocket;
			if (ServerSocket.Create(12319, SOCK_STREAM, NULL) == 0) {
				cout << "Không khởi tạo được Socket" << endl;
				cout << ServerSocket.GetLastError();
				return FALSE;
			}
			else {
				cout << " Server created  !!!" << endl;
				if (ServerSocket.Listen(1) == FALSE) {
					cout << "Không thể lắng nghe Port 12345 !!!" << endl;
					ServerSocket.Close();
					return FALSE;
				}
			}
			CSocket ConnectClient;

			// 4 //Chấp nhận kết nối

			if (ServerSocket.Accept(ConnectClient)) {
				cout << "client connected !!! " << endl;
				cout << "Let's Start !!! " << endl;

				char ServerMsg[100]; // tin nhắn
				int MsgSize; // độ dài tin nhắn
				char *temp; // vùng nhớ tin nhắn

				do {
					cout << "Server: ";
			
					cin.getline(ServerMsg, 100);
					MsgSize = strlen(ServerMsg);

					// 5 // Gửi độ dài thông điệp 
					ConnectClient.Send(&MsgSize, sizeof(MsgSize), 0);
					// 5 // Gửi tin nhắn
					ConnectClient.Send(ServerMsg, MsgSize, 0);


					// 8 // nhận độ dài thông điệp từ Client
					ConnectClient.Receive((char*)&MsgSize, sizeof(int), 0);
					temp = new char[MsgSize + 1];
					//8 //khi có độ dài thông điệp, biến lưu lại thông điệp và nhận thông điệp
					ConnectClient.Receive((char*)temp, MsgSize, 0);

					//In thông điệp 
					temp[MsgSize] = 0;
					
					cout << "Client: " << temp << endl;
					char a[] = "phone";
					/*if (strcmp(temp,a) != 0 ) {
						cout << "Server: ";

						char ServerMsgPhone[] = "0931398813";
						MsgSize = strlen(ServerMsgPhone);

						// 5 // Gửi độ dài thông điệp 
						ConnectClient.Send(&MsgSize, sizeof(MsgSize), 0);
						// 5 // Gửi tin nhắn
						ConnectClient.Send(ServerMsgPhone, MsgSize, 0);

					}*/
		
					delete temp;
				} while (1);
			}
			
			ConnectClient.Close();
			ServerSocket.Close();
            // TODO: code your application's behavior here.
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
