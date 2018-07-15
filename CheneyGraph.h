#ifndef CHENEYGRAPH_H_INCLUDED
#define CHENEYGRAPH_H_INCLUDED
#pragma once

#include "CheneyThinker.h"

#define CHENEYSHAPE vector<ThinkerPoint>

class CheneyGraph
{
public:
	SPECIAL(CheneyGraph)
    void AddCheneyShape(CHENEYSHAPE shape);
    void SaveCheneyGraphToFile(CString filename);
    void GetCheneyGraphFromFile(CString filename);
	virtual void Draw(HDC hdc);
    vector<CHENEYSHAPE> m_hCheneyShape;
};

#endif // CHENEYGRAPH_H_INCLUDED