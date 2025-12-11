#ifndef TUPLEID_HH
#define TUPLEID_HH

#include "G4AnalysisManager.hh"

struct TupleID{
    G4AnalysisManager* analysisManager;

    int leftTrackID;
    int rightTrackID;

    int leftCalID;
    int rightCalID;
};

#endif