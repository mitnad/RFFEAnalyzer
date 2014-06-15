#ifndef MANCHESTER_ANALYZER
#define MANCHESTER_ANALYZER

#ifdef WIN32
	#define EXPORT __declspec(dllexport)
#else
	#define EXPORT
	#define __cdecl
	#define __stdcall
	#define __fastcall
#endif

#include "Analyzer.h"
#include "ManchesterAnalyzerResults.h"
#include "ManchesterSimulationDataGenerator.h"

class ManchesterAnalyzerSettings;


class ManchesterAnalyzer : public Analyzer2
{
public:
	ManchesterAnalyzer();
	virtual ~ManchesterAnalyzer();
	virtual void SetupResults();
	virtual void WorkerThread();
	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();
	virtual bool NeedsRerun();
	virtual const char* GetAnalyzerName() const;
	
protected:

	void ProcessBiPhaseData();
	void SynchronizeBiPhase();
	void ProcessManchesterData();
	void SynchronizeManchester();
	void ProcessDifferential();
	void SynchronizeDifferential();
	void SaveBit( U64 location, U32 value );
	void Invalidate();
	void ProcessSpace( U32 half_periods );
	AnalyzerChannelData* mManchester;

	std::auto_ptr< ManchesterAnalyzerSettings > mSettings;
	std::auto_ptr< ManchesterAnalyzerResults > mResults;

	ManchesterSimulationDataGenerator mSimulationDataGenerator;

	U32 mSampleRateHz;

	bool mSimulationInitilized;

	U32 mT;
	U32 mTError;
	std::vector< std::pair< U32, U64 > > mBitsForNextByte; //value, location
	std::vector<U64> mUnsyncedLocations;
	bool mSynchronized;
	U32 mIgnoreBitCount;

};
extern "C" EXPORT const char* __cdecl GetAnalyzerName();
extern "C" EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );
#endif //MANCHESTER_ANALYZER