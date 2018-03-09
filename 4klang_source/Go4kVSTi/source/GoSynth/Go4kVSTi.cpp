#include <stdio.h>
#include <windows.h>
#ifndef __Go4kVSTi__
#include "Go4kVSTi.h"
#endif

//-----------------------------------------------------------------------------------------
// Go4kVSTi
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
Go4kVSTi::Go4kVSTi (audioMasterCallback audioMaster) : AudioEffectX (audioMaster, 0, 0)
{
	if (audioMaster)
	{
		setNumInputs (0);				// no inputs
		setNumOutputs (2);				// 2 outputs, stereo
		canProcessReplacing ();
		hasVu (false);
		hasClip (false);
		isSynth ();
#ifdef _8KLANG
		setUniqueID ('8klg');
#else
		setUniqueID ('4klg');
#endif
	}
	initProcess ();
	suspend ();
}

//-----------------------------------------------------------------------------------------
Go4kVSTi::~Go4kVSTi ()
{
}

//-----------------------------------------------------------------------------------------
void Go4kVSTi::setProgram (long program)
{
}

//-----------------------------------------------------------------------------------------
void Go4kVSTi::setProgramName (char *name)
{
}

//-----------------------------------------------------------------------------------------
void Go4kVSTi::getProgramName (char *name)
{
}

//-----------------------------------------------------------------------------------------
void Go4kVSTi::getParameterLabel (long index, char *label)
{
}

//-----------------------------------------------------------------------------------------
void Go4kVSTi::getParameterDisplay (long index, char *text)
{
}

//-----------------------------------------------------------------------------------------
void Go4kVSTi::getParameterName (long index, char *label)
{
}

//-----------------------------------------------------------------------------------------
void Go4kVSTi::setParameter (long index, float value)
{
}

//-----------------------------------------------------------------------------------------
float Go4kVSTi::getParameter (long index)
{
	return 0;
}

//-----------------------------------------------------------------------------------------
bool Go4kVSTi::getOutputProperties (long index, VstPinProperties* properties)
{
	if (index < 2)
	{
		sprintf (properties->label, "Vstx %1d", index + 1);
		properties->flags = kVstPinIsActive;
		properties->flags |= kVstPinIsStereo;	// test, make channel 1+2 stereo
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------------
bool Go4kVSTi::getProgramNameIndexed (long category, long index, char* text)
{
	return false;
}

//-----------------------------------------------------------------------------------------
bool Go4kVSTi::copyProgram (long destination)
{
	return false;
}

//-----------------------------------------------------------------------------------------
bool Go4kVSTi::getEffectName (char* name)
{
#ifdef _8KLANG
	strcpy (name, "8klang");
#else
	strcpy (name, "4klang");
#endif
	return true;
}

//-----------------------------------------------------------------------------------------
bool Go4kVSTi::getVendorString (char* text)
{
	strcpy (text, "Alcatraz");
	return true;
}

//-----------------------------------------------------------------------------------------
bool Go4kVSTi::getProductString (char* text)
{
#ifdef _8KLANG
	strcpy (text, "8klang");
#else
	strcpy (text, "4klang");
#endif
	return true;
}

//-----------------------------------------------------------------------------------------
long Go4kVSTi::canDo (char* text)
{
	if (!strcmp (text, "receiveVstEvents"))
		return 1;
	if (!strcmp (text, "receiveVstMidiEvent"))
		return 1;
	if (!strcmp (text, "receiveVstTimeInfo"))
		return 1;
	return -1;	// explicitly can't do; 0 => don't know
}

