#ifndef __sqaud_h__
#define  __sqaud_h__

#include "flyinit.h"
enum	SquadNum
{
	SQ_ZERO=0,
	SQ_QMSPITA=SQ_ZERO,	//these entries are intended to make PT to PT conversion transparent.
	SQ_QMSPITB,
	SQ_QMHURRA,
	SQ_QMHURRB,
	SQ_QMDEF,
	SQ_QMBLEN,
	SQ_QM109,
	SQ_QM110,
	SQ_QM87,
	SQ_QM17,
	SQ_QM88,
	SQ_QM111,
	SQ_QM59,
	SQ_GM_ATruck,
	SQ_GM_ATank,
	SQ_GM_ATroop,
	SQ_GM_ATrain,
	SQ_GM_ATransportShip,	//18


	
	
	SQ_BR_START=PT_BADMAX,
	SQ_BR_32,
	SQ_BR_610,
	SQ_BR_501,
	SQ_BR_56,
	SQ_BR_151,
	SQ_BR_85,
	SQ_BR_64,
	SQ_BR_615,
	SQ_BR_111,
	SQ_BR_1Can,
	SQ_BR_54,
	SQ_BR_65,
	SQ_BR_74,
	SQ_BR_266,
	SQ_BR_43,
	SQ_BR_601,
	SQ_BR_145,
	SQ_BR_17,
	SQ_BR_85x,	 //??????
	SQ_BR_1,
	SQ_BR_257,
	SQ_BR_303,
	SQ_BR_87,
	SQ_BR_213,
	SQ_BR_238,
	SQ_BR_609,
	SQ_BR_152,
	SQ_BR_234,
	SQ_BR_92,
	SQ_BR_310,
	SQ_BR_19,
	SQ_BR_66,
	SQ_BR_242,
	SQ_BR_222,
	SQ_BR_611,
	SQ_BR_46,
	SQ_BR_229,
	SQ_BR_72,
	SQ_BR_249,
	SQ_BR_253,
	SQ_BR_605,
	SQ_BR_603,
	SQ_BR_41,
	SQ_BR_607,
	SQ_BR_602,
	SQ_BR_73,
	SQ_BR_504,
	SQ_BR_79,
	SQ_BR_302,
	SQ_BR_616,
	SQ_BR_3,
	SQ_BR_232,
	SQ_BR_245,	 //53
	SQ_BR_END,
	SQ_BR_DEFIENT,
	SQ_BR_BLENHEIM,

	SQ_LW_START, //72

	SQ_JG_3_1,	SQ_JG_3_2,	SQ_JG_3_3,
	SQ_JG_26_1,	SQ_JG_26_2,	SQ_JG_26_3,
	SQ_JG_51_1,	SQ_JG_51_2,	SQ_JG_51_3,
	SQ_JG_52_1,	SQ_JG_52_2,	SQ_JG_52_3,
	SQ_JG_54_1,	SQ_JG_54_2,	SQ_JG_54_3,
	SQ_ZG_26_1,	SQ_ZG_26_2,	SQ_ZG_26_3,
	SQ_ZG_76_1,	SQ_ZG_76_2,	SQ_ZG_76_3,
	SQ_KG_1_1,	SQ_KG_1_2,	SQ_KG_1_3,
	SQ_KG_2_1,	SQ_KG_2_2,	SQ_KG_2_3,
	SQ_KG_3_1,	SQ_KG_3_2,	SQ_KG_3_3,
	SQ_KG_4_1,	SQ_KG_4_2,	SQ_KG_4_3,
	SQ_KG_53_1,	SQ_KG_53_2,	SQ_KG_53_3,
	SQ_KG_76_1,	SQ_KG_76_2,	SQ_KG_76_3,
 //112
	SQ_JG_2_1,	SQ_JG_2_2,	SQ_JG_2_3,
	SQ_JG_27_1,	SQ_JG_27_2,	SQ_JG_27_3,
	SQ_JG_53_1,	SQ_JG_53_2,	SQ_JG_53_3,
	SQ_SG_1_1,	SQ_SG_1_2,	SQ_SG_1_3,
	SQ_SG_2_1,	SQ_SG_2_2,	SQ_SG_2_3,
	SQ_SG_77_1,	SQ_SG_77_2,	SQ_SG_77_3,
	SQ_ZG_2_1,	SQ_ZG_2_2,	SQ_ZG_2_3,
	SQ_KG_27_1,	SQ_KG_27_2,	SQ_KG_27_3,
	SQ_KG_51_1,	SQ_KG_51_2,	SQ_KG_51_3,
	SQ_KG_54_1,	SQ_KG_54_2,	SQ_KG_54_3,
	SQ_KG_55_1,	SQ_KG_55_2,	SQ_KG_55_3,	//24*3=72 Gruppen

	SQ_MAX		  //145 approx
};
#endif
