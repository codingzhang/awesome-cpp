// threadpoolmain.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include "pch.h"
#include <iostream>
#include"threadpool.hpp"

int main()
{
    ThreadPool pool;
    std::thread thd1(
        [&pool]() {
        for (size_t i = 0; i < 10; i++)
        {
            auto thdId = std::this_thread::get_id();
            pool.AddTask([thdId] {
                std::lock_guard<std::recursive_mutex> locker(g_coutmutex);
                std::cout << "ͬ���߳�1���߳�ID:" << thdId << std::endl;
            });
        }
    }
    );

    std::thread thd2(
        [&pool]() {
        for (size_t i = 0; i < 10; i++)
        {
            auto thdId = std::this_thread::get_id();
            pool.AddTask([thdId] {
                std::lock_guard<std::recursive_mutex> locker(g_coutmutex);
                std::cout << "ͬ���߳�2���߳�ID:" << thdId << std::endl;
            });
        }
    }
    );

    std::this_thread::sleep_for(std::chrono::seconds(2));
    getchar();
    pool.Stop();
    thd1.join();
    thd2.join();
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
