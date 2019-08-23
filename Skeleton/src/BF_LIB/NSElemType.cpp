#include "stdafx.h"
#include "NSElemType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

NSElemMidNodeInfo _midElem[MAX_ELEMENT_TYPES];
TSeqEdgeInfo _seq_edge[MAX_ELEMENT_TYPES];

static BOOL RegisterFunction()
{
	memset(_midElem, 0, sizeof(_midElem));

	NSElemMidNodeInfo info;

	info.cntMidNode = 1;
	info.infoMidNode[0] = tagNSMidNodeInfo(2,0,1);
	_midElem[ELEMTYPE_LINE3] = info;

	info.cntMidNode = 3;
	info.infoMidNode[0] = tagNSMidNodeInfo(3,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(4,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(5,2,0);
	_midElem[ELEMTYPE_TRI6] = info;

	info.cntMidNode = 4;
	info.infoMidNode[0] = tagNSMidNodeInfo(4,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(5,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(6,2,3);
	info.infoMidNode[3] = tagNSMidNodeInfo(7,3,0);
	_midElem[ELEMTYPE_QUAD8] = info;

	info.cntMidNode = 6;
	info.infoMidNode[0] = tagNSMidNodeInfo(4,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(5,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(6,2,0);
	info.infoMidNode[3] = tagNSMidNodeInfo(7,0,3);
	info.infoMidNode[4] = tagNSMidNodeInfo(8,1,3);
	info.infoMidNode[5] = tagNSMidNodeInfo(9,2,3);
	_midElem[ELEMTYPE_TET10] = info;

	info.cntMidNode = 8;
	info.infoMidNode[0] = tagNSMidNodeInfo(5,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(6,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(7,2,3);
	info.infoMidNode[3] = tagNSMidNodeInfo(8,3,0);
	info.infoMidNode[4] = tagNSMidNodeInfo(9,0,4);
	info.infoMidNode[5] = tagNSMidNodeInfo(10,1,4);
	info.infoMidNode[6] = tagNSMidNodeInfo(11,2,4);
	info.infoMidNode[7] = tagNSMidNodeInfo(12,3,4);
	_midElem[ELEMTYPE_PYRAMID13] = info;

	info.cntMidNode = 9;
	info.infoMidNode[0] = tagNSMidNodeInfo(6,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(7,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(8,2,0);
	info.infoMidNode[3] = tagNSMidNodeInfo(9,3,4);
	info.infoMidNode[4] = tagNSMidNodeInfo(10,4,5); 
	info.infoMidNode[5] = tagNSMidNodeInfo(11,5,3);
	info.infoMidNode[6] = tagNSMidNodeInfo(12,0,3); 
	info.infoMidNode[7] = tagNSMidNodeInfo(13,1,4); 
	info.infoMidNode[8] = tagNSMidNodeInfo(14,2,5); 
	_midElem[ELEMTYPE_WEDGE15] = info;

	info.cntMidNode = 12;
	info.infoMidNode[0] = tagNSMidNodeInfo(8,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(9,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(10,2,3);
	info.infoMidNode[3] = tagNSMidNodeInfo(11,3,0);
	info.infoMidNode[4] = tagNSMidNodeInfo(12,4,5); 
	info.infoMidNode[5] = tagNSMidNodeInfo(13,5,6);
	info.infoMidNode[6] = tagNSMidNodeInfo(14,6,7); 
	info.infoMidNode[7] = tagNSMidNodeInfo(15,7,4); 
	info.infoMidNode[8] = tagNSMidNodeInfo(16,8,4); 
	info.infoMidNode[9] = tagNSMidNodeInfo(17,1,5); 
	info.infoMidNode[10]= tagNSMidNodeInfo(18,2,6); 
	info.infoMidNode[11]= tagNSMidNodeInfo(19,3,7); 
	_midElem[ELEMTYPE_HEX20] = info;

	//Interface
	info.cntMidNode = 2;
	info.infoMidNode[0] = tagNSMidNodeInfo(4,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(5,2,3);
	_midElem[ELEMTYPE_INTERFACE_LINE3] = info;

	info.cntMidNode = 6;
	info.infoMidNode[0] = tagNSMidNodeInfo(6,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(7,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(8,0,2);
	info.infoMidNode[3] = tagNSMidNodeInfo(9,3,4);
	info.infoMidNode[4] = tagNSMidNodeInfo(10,4,5);
	info.infoMidNode[5] = tagNSMidNodeInfo(11,3,5);
	_midElem[ELEMTYPE_INTERFACE_TRI6] = info;

	info.cntMidNode = 8;
	info.infoMidNode[0] = tagNSMidNodeInfo(8,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(9,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(10,2,3);
	info.infoMidNode[3] = tagNSMidNodeInfo(11,3,0);
	info.infoMidNode[4] = tagNSMidNodeInfo(12,4,5); 
	info.infoMidNode[5] = tagNSMidNodeInfo(13,5,6);
	info.infoMidNode[6] = tagNSMidNodeInfo(14,6,7); 
	info.infoMidNode[7] = tagNSMidNodeInfo(15,7,4); 	
	_midElem[ELEMTYPE_INTERFACE_QUAD8] = info;

	//Free Field
	info.cntMidNode = 2;
	info.infoMidNode[0] = tagNSMidNodeInfo(4,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(5,2,3);
	_midElem[ELEMTYPE_FREEFIELD_2D_LINE3] = info;

	info.cntMidNode = 3;
	info.infoMidNode[0] = tagNSMidNodeInfo(6,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(7,2,3);
	info.infoMidNode[1] = tagNSMidNodeInfo(8,4,5);
	_midElem[ELEMTYPE_FREEFIELD_3D_LINE3] = info;

	info.cntMidNode = 6;
	info.infoMidNode[0] = tagNSMidNodeInfo(6,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(7,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(8,0,2);
	info.infoMidNode[3] = tagNSMidNodeInfo(9,3,4);
	info.infoMidNode[4] = tagNSMidNodeInfo(10,4,5);
	info.infoMidNode[5] = tagNSMidNodeInfo(11,3,5);
	_midElem[ELEMTYPE_FREEFIELD_TRI6] = info;

	info.cntMidNode = 8;
	info.infoMidNode[0] = tagNSMidNodeInfo(8,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(9,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(10,2,3);
	info.infoMidNode[3] = tagNSMidNodeInfo(11,3,0);
	info.infoMidNode[4] = tagNSMidNodeInfo(12,4,5); 
	info.infoMidNode[5] = tagNSMidNodeInfo(13,5,6);
	info.infoMidNode[6] = tagNSMidNodeInfo(14,6,7); 
	info.infoMidNode[7] = tagNSMidNodeInfo(15,7,4); 	
	_midElem[ELEMTYPE_FREEFIELD_QUAD8] = info;

	info.cntMidNode = 4;
	info.infoMidNode[0] = tagNSMidNodeInfo(4,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(5,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(6,2,3);
	info.infoMidNode[3] = tagNSMidNodeInfo(7,3,0);
	_midElem[ELEMTYPE_INFINITE_QUAD8] = info;

	info.cntMidNode = 9;
	info.infoMidNode[0] = tagNSMidNodeInfo(6,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(7,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(8,2,0);
	info.infoMidNode[3] = tagNSMidNodeInfo(9,3,4);
	info.infoMidNode[4] = tagNSMidNodeInfo(10,4,5); 
	info.infoMidNode[5] = tagNSMidNodeInfo(11,5,3);
	info.infoMidNode[6] = tagNSMidNodeInfo(12,0,3); 
	info.infoMidNode[7] = tagNSMidNodeInfo(13,1,4); 
	info.infoMidNode[8] = tagNSMidNodeInfo(14,2,5); 
	_midElem[ELEMTYPE_INFINITE_WEDGE15] = info;

	info.cntMidNode = 12;
	info.infoMidNode[0] = tagNSMidNodeInfo(8,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(9,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(10,2,3);
	info.infoMidNode[3] = tagNSMidNodeInfo(11,3,0);
	info.infoMidNode[4] = tagNSMidNodeInfo(12,4,5); 
	info.infoMidNode[5] = tagNSMidNodeInfo(13,5,6);
	info.infoMidNode[6] = tagNSMidNodeInfo(14,6,7); 
	info.infoMidNode[7] = tagNSMidNodeInfo(15,7,4); 
	info.infoMidNode[8] = tagNSMidNodeInfo(16,8,4); 
	info.infoMidNode[9] = tagNSMidNodeInfo(17,1,5); 
	info.infoMidNode[10]= tagNSMidNodeInfo(18,2,6); 
	info.infoMidNode[11]= tagNSMidNodeInfo(19,3,7); 
	_midElem[ELEMTYPE_INFINITE_HEX20] = info;

	//Cutoffwall
	info.cntMidNode = 2;
	info.infoMidNode[0] = tagNSMidNodeInfo(4,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(5,2,3);
	_midElem[ELEMTYPE_CUTOFFWALL_LINE3] = info;

	info.cntMidNode = 6;
	info.infoMidNode[0] = tagNSMidNodeInfo(6,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(7,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(8,0,2);
	info.infoMidNode[3] = tagNSMidNodeInfo(9,3,4);
	info.infoMidNode[4] = tagNSMidNodeInfo(10,4,5);
	info.infoMidNode[5] = tagNSMidNodeInfo(11,3,5);
	_midElem[ELEMTYPE_CUTOFFWALL_TRI6] = info;

	info.cntMidNode = 8;
	info.infoMidNode[0] = tagNSMidNodeInfo(8,0,1);
	info.infoMidNode[1] = tagNSMidNodeInfo(9,1,2);
	info.infoMidNode[2] = tagNSMidNodeInfo(10,2,3);
	info.infoMidNode[3] = tagNSMidNodeInfo(11,3,0);
	info.infoMidNode[4] = tagNSMidNodeInfo(12,4,5); 
	info.infoMidNode[5] = tagNSMidNodeInfo(13,5,6);
	info.infoMidNode[6] = tagNSMidNodeInfo(14,6,7); 
	info.infoMidNode[7] = tagNSMidNodeInfo(15,7,4); 	
	_midElem[ELEMTYPE_CUTOFFWALL_QUAD8] = info;
	//////////////////////////////////////////////////////////////////////////
	for(long i = 0; i < MAX_ELEMENT_TYPES; i++)
	{
		memcpy(_seq_edge[i].edge, _etip[i].edge, sizeof(long)*MAX_EDGE*MAX_EDGE_NODE);
	}

	//귀찮으니 지금 필요한거만 적당히
	TSeqEdgeInfo seq_line3 = {{0,2,1}};
	_seq_edge[ELEMTYPE_LINE3] = seq_line3;

	TSeqEdgeInfo seq_interface3 = {{ {0,4,1}, {2,5,3} }};
	_seq_edge[ELEMTYPE_INTERFACE_LINE3] = seq_interface3;
	_seq_edge[ELEMTYPE_CUTOFFWALL_LINE3] = seq_interface3;

	return TRUE;
}

static BOOL bRegistered = RegisterFunction();