#include <iostream>
#include "VisualDebugger.h"

using namespace std;
using namespace VisualDebugger;

// ##################
// ### Main Class ###
// ##################
int main()
{
	// Try to Start the Game
	try 
	{ 
		Init("Physics Game", 800, 800); 
	}
	catch (Exception exc) // Catch any exceptions
	{ 
		cerr << exc.what() << endl;
		return 0; 
	}

	Start();

	return 0;
}