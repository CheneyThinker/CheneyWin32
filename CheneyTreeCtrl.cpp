#include "CheneyTreeCtrl.h"

SPECIAL_HANDLER(CheneyTreeCtrl, {}, {
	DestroyWindow();
})

BOOL CheneyTreeCtrl::Create(LPCTSTR lpszCaption, const RECT& rect, CheneyWnd* parent, UINT nID, DWORD dwStyle)
{
	CheneyWnd* pWnd = this;
	return pWnd->CreateEx(NULL, WC_TREEVIEW, lpszCaption, dwStyle, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, parent->m_hWnd, (HMENU) nID);
}

void CheneyTreeCtrl::SetItemState(HTREEITEM hItem, UINT state, UINT stateMask)
{
	TVITEM tvi;
	tvi.mask = TVIF_STATE;
	tvi.hItem = hItem;
	tvi.stateMask = stateMask;
	tvi.state = state;
	SendMessage(m_hWnd, TVM_SETITEM, 0, (LPARAM)(TV_ITEM *)&tvi);
}

void CheneyTreeCtrl::SetCheckState(HTREEITEM hItem, BOOL fCheck)
{
	SetItemState(hItem, INDEXTOSTATEIMAGEMASK((fCheck) ? 2 : 1), TVIS_STATEIMAGEMASK);
}

UINT CheneyTreeCtrl::GetItemState(HTREEITEM hti, UINT mask)
{
	assert(::IsWindow(m_hWnd));
	return (UINT)SendMessage(m_hWnd, TVM_GETITEMSTATE, (WPARAM)(hti), (LPARAM)(mask));
}

UINT CheneyTreeCtrl::GetCheckState(HTREEITEM hti)
{
	assert(::IsWindow(m_hWnd));
	return ((((UINT)(SendMessage(m_hWnd, TVM_GETITEMSTATE, (WPARAM)(hti), TVIS_STATEIMAGEMASK))) >> 12) -1);
}

COLORREF CheneyTreeCtrl::SetLineColor(COLORREF clr)
{
	assert(::IsWindow(m_hWnd));
	return (COLORREF) SendMessage(m_hWnd, TVM_SETLINECOLOR, 0, (LPARAM)(clr));
}

COLORREF CheneyTreeCtrl::GetLineColor() const
{
	assert(::IsWindow(m_hWnd));
	return (COLORREF) SendMessage(m_hWnd, TVM_GETLINECOLOR, 0, 0);
}

HTREEITEM CheneyTreeCtrl::InsertItem(const LPSTR pszText)
{
	tvis.hParent = TVI_ROOT;
	tvis.hInsertAfter = TVI_LAST;
	tvis.item.mask = TVIF_TEXT | TVIF_STATE;
	tvis.item.pszText = pszText;
	tvis.item.cchTextMax = sizeof(pszText);
	tvis.item.state = TVIS_EXPANDED;
	tvis.item.stateMask = TVIS_EXPANDED;
	HTREEITEM hTreeItem = (HTREEITEM)SendMessage(m_hWnd, TVM_INSERTITEM, 0, (LPARAM)(&tvis));
	return hTreeItem;
}

HTREEITEM CheneyTreeCtrl::InsertItem(HTREEITEM hParentItem, CString pszText)
{
	tvis.hParent = hParentItem;
	tvis.item.pszText = pszText.GetBuffer(0);
	tvis.item.cchTextMax = pszText.GetLength();
	HTREEITEM hTreeItem = (HTREEITEM)SendMessage(m_hWnd, TVM_INSERTITEM, 0, (LPARAM)(&tvis));
	return hTreeItem;
}

HTREEITEM CheneyTreeCtrl::InsertItem(HTREEITEM hParentItem, const LPSTR pszText)
{
	tvis.hParent = hParentItem;
	tvis.item.pszText = pszText;
	tvis.item.cchTextMax = sizeof(pszText);
	HTREEITEM hTreeItem = (HTREEITEM)SendMessage(m_hWnd, TVM_INSERTITEM, 0, (LPARAM)(&tvis));
	return hTreeItem;
}