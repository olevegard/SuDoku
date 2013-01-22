#pragma once

class CLogTool
{

	public:
		// Logs the differece between two poits in time.
		static void LogTime( const timespec &startTime, const timespec &stopTime )
		{
			unsigned long long iTimeStart = startTime.tv_sec * 1000000000 + startTime.tv_nsec;
			unsigned long long iTimeStop = stopTime.tv_sec * 1000000000 + stopTime.tv_nsec;
			unsigned long long iTimeDelta = iTimeStop - iTimeStart;

			std::cout << "====================Time used ====================\n"
				<< "||\tSeconds      : " << static_cast< float > ( iTimeDelta / 1000000000.0f ) << " s\t||\n"
				<< "||\tMilliseconds : " << static_cast< float > ( iTimeDelta / 1000000.0f ) << " ms\t||\n"
				<< "||\tMicroseconds : " << static_cast< float > ( iTimeDelta / 1000.0f ) << " µs\t||\n"
				<< "||\tNanoseconds  : " << static_cast< float > ( iTimeDelta ) << " ns\t\t||\n";
		}
};
