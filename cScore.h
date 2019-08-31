#ifndef _CSCORE_H_
#define _CSCORE_H_

#include "MyInclude.h"
using namespace KG;
class cScore : public KGScene
{
private:

	KGSprite*				m_pSprite;
	cRank*					m_pRank;
	int						m_rank;
	int						Next_Time;
	KGDialog*				m_pDialog;
	KGDialog*				m_pName;
	KGFont*					m_pFont;
	FILE*					fp;
	KGSound*				m_pSound;
	int						save;
	int						m_score;
	int						m_miss;
	int						m_good;
	int						m_perfect;
	int						m_combo;
	int						m_accuracy;
	int						m_check;
	D3DXVECTOR3				m_vPos;
	float					fMake_Time;
	
	
public:
	

public:
	cScore();
	~cScore();

public:
	HRESULT CALLBACK		OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);
	void rank_check(int SA,int AB, int BC ,int CD ,int DE,int EF); //// 더추가가능
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnDestroyDevice(void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	LRESULT	CALLBACK		OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);
};

#endif