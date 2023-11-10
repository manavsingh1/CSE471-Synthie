#pragma once
#include "CInstrument.h"
#include "CSineWave.h"
#include "CEnvelope.h"

class CToneInstrument :
    public CInstrument
{
public:
    CToneInstrument(void);
    ~CToneInstrument(void);
    virtual void Start();
    virtual bool Generate();

    void SetFreq(double f) { m_sinewave.SetFreq(f); }
    void SetAmplitude(double a) { m_sinewave.SetAmplitude(a); }
    void SetDuration(double d) { m_duration = d; }
    void SetNote(CNote* note);
    void SetSecPerBeat(double t) { m_secperbeat = t; }
private:
    CSineWave   m_sinewave;
    double m_duration;
    double m_time;
    //added
    double m_secperbeat;
    CEnvelope   m_adsr;

};

