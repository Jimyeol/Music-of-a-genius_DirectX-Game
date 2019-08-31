#ifndef _cMenu_H
#define _cMenu_H

#include "MyInclude.h"
#include "cRank.h"
#include <vector>
using namespace std;
class cRank;
using namespace KG;
#define	NOTE_MAX 10
#define RANKCNT 5
class cMenu : public KGScene  , public KGResponseDialog
{
private:
	enum
	{
		BT_GAME =1 ,
		BT_RANK,
		BT_HELP,
		BT_CREATE,
		BT_QUIT,
		TM_FADE,

	};

	typedef struct RANK_tag
	{
		int			nRank;
		RANK_tag()
		{
			//wsName = NULL;
			//memset(wsName, 0, sizeof(wsName));
			nRank = 0;
		}
		RANK_tag( int nScore)
		{
			//wcscpy(wsName, pName);
			nRank = nScore;
		}
		void operator = (RANK_tag& r)
		{
			//wcscpy(this->wsName , r.wsName);
			this->nRank = r.nRank;
		}
	} Rank;

private:

	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGRenderMulti*			m_pMulti;
	int						menu_check;
	D3DXVECTOR3				m_vPos;
	KGFont*					m_pFont;
	KGDialog*				m_pDialog;
	KGDialog*				m_pDialog1;
	KGDialog*				m_pDialog2;
	KGDialog*				m_pDialog_Rank;
	KGDialog*				m_pG_Rank;
	KGDialog*				m_pRank_check;
	KGDialog*				m_pdrum;
	KGDialog*				m_pbase;
	KGDialog*				m_pjembe;
	KGDialog*				m_ok;
	KGDialog*				m_name;
	KGSound*				m_pSound;
	float					m_fAlpha;
	float					m_fFadeTime;
	KGCursor*				m_pCursor;
	cRank*					m_pRank;
	Rank					m_Ranking[RANKCNT];
	Rank					m_Ranking1[RANKCNT];
	DWORD					m_Dwtime;
	int						m_check;
	int						m_rankck;
	int						m_nameok;
public:
	typedef struct Note
	{
		float				x;
		int					y;
		bool				m_bObjectUse;
		float				m_fA;
		float				m_fTime;
		IDirect3DTexture9*	Text;
	}NOTE;

	NOTE					_NOTE[NOTE_MAX];
	NOTE					_NOTE_HIGH[NOTE_MAX];


public:
	cMenu();
	~cMenu();


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
	void CALLBACK			OnEvent(UINT id, int xPos, int yPox);

protected:
	void					SetDisable(bool bDisable);
};

#endif