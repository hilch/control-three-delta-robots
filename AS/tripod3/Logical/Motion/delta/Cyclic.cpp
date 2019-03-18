
#include <bur/plctypes.h>

#define _REPLACE_CONST

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// amount of memory to be allocated for heap storage must be specified for every ANSI C++ program with the bur_heap_size variable
unsigned long bur_heap_size = 0xFFFF; 

void _CYCLIC ProgramCyclic(void)
{
	for( r = 0; r < NO_OF_ROBOTS; ++r )
	{
		MpDelta3Axis(&robot[r].delta);

		if( robot[r].delta.IsHomed )
			robot[r].delta.Home = false;

	if( robot[r].delta.MoveDone || robot[r].delta.Stopped || robot[r].delta.Error )
	{
		robot[r].delta.MoveProgram = false;
		robot[r].delta.Stop = false;
	}

}
