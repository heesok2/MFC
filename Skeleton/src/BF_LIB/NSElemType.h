#pragma once

#include "HeaderPre.h"

//////////////////////////////////////////////////////////////////////////
// Element Kinds 
#define MAX_ELEMENT_KIND		6	// Count

#define ELEMKIND_UNKNOWN		0	// Unknown Type 
#define ELEMKIND_POINT			1	// 0D Elements
#define ELEMKIND_BEAM			2	// 1D Elements
#define ELEMKIND_SHELL			3	// 2D Elements
#define ELEMKIND_SOLID			4	// 3D Elements
#define ELEMKIND_SPECIAL		5	// Special Types 

//////////////////////////////////////////////////////////////////////////
// Element Types
#define ELEMTYPE_SPECIAL_SIDX	30

//DB에 들어가는 값이므로 한번 입력된 타입의 번호를 바꾸지 말것
enum elem_type
{
	// Basic Types
	ELEMTYPE_UNKNOWN = 0,			// 0	Unknown
	ELEMTYPE_VERTEX,				// 1	0D
	ELEMTYPE_LINE2,					// 2	1D
	ELEMTYPE_LINE3,					// 3	1D
	ELEMTYPE_TRI3,					// 4	2D TRI
	ELEMTYPE_TRI6,					// 5	2D Parabolic TRI
	ELEMTYPE_QUAD4,					// 6	2D QUAD
	ELEMTYPE_QUAD8,					// 7	2D Parabolic QUAD
	ELEMTYPE_TET4,					// 8	3D TETRA
	ELEMTYPE_TET10,					// 9	3D Parabolic TETRA
	ELEMTYPE_PYRAMID5,				// 10	3D PYRAMID
	ELEMTYPE_PYRAMID13,				// 11	3D Parabolic PYRAMID
	ELEMTYPE_WEDGE6,				// 12	3D WEDGE
	ELEMTYPE_WEDGE15,				// 13	3D Parabolic Wedge
	ELEMTYPE_HEX8,					// 14	3D HEXA
	ELEMTYPE_HEX20,					// 15	3D Parabolic HEXA

	ELEMTYPE_SPRING_LOAD = ELEMTYPE_SPECIAL_SIDX,// 30	Designer: Spring Load
	ELEMTYPE_POINTINTERFACE,		// 31	
	ELEMTYPE_LINEINTERFACE,			// 32
	ELEMTYPE_PLANEINTERFACE,		// 33
	ELEMTYPE_REINFORCEMENTBAR,		// 34
	ELEMTYPE_REINFORCEMENTGRID,		// 35
	ELEMTYPE_RIGID_LINK,			// 36	Designer: Rigid Body Link
	ELEMTYPE_BOLT,					// 37	Designer: Bolt
	ELEMTYPE_SPRING,				// 38   Spring Ground/2Point Element
	ELEMTYPE_MASS,					// 39	Mass Ground/2Point Element
	ELEMTYPE_INTERPOLATION,			// 40	Interpolation Element
	ELEMTYPE_CON_MASS,				// 41	Con. Mass Element  (GTS Mass와 함께 사용)
	ELEMTYPE_BUSH,					// 42	Bush Ground/2Point Element
	ELEMTYPE_RIGID,					// 43	Rigid Body/Bar (GTS에서 Rigid Link로 활용)
	ELEMTYPE_DAMPER,				// 44	Damper Ground/2Point Element
	ELEMTYPE_GENWELD,				// 45	General Weld Type
	ELEMTYPE_INTERFACE_LINE2,		// 46	GTS: Interface 1D
	ELEMTYPE_INTERFACE_LINE3,		// 47	GTS: Interface 1D Parabolic
	ELEMTYPE_INTERFACE_TRI3,		// 48	GTS: Interface 2D TRI 
	ELEMTYPE_INTERFACE_TRI6,		// 49	GTS: Interface 2D Parabolic TRI
	ELEMTYPE_INTERFACE_QUAD4,		// 50	GTS: Interface 2D QUAD
	ELEMTYPE_INTERFACE_QUAD8,		// 51	GTS: Interface 2D Parabolic QUAD
	ELEMTYPE_PILE_TIP,				// 52	GTS: Pile Tip	
	ELEMTYPE_MATRIX_SPRING,			// 53   GTS: Matrix Spring
	ELEMTYPE_ELASTIC_LINK,			// 54	GTS: Elastic Link	
	ELEMTYPE_GAP,					// 55	Gap	2Point Element
	ELEMTYPE_FREEFIELD_2D_LINE2,	// 56	GTS: Free Field 1D
	ELEMTYPE_FREEFIELD_2D_LINE3,	// 57	GTS: Free Field 1D Parabolic
	ELEMTYPE_FREEFIELD_3D_LINE2,	// 58	GTS: Free Field 1D
	ELEMTYPE_FREEFIELD_3D_LINE3,	// 59	GTS: Free Field 1D Parabolic
	ELEMTYPE_FREEFIELD_TRI3,		// 60	GTS: Free Field 2D TRI 
	ELEMTYPE_FREEFIELD_TRI6,		// 61	GTS: Free Field 2D Parabolic TRI
	ELEMTYPE_FREEFIELD_QUAD4,		// 62	GTS: Free Field 2D QUAD
	ELEMTYPE_FREEFIELD_QUAD8,		// 63	GTS: Free Field 2D Parabolic QUAD
	ELEMTYPE_THRESIST,				// 64	CFD: Thermal Resistor/2Point Element
	ELEMTYPE_INFINITE_QUAD4,		// 65	GTS: Infinite 2D Quad
	ELEMTYPE_INFINITE_QUAD8,		// 66	GTS: Infinite 2D Quad Quadratic
	ELEMTYPE_INFINITE_WEDGE6,		// 67	GTS: Infinite 3D Wedge
	ELEMTYPE_INFINITE_WEDGE15,		// 68	GTS: Infinite 3D Wedge Quadratic
	ELEMTYPE_INFINITE_HEX8,			// 69	GTS: Infinite 3D Hex
	ELEMTYPE_INFINITE_HEX20,		// 70	GTS: Infinite 3D Hex Quadratic
	ELEMTYPE_CUTOFFWALL_LINE2,		// 71	GTS: CutOffWall 1D
	ELEMTYPE_CUTOFFWALL_LINE3,		// 72	GTS: CutOffWall 1D Parabolic
	ELEMTYPE_CUTOFFWALL_TRI3,		// 73	GTS: CutOffWall 2D TRI 
	ELEMTYPE_CUTOFFWALL_TRI6,		// 74	GTS: CutOffWall 2D Parabolic TRI
	ELEMTYPE_CUTOFFWALL_QUAD4,		// 75	GTS: CutOffWall 2D QUAD
	ELEMTYPE_CUTOFFWALL_QUAD8,		// 76	GTS: CutOffWall 2D Parabolic QUAD
	ELEMTYPE_INTERFACE_POINT,		// 77	GTS: Interface 0D
	ELEMTYPE_AXISYM_REINF,			// 78   GTS: Axisym Reinforcement 0D
	MAX_ELEMENT_TYPES				// Count
};

//////////////////////////////////////////////////////////////////////////
//
// Element Side Id를 통해서 각 Element Type의 Node idx를 알아낸다.
// Side id edge idx = 0~11 ( MAX: Hexa edge 12 )
// Side id face idx = 0~5  ( MAX: Hexa face 5  )
// 단 Line Element의 Edge Side id 및 Tri, Quad Element의 Face id는 0번째에 담는다.

//////////////////////////////////////////////////////////////////////////
// Element Type ID info
#define MAX_EDGE		12	// Hexa Max=12
#define MAX_FACE		6	// Hexa Max=6
#define MAX_NODE		20
#define MAX_EDGE_NODE	3	// Hexa20 Max=3
#define MAX_FACE_NODE	8	// Hexa20 Max=12
#define MAX_FACE_TRI	6	// QUAD8 Max=6
#define MAX_NEIGHBOR	8   // QUAD Interface=8 원래 Hexa Max=6였는데 허헣

typedef struct tagTElemTypeInfo {
	long nk;								// kind of element
	long nl;								// element neighbor count	
	long ns;								// node count except midnode
	long nn;								// node count include midnode
	long nc;								// side edge count
	long ne;								// side edge node count except midnode
	long nme;								// side edge node count include midnode	

	long nt[MAX_NEIGHBOR];					// neighbor type
	long lnn[MAX_NEIGHBOR];					// node count of each element neighbor except mid-node
	long lidx[MAX_NEIGHBOR][4];				// node indexes of each element neighbor except mid-node
	long fnn[MAX_NEIGHBOR];					// node count of each element neighbor with mid-node
	long fidx[MAX_NEIGHBOR][10];			// node indexes of each element neighbor with mid-node
	long cidx[MAX_NEIGHBOR][MAX_EDGE];		// side edge indexes of each element neighbor

	long nf[MAX_FACE];						// side face node count except midnode
	long nmf[MAX_FACE];						// side face node count include midnode	
	long edge[MAX_EDGE][MAX_EDGE_NODE];		// side edge node idx
	long face[MAX_FACE][MAX_FACE_NODE];		// side face node idx

	long nmid;								// midnode count
	long st;								// Topological Simple Type ( TET10 -> TET4 )

} TElemTypeInfo;

static TElemTypeInfo _etip[] = 
{
	// 0 : ELEMTYPE_UNKNOWN
	{
		{ ELEMKIND_UNKNOWN },		// kind of element	
	},

	// 1 : ELEMTYPE_VERTEX
	{
		{ ELEMKIND_POINT },			// kind of element	
		{ 0 },						// element neighbor count		
		{ 1 },						// node count except midnode
		{ 1 },						// node count include midnode		
		{ 0 },						// side edge count
		{ 1 },						// side edge node count except midnode
		{ 1 },						// side edge node count include midnode	
		{ 0, },						// neighbor type
		{ 0, },						// node count of each element neighbor
		{ {0,} },					// node indexes of each element neighbor 
		{ 0, },						// node count of each element neighbor with mid-node
		{ {0,} },					// node indexes of each element neighbor with mid-node
		{ {0,} },					// side edge indexes of each element neighbor
		{ 0, },						// side face node count except midnode
		{ 0, },						// side face node count include midnode	
		{ {0}, },					// side edge node idx
		{ {0}, },					// side face node idx
		{ 0 },						// midnode count		
		{ ELEMTYPE_VERTEX }			// Topological Simple Type ( TET10 -> TET4 )
		},

			// 2 : ELEMTYPE_LINE2
		{
			{ ELEMKIND_BEAM },						// kind of element
			{ 2 },									// element neighbor count		
			{ 2 },									// node count except midnode
			{ 2 },									// node count include midnode
			{ 1 },									// side edge count
			{ 2 },									// side edge node count except midnode
			{ 2 },									// side edge node count include midnode	
			{ ELEMTYPE_VERTEX, ELEMTYPE_VERTEX },	// neighbor type
			{ 1,1 },								// node count of each element neighbor
			{ {0,-1}, {1,-1} },						// node indexes of each element neighbor 
			{ 1,1 },								// node count of each element neighbor with mid-node
			{ {0,-1}, {1,-1} },						// node indexes of each element neighbor with mid-node
			{ {0,} },								// side edge indexes of each element neighbor
			{ 0, },									// side face node count except midnode
			{ 0, },									// side face node count include midnode	
			{ {0,1}, },								// side edge node idx
			{ {0,}, },								// side face node idx
			{ 0 },									// midnode count
			{ ELEMTYPE_LINE2 }						// Topological Simple Type ( TET10 -> TET4 )
		},

			// 3 : ELEMTYPE_LINE3
		{
			{ ELEMKIND_BEAM },						// kind of element
			{ 2 },									// element neighbor count		
			{ 2 },									// node count except midnode
			{ 3 },									// node count include midnode
			{ 1 },									// side edge count
			{ 2 },									// side edge node count except midnode
			{ 3 },									// side edge node count include midnode	
			{ ELEMTYPE_VERTEX, ELEMTYPE_VERTEX },	// neighbor type
			{ 1,1 },								// node count of each element neighbor
			{ {0,-1}, {1,-1} },						// node indexes of each element neighbor 
			{ 1,1 } ,								// node count of each element neighbor with mid-node
			{ {0,-1}, {1,-1} },						// node indexes of each element neighbor with mid-node
			{ {0,} },								// side edge indexes of each element neighbor
			{ 0, },									// side face node count except midnode
			{ 0, },									// side face node count include midnode	
			{ {0,1,2}, },							// side edge node idx
			{ {0,}, },								// side face node idx
			{ 1 },									// midnode count		
			{ ELEMTYPE_LINE2 }						// Topological Simple Type ( TET10 -> TET4 )
		},

			// 4 : ELEMTYPE_TRI3
		{
			{ ELEMKIND_SHELL },									// kind of element
			{ 3 },												// element neighbor count		
			{ 3 },												// node count except midnode
			{ 3 },												// node count include midnode
			{ 3 },												// side edge count
			{ 2 },												// side edge node count except midnode
			{ 2 },												// side edge node count include midnode	
			{ ELEMTYPE_LINE2, ELEMTYPE_LINE2, ELEMTYPE_LINE2 },	// neighbor type
			{ 2,2,2 },											// node count of each element neighbor
			{ {0,1,-1}, {1,2,-1}, {2,0,-1} },					// node indexes of each element neighbor 
			{ 2,2,2 },											// node count of each element neighbor with mid-node
			{ {0,1,-1}, {1,2,-1}, {2,0,-1} },					// node indexes of each element neighbor with mid-node
			{ {0},{1},{2} },									// side edge indexes of each element neighbor
			{ 3, },												// side face node count except midnode
			{ 3, },												// side face node count include midnode	
			{ {0,1}, {1,2}, {2,0} },							// side edge node idx
			{ {0,1,2}, },										// side face node idx
			{ 0 },												// midnode count
			{ ELEMTYPE_TRI3 }									// Topological Simple Type ( TET10 -> TET4 )
		},

			// 5 : ELEMTYPE_TRI6
		{
			{ ELEMKIND_SHELL },									// kind of element
			{ 3 },												// element neighbor count		
			{ 3 },												// node count except midnode
			{ 6 },												// node count include midnode
			{ 3 },												// side edge count
			{ 2 },												// side edge node count except midnode
			{ 3 },												// side edge node count include midnode	
			{ ELEMTYPE_LINE3, ELEMTYPE_LINE3, ELEMTYPE_LINE3 },	// neighbor type
			{ 2,2,2 },											// node count of each element neighbor
			{ {0,1,-1}, {1,2,-1}, {2,0,-1} },					// node indexes of each element neighbor 
			{ 3,3,3 },											// node count of each element neighbor with mid-node
			{ {0,1,3,-1}, {1,2,4,-1}, {2,0,5,-1} },				// node indexes of each element neighbor with mid-node
			{ {0},{1},{2} },									// side edge indexes of each element neighbor
			{ 3, },												// side face node count except midnode
			{ 6, },												// side face node count include midnode	
			{ {0,1,3}, {1,2,4}, {2,0,5} },						// side edge node idx
			{ {0,1,2,3,4,5}, },									// side face node idx
			{ 3 },												// midnode count
			{ ELEMTYPE_TRI3 }									// Topological Simple Type ( TET10 -> TET4 )
		},

			// 6 : ELEMTYPE_QUAD4
		{
			{ ELEMKIND_SHELL },													// kind of element
			{ 4 },																// element neighbor count		
			{ 4 },																// node count except midnode
			{ 4 },																// node count include midnode
			{ 4 },																// side edge count
			{ 2 },																// side edge node count except midnode
			{ 2 },																// side edge node count include midnode	
			{ ELEMTYPE_LINE2, ELEMTYPE_LINE2, ELEMTYPE_LINE2, ELEMTYPE_LINE2 },	// neighbor type
			{ 2,2,2,2 },														// node count of each element neighbor
			{ {0,1,-1}, {1,2,-1}, {2,3,-1}, {3,0,-1} },							// node indexes of each element neighbor 
			{ 2,2,2,2 },														// node count of each element neighbor with mid-node
			{ {0,1,-1}, {1,2,-1}, {2,3,-1}, {3,0,-1} },							// node indexes of each element neighbor with mid-node
			{ {0},{1},{2},{3} },												// side edge indexes of each element neighbor
			{ 4, },																// side face node count except midnode
			{ 4, },																// side face node count include midnode	
			{ {0,1}, {1,2}, {2,3}, {3,0} },										// side edge node idx
			{ {0,1,2,3}, },														// side face node idx
			{ 0 },																// midnode count
			{ ELEMTYPE_QUAD4 }													// Topological Simple Type ( TET10 -> TET4 )
		},

			// 7 : ELEMTYPE_QUAD8
		{
			{ ELEMKIND_SHELL },													// kind of element
			{ 4 },																// element neighbor count		
			{ 4 },																// node count except midnode
			{ 8 },																// node count include midnode
			{ 4 },																// side edge count
			{ 2 },																// side edge node count except midnode
			{ 3 },																// side edge node count include midnode	
			{ ELEMTYPE_LINE3, ELEMTYPE_LINE3, ELEMTYPE_LINE3, ELEMTYPE_LINE3 },	// neighbor type
			{ 2,2,2,2 },														// node count of each element neighbor
			{ {0,1,-1}, {1,2,-1}, {2,3,-1}, {3,0,-1} },							// node indexes of each element neighbor 
			{ 3,3,3,3 },														// node count of each element neighbor with mid-node
			{ {0,1,4,-1}, {1,2,5,-1}, {2,3,6,-1}, {3,0,7,-1} },					// node indexes of each element neighbor with mid-node
			{ {0},{1},{2},{3} },												// side edge indexes of each element neighbor
			{ 4, },																// side face node count except midnode
			{ 8, },																// side face node count include midnode	
			{ {0,1,4}, {1,2,5}, {2,3,6}, {3,0,7} },								// side edge node idx
			{ {0,1,2,3,4,5,6,7}, },												// side face node idx
			{ 4 },																// midnode count
			{ ELEMTYPE_QUAD4 }													// Topological Simple Type ( TET10 -> TET4 )
		},

			// 8 : ELEMTYPE_TET4
		{
			{ ELEMKIND_SOLID },													// kind of element
			{ 4 },																// element neighbor count
			{ 4 },																// node count except midnode
			{ 4 },																// node count include midnode
			{ 6 },																// side edge count
			{ 2 },																// side edge node count except midnode
			{ 2 },																// side edge node count include midnode	
			{ ELEMTYPE_TRI3, ELEMTYPE_TRI3, ELEMTYPE_TRI3, ELEMTYPE_TRI3 },		// neighbor type
			{ 3,3,3,3 },														// node count of each element neighbor
			{ {0,2,1,-1}, {0,1,3,-1}, {1,2,3,-1}, {2,0,3,-1} },					// node indexes of each element neighbor 
			{ 3,3,3,3 },														// node count of each element neighbor with mid-node
			{ {0,2,1,-1}, {0,1,3,-1}, {1,2,3,-1}, {2,0,3,-1} },					// node indexes of each element neighbor with mid-node
			{ {2,1,0},{0,4,3},{1,5,4},{2,3,5} },								// side edge indexes of each element neighbor
			{ 3, 3, 3, 3 },														// side face node count except midnode
			{ 3, 3, 3, 3 },														// side face node count include midnode	
			{ {0,1}, {1,2}, {2,0}, {0,3}, {1,3}, {2,3} },						// side edge node idx
			{ {0,2,1}, {0,1,3}, {1,2,3}, {2,0,3} },								// side face node idx
			{ 0 },																// midnode count
			{ ELEMTYPE_TET4 }													// Topological Simple Type ( TET10 -> TET4 )
		},

			// 9 : ELEMTYPE_TET10
		{
			{ ELEMKIND_SOLID },															// kind of element
			{ 4 },																		// element neighbor count
			{ 4 },																		// node count except midnode
			{ 10 },																		// node count include midnode
			{ 6 },																		// side edge count
			{ 2 },																		// side edge node count except midnode
			{ 3 },																		// side edge node count include midnode	
			{ ELEMTYPE_TRI6, ELEMTYPE_TRI6, ELEMTYPE_TRI6, ELEMTYPE_TRI6 },				// neighbor type
			{ 3,3,3,3 },																// node count of each element neighbor
			{ {0,2,1,-1}, {0,1,3,-1}, {1,2,3,-1}, {2,0,3,-1} },							// node indexes of each element neighbor 
			{ 6,6,6,6 },																// node count of each element neighbor with mid-node
			{ {0,2,1,6,5,4,-1}, {0,1,3,4,8,7,-1}, {1,2,3,5,9,8,-1}, {2,0,3,6,7,9,-1} },	// node indexes of each element neighbor with mid-node
			{ {2,1,0},{0,4,3},{1,5,4},{2,3,5} },										// side edge indexes of each element neighbor
			{ 3, 3, 3, 3 },																// side face node count except midnode
			{ 6, 6, 6, 6 },																// side face node count include midnode	
			{ {0,1,4}, {1,2,5}, {2,0,6}, {0,3,7}, {1,3,8}, {2,3,9} },					// side edge node idx
			{ {0,2,1,6,5,4}, {0,1,3,4,8,7}, {1,2,3,5,9,8}, {2,0,3,6,7,9} },				// side face node idx
			{ 6 },																		// midnode count
			{ ELEMTYPE_TET4 }															// Topological Simple Type ( TET10 -> TET4 )
		},

			// 10 : ELEMTYPE_PYRAMID5
		{
			{ ELEMKIND_SOLID },																// kind of element
			{ 5 },																			// element neighbor count
			{ 5 },																			// node count except midnode
			{ 5 },																			// node count include midnode
			{ 8 },																			// side edge count
			{ 2 },																			// side edge node count except midnode
			{ 2 },																			// side edge node count include midnode	
			{ ELEMTYPE_QUAD4, ELEMTYPE_TRI3, ELEMTYPE_TRI3, ELEMTYPE_TRI3, ELEMTYPE_TRI3 },	// neighbor type
			{ 4,3,3,3,3 },																	// node count of each element neighbor
			{ {0,3,2,1}, {0,1,4,-1}, {1,2,4,-1}, {2,3,4,-1}, {3,0,4,-1} },					// node indexes of each element neighbor 
			{ 4,3,3,3,3 },																	// node count of each element neighbor with mid-node
			{ {0,3,2,1}, {0,1,4,-1}, {1,2,4,-1}, {2,3,4,-1}, {3,0,4,-1} },					// node indexes of each element neighbor with mid-node
			{ {3,2,1,0}, {0,5,4,-1}, {1,6,5,-1}, {2,7,6,-1}, {3,4,7,-1} },					// side edge indexes of each element neighbor
			{ 4, 3, 3, 3, 3 },																// side face node count except midnode
			{ 4, 3, 3, 3, 3 },																// side face node count include midnode	
			{ {0,1}, {1,2}, {2,3}, {3,0}, {0,4}, {1,4}, {2,4}, {3,4} },						// side edge node idx
			{ {0,3,2,1}, {0,1,4,-1}, {1,2,4,-1}, {2,3,4,-1}, {3,0,4,-1} },					// side face node idx
			{ 0 },																			// midnode count
			{ ELEMTYPE_PYRAMID5 }															// Topological Simple Type ( TET10 -> TET4 )
		},

			// 11 : ELEMTYPE_PYRAMID13
		{
			{ ELEMKIND_SOLID },																										// kind of element
			{ 5 },																													// element neighbor count
			{ 5 },																													// node count except midnode
			{ 13 },																													// node count include midnode
			{ 8 },																													// side edge count
			{ 2 },																													// side edge node count except midnode
			{ 3 },																													// side edge node count include midnode	
			{ ELEMTYPE_QUAD8, ELEMTYPE_TRI6, ELEMTYPE_TRI6, ELEMTYPE_TRI6, ELEMTYPE_TRI6 },											// neighbor type
			{ 4,3,3,3,3 },																											// node count of each element neighbor
			{ {0,3,2,1}, {0,1,4,-1}, {1,2,4,-1}, {2,3,4,-1}, {3,0,4,-1} },															// node indexes of each element neighbor 
			{ 8,6,6,6,6 },																											// node count of each element neighbor with mid-node
			{ {0,3,2,1,8,7,6,5,-1}, {0,1,4,5,10,9,0,0,-1}, {1,2,4,6,11,10,0,0,-1}, {2,3,4,7,12,11,0,0,-1}, {3,0,4,8,9,12,0,0,-1} },	// node indexes of each element neighbor with mid-node
			{ {3,2,1,0}, {0,5,4,-1}, {1,6,5,-1}, {2,7,6,-1}, {3,4,7,-1} },															// side edge indexes of each element neighbor
			{ 4, 3, 3, 3, 3 },																										// side face node count except midnode
			{ 8, 6, 6, 6, 6 },																										// side face node count include midnode	
			{ {0,1,5}, {1,2,6}, {2,3,7}, {3,0,8}, {0,4,9}, {1,4,10}, {2,4,11}, {3,4,12} },											// side edge node idx
			{ {0,3,2,1,8,7,6,5}, {0,1,4,5,10,9,0,0}, {1,2,4,6,11,10,0,0}, {2,3,4,7,12,11,0,0}, {3,0,4,8,9,12,0,0} },				// side face node idx
			{ 8 },																													// midnode count
			{ ELEMTYPE_PYRAMID5 }																									// Topological Simple Type ( TET10 -> TET4 )
		},

			// 12 : ELEMTYPE_WEDGE6
		{
			{ ELEMKIND_SOLID },																	// kind of element
			{ 5 },																				// element neighbor count
			{ 6 },																				// node count except midnode
			{ 6 },																				// node count include midnode
			{ 9 },																				// side edge count
			{ 2 },																				// side edge node count except midnode
			{ 2 },																				// side edge node count include midnode	
			{ ELEMTYPE_TRI3, ELEMTYPE_TRI3, ELEMTYPE_QUAD4, ELEMTYPE_QUAD4, ELEMTYPE_QUAD4 },	// neighbor type
			{ 3,3,4,4,4 },																		// node count of each element neighbor
			{ {0,2,1,-1}, {3,4,5,-1}, {0,1,4,3}, {1,2,5,4}, {2,0,3,5} },						// node indexes of each element neighbor 
			{ 3,3,4,4,4 },																		// node count of each element neighbor with mid-node
			{ {0,2,1,-1}, {3,4,5,-1}, {0,1,4,3}, {1,2,5,4}, {2,0,3,5} },						// node indexes of each element neighbor with mid-node
			{ {2,1,0,-1}, {3,4,5,-1}, {0,7,3,6}, {1,8,4,7}, {2,6,5,8} },						// side edge indexes of each element neighbor
			{ 3, 3, 4, 4, 4 },																	// side face node count except midnode
			{ 3, 3, 4, 4, 4 },																	// side face node count include midnode	
			{ {0,1}, {1,2}, {2,0}, {3,4}, {4,5}, {5,3}, {0,3}, {1,4}, {2,5} },					// side edge node idx
			{ {0,2,1,-1}, {3,4,5,-1}, {0,1,4,3}, {1,2,5,4}, {2,0,3,5} },						// side face node idx
			{ 0 },																				// midnode count
			{ ELEMTYPE_WEDGE6 }																	// Topological Simple Type ( TET10 -> TET4 )
		},

			// 13 : ELEMTYPE_WEDGE15
		{
			{ ELEMKIND_SOLID },																								// kind of element
			{ 5 },																											// element neighbor count
			{ 6 },																											// node count except midnode
			{ 15 },																											// node count include midnode
			{ 9 },																											// side edge count
			{ 2 },																											// side edge node count except midnode
			{ 3 },																											// side edge node count include midnode	
			{ ELEMTYPE_TRI6, ELEMTYPE_TRI6, ELEMTYPE_QUAD8, ELEMTYPE_QUAD8, ELEMTYPE_QUAD8 },								// neighbor type
			{ 3,3,4,4,4 },																									// node count of each element neighbor
			{ {0,2,1,-1}, {3,4,5,-1}, {0,1,4,3}, {1,2,5,4}, {2,0,3,5} },													// node indexes of each element neighbor 
			{ 6,6,8,8,8 },																									// node count of each element neighbor with mid-node
			{ {0,2,1,8,7,6,0,0}, {3,4,5,9,10,11,0,0}, {0,1,4,3,6,13,9,12}, {1,2,5,4,7,14,10,13}, {2,0,3,5,8,12,11,14} },	// node indexes of each element neighbor with mid-node
			{ {2,1,0,-1}, {3,4,5,-1}, {0,7,3,6}, {1,8,4,7}, {2,6,5,8} },													// side edge indexes of each element neighbor
			{ 3, 3, 4, 4, 4 },																								// side face node count except midnode
			{ 6, 6, 8, 8, 8 },																								// side face node count include midnode	
			{ {0,1,6}, {1,2,7}, {2,0,8}, {3,4,9}, {4,5,10}, {5,3,11}, {0,3,12}, {1,4,13}, {2,5,14} },						// side edge node idx
			{ {0,2,1,8,7,6,0,0}, {3,4,5,9,10,11,0,0}, {0,1,4,3,6,13,9,12}, {1,2,5,4,7,14,10,13}, {2,0,3,5,8,12,11,14} },	// side face node idx
			{ 9 },																											// midnode count
			{ ELEMTYPE_WEDGE6 }																								// Topological Simple Type ( TET10 -> TET4 )
		},

			// 14 : ELEMTYPE_HEX8
		{
			{ ELEMKIND_SOLID },																						// kind of element
			{ 6 },																									// element neighbor count
			{ 8 },																									// node count except midnode
			{ 8 },																									// node count include midnode
			{ 12 },																									// side edge count
			{ 2 },																									// side edge node count except midnode
			{ 2 },																									// side edge node count include midnode	
			{ ELEMTYPE_QUAD4, ELEMTYPE_QUAD4, ELEMTYPE_QUAD4, ELEMTYPE_QUAD4, ELEMTYPE_QUAD4, ELEMTYPE_QUAD4 },		// neighbor type
			{ 4,4,4,4,4,4 },																						// node count of each element neighbor
			{ {0,3,2,1}, {4,5,6,7}, {0,1,5,4}, {1,2,6,5}, {6,2,3,7}, {0,4,7,3} },									// node indexes of each element neighbor 
			{ 4,4,4,4,4,4 },																						// node count of each element neighbor with mid-node
			{ {0,3,2,1}, {4,5,6,7}, {0,1,5,4}, {1,2,6,5}, {6,2,3,7}, {0,4,7,3} },									// node indexes of each element neighbor with mid-node
			{ {3,2,1,0}, {4,5,6,7}, {0,9,4,8}, {1,10,5,9},{10,2,11,6},{8,7,11,3} },									// side edge indexes of each element neighbor
			{ 4, 4, 4, 4, 4, 4 },																					// side face node count except midnode
			{ 4, 4, 4, 4, 4, 4 },																					// side face node count include midnode	
			{ {0,1}, {1,2}, {2,3}, {3,0}, {4,5}, {5,6}, {6,7}, {7,4}, {0,4}, {1,5}, {2,6}, {3,7} },					// side edge node idx
			{ {0,3,2,1}, {4,5,6,7}, {0,1,5,4}, {1,2,6,5}, {2,3,7,6}, {3,0,4,7} },									// side face node idx
			{ 0 },																									// midnode count
			{ ELEMTYPE_HEX8 }																						// Topological Simple Type ( TET10 -> TET4 )
		},

			// 15 : ELEMTYPE_HEX20
		{
			{ ELEMKIND_SOLID },																															// kind of element
			{ 6 },																																		// element neighbor count
			{ 8 },																																		// node count except midnode
			{ 20 },																																		// node count include midnode
			{ 12 },																																		// side edge count
			{ 2 },																																		// side edge node count except midnode
			{ 3 },																																		// side edge node count include midnode	
			{ ELEMTYPE_QUAD8, ELEMTYPE_QUAD8, ELEMTYPE_QUAD8, ELEMTYPE_QUAD8, ELEMTYPE_QUAD8, ELEMTYPE_QUAD8 },											// neighbor type
			{ 4,4,4,4,4,4 },																															// node count of each element neighbor
			{ {0,3,2,1}, {4,5,6,7}, {0,1,5,4}, {1,2,6,5}, {6,2,3,7}, {0,4,7,3} },																		// node indexes of each element neighbor 
			{ 8,8,8,8,8,8 },																															// node count of each element neighbor with mid-node
			{ {3,2,1,0,10,9,8,11}, {4,5,6,7,12,13,14,15}, {0,1,5,4,8,17,12,16}, {1,2,6,5,9,18,13,17}, {2,3,7,6,10,19,14,18}, {4,7,3,0,15,19,11,16} },	// node indexes of each element neighbor with mid-node
			{ {3,2,1,0}, {4,5,6,7}, {0,9,4,8}, {1,10,5,9},{10,2,11,6},{8,7,11,3} },																		// side edge indexes of each element neighbor
			{ 4, 4, 4, 4, 4, 4 },																														// side face node count except midnode
			{ 8, 8, 8, 8, 8, 8 },																														// side face node count include midnode	
			{ {0,1,8}, {1,2,9}, {2,3,10}, {3,0,11}, {4,5,12}, {5,6,13}, {6,7,14}, {7,4,15}, {0,4,16}, {1,5,17}, {2,6,18}, {3,7,19} },					// side edge node idx
			{ {0,3,2,1,11,10,9,8}, {4,5,6,7,12,13,14,15}, {0,1,5,4,8,17,12,16}, {1,2,6,5,9,18,13,17}, {2,3,7,6,10,19,14,18}, {3,0,4,7,11,16,15,19} },	// side face node idx
			{ 12 },																																		// midnode count
			{ ELEMTYPE_HEX8 }																															// Topological Simple Type ( TET10 -> TET4 )
		},
			// 16 ~ 29 Reserved
		{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},

		// 30 : ELEMTYPE_SPRING_LOAD
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 31 : ELEMTYPE_PointInterface
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 32 : ELEMTYPE_LineInterface
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 33 : ELEMTYPE_PlaneInterface
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 34 : ELEMTYPE_ReinforcementBar
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 35 : ELEMTYPE_ReinforcementGrid
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 36 : ELEMTYPE_RIGID_LINK
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 37 : ELEMTYPE_BOLT
		{
			{ ELEMKIND_SPECIAL},						// kind of element
			{ 2 },										// element neighbor count
			{ 2 },										// node count except midnode
			{ 2 },										// node count include midnode
			{ 1 },										// side edge count
			{ 2 },										// side edge node count except midnode
			{ 2 },										// side edge node count include midnode	
			{ ELEMTYPE_VERTEX, ELEMTYPE_VERTEX },		// neighbor type
			{ 1,1 },									// node count of each element neighbor
			{ {0,-1}, {1,-1} },							// node indexes of each element neighbor 
			{ 1,1 },									// node count of each element neighbor with mid-node
			{ {0,-1}, {1,-1} },							// node indexes of each element neighbor with mid-node
			{ {0} },									// side edge indexes of each element neighbor
			{ 0, },										// side face node count except midnode
			{ 0, },										// side face node count include midnode	
			{ {0,1}, },									// side edge node idx
			{ {0,}, },									// side face node idx
			{ 0 },										// midnode count
			{ ELEMTYPE_BOLT }							// Topological Simple Type ( TET10 -> TET4 )
		},

			// 38 : ELEMTYPE_SPRING
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 39 : ELEMTYPE_MASS
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 40 : ELEMTYPE_INTERPOLATION
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},
			// 41 : ELEMTYPE_CON_MASS
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 42 : ELEMTYPE_BUSH
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 43 : ELEMTYPE_RIGID
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 44 : ELEMTYPE_DAMPER
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 45 : ELEMTYPE_GENWELD
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},
			// 46 : ELEMTYPE_INTERFACE_LINE2
		{
			{ ELEMKIND_SPECIAL },					// kind of element
			{ 0 },									// element neighbor count		
			{ 4 },									// node count except midnode
			{ 4 },									// node count include midnode
			{ 2 },									// side edge count
			{ 2 },									// side edge node count except midnode
			{ 2 },									// side edge node count include midnode	
			{ 0 }, 									// neighbor type
			{ 0 },									// node count of each element neighbor
			{ 0 },									// node indexes of each element neighbor 
			{ 0 },									// node count of each element neighbor with mid-node
			{ 0 },									// node indexes of each element neighbor with mid-node
			{ 0 },									// side edge indexes of each element neighbor
			{ 0, },									// side face node count except midnode
			{ 0, },									// side face node count include midnode	
			{ {0,1}, {2,3} },						// side edge node idx
			{ {0,}, },								// side face node idx
			{ 0 },									// midnode count
			{ ELEMTYPE_INTERFACE_LINE2 }			// Topological Simple Type ( TET10 -> TET4 )
		},
			// 47 : ELEMTYPE_INTERFACE_LINE3
		{
			{ ELEMKIND_SPECIAL },					// kind of element
			{ 0 },									// element neighbor count		
			{ 4 },									// node count except midnode
			{ 6 },									// node count include midnode
			{ 2 },									// side edge count
			{ 2 },									// side edge node count except midnode
			{ 3 },									// side edge node count include midnode	
			{ 0 }, 									// neighbor type
			{ 0 },									// node count of each element neighbor
			{ 0 },									// node indexes of each element neighbor 
			{ 0 },									// node count of each element neighbor with mid-node
			{ 0 },									// node indexes of each element neighbor with mid-node
			{ 0 },									// side edge indexes of each element neighbor
			{ 0, },									// side face node count except midnode
			{ 0, },									// side face node count include midnode	
			{ {0,1,4}, {2,3,5} },					// side edge node idx
			{ {0,}, },								// side face node idx
			{ 2 },									// midnode count
			{ ELEMTYPE_INTERFACE_LINE2 }			// Topological Simple Type ( TET10 -> TET4 )
		},

			// 48 : ELEMTYPE_INTERFACE_TRI3
		{
			{ ELEMKIND_SPECIAL },								// kind of element
			{ 0 },												// element neighbor count		
			{ 6 },												// node count except midnode
			{ 6 },												// node count include midnode
			{ 6 },												// side edge count
			{ 2 },												// side edge node count except midnode
			{ 2 },												// side edge node count include midnode	
			{ 0 }, 												// neighbor type
			{ 0 },												// node count of each element neighbor
			{ 0 },												// node indexes of each element neighbor
			{ 0 },												// node count of each element neighbor with mid-node
			{ 0 },												// node indexes of each element neighbor with mid-node
			{ 0 },												// side edge indexes of each element neighbor
			{ 3, 3},											// side face node count except midnode
			{ 3, 3},											// side face node count include midnode	
			{ {0,1}, {1,2}, {2,0}, {3,4}, {4,5}, {5,3} },		// side edge node idx
			{ {0,1,2}, {3,4,5} },								// side face node idx
			{ 0 },												// midnode count
			{ ELEMTYPE_INTERFACE_TRI3 }							// Topological Simple Type ( TET10 -> TET4 )
		},

			// 49 : ELEMTYPE_INTERFACE_TRI6
		{
			{ ELEMKIND_SPECIAL },								// kind of element
			{ 0 },												// element neighbor count		
			{ 6 },												// node count except midnode
			{ 12},												// node count include midnode
			{ 6 },												// side edge count
			{ 2 },												// side edge node count except midnode
			{ 3 },												// side edge node count include midnode	
			{ 0 }, 												// neighbor type
			{ 0 },												// node count of each element neighbor
			{ 0 },												// node indexes of each element neighbor 
			{ 0 },												// node count of each element neighbor with mid-node
			{ 0 },												// node indexes of each element neighbor with mid-node
			{ 0 },												// side edge indexes of each element neighbor
			{ 3, 3},											// side face node count except midnode
			{ 6, 6},											// side face node count include midnode	
			{ {0,1,6}, {1,2,7}, {2,0,8}, {3,4,9}, {4,5,10}, {5,3,11} },		// side edge node idx
			{ {0,1,2,6,7,8}, {3,4,5,9,10,11} },					// side face node idx
			{ 6 },												// midnode count
			{ ELEMTYPE_INTERFACE_TRI3 }							// Topological Simple Type ( TET10 -> TET4 )
		},

			// 50 : ELEMTYPE_INTERFACE_QUAD4
		{
			{ ELEMKIND_SPECIAL },												// kind of element
			{ 0 },																// element neighbor count		
			{ 8 },																// node count except midnode
			{ 8 },																// node count include midnode
			{ 8 },																// side edge count
			{ 2 },																// side edge node count except midnode
			{ 2 },																// side edge node count include midnode	
			{ 0 }, 																// neighbor type
			{ 0 },																// node count of each element neighbor
			{ 0 },																// node indexes of each element neighbor 
			{ 0 },																// node count of each element neighbor with mid-node
			{ 0 },																// node indexes of each element neighbor with mid-node
			{ 0 },																// side edge indexes of each element neighbor
			{ 8, },																// side face node count except midnode
			{ 8, },																// side face node count include midnode	
			{ {0,1}, {1,2}, {2,3}, {3,0},{4,5}, {5,6}, {6,7}, {7,4} },			// side edge node idx
			{ {0,1,2,3}, {4,5,6,7} },											// side face node idx
			{ 0 },																// midnode count
			{ ELEMTYPE_INTERFACE_QUAD4 }										// Topological Simple Type ( TET10 -> TET4 )
		},

			// 51 : ELEMTYPE_INTERFACE_QUAD8
		{
			{ ELEMKIND_SPECIAL },												// kind of element
			{ 0 },																// element neighbor count		
			{ 8 },																// node count except midnode
			{ 16 },																// node count include midnode
			{ 8 },																// side edge count
			{ 2 },																// side edge node count except midnode
			{ 3 },																// side edge node count include midnode	
			{ 0 }, 																// neighbor type
			{ 0 },																// node count of each element neighbor
			{ 0 },																// node indexes of each element neighbor 
			{ 0 },																// node count of each element neighbor with mid-node
			{ 0 },																// node indexes of each element neighbor with mid-node
			{ 0 },																// side edge indexes of each element neighbor
			{ 8, },																// side face node count except midnode
			{ 16, },															// side face node count include midnode	
			{ {0,1,8}, {1,2,9}, {2,3,10}, {3,0,11},{4,5,12}, {5,6,13}, {6,7,14}, {7,4,15} }, // side edge node idx
			{ {0,1,2,3,8,9,10,11}, {4,5,6,7,12,13,14,15} },						// side face node idx
			{ 8 },																// midnode count
			{ ELEMTYPE_INTERFACE_QUAD4 }										// Topological Simple Type ( TET10 -> TET4 )
		},

			// 52 : ELEMTYPE_PILE_TIP
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 53 : ELEMTYPE_MATRIX_SPRING
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 54 : ELEMTYPE_ELASTIC_LINK
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 55 : ELEMTYPE_GAP
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 56 : ELEMTYPE_FREEFIELD_2D_LINE2
		{
			{ ELEMKIND_SPECIAL },					// kind of element
			{ 0 },									// element neighbor count		
			{ 4 },									// node count except midnode
			{ 4 },									// node count include midnode
			{ 2 },									// side edge count
			{ 2 },									// side edge node count except midnode
			{ 2 },									// side edge node count include midnode	
			{ 0 }, 									// neighbor type
			{ 0 },									// node count of each element neighbor
			{ 0 },									// node indexes of each element neighbor 
			{ 0 },									// node count of each element neighbor with mid-node
			{ 0 },									// node indexes of each element neighbor with mid-node
			{ 0 },									// side edge indexes of each element neighbor
			{ 0, },									// side face node count except midnode
			{ 0, },									// side face node count include midnode	
			{ {0,1}, {2,3} },						// side edge node idx
			{ {0,}, },								// side face node idx
			{ 0 },									// midnode count
			{ ELEMTYPE_FREEFIELD_2D_LINE2 }			// Topological Simple Type ( TET10 -> TET4 )
		},

			// 57 : ELEMTYPE_FREEFIELD_2D_LINE3
		{
			{ ELEMKIND_SPECIAL },					// kind of element
			{ 0 },									// element neighbor count		
			{ 4 },									// node count except midnode
			{ 6 },									// node count include midnode
			{ 2 },									// side edge count
			{ 2 },									// side edge node count except midnode
			{ 3 },									// side edge node count include midnode	
			{ 0 }, 									// neighbor type
			{ 0 },									// node count of each element neighbor
			{ 0 },									// node indexes of each element neighbor 
			{ 0 },									// node count of each element neighbor with mid-node
			{ 0 },									// node indexes of each element neighbor with mid-node
			{ 0 },									// side edge indexes of each element neighbor
			{ 0, },									// side face node count except midnode
			{ 0, },									// side face node count include midnode	
			{ {0,1,4}, {2,3,5} },					// side edge node idx
			{ {0,}, },								// side face node idx
			{ 2 },									// midnode count
			{ ELEMTYPE_FREEFIELD_2D_LINE2 }			// Topological Simple Type ( TET10 -> TET4 )
		},

			// 58 : ELEMTYPE_FREEFIELD_3D_LINE2
		{
			{ ELEMKIND_SPECIAL },					// kind of element
			{ 0 },									// element neighbor count		
			{ 6 },									// node count except midnode
			{ 6 },									// node count include midnode
			{ 3 },									// side edge count
			{ 2 },									// side edge node count except midnode
			{ 2 },									// side edge node count include midnode	
			{ 0 }, 									// neighbor type
			{ 0 },									// node count of each element neighbor
			{ 0 },									// node indexes of each element neighbor 
			{ 0 },									// node count of each element neighbor with mid-node
			{ 0 },									// node indexes of each element neighbor with mid-node
			{ 0 },									// side edge indexes of each element neighbor
			{ 0, },									// side face node count except midnode
			{ 0, },									// side face node count include midnode	
			{ {0,1}, {2,3}, {4,5} },				// side edge node idx
			{ {0,}, },								// side face node idx
			{ 0 },									// midnode count
			{ ELEMTYPE_FREEFIELD_3D_LINE2 }			// Topological Simple Type ( TET10 -> TET4 )
		},

			// 59 : ELEMTYPE_FREEFIELD_3D_LINE3
		{
			{ ELEMKIND_SPECIAL },					// kind of element
			{ 0 },									// element neighbor count		
			{ 6 },									// node count except midnode
			{ 9 },									// node count include midnode
			{ 3 },									// side edge count
			{ 2 },									// side edge node count except midnode
			{ 3 },									// side edge node count include midnode	
			{ 0 }, 									// neighbor type
			{ 0 },									// node count of each element neighbor
			{ 0 },									// node indexes of each element neighbor 
			{ 0 },									// node count of each element neighbor with mid-node
			{ 0 },									// node indexes of each element neighbor with mid-node
			{ 0 },									// side edge indexes of each element neighbor
			{ 0, },									// side face node count except midnode
			{ 0, },									// side face node count include midnode	
			{ {0,1,6}, {2,3,7}, {4,5,8} },			// side edge node idx
			{ {0,}, },								// side face node idx
			{ 3 },									// midnode count
			{ ELEMTYPE_FREEFIELD_3D_LINE2 }			// Topological Simple Type ( TET10 -> TET4 )
		},

			// 60 : ELEMTYPE_FREEFIELD_TRI3
		{
			{ ELEMKIND_SPECIAL },								// kind of element
			{ 0 },												// element neighbor count		
			{ 6 },												// node count except midnode
			{ 6 },												// node count include midnode
			{ 6 },												// side edge count
			{ 2 },												// side edge node count except midnode
			{ 2 },												// side edge node count include midnode	
			{ 0 }, 												// neighbor type
			{ 0 },												// node count of each element neighbor
			{ 0 },												// node indexes of each element neighbor
			{ 0 },												// node count of each element neighbor with mid-node
			{ 0 },												// node indexes of each element neighbor with mid-node
			{ 0 },												// side edge indexes of each element neighbor
			{ 3, 3},											// side face node count except midnode
			{ 3, 3},											// side face node count include midnode	
			{ {0,1}, {1,2}, {2,0}, {3,4}, {4,5}, {5,3} },		// side edge node idx
			{ {0,1,2}, {3,4,5} },								// side face node idx
			{ 0 },												// midnode count
			{ ELEMTYPE_FREEFIELD_TRI3 }							// Topological Simple Type ( TET10 -> TET4 )
		},

			// 61 : ELEMTYPE_FREEFIELD_TRI6
		{
			{ ELEMKIND_SPECIAL },								// kind of element
			{ 0 },												// element neighbor count		
			{ 6 },												// node count except midnode
			{ 12},												// node count include midnode
			{ 6 },												// side edge count
			{ 2 },												// side edge node count except midnode
			{ 3 },												// side edge node count include midnode	
			{ 0 }, 												// neighbor type
			{ 0 },												// node count of each element neighbor
			{ 0 },												// node indexes of each element neighbor 
			{ 0 },												// node count of each element neighbor with mid-node
			{ 0 },												// node indexes of each element neighbor with mid-node
			{ 0 },												// side edge indexes of each element neighbor
			{ 3, 3},											// side face node count except midnode
			{ 6, 6},											// side face node count include midnode	
			{ {0,1,6}, {1,2,7}, {2,0,8}, {3,4,9}, {4,5,10}, {5,3,11} },		// side edge node idx
			{ {0,1,2,6,7,8}, {3,4,5,9,10,11} },					// side face node idx
			{ 6 },												// midnode count
			{ ELEMTYPE_FREEFIELD_TRI3 }							// Topological Simple Type ( TET10 -> TET4 )
		},

			// 62 : ELEMTYPE_FREEFIELD_QUAD4
		{
			{ ELEMKIND_SPECIAL },												// kind of element
			{ 0 },																// element neighbor count		
			{ 8 },																// node count except midnode
			{ 8 },																// node count include midnode
			{ 8 },																// side edge count
			{ 2 },																// side edge node count except midnode
			{ 2 },																// side edge node count include midnode	
			{ 0 }, 																// neighbor type
			{ 0 },																// node count of each element neighbor
			{ 0 },																// node indexes of each element neighbor 
			{ 0 },																// node count of each element neighbor with mid-node
			{ 0 },																// node indexes of each element neighbor with mid-node
			{ 0 },																// side edge indexes of each element neighbor
			{ 8, },																// side face node count except midnode
			{ 8, },																// side face node count include midnode	
			{ {0,1}, {1,2}, {2,3}, {3,0},{4,5}, {5,6}, {6,7}, {7,4} },			// side edge node idx
			{ {0,1,2,3}, {4,5,6,7} },											// side face node idx
			{ 0 },																// midnode count
			{ ELEMTYPE_FREEFIELD_QUAD4 }										// Topological Simple Type ( TET10 -> TET4 )
		},

			// 63 : ELEMTYPE_FREEFIELD_QUAD8
		{
			{ ELEMKIND_SPECIAL },												// kind of element
			{ 0 },																// element neighbor count		
			{ 8 },																// node count except midnode
			{ 16 },																// node count include midnode
			{ 8 },																// side edge count
			{ 2 },																// side edge node count except midnode
			{ 3 },																// side edge node count include midnode	
			{ 0 }, 																// neighbor type
			{ 0 },																// node count of each element neighbor
			{ 0 },																// node indexes of each element neighbor 
			{ 0 },																// node count of each element neighbor with mid-node
			{ 0 },																// node indexes of each element neighbor with mid-node
			{ 0 },																// side edge indexes of each element neighbor
			{ 8, },																// side face node count except midnode
			{ 16, },															// side face node count include midnode	
			{ {0,1,8}, {1,2,9}, {2,3,10}, {3,0,11},{4,5,12}, {5,6,13}, {6,7,14}, {7,4,15} }, // side edge node idx
			{ {0,1,2,3,8,9,10,11}, {4,5,6,7,12,13,14,15} },						// side face node idx
			{ 8 },																// midnode count
			{ ELEMTYPE_FREEFIELD_QUAD4 }										// Topological Simple Type ( TET10 -> TET4 )
		},

			// 64 : ELEMTYPE_THRESIST
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},

			// 65 : ELEMTYPE_INFINITE_QUAD6
		{
			{ ELEMKIND_SPECIAL },												// kind of element
			{ 4 },																// element neighbor count		
			{ 4 },																// node count except midnode
			{ 4 },																// node count include midnode
			{ 4 },																// side edge count
			{ 2 },																// side edge node count except midnode
			{ 2 },																// side edge node count include midnode	
			{ ELEMTYPE_LINE2, ELEMTYPE_LINE2, ELEMTYPE_LINE2, ELEMTYPE_LINE2 },	// neighbor type
			{ 2,2,2,2 },														// node count of each element neighbor
			{ {0,1,-1}, {1,2,-1}, {2,3,-1}, {3,0,-1} },							// node indexes of each element neighbor 
			{ 2,2,2,2 },														// node count of each element neighbor with mid-node
			{ {0,1,-1}, {1,2,-1}, {2,3,-1}, {3,0,-1} },							// node indexes of each element neighbor with mid-node
			{ {0},{1},{2},{3} },												// side edge indexes of each element neighbor
			{ 4, },																// side face node count except midnode
			{ 4, },																// side face node count include midnode	
			{ {0,1}, {1,2}, {2,3}, {3,0} },										// side edge node idx
			{ {0,1,2,3}, },														// side face node idx
			{ 0 },																// midnode count
			{ ELEMTYPE_INFINITE_QUAD4 }											// Topological Simple Type ( TET10 -> TET4 )
		},


			// 66 : ELEMTYPE_INFINITE_QUAD8
		{
			{ ELEMKIND_SPECIAL },												// kind of element
			{ 4 },																// element neighbor count		
			{ 4 },																// node count except midnode
			{ 8 },																// node count include midnode
			{ 4 },																// side edge count
			{ 2 },																// side edge node count except midnode
			{ 3 },																// side edge node count include midnode	
			{ ELEMTYPE_LINE3, ELEMTYPE_LINE3, ELEMTYPE_LINE3, ELEMTYPE_LINE3 },	// neighbor type
			{ 2,2,2,2 },														// node count of each element neighbor
			{ {0,1,-1}, {1,2,-1}, {2,3,-1}, {3,0,-1} },							// node indexes of each element neighbor 
			{ 3,3,3,3 },														// node count of each element neighbor with mid-node
			{ {0,1,4,-1}, {1,2,5,-1}, {2,3,6,-1}, {3,0,7,-1} },					// node indexes of each element neighbor with mid-node
			{ {0},{1},{2},{3} },												// side edge indexes of each element neighbor
			{ 4, },																// side face node count except midnode
			{ 8, },																// side face node count include midnode	
			{ {0,1,4}, {1,2,5}, {2,3,6}, {3,0,7} },								// side edge node idx
			{ {0,1,2,3,4,5,6,7}, },												// side face node idx
			{ 4 },																// midnode count
			{ ELEMTYPE_INFINITE_QUAD4 }											// Topological Simple Type ( TET10 -> TET4 )
		},

			// 67 : ELEMTYPE_INFINITE_WEDGE9
		{
			{ ELEMKIND_SPECIAL },																// kind of element
			{ 5 },																				// element neighbor count
			{ 6 },																				// node count except midnode
			{ 6 },																				// node count include midnode
			{ 9 },																				// side edge count
			{ 2 },																				// side edge node count except midnode
			{ 2 },																				// side edge node count include midnode	
			{ ELEMTYPE_TRI3, ELEMTYPE_TRI3, ELEMTYPE_QUAD4, ELEMTYPE_QUAD4, ELEMTYPE_QUAD4 },	// neighbor type
			{ 3,3,4,4,4 },																		// node count of each element neighbor
			{ {0,2,1,-1}, {3,4,5,-1}, {0,1,4,3}, {1,2,5,4}, {2,0,3,5} },						// node indexes of each element neighbor 
			{ 3,3,4,4,4 },																		// node count of each element neighbor with mid-node
			{ {0,2,1,-1}, {3,4,5,-1}, {0,1,4,3}, {1,2,5,4}, {2,0,3,5} },						// node indexes of each element neighbor with mid-node
			{ {2,1,0,-1}, {3,4,5,-1}, {0,7,3,6}, {1,8,4,7}, {2,6,5,8} },						// side edge indexes of each element neighbor
			{ 3, 3, 4, 4, 4 },																	// side face node count except midnode
			{ 3, 3, 4, 4, 4 },																	// side face node count include midnode	
			{ {0,1}, {1,2}, {2,0}, {3,4}, {4,5}, {5,3}, {0,3}, {1,4}, {2,5} },					// side edge node idx
			{ {0,2,1,-1}, {3,4,5,-1}, {0,1,4,3}, {1,2,5,4}, {2,0,3,5} },						// side face node idx
			{ 0 },																				// midnode count
			{ ELEMTYPE_INFINITE_WEDGE6 }														// Topological Simple Type ( TET10 -> TET4 )
		},

			// 68 : ELEMTYPE_INFINITE_WEDGE15
		{
			{ ELEMKIND_SPECIAL },																							// kind of element
			{ 5 },																											// element neighbor count
			{ 6 },																											// node count except midnode
			{ 15 },																											// node count include midnode
			{ 9 },																											// side edge count
			{ 2 },																											// side edge node count except midnode
			{ 3 },																											// side edge node count include midnode	
			{ ELEMTYPE_TRI6, ELEMTYPE_TRI6, ELEMTYPE_QUAD8, ELEMTYPE_QUAD8, ELEMTYPE_QUAD8 },								// neighbor type
			{ 3,3,4,4,4 },																									// node count of each element neighbor
			{ {0,2,1,-1}, {3,4,5,-1}, {0,1,4,3}, {1,2,5,4}, {2,0,3,5} },													// node indexes of each element neighbor 
			{ 6,6,8,8,8 },																									// node count of each element neighbor with mid-node
			{ {0,2,1,8,7,6,0,0}, {3,4,5,9,10,11,0,0}, {0,1,4,3,6,13,9,12}, {1,2,5,4,7,14,10,13}, {2,0,3,5,8,12,11,14} },	// node indexes of each element neighbor with mid-node
			{ {2,1,0,-1}, {3,4,5,-1}, {0,7,3,6}, {1,8,4,7}, {2,6,5,8} },													// side edge indexes of each element neighbor
			{ 3, 3, 4, 4, 4 },																								// side face node count except midnode
			{ 6, 6, 8, 8, 8 },																								// side face node count include midnode	
			{ {0,1,6}, {1,2,7}, {2,0,8}, {3,4,9}, {4,5,10}, {5,3,11}, {0,3,12}, {1,4,13}, {2,5,14} },						// side edge node idx
			{ {0,2,1,8,7,6,0,0}, {3,4,5,9,10,11,0,0}, {0,1,4,3,6,13,9,12}, {1,2,5,4,7,14,10,13}, {2,0,3,5,8,12,11,14} },	// side face node idx
			{ 9 },																											// midnode count
			{ ELEMTYPE_INFINITE_WEDGE6 }																					// Topological Simple Type ( TET10 -> TET4 )
		},

			// 69 : ELEMTYPE_INFINITE_HEX12
		{
			{ ELEMKIND_SPECIAL },																					// kind of element
			{ 6 },																									// element neighbor count
			{ 8 },																									// node count except midnode
			{ 8 },																									// node count include midnode
			{ 12 },																									// side edge count
			{ 2 },																									// side edge node count except midnode
			{ 2 },																									// side edge node count include midnode	
			{ ELEMTYPE_QUAD4, ELEMTYPE_QUAD4, ELEMTYPE_QUAD4, ELEMTYPE_QUAD4, ELEMTYPE_QUAD4, ELEMTYPE_QUAD4 },		// neighbor type
			{ 4,4,4,4,4,4 },																						// node count of each element neighbor
			{ {0,3,2,1}, {4,5,6,7}, {0,1,5,4}, {1,2,6,5}, {6,2,3,7}, {0,4,7,3} },									// node indexes of each element neighbor 
			{ 4,4,4,4,4,4 },																						// node count of each element neighbor with mid-node
			{ {0,3,2,1}, {4,5,6,7}, {0,1,5,4}, {1,2,6,5}, {6,2,3,7}, {0,4,7,3} },									// node indexes of each element neighbor with mid-node
			{ {3,2,1,0}, {4,5,6,7}, {0,9,4,8}, {1,10,5,9},{10,2,11,6},{8,7,11,3} },									// side edge indexes of each element neighbor
			{ 4, 4, 4, 4, 4, 4 },																					// side face node count except midnode
			{ 4, 4, 4, 4, 4, 4 },																					// side face node count include midnode	
			{ {0,1}, {1,2}, {2,3}, {3,0}, {4,5}, {5,6}, {6,7}, {7,4}, {0,4}, {1,5}, {2,6}, {3,7} },					// side edge node idx
			{ {0,3,2,1}, {4,5,6,7}, {0,1,5,4}, {1,2,6,5}, {2,3,7,6}, {3,0,4,7} },									// side face node idx
			{ 0 },																									// midnode count
			{ ELEMTYPE_INFINITE_HEX8 }																				// Topological Simple Type ( TET10 -> TET4 )
		},

			// 70 : ELEMTYPE_INFINITE_HEX20
		{
			{ ELEMKIND_SPECIAL },																														// kind of element
			{ 6 },																																		// element neighbor count
			{ 8 },																																		// node count except midnode
			{ 20 },																																		// node count include midnode
			{ 12 },																																		// side edge count
			{ 2 },																																		// side edge node count except midnode
			{ 3 },																																		// side edge node count include midnode	
			{ ELEMTYPE_QUAD8, ELEMTYPE_QUAD8, ELEMTYPE_QUAD8, ELEMTYPE_QUAD8, ELEMTYPE_QUAD8, ELEMTYPE_QUAD8 },											// neighbor type
			{ 4,4,4,4,4,4 },																															// node count of each element neighbor
			{ {0,3,2,1}, {4,5,6,7}, {0,1,5,4}, {1,2,6,5}, {6,2,3,7}, {0,4,7,3} },																		// node indexes of each element neighbor 
			{ 8,8,8,8,8,8 },																															// node count of each element neighbor with mid-node
			{ {3,2,1,0,10,9,8,11}, {4,5,6,7,12,13,14,15}, {0,1,5,4,8,17,12,16}, {1,2,6,5,9,18,13,17}, {2,3,7,6,10,19,14,18}, {4,7,3,0,15,19,11,16} },	// node indexes of each element neighbor with mid-node
			{ {3,2,1,0}, {4,5,6,7}, {0,9,4,8}, {1,10,5,9},{10,2,11,6},{8,7,11,3} },																		// side edge indexes of each element neighbor
			{ 4, 4, 4, 4, 4, 4 },																														// side face node count except midnode
			{ 8, 8, 8, 8, 8, 8 },																														// side face node count include midnode	
			{ {0,1,8}, {1,2,9}, {2,3,10}, {3,0,11}, {4,5,12}, {5,6,13}, {6,7,14}, {7,4,15}, {0,4,16}, {1,5,17}, {2,6,18}, {3,7,19} },					// side edge node idx
			{ {0,3,2,1,11,10,9,8}, {4,5,6,7,12,13,14,15}, {0,1,5,4,8,17,12,16}, {1,2,6,5,9,18,13,17}, {2,3,7,6,10,19,14,18}, {3,0,4,7,11,16,15,19} },	// side face node idx
			{ 12 },																																		// midnode count
			{ ELEMTYPE_INFINITE_HEX8 }																													// Topological Simple Type ( TET10 -> TET4 )
		},
			// 71 : ELEMTYPE_CUTOFFWALL_LINE2
		{
			{ ELEMKIND_SPECIAL },					// kind of element
			{ 0 },									// element neighbor count		
			{ 4 },									// node count except midnode
			{ 4 },									// node count include midnode
			{ 2 },									// side edge count
			{ 2 },									// side edge node count except midnode
			{ 2 },									// side edge node count include midnode	
			{ 0 }, 									// neighbor type
			{ 0 },									// node count of each element neighbor
			{ 0 },									// node indexes of each element neighbor 
			{ 0 },									// node count of each element neighbor with mid-node
			{ 0 },									// node indexes of each element neighbor with mid-node
			{ 0 },									// side edge indexes of each element neighbor
			{ 0, },									// side face node count except midnode
			{ 0, },									// side face node count include midnode	
			{ {0,1}, {2,3} },						// side edge node idx
			{ {0,}, },								// side face node idx
			{ 0 },									// midnode count
			{ ELEMTYPE_CUTOFFWALL_LINE2 }			// Topological Simple Type ( TET10 -> TET4 )
		},
			// 72 : ELEMTYPE_CUTOFFWALL_LINE3
		{
			{ ELEMKIND_SPECIAL },					// kind of element
			{ 0 },									// element neighbor count		
			{ 4 },									// node count except midnode
			{ 6 },									// node count include midnode
			{ 2 },									// side edge count
			{ 2 },									// side edge node count except midnode
			{ 3 },									// side edge node count include midnode	
			{ 0 }, 									// neighbor type
			{ 0 },									// node count of each element neighbor
			{ 0 },									// node indexes of each element neighbor 
			{ 0 },									// node count of each element neighbor with mid-node
			{ 0 },									// node indexes of each element neighbor with mid-node
			{ 0 },									// side edge indexes of each element neighbor
			{ 0, },									// side face node count except midnode
			{ 0, },									// side face node count include midnode	
			{ {0,1,4}, {2,3,5} },					// side edge node idx
			{ {0,}, },								// side face node idx
			{ 2 },									// midnode count
			{ ELEMTYPE_CUTOFFWALL_LINE2 }			// Topological Simple Type ( TET10 -> TET4 )
		},
			// 73 : ELEMTYPE_CUTOFFWALL_TRI3
		{
			{ ELEMKIND_SPECIAL },								// kind of element
			{ 0 },												// element neighbor count		
			{ 6 },												// node count except midnode
			{ 6 },												// node count include midnode
			{ 6 },												// side edge count
			{ 2 },												// side edge node count except midnode
			{ 2 },												// side edge node count include midnode	
			{ 0 }, 												// neighbor type
			{ 0 },												// node count of each element neighbor
			{ 0 },												// node indexes of each element neighbor
			{ 0 },												// node count of each element neighbor with mid-node
			{ 0 },												// node indexes of each element neighbor with mid-node
			{ 0 },												// side edge indexes of each element neighbor
			{ 3, 3},											// side face node count except midnode
			{ 3, 3},											// side face node count include midnode	
			{ {0,1}, {1,2}, {2,0}, {3,4}, {4,5}, {5,3} },		// side edge node idx
			{ {0,1,2}, {3,4,5} },								// side face node idx
			{ 0 },												// midnode count
			{ ELEMTYPE_CUTOFFWALL_TRI3 }						// Topological Simple Type ( TET10 -> TET4 )
		},
			// 74 : ELEMTYPE_CUTOFFWALL_TRI6
		{
			{ ELEMKIND_SPECIAL },								// kind of element
			{ 0 },												// element neighbor count		
			{ 6 },												// node count except midnode
			{ 12},												// node count include midnode
			{ 6 },												// side edge count
			{ 2 },												// side edge node count except midnode
			{ 3 },												// side edge node count include midnode	
			{ 0 }, 												// neighbor type
			{ 0 },												// node count of each element neighbor
			{ 0 },												// node indexes of each element neighbor 
			{ 0 },												// node count of each element neighbor with mid-node
			{ 0 },												// node indexes of each element neighbor with mid-node
			{ 0 },												// side edge indexes of each element neighbor
			{ 3, 3},											// side face node count except midnode
			{ 6, 6},											// side face node count include midnode	
			{ {0,1,6}, {1,2,7}, {2,0,8}, {3,4,9}, {4,5,10}, {5,3,11} },		// side edge node idx
			{ {0,1,2,6,7,8}, {3,4,5,9,10,11} },					// side face node idx
			{ 6 },												// midnode count
			{ ELEMTYPE_CUTOFFWALL_TRI3 }							// Topological Simple Type ( TET10 -> TET4 )
		},
			// 75 : ELEMTYPE_CUTOFFWALL_QUAD4
		{
			{ ELEMKIND_SPECIAL },												// kind of element
			{ 0 },																// element neighbor count		
			{ 8 },																// node count except midnode
			{ 8 },																// node count include midnode
			{ 8 },																// side edge count
			{ 2 },																// side edge node count except midnode
			{ 2 },																// side edge node count include midnode	
			{ 0 }, 																// neighbor type
			{ 0 },																// node count of each element neighbor
			{ 0 },																// node indexes of each element neighbor 
			{ 0 },																// node count of each element neighbor with mid-node
			{ 0 },																// node indexes of each element neighbor with mid-node
			{ 0 },																// side edge indexes of each element neighbor
			{ 8, },																// side face node count except midnode
			{ 8, },																// side face node count include midnode	
			{ {0,1}, {1,2}, {2,3}, {3,0},{4,5}, {5,6}, {6,7}, {7,4} },			// side edge node idx
			{ {0,1,2,3}, {4,5,6,7} },											// side face node idx
			{ 0 },																// midnode count
			{ ELEMTYPE_CUTOFFWALL_QUAD4 }										// Topological Simple Type ( TET10 -> TET4 )
		},
			// 76 : ELEMTYPE_CUTOFFWALL_QUAD8
		{
			{ ELEMKIND_SPECIAL },												// kind of element
			{ 0 },																// element neighbor count		
			{ 8 },																// node count except midnode
			{ 16 },																// node count include midnode
			{ 8 },																// side edge count
			{ 2 },																// side edge node count except midnode
			{ 3 },																// side edge node count include midnode	
			{ 0 }, 																// neighbor type
			{ 0 },																// node count of each element neighbor
			{ 0 },																// node indexes of each element neighbor 
			{ 0 },																// node count of each element neighbor with mid-node
			{ 0 },																// node indexes of each element neighbor with mid-node
			{ 0 },																// side edge indexes of each element neighbor
			{ 8, },																// side face node count except midnode
			{ 16, },															// side face node count include midnode	
			{ {0,1,8}, {1,2,9}, {2,3,10}, {3,0,11},{4,5,12}, {5,6,13}, {6,7,14}, {7,4,15} }, // side edge node idx
			{ {0,1,2,3,8,9,10,11}, {4,5,6,7,12,13,14,15} },						// side face node idx
			{ 8 },																// midnode count
			{ ELEMTYPE_CUTOFFWALL_QUAD4 }										// Topological Simple Type ( TET10 -> TET4 )
		},
			// 77 : ELEMTYPE_INTERFACE_POINT
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},
			// 78 : ELEMTYPE_AXISYM_REINF
		{
			{ ELEMKIND_SPECIAL },
			{ 0 }
		},
};

//////////////////////////////////////////////////////////////////////////
//요소의 엣지 노드 정보를... 연결순서대로 표현한 테이블
//etip의 edge는 저차노드 우선이라, 필요에 의해 따로 만듬... 
//ex) line-3 : 0-2-1
struct TSeqEdgeInfo
{
	long edge[MAX_EDGE][MAX_EDGE_NODE];		// side edge node idx
};

__MY_EXT_DATA__ extern TSeqEdgeInfo _seq_edge[MAX_ELEMENT_TYPES];

//////////////////////////////////////////////////////////////////////////
// 고차 Element의 Midnode value 계산시 사용

typedef struct tagNSMidNodeInfo {
	tagNSMidNodeInfo(){}
	tagNSMidNodeInfo(long m, long s0, long s1)
	{
		idxMidNode = m;
		idxSideNode[0] = s0;
		idxSideNode[1] = s1;
	}

	long idxMidNode;
	long idxSideNode[2];
} NSMidNodeInfo;

typedef struct tagNSElemMidNodeInfo {
	long cntMidNode;
	NSMidNodeInfo infoMidNode[12];
} NSElemMidNodeInfo;

__MY_EXT_DATA__ extern NSElemMidNodeInfo _midElem[MAX_ELEMENT_TYPES];

//////////////////////////////////////////////////////////////////////////
//
// Element Face의 Area를 구하기 위한 Info
// 사용예) NSMeshUtil의 GetFaceArea 참고
//
//////////////////////////////////////////////////////////////////////////

typedef struct tagTFaceTriInfo {
	long nft;								// triangle count of side face
	long facetri[MAX_FACE][3];				// triangle idx of side face
} TFaceTriInfo;

static TFaceTriInfo _fti[] =
{
	// ELEMTYPE_UNKNOWN
	{
		{ 0 },
		{ {0,}, }
	},

		// ELEMTYPE_VERTEX
	{
		{ 0 },
		{ {0,}, }
	},

		// ELEMTYPE_LINE2
	{
		{ 0 },
		{ {0,}, }
	},

		// ELEMTYPE_LINE3
	{
		{ 0 },
		{ {0,}, }
	},

		// ELEMTYPE_TRI3
	{
		{ 1 },
		{ {0,1,2}, }
	},

		// ELEMTYPE_TRI6
	{
		{ 4 },
		{ {0,3,5}, {1,4,3}, {2,5,4}, {3,4,5}, }
	},

		// ELEMTYPE_QUAD4
	{
		{ 2 },
		{ {0,1,2}, {0,2,3}, }
	},

		// ELEMTYPE_QUAD8
	{
		{ 6 },
		{ {0,4,7}, {1,5,4}, {2,6,5}, {3,7,6}, {4,5,7}, {6,7,5} }
	},
};

// Element node, edge & face side, and mid-node number
//
//        [LINE]       [ TRIANGLE ]         [ QUADRILATERAL ]
//             
//       0     1       0   5  2              0     7     3
//       o-----o        o----o                o---------o
//          2           |   /                 |         |
//                     3|  /                 4|         |6 
//                      | /4                  |         |
//                      |/                    o---------o
//                      o                    1     5     2
//                      1
//
//   [ TETRAHEDRON ]            [ HEXAHEDRON ]         [ PENTAHEDRON - WEDGE ]     [PYRAMID]
//                        
//             3                7                 6     3 o-----------o 5               o 4
//            o                 o---------------o         | \       / |                / \
//          / | \              /|              /|         |   \   /   |              / / \ \   
//        /   |   \        4  / |           5 / |         |     o 4   |            /  /   \  \
//      /     |     \        o---------------o  |         |     |     |        3 /   /     \   \  2
//  0 o-- -- -|- -- --o 2    |  |            |  |         |     |     |         o---/-------\---o
//     \      |     /        |  |            |  |         |     |     |         |  /         \  |
//       \    |   /          |  | 3          |  |       0 o-- --|-- --o 2       | /           \ |
//         \  | /            |  o- -- -- -- -+ -o 2         \   |   /           |/             \|
//            o              | /             | /              \ | /             o---------------o
//           1               |/              |/                 o              0                  1
//                           o---------------o                  1
//                         0                 1
//   
//  [ INTERAFACE LINE ]			  [ INTERAFACE TRI ]			  [ INTERAFACE QUAD ]
//  [ CUTOFFWALL LINE ]			  [ CUTOFFWALL TRI ]			  [ CUTOFFWALL QUAD ]
//							
//	0  4  1					 0   8  2	 3  11  5					0     11    3	4     15     7
//	o-----o					  o----o  	  o----o 					 o---------o	 o---------o
//	   						  |   /   	  |   /  					 |         |	 |         |
//	   						 6|  /    	 9|  /   					8|         |10 12|         |14
//	o-----o					  | /7    	  | /10  					 |         |	 |         |
//  2  5  3					  |/      	  |/     					 o---------o	 o---------o
//							  o       	  o      					1     9     2	5    13     6
//							  1			  4
//
//
//  [ FREEFIELD LINE 2D ]    [ FREEFIELD LINE 3D ]
//							 					
//	0  4  1					 4  8  5				
//	o-----o					 o-----o				
//	   						    					
//	   						    					
//	o-----o					 o-----o				
//  2  5  3					 0  6  1				
//						
//							
//							 o-----o					
//							 2  7  3				
//									
//
//   [ FREEFIELD TRI ]			             [ FREEFIELD QUAD ]
//	
//	 0   8  2	 3  11  5					0     11    3	4     15     7
//	  o----o  	  o----o 					 o---------o	 o---------o
//	  |   /   	  |   /  					 |         |	 |         |
//	 6|  /    	 9|  /   					8|         |10 12|         |14
//	  | /7    	  | /10  					 |         |	 |         |
//	  |/      	  |/     					 o---------o	 o---------o
//	  o       	  o      					1     9     2	5    13     6
//	  1			  4
//
//
//		  [INFINITE QUAD]					[INFINITE QUAD - QUADRATIC]
//		3 ------   ------ 2						3 ------ 6 ------ 2
//      |				  |						|				  |
//		|				  |						|				  |
//		|				  |						7				  5
//		|				  |						|				  |
//		|				  |						|				  |
//		4 ------   ------ 1						4 ------ 8 ------ 1
//
//
//		  [INFINITE WEDGE]						[INFINITE WEDGE - QADRATIC]	
//	                      						            7     	
//		 1 o-----------o 2							1 o-----o-----o 2  
//		   | \       / |							  | \       / |    
//		   |   \   /   |							  | 9 o   o 8 |    
//		   |     o 3   |							  |     o 3   |    
//		   o     |     o 			  			   10 o     |     o 11  
//		   |     |     |							  |     o 12  |    
//		   |     o     |							  |     |  13 |    
//		 4 o-- --|-- --o 5							4 o-- --|-o --o 5  
//		     \   |   /								    \   |   /      
//		       \ | /								   15 o | o 14       
//		         o									        o          
//		         6									        6			
//
//
//		[INFINITE HEXAHEDRON]       		    [INFINITE HEXAHEDRON - QADRATIC]       
//                        					                          
//													  1         9         2    
//         1               2    			           o-------o-------- o      
//         o---------------o      			       12 /|		    10 / |
//        /|              /|      			         o |              o  |      
//     4 / |           3 / |      			      4 /  |  11       3 /   |      
//      o---------------o  |      			       o-------o--------o    |      
//	    |  o            |  o         		       |   o 17         |    o 18      
//      |  |            |  |      			       |   |            |    |      
//      o  |            o  |        			    20 o   | 5    13    o 19 | 6     
//      |  o- -- -- -- -+ -o     			       |   o- --  o -- -+ -- o        
//      | / 5           | / 6      			       |  /             |   /     
//      |/              |/        			       | o 16           |  o 14       
//      o---------------o         			       |/               | /
//      8               7					       o-------o--------o  
//											       8       15         7
//


#include "HeaderPost.h"