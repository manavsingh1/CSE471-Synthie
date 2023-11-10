#include "pch.h"
#include "CEnvelope.h"

CEnvelope::CEnvelope() {
    attack_ratio = 0.1;
    release_ratio = 0.1;
    decay_ratio = 0.4;
    time = 0.0;
    sustain_level = 0.7;
}

void CEnvelope::Start() {
}

bool CEnvelope::Generate(double duration) {
    // get the sample
    double attack = attack_ratio * duration;
    double release = release_ratio * duration;
    double decay = decay_ratio * duration;
    if (time < attack) {
        
        m_frame[0] = source->Frame(0) * time / attack;
        m_frame[1] = source->Frame(1) * time / attack;
    }
    else if (time >= attack && time < (attack + decay)) {
        //Decay
        m_frame[0] = source->Frame(0) * sustain_level +
            source->Frame(0) * (1 - sustain_level) * (decay + attack - time) / decay;
        m_frame[1] = source->Frame(1) * sustain_level +
            source->Frame(1) * (1 - sustain_level) * (decay + attack - time) / decay;
    }
    else if (time > (duration - release)) {
        //Release
        m_frame[0] = sustain_level * source->Frame(0) * (duration - time) / release;
        m_frame[1] = sustain_level * source->Frame(1) * (duration - time) / release;
    }
    else {
        //Sustain
        m_frame[0] = sustain_level * source->Frame(0);
        m_frame[1] = sustain_level * source->Frame(1);
    }


    
    time += GetSamplePeriod();

    
    return time < duration;
    // true until time reaches dur
}


bool CEnvelope::Generate() {
    return false;
}
void CEnvelope::SetSource(CAudioNode* sourcefile) {
    source = sourcefile;
}