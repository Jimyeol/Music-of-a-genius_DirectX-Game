#include "cRank.h"

cRank::cRank()
{
}
cRank::~cRank()
{

}
void cRank::Rank_Load(WCHAR* pFileName,int check)
{
	FILE* pFile;
	WCHAR	buff[256];
	KGFindDXSDKMediaFileCch(buff,256,pFileName);
	pFile = _wfopen(buff, L"rb");
	if(pFile == NULL)
		return;
	Rank_Decode(pFile,check);
	fclose(pFile);
}
void cRank::Rank_Decode(FILE* pFile,int check)
{
	for( int i = 0 ; i < RANKCNT ; i++ )
	{
		m_Ranking[i].nRank = 0;
		//memset(m_Ranking[i].wsName, 0, sizeof(m_Ranking[i].wsName));
	}
	for(int i=0;i< RANKCNT;i++)
	{
		fread(&m_Ranking[i], sizeof(Rank), 1, pFile);
	}
	if(check == 1)
	{
		Rank_Check();
	}	
}
void cRank::Rank_Check()
{

	Rank temp;
	for(int i=0;i<RANKCNT;i++)
	{
		for(int j=0;j<RANKCNT;j++)
		{
			if(m_Ranking[j].nRank < m_Ranking[j+1].nRank)
			{
				temp = m_Ranking[j];
				m_Ranking[j] = m_Ranking[j+1];
				m_Ranking[j+1] = temp; 
			}
		}
	}
	if(SCORE >  m_Ranking[4].nRank)
	{
		m_Ranking[4].nRank = SCORE;
		//wcscpy(m_Ranking[4].wsName, cMain()->g_pName.c_str());
		//m_Ranking[4].wsName = (WCHAR*)cMain()->g_pName.c_str();
	}
	Rank_Save();
}
void cRank::Rank_Save()
{
	Rank temp;
	for(int i=0;i<RANKCNT;i++)
	{
		for(int j=0;j<RANKCNT;j++)
		{
			if(m_Ranking[j].nRank < m_Ranking[j+1].nRank)
			{
				temp = m_Ranking[j];
				m_Ranking[j] = m_Ranking[j+1];
				m_Ranking[j+1] = temp; 
			}
		}
	}
	// µå·³
	if(PLAYCHOICE == DRUM) 
	{
		if(MUSIC == JUST)
		{
			switch(LEVEL)
			{
			case EASY:
				Rank_finish(L"res/DRUMJUSTEASYRANK.txt");
				break;
			case NORMAL:
				Rank_finish(L"res/DRUMJUSTNORMALRANK.txt");
				break;
			case HARD:
				Rank_finish(L"res/DRUMJUSTHARDRANK.txt");
				break;
			}
		}
		if(MUSIC == SWAGGA)
		{
			switch(LEVEL)
			{
			case EASY:
				Rank_finish(L"res/DRUMSWAGGAEASYRANK.txt");
				break;
			case NORMAL:
				Rank_finish(L"res/DRUMSWAGGANORMALRANK.txt");
				break;
			case HARD:
				Rank_finish(L"res/DRUMSWAGGAHARDRANK.txt");
				break;
			}
		}
	}
	// Áªº£
	if(PLAYCHOICE == JEMBE) 
	{
		if(MUSIC == JUST)
		{
			switch(LEVEL)
			{
			case EASY:
				Rank_finish(L"res/JEMBEJUSTEASYRANK.txt");
				break;
			case NORMAL:
				Rank_finish(L"res/JEMBEJUSTNORMALRANK.txt");
				break;
			case HARD:
				Rank_finish(L"res/JEMBEJUSTHARDRANK.txt");
				break;
			}
		}
		if(MUSIC == SWAGGA)
		{
			switch(LEVEL)
			{
			case EASY:
				Rank_finish(L"res/JEMBESWAGGAEASYRANK.txt");
				break;
			case NORMAL:
				Rank_finish(L"res/JEMBESWAGGANORMALRANK.txt");
				break;
			case HARD:
				Rank_finish(L"res/JEMBESWAGGAHARDRANK.txt");
				break;
			}
		}
	}

	if(PLAYCHOICE == BASE) 
	{
		if(MUSIC == JUST)
		{
			switch(LEVEL)
			{
			case EASY:
				Rank_finish(L"res/BASEJUSTEASYRANK.txt");
				break;
			case NORMAL:
				Rank_finish(L"res/BASEJUSTNORMALRANK.txt");
				break;
			case HARD:
				Rank_finish(L"res/BASEJUSTHARDRANK.txt");
				break;
			}
		}
		if(MUSIC == SWAGGA)
		{
			switch(LEVEL)
			{
			case EASY:
				Rank_finish(L"res/BASESWAGGAEASYRANK.txt");
				break;
			case NORMAL:
				Rank_finish(L"res/BASESWAGGANORMALRANK.txt");
				break;
			case HARD:
				Rank_finish(L"res/BASESWAGGAHARDRANK.txt");
				break;
			}
		}
	}
}

void cRank::Rank_finish(WCHAR* pFileName)
{
	FILE* pFile;
	WCHAR	buff[256];
	KGFindDXSDKMediaFileCch(buff,256,pFileName);
	pFile = _wfopen(buff, L"wb");
	for(int i=0;i<RANKCNT;i++)
	{
		fwrite(&m_Ranking[i], sizeof(Rank), 1, pFile);
	}
	fclose(pFile);

}