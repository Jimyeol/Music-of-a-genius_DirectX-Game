#ifndef _cBaseLoad_H
#define _cBaseLoad_H

#include "MyInclude.h"
#include "cBaseNote.h"
#include <KGEmotion.h>
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "KGEmotionD.lib")
#else
#pragma comment(lib, "KGEmotion.lib")
#endif
using namespace KG;

class cBaseNote;

class cBaseLoad
{
public:
	WCHAR					m_LoadName[256];
	int						m_Number;

	cBaseNote**				m_pBaseNote;

public:
	cBaseLoad();
	~cBaseLoad();


public:
	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnDestroyDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);

};

#endif