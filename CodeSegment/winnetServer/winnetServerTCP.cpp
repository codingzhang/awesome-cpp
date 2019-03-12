// winnetServerTCP.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
// tcp �����

#include "pch.h"
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>  
#pragma comment(lib,"ws2_32.lib") 
int main()
{
    const int versionL = 1;
    const int versionH = 1;
    // 1�� ��ʼ���׽���:���ͷ�ļ���#include <WinSock2.h>�� �� lib�⣨#pragma comment(lib,"ws2_32.lib")
    WSAData wsaData;
    int nErr = WSAStartup(MAKEWORD(versionL, versionH), &wsaData);
    if (0 != nErr)
    {
        std::cout << " ��ʼ���׽���ʧ��:" << WSAGetLastError() << std::endl;
        return 0;
    }
    // WSAStartup ��ʹû������Ҫ�Ŀ�1.1������Ҳ�����ϵͳ�ϵĿ⣬������ҪУ��汾
    if (LOBYTE(wsaData.wVersion) != versionL || HIBYTE(wsaData.wVersion) != versionH)
    {
        std::cout << " ��ʼ���׽���ʧ��:" << "����������汾" << std::endl;
        return 0;
    }

    // 2�� ����socket
    SOCKET socServer = socket(AF_INET, SOCK_STREAM, 0); // ָ����ַ������(IPV4:AF_INET), ָ��socket������(���ݱ��׽���TCP:SOCK_STREAM),ָ�����ݴ���Э��/ָ���˵���Э��
    if (INVALID_SOCKET == socServer)
    {
        std::cout << " ��ʼ��socketʧ��:" << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }

    // 3����ʼ���Լ��ĵ�ַ
    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(8182);//��"�����ֽ�˳��" ת��Ϊ "�����ֽ�˳��"
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    // 4����socket
    int nBind = bind(socServer, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
    if (0 != nBind)
    {
        std::cout << WSAGetLastError() << std::endl;
        return 0;
    }
    //5��listen ����
    if (listen(socServer, 1))
    {
        std::cout << "listen failed:" << WSAGetLastError() << std::endl;
        return 0;
    }
    SOCKET socClientServer;
    SOCKADDR_IN addrClient;
    int len = sizeof(addrClient);
    char revData[1024];
    //6���ȴ�����
    if ((socClientServer = accept(socServer, (SOCKADDR*)&addrClient, &len)) <= 0) // ʹ�� socClient ���кͿͻ��˵�ͨ��
    {
        std::cout << "accept failed:" << WSAGetLastError() << std::endl;
        return 0;

    }
    while (true)
    {
        if (recv(socClientServer, revData, 1024, 0) <= 0)
        {
            std::cout << "recv failed:" << WSAGetLastError() << std::endl;
            closesocket(socClientServer);
            closesocket(socServer);
            return 0;
        }
        std::cout << "tcp recv:" << revData << std::endl;
    }
    closesocket(socClientServer);
    closesocket(socServer);
    WSACleanup();
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ������ʾ: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
