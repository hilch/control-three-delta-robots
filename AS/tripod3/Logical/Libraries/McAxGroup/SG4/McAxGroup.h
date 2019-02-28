/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _MCAXGROUP_
#define _MCAXGROUP_

#ifndef _MCBASE_
#include <McBase.h>
#endif
#ifndef _PLCTYPES_H_
#include <bur/plctypes.h>
#endif

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif
#if defined(_WIN32) || defined(__WINDOWS__) || defined(__MINGW32__) || defined(__CYGWIN__)
#if defined(BUILD_MCAXGROUP)
#define DECLSPEC_MCAXGROUP __declspec(dllexport)
#else
#define DECLSPEC_MCAXGROUP __declspec(dllimport)
#endif
#else	/* not Windows */
#define DECLSPEC_MCAXGROUP _BUR_PUBLIC
#endif

/* Datatypes and datatypes of function blocks */
typedef enum McHomingOrderSourceEnum
{
	mcHO_CONFIGURATION,
	mcHO_FUNCTIONBLOCK
} McHomingOrderSourceEnum;

typedef enum McJogStatusEnum
{
	mcJOGSTATUS_DISABLED,
	mcJOGSTATUS_STANDSTILL,
	mcJOGSTATUS_JOGGING,
	mcJOGSTATUS_TARGET_REACHED,
	mcJOGSTATUS_AXES_VIOLATION,
	mcJOGSTATUS_JOINTAXES_VIOLATION,
	mcJOGSTATUS_SLAVEAXES_VIOLATION,
	mcJOGSTATUS_WORKSPACE_VIOLATION,
	mcJOGSTATUS_SAFESPACE_VIOLATION,
	mcJOGSTATUS_SELF_COLLISION,
	mcJOGSTATUS_TARGET_NOT_REACHABLE
} McJogStatusEnum;

typedef enum McOverrideEnum
{
	mcOVERRIDE_VELOCITY,
	mcOVERRIDE_VELOCITY_AXIS,
	mcOVERRIDE_ACCELERATION,
	mcOVERRIDE_ACCELERATION_AXIS,
	mcOVERRIDE_JERK,
	mcOVERRIDE_FEEDRATE = 10,
	mcOVERRIDE_RAPID,
	mcOVERRIDE_SPINDLE,
	mcOVERRIDE_TIMESTRETCH = 20
} McOverrideEnum;

typedef enum McMotionChainModuleEnum
{
	mcMCM_DEFAULT,
	mcMCM_INTERPRETER
} McMotionChainModuleEnum;

typedef enum McPrgAxesReposTypeEnum
{
	mcPRGRP_SINGLE_AXIS,
	mcPRGRP_PROGRAM,
	mcPRGRP_SINGLE_AXIS_AUTOMATIC
} McPrgAxesReposTypeEnum;

typedef enum McPrgPhaseEnum
{
	mcPRGPH_INACTIVE,
	mcPRGPH_SIMULATION_RUN,
	mcPRGPH_WAIT_FOR_AXES_REPOS,
	mcPRGPH_AXES_REPOS,
	mcPRGPH_WAIT_FOR_REAL_RUN,
	mcPRGPH_REAL_RUN
} McPrgPhaseEnum;

typedef enum McPrgStartModeEnum
{
	mcPRGSM_NON_MODAL,
	mcPRGSM_MODAL,
	mcPRGSM_RESTART
} McPrgStartModeEnum;

typedef enum McPrgStartPointEnum
{
	mcPRGSP_STANDARD,
	mcPRGSP_BLOCK_NUMBER,
	mcPRGSP_ABORT_LINE,
	mcPRGSP_LINE_NUMBER = 5,
	mcPRGSP_PATH_DISTANCE_LINE
} McPrgStartPointEnum;

typedef enum McPrgInfoInterruptEnum
{
	mcINTERRUPT_NOT_INTERRUPTED,
	mcINTERRUPT_SINGLESTEP,
	mcINTERRUPT_FB,
	mcINTERRUPT_INTERPRETER,
	mcINTERRUPT_MFUNCTION,
	mcINTERRUPT_PROGRAM
} McPrgInfoInterruptEnum;

typedef enum McStopModeEnum
{
	mcSTOPMODE_JERK_LIMIT,
	mcSTOPMODE_NO_JERK_LIMIT
} McStopModeEnum;

typedef enum McManualMoveTypeEnum
{
	mcMOVE_ABSOLUTE = 0,
	mcMOVE_RELATIVE = 1
} McManualMoveTypeEnum;

typedef struct McAddGroupReadInfoType
{
	plcbit GroupInterrupted;
	plcbit WaitForContinue;
} McAddGroupReadInfoType;

typedef struct McAdvGroupHome_15_Type
{
	enum McHomingOrderSourceEnum HomingOrderSource;
	unsigned short HomingOrder[15];
} McAdvGroupHome_15_Type;

typedef struct McSingleStepAdvParType
{
	enum McMotionChainModuleEnum Module;
} McSingleStepAdvParType;

typedef struct McPathInfoType
{
	float CurrentPathVelocity;
	double CurrentPathPosition;
	double CurrentLength;
	double RemainingDistance;
	float ProgrammedPathVelocity;
} McPathInfoType;

typedef struct McPrgAxesReposParType
{
	enum McPrgAxesReposTypeEnum Type;
	plcstring String[261];
} McPrgAxesReposParType;

typedef struct McPrgAdvParType
{
	plcstring InitProgram[261];
	enum McPrgStartModeEnum StartMode;
	enum McPrgStartPointEnum StartPointType;
	double StartPointParameter;
	struct McPrgAxesReposParType RepositioningParameter;
	enum McSwitchEnum SaveRestartData;
} McPrgAdvParType;

typedef struct McPrgInfoBlockMonitorType
{
	plcstring SecondLast[261];
	plcstring Last[261];
	plcstring Current[261];
	plcstring Next[261];
	plcstring SecondNext[261];
} McPrgInfoBlockMonitorType;

typedef struct McPrgInfoPrgMonitorType
{
	unsigned long LineNumber;
	unsigned long BlockNumber;
	double OverallRuntime;
	double MovementRuntime;
	double CurrentDwellTime;
	double RemainingDwellTime;
	struct McPrgInfoBlockMonitorType BlockMonitor;
} McPrgInfoPrgMonitorType;

typedef struct McPrgInfoType
{
	plcstring MainProgram[261];
	plcstring InitProgram[261];
	plcstring CurrentProgram[261];
	struct McPrgInfoPrgMonitorType ProgramMonitor;
	enum McPrgPhaseEnum ProgramPhase;
	enum McPrgInfoInterruptEnum InterruptStatus;
} McPrgInfoType;

typedef struct McJogPathLimitsType
{
	float Velocity;
	float Acceleration;
	float Deceleration;
	float Jerk;
} McJogPathLimitsType;

typedef struct MC_BR_ConditionalStop
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	unsigned long Identifier;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit Deactivate;
	plcbit Reactivate;
	/* VAR_OUTPUT (digital) */
	plcbit Valid;
	plcbit Busy;
	plcbit Error;
	plcbit Programmed;
	plcbit Activated;
	plcbit Interrupting;
} MC_BR_ConditionalStop_typ;


typedef struct MC_BR_GroupCommandError
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	McErrorCmdEnum Command;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit CommandAborted;
	plcbit Error;
} MC_BR_GroupCommandError_typ;

typedef struct MC_BR_GroupHome_15
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	double Position[15];
	McHomingModeEnum HomingMode[15];
	struct McAdvGroupHome_15_Type AdvancedParameters;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit CommandAborted;
	plcbit Error;
} MC_BR_GroupHome_15_typ;

typedef struct MC_BR_GroupJogAbsolute_15
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	double JogPosition[15];
	float Velocity;
	float Acceleration;
	float Deceleration;
	float Jerk;
	unsigned long CoordSystem;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	enum McJogStatusEnum JogStatus;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit Jog;
	/* VAR_OUTPUT (digital) */
	plcbit Ready;
	plcbit Busy;
	plcbit CommandAborted;
	plcbit Error;
} MC_BR_GroupJogAbsolute_15_typ;

typedef struct MC_BR_GroupJogRelative_15
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	double JogDistance[15];
	float Velocity;
	float Acceleration;
	float Deceleration;
	float Jerk;
	unsigned long CoordSystem;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	enum McJogStatusEnum JogStatus;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit Jog;
	/* VAR_OUTPUT (digital) */
	plcbit Ready;
	plcbit Busy;
	plcbit CommandAborted;
	plcbit Error;
} MC_BR_GroupJogRelative_15_typ;

typedef struct MC_BR_GroupJogVelocity_15
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	float JogVelocity[15];
	float Velocity;
	float Acceleration;
	float Deceleration;
	float Jerk;
	unsigned long CoordSystem;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	enum McJogStatusEnum JogStatus;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit Jog;
	/* VAR_OUTPUT (digital) */
	plcbit Ready;
	plcbit Busy;
	plcbit CommandAborted;
	plcbit Error;
} MC_BR_GroupJogVelocity_15_typ;

typedef struct MC_BR_GroupMoveCyclicPosition_15
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	unsigned long CoordSystem;
	McIplModeEnum InterpolationMode;
	struct McAdvMoveCycParType AdvancedParameters[15];
	double CyclicPosition[15];
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit DisableAxis[15];
	/* VAR_OUTPUT (digital) */
	plcbit Valid;
	plcbit Busy;
	plcbit CommandAborted;
	plcbit Error;
} MC_BR_GroupMoveCyclicPosition_15_typ;

typedef struct MC_BR_GroupPower
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	/* VAR_OUTPUT (digital) */
	plcbit Status;
	plcbit Busy;
	plcbit Error;
} MC_BR_GroupPower_typ;

typedef struct MC_BR_GroupReadInfo
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	struct McAddGroupReadInfoType AdditionalInfo;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	/* VAR_OUTPUT (digital) */
	plcbit Valid;
	plcbit Busy;
	plcbit Error;
	plcbit CommunicationReady;
	plcbit ReadyForPowerOn;
	plcbit PowerOn;
	plcbit IsHomed;
} MC_BR_GroupReadInfo_typ;

typedef struct MC_BR_GroupSetOverride
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	enum McOverrideEnum Type;
	float Factor;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	/* VAR_OUTPUT (digital) */
	plcbit Enabled;
	plcbit Busy;
	plcbit Error;
} MC_BR_GroupSetOverride_typ;

typedef struct MC_BR_MFunction
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	unsigned long MFunction;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit Reset;
	/* VAR_OUTPUT (digital) */
	plcbit Valid;
	plcbit Busy;
	plcbit Error;
	plcbit Value;
} MC_BR_MFunction_typ;

typedef struct MC_BR_MoveBlock
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	plcstring Block[261];
	McBufferModeEnum BufferMode;
	McTransitionModeEnum TransitionMode;
	double TransitionParameter;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Active;
	plcbit CommandAborted;
	plcbit Error;
} MC_BR_MoveBlock_typ;

typedef struct MC_BR_MoveProgram
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	plcstring Name[261];
	McBufferModeEnum BufferMode;
	McTransitionModeEnum TransitionMode;
	double TransitionParameter;
	struct McPrgAdvParType AdvancedParameters;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	enum McPrgPhaseEnum Phase;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	plcbit Continue;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Active;
	plcbit CommandAborted;
	plcbit Error;
} MC_BR_MoveProgram_typ;

typedef struct MC_BR_PathInfo
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	struct McPathInfoType PathInfo;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	/* VAR_OUTPUT (digital) */
	plcbit Valid;
	plcbit Busy;
	plcbit Error;
} MC_BR_PathInfo_typ;

typedef struct MC_BR_ProgramInfo
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	struct McPrgInfoType ProgramInfo;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	/* VAR_OUTPUT (digital) */
	plcbit Valid;
	plcbit Busy;
	plcbit Error;
} MC_BR_ProgramInfo_typ;

typedef struct MC_BR_SingleStep
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	struct McSingleStepAdvParType AdvancedParameters;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit Continue;
	/* VAR_OUTPUT (digital) */
	plcbit Enabled;
	plcbit Busy;
	plcbit Error;
	plcbit Interrupted;
} MC_BR_SingleStep_typ;

typedef struct MC_BR_OptionalStop
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit Continue;
	/* VAR_OUTPUT (digital) */
	plcbit Valid;
	plcbit Busy;
	plcbit Error;
	plcbit Programmed;
	plcbit Interrupting;
} MC_BR_OptionalStop_typ;

typedef struct MC_BR_OnlinePathInfluence_15
{
	/* VAR_INPUT (analog) */
	McAxesGroupType* AxesGroup;
	unsigned long CoordSystem;
	double PositionOffset[15];
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	/* VAR_OUTPUT (digital) */
	plcbit Enabled;
	plcbit Busy;
	plcbit CommandAborted;
	plcbit Error;
} MC_BR_OnlinePathInfluence_15_typ;

typedef struct MC_GroupContinue
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit CommandAborted;
	plcbit Error;
} MC_GroupContinue_typ;

typedef struct MC_GroupDisable
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Error;
} MC_GroupDisable_typ;

typedef struct MC_GroupEnable
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Error;
} MC_GroupEnable_typ;

typedef struct MC_GroupInterrupt
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit CommandAborted;
	plcbit Error;
} MC_GroupInterrupt_typ;

typedef struct MC_GroupReadActualPosition_15
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	unsigned long CoordSystem;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	double Position[15];
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	/* VAR_OUTPUT (digital) */
	plcbit Valid;
	plcbit Busy;
	plcbit Error;
} MC_GroupReadActualPosition_15_typ;

typedef struct MC_GroupReadError
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	signed long GroupErrorID;
	unsigned long RecordID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit ReadNext;
	/* VAR_OUTPUT (digital) */
	plcbit Valid;
	plcbit Busy;
	plcbit Error;
} MC_GroupReadError_typ;

typedef struct MC_GroupReadStatus
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	/* VAR_OUTPUT (digital) */
	plcbit Valid;
	plcbit Busy;
	plcbit Error;
	plcbit GroupMoving;
	plcbit GroupHoming;
	plcbit GroupErrorStop;
	plcbit GroupStandby;
	plcbit GroupStopping;
	plcbit GroupDisabled;
} MC_GroupReadStatus_typ;

typedef struct MC_GroupReset
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Error;
} MC_GroupReset_typ;

typedef struct MC_GroupStop
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	McStopModeEnum StopMode;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit CommandAborted;
	plcbit Error;
} MC_GroupStop_typ;

typedef struct MC_MoveDirectAbsolute_15
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	double Position[15];
	float Velocity;
	float Acceleration;
	float Deceleration;
	float Jerk;
	unsigned long CoordSystem;
	McBufferModeEnum BufferMode;
	McTransitionModeEnum TransitionMode;
	double TransitionParameter;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Active;
	plcbit CommandAborted;
	plcbit Error;
} MC_MoveDirectAbsolute_15_typ;

typedef struct MC_MoveDirectRelative_15
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	double Distance[15];
	float Velocity;
	float Acceleration;
	float Deceleration;
	float Jerk;
	unsigned long CoordSystem;
	McBufferModeEnum BufferMode;
	McTransitionModeEnum TransitionMode;
	double TransitionParameter;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Active;
	plcbit CommandAborted;
	plcbit Error;
} MC_MoveDirectRelative_15_typ;

typedef struct MC_MoveLinearAbsolute_15
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	double Position[15];
	float Velocity;
	float Acceleration;
	float Deceleration;
	float Jerk;
	unsigned long CoordSystem;
	McBufferModeEnum BufferMode;
	McTransitionModeEnum TransitionMode;
	double TransitionParameter;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Active;
	plcbit CommandAborted;
	plcbit Error;
} MC_MoveLinearAbsolute_15_typ;

typedef struct MC_MoveLinearRelative_15
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	double Distance[15];
	float Velocity;
	float Acceleration;
	float Deceleration;
	float Jerk;
	unsigned long CoordSystem;
	McBufferModeEnum BufferMode;
	McTransitionModeEnum TransitionMode;
	double TransitionParameter;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Active;
	plcbit CommandAborted;
	plcbit Error;
} MC_MoveLinearRelative_15_typ;


typedef struct MC_BR_SetTool
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	plcstring Name[51];
	McExecutionModeEnum ExecutionMode;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Error;
} MC_BR_SetTool_typ;


typedef struct MC_BR_SetToolTable
{
	/* VAR_INPUT (analog) */
	struct McAxesGroupType* AxesGroup;
	plcstring Name[51];
	unsigned short ToolNumber;
	McExecutionModeEnum ExecutionMode;
	/* VAR_OUTPUT (analog) */
	signed long ErrorID;
	/* VAR (analog) */
	struct McInternalType Internal;
	/* VAR_INPUT (digital) */
	plcbit Execute;
	/* VAR_OUTPUT (digital) */
	plcbit Done;
	plcbit Busy;
	plcbit Error;
} MC_BR_SetToolTable_typ;


/* Prototyping of functions and function blocks */
#ifdef __cplusplus
extern "C" {
#endif

_BUR_PUBLIC void MC_BR_ConditionalStop(struct MC_BR_ConditionalStop* inst);
_BUR_PUBLIC void MC_BR_GroupCommandError(struct MC_BR_GroupCommandError* inst);
_BUR_PUBLIC void MC_BR_GroupHome_15(struct MC_BR_GroupHome_15* inst);
_BUR_PUBLIC void MC_BR_GroupJogAbsolute_15(struct MC_BR_GroupJogAbsolute_15* inst);
_BUR_PUBLIC void MC_BR_GroupJogRelative_15(struct MC_BR_GroupJogRelative_15* inst);
_BUR_PUBLIC void MC_BR_GroupJogVelocity_15(struct MC_BR_GroupJogVelocity_15* inst);
_BUR_PUBLIC void MC_BR_GroupMoveCyclicPosition_15(struct MC_BR_GroupMoveCyclicPosition_15* inst);
_BUR_PUBLIC void MC_BR_GroupPower(struct MC_BR_GroupPower* inst);
_BUR_PUBLIC void MC_BR_GroupReadInfo(struct MC_BR_GroupReadInfo* inst);
_BUR_PUBLIC void MC_BR_GroupSetOverride(struct MC_BR_GroupSetOverride* inst);
_BUR_PUBLIC void MC_BR_MFunction(struct MC_BR_MFunction* inst);
_BUR_PUBLIC void MC_BR_MoveBlock(struct MC_BR_MoveBlock* inst);
_BUR_PUBLIC void MC_BR_MoveProgram(struct MC_BR_MoveProgram* inst);
_BUR_PUBLIC void MC_BR_PathInfo(struct MC_BR_PathInfo* inst);
_BUR_PUBLIC void MC_BR_ProgramInfo(struct MC_BR_ProgramInfo* inst);
_BUR_PUBLIC void MC_BR_SingleStep(struct MC_BR_SingleStep* inst);
_BUR_PUBLIC void MC_BR_OptionalStop(struct MC_BR_OptionalStop* inst);
_BUR_PUBLIC void MC_BR_OnlinePathInfluence_15(struct MC_BR_OnlinePathInfluence_15* inst);
_BUR_PUBLIC void MC_GroupContinue(struct MC_GroupContinue* inst);
_BUR_PUBLIC void MC_GroupDisable(struct MC_GroupDisable* inst);
_BUR_PUBLIC void MC_GroupEnable(struct MC_GroupEnable* inst);
_BUR_PUBLIC void MC_GroupInterrupt(struct MC_GroupInterrupt* inst);
_BUR_PUBLIC void MC_GroupReadActualPosition_15(struct MC_GroupReadActualPosition_15* inst);
_BUR_PUBLIC void MC_GroupReadError(struct MC_GroupReadError* inst);
_BUR_PUBLIC void MC_GroupReadStatus(struct MC_GroupReadStatus* inst);
_BUR_PUBLIC void MC_GroupReset(struct MC_GroupReset* inst);
_BUR_PUBLIC void MC_GroupStop(struct MC_GroupStop* inst);
_BUR_PUBLIC void MC_MoveDirectAbsolute_15(struct MC_MoveDirectAbsolute_15* inst);
_BUR_PUBLIC void MC_MoveDirectRelative_15(struct MC_MoveDirectRelative_15* inst);
_BUR_PUBLIC void MC_MoveLinearAbsolute_15(struct MC_MoveLinearAbsolute_15* inst);
_BUR_PUBLIC void MC_MoveLinearRelative_15(struct MC_MoveLinearRelative_15* inst);
_BUR_PUBLIC void MC_BR_SetTool(struct MC_BR_SetTool* inst);
_BUR_PUBLIC void MC_BR_SetToolTable(struct MC_BR_SetToolTable* inst);

#ifdef __cplusplus
} // End of C-Linkage
#endif
#endif /* _MCAXGROUP_ */

