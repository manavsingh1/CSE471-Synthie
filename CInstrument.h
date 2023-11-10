#pragma once
#include "CAudioNode.h"
#include "CNote.h"
class CInstrument :
    public CAudioNode
{
public:
    CInstrument(void);
    ~CInstrument(void);
    virtual void SetNote(CNote* note) = 0;
    // added below
    virtual void SetSecPerBeat(double t) = 0;

};

