
FUNCTION_BLOCK MpDelta3Axis
	VAR_INPUT
		MpLink : REFERENCE TO McAxesGroupType; (*The axis group reference establishes the connection between the function block and the axis group.*)
		Enable : BOOL; (*The function block is active as long as this input is set.*)
		ErrorReset : BOOL; (*Used to reset errors*)
		Parameters : REFERENCE TO MpDelta3AxisParType; (*Parameters of the function block*)
		Update : BOOL; (*Updates the parameters*)
		Override : REAL; (*Velocity override*)
		Power : BOOL; (*Level-sensitive command for turning an axis on/off. In the event of an error, a new rising edge is required to restart the axis.*)
		Home : BOOL; (*Command for homing the axis*)
		MoveProgram : BOOL; (*Start a robot's program*)
		Interrupt : BOOL; (*Interrupts a robot's program*)
		Continue : BOOL; (*Resumes a robot's program*)
		Stop : BOOL; (*Stops the axis*)
		Jog : BOOL; (*Jogs the robot axes in the positive direction*)
		MoveDirect : BOOL; (*Executes a point-to-point movement*)
		MoveLinear : BOOL; (*Executes a linear movement*)
		SingleStep : BOOL; (*Controls the robot in single-step mode*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Indicates whether the function block is active*)
		Error : BOOL; (*Error occurred during operation*)
		StatusID : DINT; (*Status information about the function block*)
		UpdateDone : BOOL; (*Parameter update completed*)
		X : LREAL; (*Current X position [measurement units]*)
		Y : LREAL; (*Current Y position [measurement units]*)
		Z : LREAL; (*Current Z position [measurement units]*)
		PathVelocity : REAL; (*Current path velocity [measurement units/s]*)
		CommandBusy : BOOL; (*Function block currently executing a command*)
		CommandAborted : BOOL; (*Function block interrupted while executing a command*)
		PowerOn : BOOL; (*Robot axes switched on.*)
		IsHomed : BOOL; (*Robot axes homed.*)
		MoveActive : BOOL; (*Robot movement active.*)
		MoveInterrupted : BOOL; (*Robot movement interrupted.*)
		MoveDone : BOOL; (*Robot movement completed.*)
		Stopped : BOOL; (*Axis stopped*)
		InMotion : BOOL; (*At least one of the robot's axes is performing a movement.*)
		SingleStepActive : BOOL; (*Single-step mode active*)
		Info : MpDelta3AxisInfoType; (*Additional information*)
	END_VAR
	VAR
		Internal : {REDUND_UNREPLICABLE} MpComInternalDataType; (*Internal data*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK MpDelta4Axis
	VAR_INPUT
		MpLink : REFERENCE TO McAxesGroupType; (*The axis group reference establishes the connection between the function block and the axis group.*)
		Enable : BOOL; (*The function block is active as long as this input is set.*)
		ErrorReset : BOOL; (*Used to reset errors*)
		Parameters : REFERENCE TO MpDelta4AxisParType; (*Parameters of the function block*)
		Update : BOOL; (*Updates the parameters*)
		Override : REAL; (*Velocity override*)
		Power : BOOL; (*Level-sensitive command for turning an axis on/off. In the event of an error, a new rising edge is required to restart the axis.*)
		Home : BOOL; (*Command for homing the axis*)
		MoveProgram : BOOL; (*Start a robot's program*)
		Interrupt : BOOL; (*Interrupts a robot's program*)
		Continue : BOOL; (*Resumes a robot's program*)
		Stop : BOOL; (*Stops the axis*)
		Jog : BOOL; (*Jogs the robot axes in the positive direction*)
		MoveDirect : BOOL; (*Executes a point-to-point movement*)
		MoveLinear : BOOL; (*Executes a linear movement*)
		SingleStep : BOOL; (*Controls the robot in single-step mode*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Indicates whether the function block is active*)
		Error : BOOL; (*Error occurred during operation*)
		StatusID : DINT; (*Status information about the function block*)
		UpdateDone : BOOL; (*Parameter update completed*)
		X : LREAL; (*Current X position [measurement units]*)
		Y : LREAL; (*Current Y position [measurement units]*)
		Z : LREAL; (*Current Z position [measurement units]*)
		C : LREAL; (*Current C position [measurement units]*)
		PathVelocity : REAL; (*Current path velocity [measurement units/s]*)
		CommandBusy : BOOL; (*Function block currently executing a command*)
		CommandAborted : BOOL; (*Function block interrupted while executing a command*)
		PowerOn : BOOL; (*Robot axes switched on.*)
		IsHomed : BOOL; (*Robot axes homed.*)
		MoveActive : BOOL; (*Robot movement active.*)
		MoveInterrupted : BOOL; (*Robot movement interrupted.*)
		MoveDone : BOOL; (*Robot movement completed.*)
		Stopped : BOOL; (*Axis stopped*)
		InMotion : BOOL; (*At least one of the robot's axes is performing a movement.*)
		SingleStepActive : BOOL; (*Single-step mode active*)
		Info : MpDelta4AxisInfoType; (*Additional information*)
	END_VAR
	VAR
		Internal : {REDUND_UNREPLICABLE} MpComInternalDataType; (*Internal data*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK MpRoboticsFlex
	VAR_INPUT
		MpLink : REFERENCE TO McAxesGroupType; (*The axis group reference establishes the connection between the function block and the axis group.*)
		Enable : BOOL; (*The function block is active as long as this input is set.*)
		ErrorReset : BOOL; (*Used to reset errors*)
		Parameters : REFERENCE TO MpRoboticsFlexParType; (*Parameters of the function block*)
		Update : BOOL; (*Updates the parameters*)
		Override : REAL; (*Velocity override*)
		Power : BOOL; (*Level-sensitive command for turning an axis on/off. In the event of an error, a new rising edge is required to restart the axis.*)
		Home : BOOL; (*Command for homing the axis*)
		MoveProgram : BOOL; (*Start a robot's program*)
		Interrupt : BOOL; (*Interrupts a robot's program*)
		Continue : BOOL; (*Resumes a robot's program*)
		Stop : BOOL; (*Stops the axis*)
		Jog : BOOL; (*Jogs the robot axes in the positive direction*)
		MoveDirect : BOOL; (*Executes a point-to-point movement*)
		MoveLinear : BOOL; (*Executes a linear movement*)
		SingleStep : BOOL; (*Controls the robot in single-step mode*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Indicates whether the function block is active*)
		Error : BOOL; (*Error occurred during operation*)
		StatusID : DINT; (*Status information about the function block*)
		UpdateDone : BOOL; (*Parameter update completed*)
		Position : ARRAY[0..14] OF LREAL; (*Current position [measurement units]*)
		PathVelocity : REAL; (*Current path velocity [measurement units/s]*)
		CommandBusy : BOOL; (*Function block currently executing a command*)
		CommandAborted : BOOL; (*Function block interrupted while executing a command*)
		PowerOn : BOOL; (*Robot axes switched on.*)
		IsHomed : BOOL; (*Robot axes homed.*)
		MoveActive : BOOL; (*Robot movement active.*)
		MoveInterrupted : BOOL; (*Robot movement interrupted.*)
		MoveDone : BOOL; (*Robot movement completed.*)
		Stopped : BOOL; (*Axis stopped*)
		InMotion : BOOL; (*At least one of the robot's axes is performing a movement.*)
		SingleStepActive : BOOL; (*Single-step mode active*)
		Info : MpRoboticsFlexInfoType; (*Additional information*)
	END_VAR
	VAR
		Internal : {REDUND_UNREPLICABLE} MpComInternalDataType; (*Internal data*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK MpRoboArm6Axis
	VAR_INPUT
		MpLink : REFERENCE TO McAxesGroupType; (*The axis group reference establishes the connection between the function block and the axis group.*)
		Enable : BOOL; (*The function block is active as long as this input is set.*)
		ErrorReset : BOOL; (*Used to reset errors*)
		Parameters : REFERENCE TO MpRoboArm6AxisParType; (*Parameters of the function block*)
		Update : BOOL; (*Updates the parameters*)
		Override : REAL; (*Velocity override*)
		Power : BOOL; (*Level-sensitive command for turning an axis on/off. In the event of an error, a new rising edge is required to restart the axis.*)
		Home : BOOL; (*Command for homing the axis*)
		MoveProgram : BOOL; (*Start a robot's program*)
		Interrupt : BOOL; (*Interrupts a robot's program*)
		Continue : BOOL; (*Resumes a robot's program*)
		Stop : BOOL; (*Stops the axis*)
		Jog : BOOL; (*Jogs the robot axes in the positive direction*)
		MoveDirect : BOOL; (*Executes a point-to-point movement*)
		MoveLinear : BOOL; (*Executes a linear movement*)
		SingleStep : BOOL; (*Controls the robot in single-step mode*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Indicates whether the function block is active*)
		Error : BOOL; (*Error occurred during operation*)
		StatusID : DINT; (*Status information about the function block*)
		UpdateDone : BOOL; (*Parameter update completed*)
		X : LREAL; (*Current X position [measurement units]*)
		Y : LREAL; (*Current Y position [measurement units]*)
		Z : LREAL; (*Current Z position [measurement units]*)
		A : LREAL; (*Current C position [measurement units]*)
		B : LREAL; (*Current C position [measurement units]*)
		C : LREAL; (*Current C position [measurement units]*)
		PathVelocity : REAL; (*Current path velocity [measurement units/s]*)
		CommandBusy : BOOL; (*Function block currently executing a command*)
		CommandAborted : BOOL; (*Function block interrupted while executing a command*)
		PowerOn : BOOL; (*Robot axes switched on.*)
		IsHomed : BOOL; (*Robot axes homed.*)
		MoveActive : BOOL; (*Robot movement active.*)
		MoveInterrupted : BOOL; (*Robot movement interrupted.*)
		MoveDone : BOOL; (*Robot movement completed.*)
		Stopped : BOOL; (*Axis stopped*)
		InMotion : BOOL; (*At least one of the robot's axes is performing a movement.*)
		SingleStepActive : BOOL; (*Single-step mode active*)
		Info : MpRoboArm6AxisInfoType; (*Additional information*)
	END_VAR
	VAR
		Internal : MpComInternalDataType; (*Internal data*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK MpRoboArm4Axis
	VAR_INPUT
		MpLink : REFERENCE TO McAxesGroupType; (*The axis group reference establishes the connection between the function block and the axis group.*)
		Enable : BOOL; (*The function block is active as long as this input is set.*)
		ErrorReset : BOOL; (*Used to reset errors*)
		Parameters : REFERENCE TO MpRoboArm4AxisParType; (*Parameters of the function block*)
		Update : BOOL; (*Updates the parameters*)
		Override : REAL; (*Velocity override*)
		Power : BOOL; (*Level-sensitive command for turning an axis on/off. In the event of an error, a new rising edge is required to restart the axis.*)
		Home : BOOL; (*Command for homing the axis*)
		MoveProgram : BOOL; (*Start a robot's program*)
		Interrupt : BOOL; (*Interrupts a robot's program*)
		Continue : BOOL; (*Resumes a robot's program*)
		Stop : BOOL; (*Stops the axis*)
		Jog : BOOL; (*Jogs the robot axes in the positive direction*)
		MoveDirect : BOOL; (*Executes a point-to-point movement*)
		MoveLinear : BOOL; (*Executes a linear movement*)
		SingleStep : BOOL; (*Controls the robot in single-step mode*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Indicates whether the function block is active*)
		Error : BOOL; (*Error occurred during operation*)
		StatusID : DINT; (*Status information about the function block*)
		UpdateDone : BOOL; (*Parameter update completed*)
		X : LREAL; (*Current X position [measurement units]*)
		Y : LREAL; (*Current Y position [measurement units]*)
		Z : LREAL; (*Current Z position [measurement units]*)
		C : LREAL; (*Current C position [measurement units]*)
		PathVelocity : REAL; (*Current path velocity [measurement units/s]*)
		CommandBusy : BOOL; (*Function block currently executing a command*)
		CommandAborted : BOOL; (*Function block interrupted while executing a command*)
		PowerOn : BOOL; (*Robot axes switched on.*)
		IsHomed : BOOL; (*Robot axes homed.*)
		MoveActive : BOOL; (*Robot movement active.*)
		MoveInterrupted : BOOL; (*Robot movement interrupted.*)
		MoveDone : BOOL; (*Robot movement completed.*)
		Stopped : BOOL; (*Axis stopped*)
		InMotion : BOOL; (*At least one of the robot's axes is performing a movement.*)
		SingleStepActive : BOOL; (*Single-step mode active*)
		Info : MpRoboArm4AxisInfoType; (*Additional information*)
	END_VAR
	VAR
		Internal : MpComInternalDataType; (*Internal data*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK MpScara4Axis
	VAR_INPUT
		MpLink : REFERENCE TO McAxesGroupType; (*The axis group reference establishes the connection between the function block and the axis group.*)
		Enable : BOOL; (*The function block is active as long as this input is set.*)
		ErrorReset : BOOL; (*Used to reset errors*)
		Parameters : REFERENCE TO MpScara4AxisParType; (*Parameters of the function block*)
		Update : BOOL; (*Updates the parameters*)
		Override : REAL; (*Velocity override*)
		Power : BOOL; (*Level-sensitive command for turning an axis on/off. In the event of an error, a new rising edge is required to restart the axis.*)
		Home : BOOL; (*Command for homing the axis*)
		MoveProgram : BOOL; (*Start a robot's program*)
		Interrupt : BOOL; (*Interrupts a robot's program*)
		Continue : BOOL; (*Resumes a robot's program*)
		Stop : BOOL; (*Stops the axis*)
		Jog : BOOL; (*Jogs the robot axes in the positive direction*)
		MoveDirect : BOOL; (*Executes a point-to-point movement*)
		MoveLinear : BOOL; (*Executes a linear movement*)
		SingleStep : BOOL; (*Controls the robot in single-step mode*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Indicates whether the function block is active*)
		Error : BOOL; (*Error occurred during operation*)
		StatusID : DINT; (*Status information about the function block*)
		UpdateDone : BOOL; (*Parameter update completed*)
		X : LREAL; (*Current X position [measurement units]*)
		Y : LREAL; (*Current Y position [measurement units]*)
		Z : LREAL; (*Current Z position [measurement units]*)
		C : LREAL; (*Current C position [measurement units]*)
		PathVelocity : REAL; (*Current path velocity [measurement units/s]*)
		CommandBusy : BOOL; (*Function block currently executing a command*)
		CommandAborted : BOOL; (*Function block interrupted while executing a command*)
		PowerOn : BOOL; (*Robot axes switched on.*)
		IsHomed : BOOL; (*Robot axes homed.*)
		MoveActive : BOOL; (*Robot movement active.*)
		MoveInterrupted : BOOL; (*Robot movement interrupted.*)
		MoveDone : BOOL; (*Robot movement completed.*)
		Stopped : BOOL; (*Axis stopped*)
		InMotion : BOOL; (*At least one of the robot's axes is performing a movement.*)
		SingleStepActive : BOOL; (*Single-step mode active*)
		Info : MpScara4AxisInfoType; (*Additional information*)
	END_VAR
	VAR
		Internal : {REDUND_UNREPLICABLE} MpComInternalDataType; (*Internal data*)
	END_VAR
END_FUNCTION_BLOCK
