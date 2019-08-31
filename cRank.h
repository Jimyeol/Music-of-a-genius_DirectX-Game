#ifndef _CRANK_H
#define _CRANK_H

#include "MyInclude.h"
#include <vector>
using namespace std;
using namespace KG;
#define RANKCNT 5
class cRank : public KGScene
{
private:

public:

typedef struct RANK_tag
	{
		//WCHAR		wsName[64];
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

	Rank		m_Ranking[RANKCNT];

public:
	cRank();
	~cRank();


public:
	void Rank_Load(WCHAR* pFileName,int check);
	void Rank_Decode(FILE* pFile,int check);
	void Rank_Check();
	void Rank_Save();
	void Rank_finish(WCHAR* pFileName);
};

#endif