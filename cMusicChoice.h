#ifndef _cMusicChoice_H
#define _cMusicChoice_H

#include "MyInclude.h"
#include "cRank.h"
using namespace KG;

class cMusicChoice : public KGScene, public KGResponseDialog
{
private:

	KGSprite*				m_pSprite;
	KGSound*				m_pSound;
	D3DXVECTOR3				m_vPos;	//À½¾Ç º¤ÅÍ°ª
	D3DXVECTOR3				m_vMPos;	//¸¶¿ì½º º¤ÅÍ°ª
	int						m_MusicState; //¹ÂÁ÷ °í¸¦¶§ »óÅÂ
	int						m_SelectCD;
	int						m_Icheck;
	KGCursor*				m_pCursor;
	KGDialog*				m_pDialog;
	KGDialog*				m_pDialog1;
	int						m_iO;
	float					m_fFadeTime;
	float					m_fAlpha;
	KGAnimate*				m_pAnimate;
	KGRenderMulti*			m_pMulti;
	int						m_xcheck;
	int						m_ycheck;
	double					m_dcheck[51];
	double					m_dcheck1;
	int						m_iRank;
	cRank*					m_pRank;
	
public:
	

public:
	cMusicChoice();
	~cMusicChoice();


public:
	HRESULT CALLBACK		OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);

	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnDestroyDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);

	LRESULT CALLBACK		OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);
	void CALLBACK			OnEvent(UINT id, int xPos, int yPos);
	double L_Inter(double x1, double x2, double t);
	void CD(int CD);
};

#endif

