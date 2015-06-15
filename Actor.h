#pragma once
#include <thread>
#include <functional>
#include <memory>
#include <queue>
#include <mutex>
#include <string>
#include "Buffer.h"
#include <atomic>
#include <vector>
#include <set>


typedef std::function<void(Buffer*&)> Callback;
typedef std::function<void()> BeginInThreadCallback;

class Active {
private:
	Active(const Active&);
	Active& operator=(const Active&);
	Active();
	Active(int n32BlockSize, int n32BufferSize);
	void Run();
	void RunWithUpdate();
	void setCallBack(Callback aCallBack);
	bool IfEmpty();
	void Consume();
	std::queue<Buffer*> m_Queue;
	std::thread	m_Thread;
	Callback		m_Callback;
	std::mutex	m_IOMutex;
	std::condition_variable m_ConditionVar;
	std::atomic<int>		m_PendingWorkNum;
	int		m_ActiveID;
	static std::atomic<int> m_GlobalActiveID;
    std::atomic<bool>	m_IfNeedSig;
	unsigned		m_ThreadID;
	std::queue<Buffer*> m_SwapQueue;
	bool m_IfUpdate;
public:
	~Active();
	Buffer*			GetBuffer();
	int				GetActorID(){return m_ActiveID;}
	void			ReleaseBuffer(Buffer*& pBuffer);
	void			Send(Buffer* apBuffer);
	void			Stop();
	static Active*	CreateActive(Callback aCallBack, int n32BlockSize, int b32BufferSize);
	int				GetPendingWorkNum()const{return m_PendingWorkNum;}
	unsigned		GetThreadID();

	void			Start();
	void			SetThreadStartCallback(BeginInThreadCallback pBeginInThreadCallback);

private:
	BeginInThreadCallback m_BeginInThreadCallback;
};

