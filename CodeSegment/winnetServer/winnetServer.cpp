﻿// winnetServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// udp 服务端

#include "pch.h"
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>  
#pragma comment(lib,"ws2_32.lib") 
int mainUDP()
{
    // 1、 初始化套接字:添加头文件（#include <WinSock2.h>） 和 lib库（#pragma comment(lib,"ws2_32.lib")
    const int versionL = 1;
    const int versionH = 1;
    WSAData wsaData;
    int nErr = WSAStartup(MAKEWORD(versionL, versionH), &wsaData);
    if (0 != nErr)
    {
        std::cout << " 初始化套接字失败:" << WSAGetLastError() << std::endl;
        return 0;
    }
    // WSAStartup 即使没有我需要的库1.1，但是也会加载系统上的库，所以需要校验版本
    if (LOBYTE(wsaData.wVersion) != versionL || HIBYTE(wsaData.wVersion) != versionH)
    {
        std::cout << " 初始化套接字失败:" << "错误的网络库版本" << std::endl;
        return 0;
    }

    // 2、 创建socket
    SOCKET socServer = socket(AF_INET, SOCK_DGRAM, 0); // 指明地址簇类型(IPV4:AF_INET), 指明socket的类型(数据报套接字UDP:SOCK_DGRAM),指明数据传输协议/指明端到端协议
    if (INVALID_SOCKET == socServer)
    {
        std::cout << " 初始化socket失败:" << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }

    // 3、初始化自己的地址
    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(8181);//从"主机字节顺序" 转变为 "网络字节顺序"
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    // 4、绑定socket
    int nBind = bind(socServer, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
    if (0 != nBind)
    {
        std::cout << WSAGetLastError() << std::endl;
    }
    //
    SOCKADDR_IN addClient;
    char szRecv[100] = { 0 };
    int fromlen = sizeof(SOCKADDR);
    while (true)
    {
        recvfrom(socServer, szRecv, 100, 0, (SOCKADDR*)&addClient,&fromlen);
        std::cout << szRecv << std::endl;
        sendto(socServer, "OK", strlen("OK") + 1, 0, (SOCKADDR*)&addClient, sizeof(SOCKADDR));
    }

    closesocket(socServer);
    WSACleanup();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
