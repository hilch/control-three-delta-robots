VAR CONSTANT      
	P1 : McPointType := (Pos:=(X:=0, Y:=0, Z:=-386));
	P2 : McPointType := (Pos:=(X:=-50, Y:=-20, Z:=-386));
	P0 : McPointType := (Pos:=(X:=0, Y:=0, Z:=-386));
END_VAR

PROGRAM _MAIN          
	Feedrate(5000);   //move with reduced speed
	MoveJ(P1);        //move system to point P1
	MoveJ(P2);        //move system to point P2
	
	WaitTime(3);        //wait for 3 seconds
	
	MoveJ(P0);        //move back to origin position
END_PROGRAM
