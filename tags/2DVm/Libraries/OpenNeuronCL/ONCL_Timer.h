/**
\file	Timer.h

\brief	Declares the standard color class.
**/

#pragma once

/**
\namespace	StdUtils

\brief	Namespace for the standard utility objects.
**/
namespace OpenNeuronCL
{

typedef struct {
     LARGE_INTEGER start;
     LARGE_INTEGER stop;
 } stopWatch;
 

/**
\brief	Standard Timer class. 

\author	dcofer
\date	5/3/2011
**/
/**
\brief	Standard color class. 

\author	dcofer
\date	5/3/2011
**/
class OPENNEURONCL_PORT Timer {
 
 private:
     stopWatch timer;
     LARGE_INTEGER frequency;
     double LIToSecs( LARGE_INTEGER & L) ;
	 bool m_bStarted;
 public:
     Timer() ;
     void StartTimer( ) ;
     double StopTimer( ) ;
     double ElapsedTime() ;

	 bool TimerStarted() {return m_bStarted;}
 };

}				//StdUtils
