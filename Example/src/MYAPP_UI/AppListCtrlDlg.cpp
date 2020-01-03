#include "pch.h"
#include "Resource.h"
#include "AppListCtrlDlg.h"

#include "..\MYENG_BASE\DocBase.h"

CAppListCtrlDlg::CAppListCtrlDlg(CDocBase * pDoc, CWnd * pParent)
	: CMyDialog(CAppListCtrlDlg::IDD, pDoc, pParent)
{
}

CAppListCtrlDlg::~CAppListCtrlDlg()
{
}

void CAppListCtrlDlg::DoDataExchange(CDataExchange * pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_APPUI_LIST, m_listctrl);
}

BEGIN_MESSAGE_MAP(CAppListCtrlDlg, CMyDialog)
	ON_NOTIFY(NM_CLICK, IDC_APPUI_LIST, OnNMClickAppuiList)
	ON_NOTIFY(NM_DBLCLK, IDC_APPUI_LIST, OnNMDblclkAppuiList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_APPUI_LIST, OnLvnColumnclickAppuiList)
END_MESSAGE_MAP();

BOOL CAppListCtrlDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	SetText();

	SetControl();

	return TRUE;
}

void CAppListCtrlDlg::SetText()
{
}

void CAppListCtrlDlg::SetControl()
{
	SetListHeader();

	SetListItem();


}

void CAppListCtrlDlg::SetListHeader()
{
	CBitmap img;
	img.LoadBitmap(IDB_APPUI_CHECKBOX);
	m_aImage.Create(13, 13, ILC_COLOR16 | ILC_MASK, 26, 2);
	m_aImage.Add(&img, RGB(255, 255, 255));
	m_listctrl.GetHeaderCtrl()->SetImageList(&m_aImage);

	CRect rect;
	m_listctrl.GetWindowRect(rect);
	auto dwItem = m_listctrl.GetExtendedStyle();
	m_listctrl.SetExtendedStyle(dwItem | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	m_listctrl.InsertColumn(0, _T(""), LVCFMT_CENTER, (int)(rect.Width() * 0.08));
	m_listctrl.InsertColumn(1, _T("ÀÌ¸§"), LVCFMT_LEFT, (int)(rect.Width() * 0.897));

	SetHeaderCheck(FALSE);
}

long CAppListCtrlDlg::GetHeaderCheck()
{
	HDITEM hditem;
	hditem.mask = HDI_IMAGE | HDI_FORMAT;
	m_listctrl.GetHeaderCtrl()->GetItem(0, &hditem);

	return hditem.iImage;
}

void CAppListCtrlDlg::SetHeaderCheck(BOOL bCheck)
{
	HDITEM hditem;
	hditem.mask = HDI_IMAGE | HDI_FORMAT;
	m_listctrl.GetHeaderCtrl()->GetItem(0, &hditem);

	hditem.fmt = HDF_IMAGE | HDF_LEFT;
	hditem.iImage = bCheck ? 1 : 0;
	m_listctrl.GetHeaderCtrl()->SetItem(0, &hditem);
}

void CAppListCtrlDlg::SetListItem()
{
	const auto sz_default = 5;

	m_listctrl.DeleteAllItems();
	for (auto indx = 0; indx < sz_default; ++indx)
	{
		CString strFormat;
		strFormat.Format(_T("Name%d - ID(%d)"), (indx + 1), (indx + 1));

		LVITEM lvItem;
		lvItem.iItem = indx;
		lvItem.iSubItem = 0;
		lvItem.pszText = _T("");
		lvItem.lParam = (LPARAM)(indx+1);
		lvItem.mask = LVIF_TEXT | LVIF_PARAM;
		m_listctrl.InsertItem(&lvItem);

		lvItem.iItem = indx;
		lvItem.iSubItem = 1;
		lvItem.pszText = strFormat.GetBuffer();
		lvItem.mask = LVIF_TEXT;
		m_listctrl.SetItem(&lvItem);

		m_listctrl.SetCheck(indx, FALSE);
	}
}


void CAppListCtrlDlg::OnNMClickAppuiList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if (pNMItemActivate->iItem > -1)
	{
		if (pNMItemActivate->iSubItem == 0)
		{
			auto bCheck = m_listctrl.GetCheck(pNMItemActivate->iItem);
			auto pos = m_listctrl.GetFirstSelectedItemPosition();
			while (pos)
			{
				auto item = m_listctrl.GetNextSelectedItem(pos);
				if (item != pNMItemActivate->iItem)
					m_listctrl.SetCheck(item, !bCheck);
			}
		}
	}

	*pResult = 0;
}


void CAppListCtrlDlg::OnNMDblclkAppuiList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem > -1)
	{
		if (pNMItemActivate->iSubItem == 0)
		{
			auto bCheck = m_listctrl.GetCheck(pNMItemActivate->iItem);
			auto pos = m_listctrl.GetFirstSelectedItemPosition();
			while (pos)
			{
				auto item = m_listctrl.GetNextSelectedItem(pos);
				if (item != pNMItemActivate->iItem)
					m_listctrl.SetCheck(item, !bCheck);
			}
		}
	}

	*pResult = 0;
}


void CAppListCtrlDlg::OnLvnColumnclickAppuiList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	if (pNMLV->iSubItem == 0)
	{
		auto nCheck = GetHeaderCheck() > 0 ? FALSE : TRUE;

		int nCnt = m_listctrl.GetItemCount();
		for (int i = 0; i < nCnt; i++)
			m_listctrl.SetCheck(i, nCheck);

		SetHeaderCheck(nCheck);
	}

	*pResult = 0;
}
