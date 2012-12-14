/**
\file	Timer.cpp

\brief	Implements the standard color class.
**/

#include "StdAfx.h"

namespace OpenNeuronCL
{

 double Timer::LIToSecs( LARGE_INTEGER & L) {
     return ((double)L.QuadPart /(double)frequency.QuadPart) ;
 }
 
 Timer::Timer(){
     timer.start.QuadPart=0;
     timer.stop.QuadPart=0; 
     QueryPerformanceFrequency( &frequency ) ;
 	 m_bStarted = false;
}
 
 void Timer::StartTimer( ) {
	 m_bStarted = true;
     QueryPerformanceCounter(&timer.start) ;
 }
 
 double Timer::StopTimer( ) {
     QueryPerformanceCounter(&timer.stop) ;
	 m_bStarted = false;
	 return ElapsedTime();
 }
 
 double Timer::ElapsedTime() {
     LARGE_INTEGER time;
     time.QuadPart = timer.stop.QuadPart - timer.start.QuadPart;
     return LIToSecs( time) ;
 }


}				//StdUtils
