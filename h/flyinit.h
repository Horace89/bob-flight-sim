//------------------------------------------------------------------------------
//Filename       flyinit.h
//System         
//Author         R. Hyde 
//Date           Mon 4 Dec 1995
//Description    project specific list of planeytpes
//------------------------------------------------------------------------------
#ifndef	FLYINIT_Included
#define	FLYINIT_Included

#define	DEFAULT_FLYINIT 0

enum	QuitGameConditions {ALT_X = 0,STANDARDQUIT,SEENBYLEADER , COMECLOSETOLEADER, LEADERREACHEDDESTINATION,ACMTRAININGTIMEUP,
							CRASHED_DEAD,CRASHED_ALIVE,CRASHED_BENTWING,CRASH_TOOFAST,LANDED_OK,LANDED_ONSQUARE,
							SPRINGOFFENSIVELOST,SPRINGOFFENSIVEWON,
							EVACUATESUCCESS,EVACUATEFAILURE, COMMSQUIT
							
							
							};
//These are matched by identical equates in SquadNum
enum	PlaneTypeSelect											//RDH 06Aug96
		{
			PT_BRIT_FLYABLE,PT_RAF_FLYABLE=PT_BRIT_FLYABLE,
			PT_SPIT_A=PT_BRIT_FLYABLE,PT_SPIT_B, PT_HURR_A,PT_HURR_B,

			PT_BRIT_NONFLY,PT_RAF_NONFLY=PT_BRIT_NONFLY,
			PT_DEFIANT=PT_BRIT_NONFLY,PT_BLEN,

			PT_GER_FLYABLE,
			PT_ME109=PT_GER_FLYABLE,
			PT_ME110,PT_JU87, PT_LW_BOMBERS = PT_JU87,
			PT_GER_NONFLY,
			PT_DO17=PT_GER_NONFLY,PT_JU88,PT_HE111,
			PT_HE59,
	
//DEADCODE DAW 25/11/99 			PT_F86A=0,PT_F86E ,PT_F86F, PT_F84,PT_F80,PT_F51,PT_F82,	//DELETE THESE ETA 1/4/2000
//DEADCODE DAW 25/11/99 			PT_B26,
//DEADCODE DAW 25/11/99 			PT_B29,
//DEADCODE DAW 25/11/99 			PT_T6,PT_4U,
//DEADCODE DAW 25/11/99 			PT_MIG15,PT_MIG15BIS,		//RDH 17Feb97
//DEADCODE DAW 25/11/99 			PT_YAK,


			PT_VEHICLES,
			PT_ATruck=PT_VEHICLES,
			PT_ATank,
			PT_ATroop,
			PT_ATrain,
			PT_ATransportShip,
			PT_BADMAX,
	
//DEADCODE DAW 25/11/99 			PT_F86WEAPPAK=PT_F86F,									//DELETE THESE ETA 1/4/2000
//DEADCODE DAW 25/11/99 			PT_MIGWEAPPAK=PT_T6,
/**/		PT_BRITCOUNT=+PT_GER_FLYABLE- +PT_BRIT_FLYABLE,
/**/		PT_GERMCOUNT=+PT_VEHICLES- +PT_GER_FLYABLE,
/**/		PT_GERMFCOUNT=+PT_GER_NONFLY- +PT_GER_FLYABLE,
/**/		PT_VEHCOUNT=+PT_BADMAX- +PT_VEHICLES,

		};
typedef PlaneTypeSelect SquadSelect;
//DEADCODE DAW 18/11/99 enum	SquadSelect	 		
//DEADCODE DAW 18/11/99 //The five fully populated flyable blue squadrons must come first in this list,
//DEADCODE DAW 18/11/99 //then non-flyable blues, then flyable reds, then non-flyable reds
//DEADCODE DAW 18/11/99 	{	SQ_B_FLYABLE=0,
//DEADCODE DAW 18/11/99 			SQ_F86A=0,SQ_F86B,SQ_F80,SQ_F84,SQ_F51,
//DEADCODE DAW 18/11/99 		SQ_B_NONFLYABLE=5,
//DEADCODE DAW 18/11/99 			SQ_B26=5,SQ_B29,
//DEADCODE DAW 18/11/99 		SQ_B_NONFLYSPOT=7,	
//DEADCODE DAW 18/11/99 			SQ_T6=7,SQ_4U,
//DEADCODE DAW 18/11/99 		SQ_R_FLYABLE=9,			SQ_MIG15=9,//alias
//DEADCODE DAW 18/11/99 			SQ_M15=9,SQ_M15B,
//DEADCODE DAW 18/11/99 		SQ_R_NONFLYABLE=11,
//DEADCODE DAW 18/11/99 			SQ_YAK=11,
//DEADCODE DAW 18/11/99 		SQ_R_MOREMIGSQUADS=12,
//DEADCODE DAW 18/11/99 		SQ_M15_0=12,SQ_M15_1,SQ_M15_2,SQ_M15_3,
//DEADCODE DAW 18/11/99 		SQ_M15_4,SQ_M15_5,SQ_M15_6,SQ_M15_7,
//DEADCODE DAW 18/11/99 		SQ_VEHICLES=20,
//DEADCODE DAW 18/11/99 			SQ_ATruck=20,SQ_ATank
//DEADCODE DAW 18/11/99 
//DEADCODE DAW 18/11/99 	};
//
//Translation between squad and planetype takes place in Persons3::Squad2Type()
//

//DEADCODE RDH 03/03/99 enum	AcPosition{ FLIGHTLEADER, ELEMENTLEADER, WINGMAN, LONER };
enum	tThreatLevel	{
		BANDITNEVER,						//never engage, used if damaged
		BANDITINENGAGERANGEOFFRIENDLY,		//used for bait
		BANDITFIRING,
		BANDITINWEAPONSRANGE,
		BANDITINDANGERRANGE,
		BANDITINENGAGERANGE,
		BANDITINCOMBATRANGE,
		BANDITANYWHERE
		};
enum	tAggressionLevel	{
		AL_STOODDOWN,			//don't launch
		AL_MIN = AL_STOODDOWN,
		AL_TRAINING,			//launch but will not engage
		AL_DEFENSIVE,			//attack bombers if with weapons
		AL_ATTACKBOMBERSONLY,	//never attack fighters
		AL_SPLITFORCE,			//attack fighters only if they are 
								//escorting bombers
		AL_ATTACKWEAKNESSES,	//attack fighters if low on fuel, 
								//damaged etc.
		AL_ATTACKANYTHING,		//aggressive behaviour
		AL_MAX=AL_ATTACKANYTHING,
		AL_STAGE = 1
				};

enum AcTactics {WELDEDWING, TOPCOVER, SWORDANDSHIELD, LOOSEDEUCE};

const size_t	MAX_NUM_AC_IN_SQUADRON = 19;

enum	tFirstEncounterTactics
			{
				TACTIC_NULL,
				TACTIC_DIVEANDZOOM,
				TACTIC_HEADONATTACK,
				TACTIC_LINEABREAST,
				TACTIC_LINEASTERN,		
				TACTIC_VICATTACK,		
				TACTIC_INDIVIDUAL		
//DEADCODE CSB 24/01/00 				TACTIC_SCATTER,		//go straight in
//DEADCODE CSB 24/01/00 				TACTIC_PINCER,		//split force and pincer
//DEADCODE CSB 24/01/00 				TACTIC_MULTIWAVE,		//split force and delay some of it
//DEADCODE RDH 08/03/99 			 TACTIC_DECOYACTIVE,	//decoy ac do something, ie skip waypoint
//DEADCODE RDH 08/03/99 			 TACTIC_DECOYPASSIVE,	//decoy ac continue unaffected
//DEADCODE CSB 24/01/00 				TACTIC_ROUNDABOUT		//go int circles
			};

//DEADCODE DAW 22/03/00 enum	DutyType
//DEADCODE DAW 22/03/00 {
//DEADCODE DAW 22/03/00 	DUTYMASK=0xf0,
//DEADCODE DAW 22/03/00 	DC_BOMB=0x00,
//DEADCODE DAW 22/03/00 	DC_TARGPATROLS=0x10,
//DEADCODE DAW 22/03/00 	DC_CAS=0x10,
//DEADCODE DAW 22/03/00 	DC_WW=0x20,
//DEADCODE DAW 22/03/00 	DC_AR=0x30,
//DEADCODE DAW 22/03/00 
//DEADCODE DAW 22/03/00 	DA_LEVEL=0,
//DEADCODE DAW 22/03/00 	DA_DIVE=8,
//DEADCODE DAW 22/03/00 	ACTIONCODE=0x0f,
//DEADCODE DAW 22/03/00 	ACTIONSUBCODE=0x07,
//DEADCODE DAW 22/03/00 	ACTIONSUBCODEMAX=0x08,
//DEADCODE DAW 22/03/00 	DA_HIGH=0,
//DEADCODE DAW 22/03/00 	DA_WIDE=1,
//DEADCODE DAW 22/03/00 	DA_SINGLEFILE=2,
//DEADCODE DAW 22/03/00 	DA_INDIVIDUAL=3,
//DEADCODE DAW 22/03/00 	DA_ELEMENT=4,
//DEADCODE DAW 22/03/00 	DA_SPACEDIND=5,
//DEADCODE DAW 22/03/00 	DA_SPACEDELT=6,
//DEADCODE DAW 22/03/00 	DA_SPACEDFLT=7,
//DEADCODE DAW 22/03/00 	DA_CAP=8,
//DEADCODE DAW 22/03/00 
//DEADCODE DAW 22/03/00 	DD_ILLEGALWIDE=9,
//DEADCODE DAW 22/03/00 	DD_SINGLEFILE=10,
//DEADCODE DAW 22/03/00 	DD_INDIVIDUAL=11,
//DEADCODE DAW 22/03/00 	DD_ELEMENT=12,
//DEADCODE DAW 22/03/00 	DD_SPACEDIND=13,
//DEADCODE DAW 22/03/00 	DD_SPACEDELT=14,
//DEADCODE DAW 22/03/00 	DD_SPACEDFLT=15,
//DEADCODE DAW 22/03/00 
//DEADCODE DAW 22/03/00 	DUTYESCORT=0x18,
//DEADCODE DAW 22/03/00 	DUTYBARCAP=0x28,
//DEADCODE DAW 22/03/00 	DUTYMIGCAP=0x38,
//DEADCODE DAW 22/03/00 
//DEADCODE DAW 22/03/00 /**/	MAKEDUTYBOMB=(int)DC_BOMB+(int)DA_HIGH,
//DEADCODE DAW 22/03/00 /**/	MAKEDUTYCAS=(int)DC_CAS+(int)DA_LEVEL+(int)DA_SPACEDELT,
//DEADCODE DAW 22/03/00 /**/	MAKEDUTYWW=(int)DC_WW+(int)DA_DIVE+(int)DA_SPACEDIND,
//DEADCODE DAW 22/03/00 /**/	MAKEDUTYAR=(int)DC_AR+(int)DA_DIVE+(int)DA_INDIVIDUAL,
//DEADCODE DAW 22/03/00     DUTY_ALIGN=0xffff
//DEADCODE DAW 22/03/00 };

//DEADCODE JIM 24/03/99 enum	DutyType
//DEADCODE JIM 24/03/99 
//DEADCODE JIM 24/03/99 //there is a list of text strings which uses this set of duties
//DEADCODE JIM 24/03/99 //called IDS_L_
//DEADCODE JIM 24/03/99 		{
//DEADCODE JIM 24/03/99 //17Nov 98 list
//DEADCODE JIM 24/03/99 			DUTYBOMB=0,
//DEADCODE JIM 24/03/99 			DUTYDIVEBOMB=1,
//DEADCODE JIM 24/03/99 			DUTYRECONN=2,
//DEADCODE JIM 24/03/99 			DUTYTARGPATROLS=3,
//DEADCODE JIM 24/03/99 			DUTYFLAKSUPP=3,
//DEADCODE JIM 24/03/99 			DUTYESCORT=4,				//RDH 18Feb97
//DEADCODE JIM 24/03/99 			DUTYCAP=5,
//DEADCODE JIM 24/03/99 			DUTYCAS=6,
//DEADCODE JIM 24/03/99 			DUTYSPOT=7,
//DEADCODE JIM 24/03/99 //			DUTYCAP=0,
//DEADCODE JIM 24/03/99 //			DUTYHEAVYBOMB=1,
//DEADCODE JIM 24/03/99 //			DUTYBOMB=2,
//DEADCODE JIM 24/03/99 //			DUTYCLOSEESCORT=3,				//RDH 18Feb97
//DEADCODE JIM 24/03/99 //			DUTYHIGHESCORT=4,
//DEADCODE JIM 24/03/99 //			DUTYFLAKSUPP=5,
//DEADCODE JIM 24/03/99 //			DUTYRECONN=6,
//DEADCODE JIM 24/03/99 //			DUTYSPOT=7,
//DEADCODE JIM 24/03/99 //			DUTYNAPALM=8,
//DEADCODE JIM 24/03/99 //			DUTYROCKETS=9,
//DEADCODE JIM 24/03/99 //			DUTYSTRAFF=10,
//DEADCODE JIM 24/03/99 //			DUTYCAS=11,
//DEADCODE JIM 24/03/99 			
//DEADCODE JIM 24/03/99 			DUTY_ALIGN=0xffff};		//RDH 18Feb97

//DEADCODE DAW 22/03/00 inline	SWord&	operator *(DutyType& f){return(SWord&) f;}
enum	PackageAttackMethodAliases
{
	PACK_AM_RAF=0,
	PACK_AM_LWSTART=8,
		PACK_AM_DECOYPATROL,	//probably fighter patrol
		PACK_AM_RECON,			//probably bomber
		PACK_AM_DIVEBOMB,		//definite bomber
		PACK_AM_LEVELBOMB,
		PACK_AM_CHAINBOMB,

	PACK_AM_ESCORT=16,
	PACK_AM_ATTACHED=24,
	PACK_AM_RETURN=32,
	PACK_AM_MASK=-8,

	PACK_AM_SUBMETHOD_SHIFT	=8,			//These are only used in Persons3
	PACK_AM_SUBMETHOD_MASK	=0x0ff00,
	PACK_AM_MAINMETHOD_MASK	=0x000ff,	

	PACK_AM_SM_NOTBOMBERS	=0x00100,	//These are just so Mark can set in quick missions
	PACK_AM_SM_NOTFIGHTERS	=0x00200,
	PACK_AM_SM_STRAFFE		=0x00400

};

//MARK, here are the form types for flight and group levels		//RDH 05Mar99
enum	InFormation	 //got 6 bits!
{
	IF_ALLBAD=0,
	IF_NOCLIMB=1,
	IF_NOTURN=2,
	IF_NOACCEL=4,
	IF_ALLGOOD=7,
	IF_ALLGOODLEADER=32,

	IF_OUT_POS  = 0,													  //CSB 05/01/00
	IF_IN_POS   = 7,													  //CSB 05/01/00
	IF_NEAR_POS = 1														  //CSB 05/01/00
};

enum	FormationTypeIndex
{
		FTT_BIGV		=	0,
		FTT_LONGLINE	=	1,
		FTT_SHIPCONVOY1	=	2,


		FORMTYPE_WING	=	0x0007,	FORMTYPE_WING_SH=0,
			FTW_RAFVIC	=	0x0000,
			FTW_LWVIC	=	0x0001,
			FTW_FLAT5	=	0x0002,
			FTW_SCWARM	=	0x0003,
			FTW_BSCRWARM=	0x0004,
			FTW_FINGER	=	0x0005,
			FTW_RAFTAIL	=	0x0006,
			FTW_MAL		=	0x0007,

		FORMTYPE_SQUAD	=	0x0038,	FORMTYPE_SQUAD_SH=3,
			FTS_VIC		=	0x0000,
			FTS_ECHL	=	0x0008,
			FTS_ECHR	=	0x0010,
			FTS_ABREST	=	0x0018,
			FTS_ASTERN	=	0x0020,
			FTS_DIAMOND	=	0x0028,
			FTS_BOX		=	0x0030,
			FTS_WEAVE	=	0x0038,

		FORMTYPE_WINGSQUAD=	0x003f,	FORMTYPE_WINGSQUAD_SH=0,

		FORMTYPE_INTERCHILD	=	0x0040,	FORMTYPE_INTERCHILD_SH=6,

		FORMTYPE_INTER	=	0x0180,	FORMTYPE_INTER_SH=7,
			FTI_SAME	=	0x0000,
			FTI_DEFAULT	=	0x0000,
			FTI_ASTERN	=	0x0080,
			FTI_ABREST	=	0x0100,
			FTI_ABOVE	=	0x0180,
			FTI_SCWARM_SWAPPING_FLAG=FTI_ABREST,

		//This is a 'different' perspective on the   
		//INTER/INTERCHILD field relationship   
		FORMTYPE_INTERPAIR=	0x01c0,	FORMTYPE_INTERPAIR_SH=6,
			FTIP_GRUPII	=	0x0000,	//default 3 squad formation given squad formtype
			FTIP_GRUPIII=	0x0040,	
			FTIP_ASTERN	=	0x0080,	//escort positions and alternate formation
			FTIP_AHEAD	=	0x00c0,	FTIP_ASTERN2=	0x00c0,
			FTIP_LEFT	=	0x0100,
			FTIP_RIGHT	=	0x0140,	FTIP_LEFTBACK=	0x0140,	//for box Grupp
			FTIP_ABOVE	=	0x0180,
			FTIP_BELOW	=	0x01c0,


		FORMTYPE_COURSESEL=	0x0e00,	FORMTYPE_COURSESEL_SH=9,
			FTC_MAINFL	=	0x0000,
			FTC_RAF		=	0x0200,
			FTC_CEILING	=	0x0400,
			FTC_HIGH	=	0x0600,
			FTC_FWDHIGH	=	0x0800,
			FTC_FWDLVL	=	0x0A00,
			FTC_FWDLOW	=	0x0C00,
 			FTC_LATE	=	0x0E00,

		FORMTYPE_COURSEPOS=	0xf000,	FORMTYPE_COURSEPOS_SH=12,
			FTC_POSMUL	=	0x1000,

		FORMTYPE_COURSEPAIR=0xfe00,
			
//DEADCODE JIM 14/01/00 			FORM_V =0,				//ground mobiles			//MS 07Apr99
//DEADCODE JIM 14/01/00 			FORM_SINGLEFILE,		//ground mobiles			//MS 07Apr99
//DEADCODE JIM 14/01/00 			SQUAD_TAKEOFF,
//DEADCODE JIM 14/01/00 //UN SQUAD FORMATIONS
//DEADCODE JIM 14/01/00 			SQUAD_FLATV,	SQUAD_FIRST_UN=SQUAD_FLATV,
//DEADCODE JIM 14/01/00 			SQUAD_FLATV_Right,
//DEADCODE JIM 14/01/00 			SQUAD_FLATV_Left,
//DEADCODE JIM 14/01/00 			SQUAD_FLATV_Ahead,
//DEADCODE JIM 14/01/00 			SQUAD_STACKEDV,
//DEADCODE JIM 14/01/00 			SQUAD_STACKEDV_Right,
//DEADCODE JIM 14/01/00 			SQUAD_STACKEDV_Left,
//DEADCODE JIM 14/01/00 			SQUAD_STACKEDV_Ahead,
//DEADCODE JIM 14/01/00 			SQUAD_ECHELONRIGHT,
//DEADCODE JIM 14/01/00 			SQUAD_ECHELONRIGHT_Right,
//DEADCODE JIM 14/01/00 			SQUAD_ECHELONRIGHT_Left,	
//DEADCODE JIM 14/01/00 			SQUAD_ECHELONRIGHT_Ahead,
//DEADCODE JIM 14/01/00 			SQUAD_ECHELONLEFT,
//DEADCODE JIM 14/01/00 			SQUAD_ECHELONLEFT_Right,
//DEADCODE JIM 14/01/00 			SQUAD_ECHELONLEFT_Left,	
//DEADCODE JIM 14/01/00 			SQUAD_ECHELONLEFT_Ahead,
//DEADCODE JIM 14/01/00 			SQUAD_STACKEDLINE,
//DEADCODE JIM 14/01/00 			SQUAD_STACKEDLINE_Right,
//DEADCODE JIM 14/01/00 			SQUAD_STACKEDLINE_Left,	
//DEADCODE JIM 14/01/00 			SQUAD_STACKEDLINE_Ahead,
//DEADCODE JIM 14/01/00 			SQUAD_LINEABREAST,
//DEADCODE JIM 14/01/00 			SQUAD_LINEABREAST_Right,
//DEADCODE JIM 14/01/00 			SQUAD_LINEABREAST_Left,	
//DEADCODE JIM 14/01/00 			SQUAD_LINEABREAST_Ahead,
//DEADCODE JIM 14/01/00 			SQUAD_BOX,
//DEADCODE JIM 14/01/00 			SQUAD_BOX_Right,
//DEADCODE JIM 14/01/00 			SQUAD_BOX_Left,	
//DEADCODE JIM 14/01/00 			SQUAD_BOX_Ahead,
//DEADCODE JIM 14/01/00 			SQUAD_DIAMOND,
//DEADCODE JIM 14/01/00 			SQUAD_DIAMOND_Right,
//DEADCODE JIM 14/01/00 			SQUAD_DIAMOND_Left,	
//DEADCODE JIM 14/01/00 			SQUAD_DIAMOND_Ahead,
//DEADCODE JIM 14/01/00 //UN COMBAT FORMATIONS
//DEADCODE JIM 14/01/00 			SQUAD_COMBAT_FLATV,
//DEADCODE JIM 14/01/00 //MIG SQUAD FORMATIONS - NOT ACCESIBLE BY PLAYER				//MS 07Apr99
//DEADCODE JIM 14/01/00 			SQUAD_DECOY,	SQUAD_FIRST_MIG=SQUAD_DECOY,
//DEADCODE JIM 14/01/00 			SQUAD_UPPERCUT,										//MS 05Mar99
//DEADCODE JIM 14/01/00 			SQUAD_STAIRCASE,									//MS 05Mar99
//DEADCODE JIM 14/01/00 			SQUAD_3LEVELS,										//MS 05Mar99
//DEADCODE JIM 14/01/00 			SQUAD_STRING,										//MS 05Mar99
//DEADCODE JIM 14/01/00 			SQUAD_CH_ABREAST,									//MS 07Apr99
//DEADCODE JIM 14/01/00 			SQUAD_GAGGLE,										//MS 07Apr99
//DEADCODE JIM 14/01/00 			SQUAD_MIG_LEFT,
//DEADCODE JIM 14/01/00 			SQUAD_MIG_RIGHT,
//DEADCODE JIM 14/01/00 			SQUAD_VIC,
//DEADCODE JIM 14/01/00 //NOT ACCESSIBLE BY PLAYER										//MS 05Mar99
//DEADCODE JIM 14/01/00 			SQUAD_TRUCKCONVOY,
//DEADCODE JIM 14/01/00 			SQUAD_TRAINCONVOY,
//DEADCODE JIM 14/01/00 			SQUAD_BATTLELINE,
//DEADCODE JIM 14/01/00 			SQUAD_BAIT,
//DEADCODE JIM 14/01/00 			SQUAD_DUMMY02,										//MS 05Mar99
//DEADCODE JIM 14/01/00 			SQUAD_DUMMY03,										//MS 05Mar99
//DEADCODE JIM 14/01/00 			SQUAD_DUMMY04,										//MS 05Mar99
//DEADCODE JIM 14/01/00 			SQUAD_DUMMY05,										//MS 05Mar99
//DEADCODE JIM 14/01/00 			SQUAD_DUMMY06,										//MS 05Mar99
//DEADCODE JIM 14/01/00 //DEADCODE CSB 14/12/99 			SQUAD_DUMMY07,										//MS 05Mar99
//DEADCODE JIM 14/01/00 //DEADCODE CSB 14/12/99 			SQUAD_DUMMY08										//MS 05Mar99
//DEADCODE JIM 14/01/00 			SQUAD_CROSSOVERTURN_L,											  //CSB 14/12/99
//DEADCODE JIM 14/01/00 			SQUAD_CROSSOVERTURN_R											  //CSB 14/12/99
		};
inline	FormationTypeIndex	operator|(FormationTypeIndex a,FormationTypeIndex b)	{return FormationTypeIndex(int(a)|int(b));}					
inline	FormationTypeIndex	operator+(FormationTypeIndex a,FormationTypeIndex b)	{return a|b;}					
inline	FormationTypeIndex	operator&(FormationTypeIndex a,FormationTypeIndex b)	{return FormationTypeIndex(int(a)&int(b));}					
//DEADCODE JIM 09/02/00 inline	FormationTypeIndex	operator-(FormationTypeIndex a,FormationTypeIndex b)	{return a&b;}					
inline	FormationTypeIndex	operator%(FormationTypeIndex a,FormationTypeIndex b)	{return FormationTypeIndex(int(a)&~int(b));}					
inline	FormationTypeIndex	operator|=(FormationTypeIndex& a,FormationTypeIndex b)	{return a=a|b;}					
inline	FormationTypeIndex	operator+=(FormationTypeIndex& a,FormationTypeIndex b)	{return a=a+b;}					
inline	FormationTypeIndex	operator&=(FormationTypeIndex& a,FormationTypeIndex b)	{return a=a&b;}					
//DEADCODE JIM 09/02/00 inline	FormationTypeIndex	operator-=(FormationTypeIndex& a,FormationTypeIndex b)	{return a=a-b;}					
inline	FormationTypeIndex	operator%=(FormationTypeIndex& a,FormationTypeIndex b)	{return a=a%b;}					
struct	FormationType;
FormationType*	GetEscortTable(FormationTypeIndex fi);
//DEADCODE JIM 09/02/00 enum	SquadronTypeIndex	{STI_DUMMY};
MINMAX(FormationIndex,0,255);
MINMAX(InWing,0,15);		//high field
MINMAX(InForm,0,15);	//low field
inline	FormationIndex	operator	+	(InWing W,InForm F)			{return (FormationIndex) (((int)W<<4)+(int)F);}
inline	FormationIndex	operator	+	(InForm F,InWing W)			{return (FormationIndex) (((int)W<<4)+(int)F);}
inline	FormationIndex	operator	*	(InForm	F)					{return (FormationIndex)(F);}

inline	FormationIndex	operator	+=	(FormationIndex& I,InForm F){return (  I=(FormationIndex)  ( ((int)I&15) + (int)F )  );}
inline	FormationIndex	operator	+=	(FormationIndex& I,InWing W){return (  I=(FormationIndex)  ( (int)I + ((int)W<<4) )  );}
inline	FormationIndex	operator	+	(FormationIndex I,InWing W)	{return (  (FormationIndex)  ( (int)I + ((int)W<<4) )  );}
inline	FormationIndex	operator	+	(FormationIndex I,InForm F)	{return (  (FormationIndex)  ( ((int)I&15) + (int)F )  );}

inline	FormationIndex	operator	&	(FormationIndex I,InWing W)	{return   (FormationIndex)  ( ((int)I>>4) & (int)W  );}	//RDH 13May96
inline	FormationIndex	operator	&	(FormationIndex I,InForm F)	{return (  (FormationIndex)  ( (int)I & (int)F )  );}

enum	CharacterType
		{CHAR_TACTICIAN = 0,CHAR_MRAVERAGE,CHAR_CAVALIER,CHAR_TIMID,CHAR_align=255};		
enum	SkillType
		{	SKILL_NOVICE = 0,	SKILL_NOVICE1=15,SKILL_NOVICE2=30,
			SKILL_POOR = 45,	SKILL_POOR1 = 60,SKILL_POOR2 = 75,
			SKILL_REGULAR=90,	SKILL_REGULAR1=105,SKILL_REGULAR2=120,
			SKILL_VETERAN=135,	SKILL_VETERAN1=150,SKILL_VETERAN2=165,
			SKILL_ACE=180,		SKILL_ACE1=195,SKILL_ACE2=210,
			SKILL_HERO=225,		SKILL_HERO1=240,SKILL_HERO2=255,
			SKILL_STAGE=45,		SKILL_SUBSTAGE=15,
			SKILL_LOSSPERNEWPILOT=5,SKILL_GAINNEWPILOTSPERDAY=30,
			SKILL_MAX=255};

//DEADCODE DAW 16/02/00 enum	Potential
//DEADCODE DAW 16/02/00 		{
//DEADCODE DAW 16/02/00 			POTENTIAL_MAX		=15,
//DEADCODE DAW 16/02/00 			POTENTIAL_EXCELLENT	=13,
//DEADCODE DAW 16/02/00 			POTENTIAL_VERYGOOD	=11,
//DEADCODE DAW 16/02/00 			POTENTIAL_GOOD		=9,
//DEADCODE DAW 16/02/00 			POTENTIAL_REGULAR	=7,
//DEADCODE DAW 16/02/00 			POTENTIAL_POOR		=5,
//DEADCODE DAW 16/02/00 			POTENTIAL_VERYPOOR	=3,
//DEADCODE DAW 16/02/00 			POTENTIAL_NONE		=0
//DEADCODE DAW 16/02/00 		};
enum	MoraleType
		{MORALE_ROCKBOTTOM = 0,MORALE_VERYPOOR = 40,MORALE_STAGE = 40,MORALE_HALFSTAGE = 20,
//DeadCode RDH 27Mar98 			MORALE_MINUSHALFSTAGE = -20,
		MORALEINC_STEP = 120,
		MORALE_POOR =80,MORALE_MEDIUM = 120,MORALE_GOOD =160,MORALE_VERYGOOD = 200,MORALE_EXCELLENT = 240,MORALE_TOPMORALE = 255 };
#define			MORALE_MINUSHALFSTAGE (-MORALE_HALFSTAGE)

//DeadCode RDH 27Mar98 enum	DispositionType
//DeadCode RDH 27Mar98 		{	PESSIMISTIC = 0, REALISTIC,OPTIMISTIC
//DeadCode RDH 27Mar98 			};
enum	MeritType
		{MERIT_ROCKBOTTOM = 0,MERIT_INITIAL = 1000,MERIT_2LFTEXPERIENCED =5000,
		MERIT_LFT = 8000,
		MERIT_CAPTAIN = 12000,MERIT_MAJOR =18000,MERIT_MAJORHONOUR = 27000,
		MERIT_MAJORHONOURPLUS = 30000,MERIT_TOP = 65534,MERIT_IMPOSSIBLE = 65535,
		
//Spring Offensive merits to get operational		
		MERIT_OPERATIONAL = 3000
			

		};
//aims is to get 30000 merit points by end of campaign			//RDH 23Sep96
//Circus	36 kills: 2 kills a mission, 20 missions -> 750 merit per kill
enum	DeltaMeritType
		{
//DeadCode RDH 08Dec96 		MERIT_TARGET_DESTROYED = 3000,
		MERIT_TARGET_DESTROYED = 2000,							//RDH 08Dec96
		MERIT_KILL = 750,
		MERIT_VIS_MSN_SUCCESS =4000,
		MERIT_OP_CRASHLAND = -300,
		MERIT_OP_BENTGEAR = -100,
//DeadCode RDH 11Dec96 		MERIT_OP_KANGAROO = 300,
		MERIT_OP_GOODLANDING = 100,
		MERIT_OP_LANDEDONSQUARE = 500,
		MERIT_OP_STAYEDVCLOSETOCO = 3000,
		MERIT_OP_STAYEDCLOSETOCO = 1500,
		MERIT_OP_STAYEDINVICINITYOFCO = 1000,
		MERIT_OP_MILESFROMCO = -1000,
		MERIT_OP_SEENBYCO = -1000,
		MERIT_OP_NOTSEENBYCO =1000,
		MERIT_OP_HITSNEARCO = 3000

		};


//DeadCode RDH 27Mar98 enum 	AerobaticFactor {AEROBATIC_LOW,AEROBATIC_MEDIUM,AEROBATIC_HIGH};
//		Aerobaticfactor is used to determine type of aircraft	//RDH 03Mar98
//		perhaps it should be combat ability						//RDH 03Mar98
enum 	AerobaticFactor {AEROBATIC_LOW,			//medium bomber
						AEROBATIC_MEDIUM,		//prop
						AEROBATIC_HIGH,	 		//fighterbomber
						AEROBATIC_FIGHTER,		//sabre or mig
//						AEROBATIC_MIG,
//						AEROBATIC_SABRE,
						AEROBATIC_HIGHEST
						};
 
//DEADCODE AMM 12/01/00 enum	CallNames	{	Call_Pilot0=1,Call_Pilot29=30,
//DEADCODE AMM 12/01/00 						Call_FAC0,Call_FAC1,Call_FAC2,
//DEADCODE AMM 12/01/00 						Call_TAC0,Call_TAC1,Call_TAC2,
//DEADCODE AMM 12/01/00 						Call_Dentist,Call_Tower,
//DEADCODE AMM 12/01/00 					};

//DEADCODE JIM 04/03/99 enum	SquadNames
//DEADCODE JIM 04/03/99 		{
//DEADCODE JIM 04/03/99 
//DEADCODE JIM 04/03/99 			MySquadAce,TheirSquadAce,AnotherSquadAce,SqdnAce48,
//DEADCODE JIM 04/03/99 			SqdnAce56,Jasta11Ace,OttoKonnecke,FritzRumey,
//DEADCODE JIM 04/03/99 				SNEQU_LASTACE,
//DEADCODE JIM 04/03/99  			Jasta02,Jasta03,Jasta04,Jasta05,
//DEADCODE JIM 04/03/99 			Jasta06,Jasta07,Jasta08,Jasta10,
//DEADCODE JIM 04/03/99 			Jasta11,Jasta12,Jasta19,Jasta23,
//DEADCODE JIM 04/03/99 			Jasta32,Jasta64,Jasta65,JastaAnon,
//DEADCODE JIM 04/03/99 				SNEQU_SECONDSET,
//DEADCODE JIM 04/03/99 			Pursuit27,Pursuit95,Group02,Frog,
//DEADCODE JIM 04/03/99 			SquadAnon,SquadBIAF,Squad11,Squad29,
//DEADCODE JIM 04/03/99 			Squad40,Squad43,Squad48,Squad54,
//DEADCODE JIM 04/03/99 			Squad56,Squad60,Squad66,Squad70
//DEADCODE JIM 04/03/99 		};
//DEADCODE JIM 04/03/99 
//Blues are aggressive friendly forces (do the killing)
//Reds are aggressive unfriendly forces (get killed)
//green are non-aggressive neutral forces (bugger 'em)
//amber are aggressive neutral forces (bugger me)
//	 moved from worldinc 7/8/98
enum	Nationality	{NAT_RED=1,NAT_BLUE=2,NAT_GREEN=0,NAT_AMBER=3,NAT_ALIGN=255, NAT_RAF = NAT_RED, NAT_LUF = NAT_BLUE}; //CSB 17/12/99
enum FuelTankType	{FT_FIXED=0, FT_DROPTANK=1};

enum	QuickMissDamageTypes
{
	QMD_RANDOMTYPE,					//Chooses unused slot from list below.

	QMD_LEFTWINGOUT,				//Add LEVEL*int or RANDOMLEVEL or RANDOMLEVEL+LEVEL*int
	QMD_LEFTWINGIN,
	QMD_RIGHTWINGOUT,
	QMD_RIGHTWINGIN,
	QMD_ENGINELEFT,
	QMD_ENGINERIGHT,
	QMD_TAIL,
	QMD_FINLEFT,
	QMD_FINRIGHT,
	QMD_FRONT,
	QMD_LEFTWHEEL,
	QMD_RIGHTWHEEL,
	QMD_FUELTANK,
	QMD_CANOPY,
	QMD_OTHER,
	QMD_TOTAL_DAMAGE_LOCATIONS,

	QMD_FUELKILOS=0x00020,		//Add LEVEL*int
	QMD_FUELPERCENT,
	QMD_ENGINEPHASE,
	QMD_TOTAL_ALL_LOCATIONS,
	QMD_LOCATIONS_MASK=0xff,

	QMD_FUELKILOS_10	=0x00A20,
	QMD_FUELKILOS_100	=0x06420,
	QMD_FUELKILOS_TON	=0x40020,
	QMD_ENGINEPHASE_OFF	=0x00021,
	QMD_ENGINEPHASE_ON	=0x0ff21,


	QMD_LEVEL		=0x00100,
	QMD_NORMAL		=0x00000,
	QMD_LOW			=0x03300,
	QMD_MED			=0x06600,
	QMD_HIGH		=0x09900,
	QMD_DANGER		=0x0CC00,
	QMD_DEAD		=0x0ff00,
	QMD_LOCSHIFT	=	8,
	QMD_RANDOMLEVEL	=0x10000	//Add a level to set the max. level.
};

#endif


