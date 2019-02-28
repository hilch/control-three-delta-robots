
TYPE
	Robot : 	STRUCT 
		axisQ1 : REFERENCE TO McAxisType;
		axisQ2 : REFERENCE TO McAxisType;
		axisQ3 : REFERENCE TO McAxisType;
		deltaParameters : MpDelta3AxisParType;
		delta : MpDelta3Axis;
	END_STRUCT;
END_TYPE
