/*
	 Battle of Britain
	 Copyright (C) 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at bob@rowansoftware.com a
better place to ask is http://www.simhq.com/ or even :-
http://www.simhq.com/cgi-bin/boards/cgi-bin/forumdisplay.cgi?action=topics&forum=Battle+of+Britain&number=40&DaysPrune=20&LastLogin=
*/

// RowanDialog: // RAFTaskT.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "RAFTaskT.h"
#include "package.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
typedef	Profile::AttackMethod	AttackMethod;
MAKEFIELD (AttackMethod, Profile::AM_FIELD_MIN,Profile::AM_FIELD_MAX);

/////////////////////////////////////////////////////////////////////////////
// RAFTaskTop dialog


RDialog*	RAFTaskTop::Make()
{

	CString	tabtitle[6];
		Todays_Packages.SetRAFTaskData();

	tabtitle[0] = RESSTRING(SUMMARY); 
	tabtitle[1] = RESSTRING(HURRICANES); 
	tabtitle[2] = RESSTRING(SPITFIRES);
		return
			MakeTopDialog(::Place(POSN_CENTRE,POSN_MIN),
					DialList(DialBox(FIL_NULL,new RAFTaskTop,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
						HTabBox(FIL_NULL,IdList(tabtitle[0],tabtitle[1],tabtitle[2],tabtitle[3],tabtitle[4]),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
							DialBox(FIL_D_RAFTASK_SUMMARY,new RAFTaskSummary()),
							DialBox(FIL_D_RAFTASK_HURRICANE,new RAFTaskFighter(Profile::AM_ATTACHED)),
							DialBox(FIL_D_RAFTASK_SPITFIRE,new RAFTaskFighter(Profile::AM_DETACHED))
										)	)	);

}


RAFTaskTop::RAFTaskTop(CWnd* pParent /*=NULL*/)
	: RowanDialog(RAFTaskTop::IDD, pParent)
{
	//{{AFX_DATA_INIT(RAFTaskTop)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	packnum=Todays_Packages.hipack;
}


void RAFTaskTop::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RAFTaskTop)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RAFTaskTop, CDialog)
	//{{AFX_MSG_MAP(RAFTaskTop)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void RAFTaskTop::RefreshData(int childnum)
{
	if (childnum == -2)
	{
		if (Todays_Packages.pack[packnum].packagestatus==Profile::PS_SPARE)
			OnCancel();
		else
		if (Todays_Packages.pack[packnum].packagestatus > Profile::PS_ACTIVE_MIN)
			CDialog::OnOK();
		else
		if (Todays_Packages.hipack!=packnum)
			OnOK();
	}
}

/////////////////////////////////////////////////////////////////////////////
// RAFTaskTop message handlers
void RAFTaskTop::OnOK() 
{
 	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];

	pk.ReorderPackage(AttackMethodField::Make());


 	//update profile
	Directives::RAF::MissTypes misstype = RAFDirectivesResults::RAFMissType(Todays_Packages.hipack);

	MMC.directives.raf.userprofiles[misstype].acselectionrules = pk.RAFFindBetterRule();
	MMC.directives.raf.userprofiles[misstype].packageattackmethod = pk.attackmethod;
	
//FormationTypeIndex,		formation	FTW_RAFVIC	



	int detached;
	detached = Todays_Packages.taskdata.detached.acnum;
	if (detached <= 0)
		detached = -Todays_Packages.taskdata.detached.squadnum;
	MMC.directives.raf.userprofiles[misstype].spit.numac = detached;
	int pt = pk.FindPreferredTarget(PT_SPIT_A);
	int am = pk.FindAttackMethod(PT_SPIT_A);
	Profile::SubMethod sm;
 	sm = Profile::SubMethod(pt + Profile::SM_DIVEANDZOOM + (Profile::SM_DIVEANDZOOM * am));
 	MMC.directives.raf.userprofiles[misstype].spit.what =sm;



	int attached;
	attached = Todays_Packages.taskdata.attached.acnum;
	if (attached <= 0)
		attached = -Todays_Packages.taskdata.attached.squadnum;
	MMC.directives.raf.userprofiles[misstype].hurr.numac = attached;
	pt = pk.FindPreferredTarget(PT_HURR_A);
	am =  pk.FindAttackMethod(PT_HURR_A);
 	sm = Profile::SubMethod(pt + Profile::SM_DIVEANDZOOM + (Profile::SM_DIVEANDZOOM * am));
	MMC.directives.raf.userprofiles[misstype].hurr.what = sm;

	Campaign::GlobalRefreshData();

	CDialog::OnOK();
}
