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
void ThreadProcess(CImage* pImage, CRect rect, CPoint* ptResult, int* nTotal)
{
	auto start = system_clock::now();

	int nPitch = pImage->GetPitch();
	unsigned char* fm = static_cast<unsigned char*>(pImage->GetBits());

	int nSumX = 0;
	int nSumY = 0;
	for (int j = rect.top; j < rect.bottom; ++j)
	{
		for (int i = rect.left; i < rect.right; ++i)
		{
			if (fm[j * nPitch + i] < COLOR_WHITE)
			{
				nSumX += i;
				nSumY += j;
				++(*nTotal);
			}
		}
	}
	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);
	cout << "[Thread]\t" << millisec.count() << "ms\n";

	ptResult->x += nSumX;
	ptResult->y += nSumY;
}

CPoint CProcess::GetCenter(CImage* pImage)
{
	auto start = system_clock::now();

	int nWidth = pImage->GetWidth() / 2;
	int nHeight = pImage->GetHeight() / 2;

	CRect rectDefault(0, 0, nWidth, nHeight);
	CRect rect[4];
	for(int i = 0; i < 4; ++i)
	{
		rect[i] = rectDefault;
		rect[i].OffsetRect(nWidth * (i % 2), nHeight * (i / 2));
	}

	CPoint ptResult;
	int nTotal = 0;

	thread _thread0(ThreadProcess, pImage, rect[0], &ptResult, &nTotal);
	thread _thread1(ThreadProcess, pImage, rect[1], &ptResult, &nTotal);
	thread _thread2(ThreadProcess, pImage, rect[2], &ptResult, &nTotal);
	thread _thread3(ThreadProcess, pImage, rect[3], &ptResult, &nTotal);

	_thread0.join();
	_thread1.join();
	_thread2.join();
	_thread3.join();

	ptResult.x /= nTotal;
	ptResult.y /= nTotal;

	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);
	cout << "[Main]\t" << millisec.count() << "ms\n";

	return ptResult;
}