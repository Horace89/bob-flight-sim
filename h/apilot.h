/*
//{{AFX_INCLUDES()
#include "rcombo.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_APILOT_H__9081A781_F949_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_APILOT_H__9081A781_F949_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// APilot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAutoPilot dialog

class CAutoPilot : public RowanDialog
{
// Construction
public:
	CAutoPilot(CWnd* pParent = NULL);   // standard constructor
	UINT	ThreeDee2Pref_Timer;
	void PreDestroyPanel();

// Dialog Data
	//{{AFX_DATA(CAutoPilot)
	enum { IDD = IDD_3dII };
	CRStatic	m_IDC_SDETAIL1;
	CRStatic	m_IDC_RSTATICCTRL2;
	CRStatic	m_IDC_RSTATICCTRL3;
	CRStatic	m_IDC_RSTATICCTRL4;
	CRStatic	m_IDC_RSTATICCTRL5;
	CRStatic	m_IDC_RSTATICCTRL6;
	CRStatic	m_IDC_RSTATICCTRL7;
	CRStatic	m_IDC_RSTATICCTRL8;
	CRStatic	m_IDC_RSTATICCTRL9;
	CRStatic	m_IDC_RSTATICCTRL10;
	CRStatic	m_IDC_RSTATICCTRL12;
	CRCombo m_IDC_CBO_FILTERING;
	CRCombo m_IDC_CBO_TRANSPARENCY;
	CRCombo m_IDC_CBO_TEXTUREQUALITY;
	CRCombo m_IDC_CBO_TREES;
	CRCombo m_IDC_CBO_ROUTES;
	CRCombo m_IDC_CBO_ACSHADOWS;
	CRCombo m_IDC_CBO_ITEMSHADOWS;
	CRCombo m_IDC_CBO_HORIZONFADE;
	CRCombo m_IDC_CBO_HORIZON_DISTANCE;
	CRCombo m_IDC_CBO_CONTOUR_DETAIL;
	CRCombo	m_IDC_CBO_GEFFECTS;
	CRCombo	m_IDC_CBO_INJURYEFFECTS;
	CRCombo	m_IDC_CBO_WHITEOUTS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoPilot)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAutoPilot)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnTextChangedCboFiltering(LPCTSTR text, short index);
	afx_msg void OnTextChangedCboQuality(LPCTSTR text, short index);
	afx_msg void OnTextChangedCboInjuryeffects(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboGeffects(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboWhiteouts(LPCTSTR Caption, short index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APILOT_H__9081A781_F949_11D1_A5A3_0040052179B6__INCLUDED_)
