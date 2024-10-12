// CProcess.cpp: 구현 파일
//

#include "pch.h"
#include "MFC.h"
#include "CProcess.h"

#include <iostream>
#include <thread>

#include "CustomDefine.h"
#include "chrono"

using namespace std;
using namespace chrono;

// CProcess

CProcess::CProcess()
{
}

CProcess::~CProcess()
{
}

// 스레드 함수
void ThreadProcess(CImage* pImage, CRect rect, CPoint* ptResult)
{
	auto start = system_clock::now();

	int nPitch = pImage->GetPitch();
	unsigned char* fm = static_cast<unsigned char*>(pImage->GetBits());

	int nSumX = 0;
	int nSumY = 0;
	int nTotal = 0;
	for (int j = rect.top; j < rect.bottom; ++j)
	{
		for (int i = rect.left; i < rect.right; ++i)
		{
			if (fm[j * nPitch + i] < COLOR_WHITE)
			{
				nSumX += i;
				nSumY += j;
				++nTotal;
			}
		}
	}
	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);
	cout << "[Thread]\t" << millisec.count() << "ms\n";

	ptResult->x = nSumX / nTotal;
	ptResult->y = nSumY / nTotal;
}

CPoint CProcess::GetCenter(CImage* pImage)
{
	auto start = system_clock::now();

	CRect rect(0, 0, pImage->GetWidth(), pImage->GetHeight());
	CPoint ptResult;

	thread _thread(ThreadProcess, pImage, rect, &ptResult);
	_thread.join();

	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);
	cout << "[Main]\t" << millisec.count() << "ms\n";

	return ptResult;
}