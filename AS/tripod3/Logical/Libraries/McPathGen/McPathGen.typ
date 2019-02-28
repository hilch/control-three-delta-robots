TYPE
	McPathGenMonElemPrgType : STRUCT (*Monitoring Element: Program*)
		FileName : STRING[260]; (**)
		FullPath : STRING[260]; (**)
		Number : UDINT; (**)
	END_STRUCT;

	McPathGenMonElemCurrentPrgType : STRUCT (*Monitoring Element: Current program*)
		FileName : STRING[260]; (**)
		FullPath : STRING[260]; (**)
		Number : UDINT; (**)
		CallLevel : UDINT; (**)
	END_STRUCT;

	McPathGenMonElemBlockMonType : STRUCT (*Monitoring Element: Block monitor*)
		BlockLast2 : STRING[260]; (**)
		BlockLast1 : STRING[260]; (**)
		BlockActual : STRING[260]; (**)
		BlockNext1 : STRING[260]; (**)
		BlockNext2 : STRING[260]; (**)
	END_STRUCT;

	McPathGenMonElemPrgSequenceType : STRUCT (*Monitoring Element: Nested program sequence*)
		CallLevel : UDINT; (**)
		Program : ARRAY [0..31] OF McPathGenMonElemPrgType; (**)
	END_STRUCT;

	McPathGenMonElemAxPositionsType : STRUCT (*Monitoring Element: Axes positions*)
		SetPosition : ARRAY [0..9] OF LREAL; (**)
	END_STRUCT;

	McPathGenMonElemPathSpeedType : STRUCT (*Monitoring Element: Programmed path speed*)
		UnitPerMinute : REAL; (**)
		UnitPerRevolution : REAL; (**)
		Inverse : REAL; (**)
	END_STRUCT;

	McPathGenMonElemToolTransType : STRUCT (*Monitoring Element: Tool description: Translation*)
		X : LREAL; (**)
		Y : LREAL; (**)
		Z : LREAL; (**)
	END_STRUCT;

	McPathGenMonElemToolOrientType : STRUCT (*Monitoring Element: Tool description: Orientation*)
		Angle1 : LREAL; (**)
		Angle2 : LREAL; (**)
		Angle3 : LREAL; (**)
	END_STRUCT;

	McPathGenMonElemToolDescType : STRUCT (*Monitoring Element: Tool description*)
		ToolTranslation : McPathGenMonElemToolTransType; (**)
		ToolOrientation : McPathGenMonElemToolOrientType; (**)
		ToolLength : LREAL; (**)
		ToolRadius : LREAL; (**)
		ToolVirtualToolTip : DINT; (**)
	END_STRUCT;

	McPathGenMonElemAxLimitsType : STRUCT (*Monitoring Element: Axis limits*)
		UpperPositionLimit : LREAL; (**)
		LowerPositionLimit : LREAL; (**)
		VelocityPositive : REAL; (**)
		VelocityNegative : REAL; (**)
		AccelerationPositive : REAL; (**)
		AccelerationNegative : REAL; (**)
		DecelerationPositive : REAL; (**)
		DecelerationNegative : REAL; (**)
		JerkAccelerationPositive : REAL; (**)
		JerkAccelerationNegative : REAL; (**)
		JerkDecelerationPositive : REAL; (**)
		JerkDecelerationNegative : REAL; (**)
	END_STRUCT;

	McPathGenMonElemAxTorquesType : STRUCT (*Monitoring Element: Torques*)
		Torques : ARRAY [0..9] OF LREAL; (**)
	END_STRUCT;

	McPathGenMonElemBasicMonType : STRUCT (*Monitoring Element: Basic monitor*)
		CurrentProgram : McPathGenMonElemCurrentPrgType; (**)
		LineNumber : UDINT; (**)
		BlockNumber : UDINT; (**)
		Runtime : LREAL; (**)
		PathSpeed : REAL; (**)
		Axes : McPathGenMonElemAxPositionsType; (**)
		TCPInMCS : McPathGenMonElemAxPositionsType; (**)
		SlaveAxes : McPathGenMonElemAxPositionsType; (**)
	END_STRUCT;
END_TYPE
