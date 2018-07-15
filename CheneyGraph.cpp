#include "CheneyGraph.h"

SPECIAL_HANDLER(CheneyGraph, {}, {})

void CheneyGraph::AddCheneyShape(CHENEYSHAPE shape)
{
    m_hCheneyShape.push_back(shape);
}

void CheneyGraph::Draw(HDC hdc)
{
    int nCount = (int) m_hCheneyShape.size();
    for(int i = 0; i < nCount; i++)
    {
        CHENEYSHAPE shape = (CHENEYSHAPE) m_hCheneyShape.at(i);
        int nPtCount = (int) shape.size();
        if(nPtCount > 0)
        {
            ThinkerPoint p = shape.at(0);
            MoveToEx(hdc, p.x, p.y, NULL);
            for(int j = 0; j < nPtCount; j++)
            {
                ThinkerPoint pt = shape.at(j);
                LineTo(hdc, pt.x, pt.y);
                MoveToEx(hdc, pt.x, pt.y, NULL);
            }
        }
    }
}

void CheneyGraph::SaveCheneyGraphToFile(CString filename)
{
	errno_t err;
	FILE* fp;
	err = fopen_s(&fp, filename.GetBuffer(0), _T("w+b"));
    if(err != 0)
        return;
    int nCount = m_hCheneyShape.size();
    fwrite((void*)&nCount, sizeof(int), sizeof(int), fp);
    for(int i = 0; i <nCount; i++)
    {
        CHENEYSHAPE shape = m_hCheneyShape.at(i);
        int nPtCount = shape.size();
        fwrite((void*)&nPtCount, sizeof(int), sizeof(int), fp);
        if(nPtCount > 0)
        {
            for(int j = 0; j < nPtCount; j++)
            {
                ThinkerPoint p = shape.at(j);
                fwrite((void*)&p.x, sizeof(p.x), sizeof(p.x), fp);
                fwrite((void*)&p.y, sizeof(p.y), sizeof(p.y), fp);
            }
        }
    }
    fclose(fp);
}

void CheneyGraph::GetCheneyGraphFromFile(CString filename)
{
    m_hCheneyShape.clear();
	errno_t err;
	FILE* fp;
	err = fopen_s(&fp, filename.GetBuffer(0), _T("rb"));
    if(err != 0)
        return;
    int nCount = 0;
    fread((void*)&nCount, sizeof(int), sizeof(int), fp);
    for(int i = 0; i <nCount; i++)
    {
        CHENEYSHAPE shape;
        int nPtCount = 0;
        fread((void*)&nPtCount, sizeof(int), sizeof(int), fp);
        if(nPtCount > 0)
        {
            for(int j = 0; j < nPtCount; j++)
            {
                ThinkerPoint p;
                fread((void*)&p.x, sizeof(p.x), sizeof(p.x), fp);
                fread((void*)&p.y, sizeof(p.y), sizeof(p.y), fp);
                shape.push_back(p);
            }
        }
        AddCheneyShape(shape);
    }
    fclose(fp);
}