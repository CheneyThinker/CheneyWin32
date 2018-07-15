#include "CheneyListCtrl.h"

SPECIAL_HANDLER(CheneyListCtrl, {}, {})

BOOL CheneyListCtrl::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CheneyWnd* parent, UINT nID)
{
	CheneyWnd* pWnd = this;
	return pWnd->CreateEx(NULL, WC_LISTVIEW, lpszCaption, dwStyle, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, parent->m_hWnd, (HMENU) nID);
}

void CheneyListCtrl::InsertColumn(int iCol, const LPSTR pszText, int cx)
{
    LV_COLUMN lvc;
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
    lvc.pszText = pszText;
    lvc.cx = cx;
	lvc.fmt = LVCFMT_LEFT;
	assert(::IsWindow(m_hWnd));
	SendMessage(m_hWnd, LVM_INSERTCOLUMN, iCol, (LPARAM)&lvc);
}

int CheneyListCtrl::InsertColumn(int iCol, const LPSTR pszText, int fmt, int cx, int iSubItem)
{
	LV_COLUMN lvc;
	lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_FMT;
	lvc.cx = cx;
	lvc.fmt = fmt;
	lvc.iSubItem = iSubItem;
	lvc.pszText = pszText;
	lvc.cchTextMax = sizeof(pszText);
	return InsertColumn(iCol, &lvc);
}

int CheneyListCtrl::InsertColumn(int iCol, const LV_COLUMN* lvc)
{
	assert(::IsWindow(m_hWnd));
	return (int) SendMessage(m_hWnd, LVM_INSERTCOLUMN, (WPARAM)(int)(iCol), (LPARAM)(const LV_COLUMN *)(lvc));
}

BOOL CheneyListCtrl::DeleteColumn(int nCol)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) SendMessage(m_hWnd, LVM_DELETECOLUMN, nCol, 0);
}

int CheneyListCtrl::GetItemCount() const
{
	assert(::IsWindow(m_hWnd));
	return (int) ::SendMessage(m_hWnd, LVM_GETITEMCOUNT, 0, 0L);
}

BOOL CheneyListCtrl::DeleteItem(int nItem)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) ::SendMessage(m_hWnd, LVM_DELETEITEM, nItem, 0L);
}

BOOL CheneyListCtrl::DeleteAllItems()
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) ::SendMessage(m_hWnd, LVM_DELETEALLITEMS, 0, 0L);
}

UINT CheneyListCtrl::GetCallbackMask() const
{
	assert(::IsWindow(m_hWnd));
	return (UINT) ::SendMessage(m_hWnd, LVM_GETCALLBACKMASK, 0, 0);
}

BOOL CheneyListCtrl::SetCallbackMask(UINT nMask)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) ::SendMessage(m_hWnd, LVM_SETCALLBACKMASK, nMask, 0);
}

int CheneyListCtrl::GetNextItem(int nItem, int nFlags) const
{
	assert(::IsWindow(m_hWnd));
	return (int) ::SendMessage(m_hWnd, LVM_GETNEXTITEM, nItem, MAKELPARAM(nFlags, 0));
}

BOOL CheneyListCtrl::SetItemPosition(int nItem, POINT pt)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) SendMessage(m_hWnd, LVM_SETITEMPOSITION, (WPARAM)(int)(nItem), MAKELPARAM(pt.x, pt.y));
}

BOOL CheneyListCtrl::GetItemPosition(int nItem, LPPOINT lpPoint) const
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) SendMessage(m_hWnd, LVM_GETITEMPOSITION, nItem, (LPARAM)lpPoint);
}

BOOL CheneyListCtrl::EnsureVisible(int nItem, BOOL bPartialOK)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) ::SendMessage(m_hWnd, LVM_ENSUREVISIBLE, nItem, MAKELPARAM(bPartialOK, 0));
}

BOOL CheneyListCtrl::Scroll(ThinkerSize size)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) SendMessage(m_hWnd, LVM_SCROLL, size.cx, size.cy);
}

BOOL CheneyListCtrl::RedrawItems(int nFirst, int nLast)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) ::SendMessage(m_hWnd, LVM_REDRAWITEMS, nFirst, nLast);
}

BOOL CheneyListCtrl::Arrange(UINT nCode)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) ::SendMessage(m_hWnd, LVM_ARRANGE, nCode, 0L);
}

int CheneyListCtrl::GetStringWidth(LPCTSTR lpsz) const
{
	assert(::IsWindow(m_hWnd));
	return (int) ::SendMessage(m_hWnd, LVM_GETSTRINGWIDTH, 0, (LPARAM)lpsz);
}

BOOL CheneyListCtrl::SetColumnWidth(int nCol, int cx)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) ::SendMessage(m_hWnd, LVM_SETCOLUMNWIDTH, nCol, MAKELPARAM(cx, 0));
}

int CheneyListCtrl::InsertItem(int nItem, const LPSTR lpszItem, int nImage)
{
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvItem.iItem = nItem;
	lvItem.iSubItem = 0;
	lvItem.pszText = lpszItem;
	lvItem.cchTextMax = sizeof(lpszItem);
	lvItem.state = 0;
	lvItem.stateMask = 0;
	lvItem.iImage = nImage;
	lvItem.lParam = 0;
	return InsertItem(&lvItem);
}

int CheneyListCtrl::InsertItem(int nItem, const LPSTR lpszItem)
{
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nItem;
	lvItem.iSubItem = 0;
	lvItem.pszText = lpszItem;
	lvItem.cchTextMax = sizeof(lpszItem);
	lvItem.state = 0;
	lvItem.stateMask = 0;
	lvItem.iImage = 0;
	lvItem.lParam = 0;
	return InsertItem(&lvItem);
}

int CheneyListCtrl::InsertItem(const LVITEM* pItem)
{
	assert(::IsWindow(m_hWnd));
	return (int) ::SendMessage(m_hWnd, LVM_INSERTITEM, 0, (LPARAM)pItem);
}

BOOL CheneyListCtrl::GetItem(LVITEM* pItem) const
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) ::SendMessage(m_hWnd, LVM_GETITEM, 0, (LPARAM)pItem);
}

BOOL CheneyListCtrl::SetItem(const LVITEM* pItem)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) ::SendMessage(m_hWnd, LVM_SETITEM, 0, (LPARAM)pItem);
}

BOOL CheneyListCtrl::SetItemData(int nItem, DWORD_PTR dwData)
{
	assert(::IsWindow(m_hWnd));
	LVITEM pItem;
	pItem.iItem = nItem;
	pItem.iSubItem = 0;
	pItem.mask = LVIF_PARAM;
	pItem.pszText = NULL;
	pItem.iImage = 0;
	pItem.state = 0;
	pItem.stateMask = 0;
	pItem.lParam = dwData;
	return SetItem(&pItem);
}

BOOL CheneyListCtrl::SetTextColor(COLORREF cr)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) ::SendMessage(m_hWnd, LVM_SETTEXTCOLOR, 0, cr);
}

BOOL CheneyListCtrl::SetTextBkColor(COLORREF cr)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) ::SendMessage(m_hWnd, LVM_SETTEXTBKCOLOR, 0, cr);
}

BOOL CheneyListCtrl::SetBkColor(COLORREF cr)
{
	assert(::IsWindow(m_hWnd));
	return (BOOL) ::SendMessage(m_hWnd, LVM_SETBKCOLOR, 0, cr);
}

COLORREF CheneyListCtrl::GetBkColor() const
{
	assert(::IsWindow(m_hWnd));
	return (COLORREF) ::SendMessage(m_hWnd, LVM_GETBKCOLOR, 0, 0L);
}