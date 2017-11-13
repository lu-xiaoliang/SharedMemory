#pragma once
#include <windows.h>
#include <mutex>
#include <thread>
#include <list>
using namespace std;

class SharedMemory
{
public:
	SharedMemory();
	virtual ~SharedMemory();

	//���������ڴ�
	bool CreateSharedMemory(const char* cstrName, int iSize = 1024);

	//�򿪹����ڴ�
	bool OpenSharedMemory(const char* cstrName, int iSize = 1024);

	//�رչ����ڴ�
	void CloseSharedMemory();

	//д�빲���ڴ�
	void WriteSharedMemory(const char* cstrData, int iSize);

	//��ȡ�����ڴ�
	void ReadSharedMemory(char* cstrData, int iSize);

	static void WriteThreadFunc(void* param);

	class SharedData
	{
	public:
		SharedData(const char* _data, int _size)
		{
			size = _size;
			buff = new char[_size + 1];
			buff[_size] = '\0';

			memcpy_s(buff, _size, _data, _size);
		}

		~SharedData() 
		{
			if (buff)
			{
				delete[] buff;
				buff = NULL;
			}
		}

		SharedData(const SharedData& data)
		{
			buff = new char[data.size + 1];
			buff[data.size] = '\0';
			size = data.size;
			memcpy_s(buff, data.size, data.buff, size);
		}

		char* buff;
		int   size;
	};

private:
	HANDLE	m_hMapFile;
	char*	m_pMapBuff;
	int		m_iBuffSize;
	mutex	m_lock;

	list<SharedData> m_dataList;

	thread* m_pWriteThread;
};

