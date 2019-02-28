/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _MCPROGINT_
#define _MCPROGINT_

#include <McBase.h>
#include <bur/plctypes.h>

/* Datatypes and datatypes of function blocks */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct McProgIntIpMonitorType
{
	plcbit Handshake;
	plcbit Reserve[3];
	plcstring StatusMsg[264];
	plcstring LastErrorMsg[120];
	unsigned short LastErrorCode;
	unsigned short LoadedProgCount;
	plcstring ProgName[264];
	plcstring NcblockL2[264];
	plcstring NcblockL1[264];
	plcstring Ncblock[264];
	plcstring NcblockN1[264];
	plcstring NcblockN2[264];
	unsigned long CurLineNum;
	unsigned long CurBlockNum;
	unsigned long LoadFreadTime;
	unsigned long LoadPrepTime;
	unsigned long LoadSepLinesTime;
	unsigned long LoadParseTime;
	unsigned long LoadParseLexTime;
	unsigned long BreakpointCount;
	unsigned long IpvarAccessCount;
	unsigned long ExecTime;
	unsigned long IdleTime;
	unsigned long NumParallelEvents;
	unsigned long ParallelCycleCount;
	plcstring ParallelActionText[12][264];
	unsigned long ParallelEvalCount[12];
	unsigned long ParallelExecCount[12];
	unsigned long NumFubsExecIpsynch;
	unsigned long NumFubsExecPpsynch;
	plcstring Callstack[12][264];
	unsigned long SharedMem_size;
	unsigned long IpMemSize;
	unsigned long IpCurFileMemSize;
	unsigned long SysFreeMem;
	unsigned long ReadingLineNum;
	unsigned long TranslatingLineNuM;
	unsigned long GeneratingAilLineNum;
	unsigned long ParsingAilLineNum;
	plcbit ParallelEnabled;
	plcbit ParallelRdisableSet;
	plcbit StopAtM1;
	plcbit Unused;
	plcstring CurProgFileName[264];
	plcstring CurProgName[264];
} McProgIntIpMonitorType;

typedef struct McProgIntFileMonitorEntryType
{
	plcstring *Name;                              	/* Name of loaded file */
	plcstring *PathName;                          	/* Full path file name */
	plcstring *DirName;                           	/* Directory name */
	plcstring *DeviceName;                        	/* File device name */
	unsigned long ProgramNumber;             		/* Program number */
	unsigned long StorageType;               		/* Storage type */
	unsigned long TimeStamp;                 		/* File time stamp */
	plcbit PrecompiledLCF;            				/* Loaded file is language configuration file */
	struct McProgIntFileMonitorEntryType *Next;  	/* Next element in file list */
} McProgIntFileMonitorEntryType;

typedef struct McProgIntFileMonitorAccessType
{
	plcbit Valid;                     				/* Data are valid and can be accessed */
	McProgIntFileMonitorEntryType *First;        	/* First element of file list */
} McProgIntFileMonitorAccessType;

typedef struct McProgIntFileMonitorLineType
{
	plcstring Name[32];       						/* Name of loaded file */
	unsigned long ProgramNumber;             		/* Program number; automatic if allowed, or dafault/user defined */
	unsigned long StorageType;               		/* Storage type */
} McProgIntFileMonitorLineType;

typedef struct McProgIntFileMonitorType
{
	plcbit Handshake;                 				/* Handshake - set to request data refresh, data valid after zero */
	unsigned long SetOffset;                 		/* Set offset */
	unsigned long Offset;                    		/* Offset of currently displayed files */
	McProgIntFileMonitorLineType File[32]; 			/* File monitor */
	McProgIntFileMonitorAccessType DirectAccess; 	/* Access to extended data */
} McProgIntFileMonitorType;

typedef double McSlaveAxisType[15];

typedef struct McPointType
{
	struct McPosType Pos;
	struct McOrientType Orient;
	McSlaveAxisType SlaveAxis;
} McPointType;

typedef double McJointAxisType[6];

typedef struct McAxisTargetType
{
	McJointAxisType JointAxis;
	McSlaveAxisType SlaveAxis;
} McAxisTargetType;

typedef double McRotationMatrixType[9];

typedef struct McLatchPositionsType
{
	plcbit TriggerEvent;
	unsigned long CoordSystem;
	double Position[15];
} McLatchPositionsType;


#ifdef __cplusplus
} // End of C-Linkage
#endif
#endif /* _MCPROGINT_ */

