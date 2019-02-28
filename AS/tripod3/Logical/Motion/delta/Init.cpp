
#include <bur/plctypes.h>
#include <cstring>

#define _REPLACE_CONST

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

using std::strncpy;

void _INIT ProgramInit(void)
{
	robot[0].delta.MpLink = &g3AxDeltaA;
	robot[0].axisQ1 = &gAxisQ1A;
	robot[0].axisQ2 = &gAxisQ2A;
	robot[0].axisQ3 = &gAxisQ3A;

	//robot[1].delta.MpLink = &g3AxDeltaB; requires additional license
	robot[1].axisQ1 = &gAxisQ1B;
	robot[1].axisQ2 = &gAxisQ2B;
	robot[1].axisQ3 = &gAxisQ3B;

	//robot[2].delta.MpLink = &g3AxDeltaC; requires additional license
	robot[2].axisQ1 = &gAxisQ1C;
	robot[2].axisQ2 = &gAxisQ2C;
	robot[2].axisQ3 = &gAxisQ3C;


	
	for( r = 0; r < NO_OF_ROBOTS; ++r )
	{
		/* Delta parameters */
		strncpy( (char*) &robot[r].deltaParameters.ProgramName, "Robotic.st", sizeof(robot[r].deltaParameters.ProgramName) );

		/* Delta function block */
		robot[r].delta.Parameters = &robot[r].deltaParameters;
		robot[r].delta.Enable = true;
		robot[r].delta.Override = 100;
	}

}


void _EXIT ProgramExit(void)
{
	for( r = 0; r < NO_OF_ROBOTS; ++r )
	{	
		robot[r].delta.Power = false;
		robot[r].delta.Home = false;
		robot[r].delta.MoveDirect = false;
		robot[r].delta.MoveLinear = false;
		MpDelta3Axis(&robot[r].delta);
		robot[r].delta.Enable = false;
		MpDelta3Axis(&robot[r].delta);
	}
}
