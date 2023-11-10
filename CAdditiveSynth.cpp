#include "pch.h"
#include "CAdditiveSynth.h"
#include "Notes.h"
#include <sstream>

CAdditiveSynth::CAdditiveSynth(void)
{
    m_duration = 0.1;
    m_secperbeat = 0.1;
}

void CAdditiveSynth::SetFreq(double f) {
    for (int i = 1; i <= 8; i++) {
        if (f * i >= GetSampleRate() / 2) {
            break;
        }
        CSineWave sinewave;
        sinewave.SetFreq(f * i);
        m_sinewaves.push_back(sinewave);
    }
}
void CAdditiveSynth::SetAmplitude(std::vector<std::wstring> amplitudes) {
    std::vector<std::wstring>::iterator am = amplitudes.begin();
    double amplitude = 0;
    if (am != amplitudes.end()) {
        amplitude = std::stod(*am);
    }

    for (std::vector<CSineWave>::iterator it = m_sinewaves.begin(); it != m_sinewaves.end(); ++it) {
        it->SetAmplitude(amplitude);
        if (am != amplitudes.end()) {
            ++am;
        }
        if (am != amplitudes.end()) {
            amplitude = std::stod(*am);
        }
        else {
            amplitude = 0.0;
        }

    }
}



void CAdditiveSynth::Start()
{
    for (std::vector<CSineWave>::iterator it = m_sinewaves.begin(); it != m_sinewaves.end(); ++it) {
        it->SetSampleRate(GetSampleRate());
        it->Start();
// sinewave below

        CEnvelope adsr;
        adsr.SetSource(&(*it));
        adsr.SetSampleRate(GetSampleRate());
        adsr.Start();

        m_adsrs.push_back(adsr);
    }

    m_time = 0;
}


bool CAdditiveSynth::Generate()
{
    //  generate an audio sample
    for (std::vector<CSineWave>::iterator it = m_sinewaves.begin(); it != m_sinewaves.end(); ++it) {
        it->Generate();
    }

    bool valid;
    m_frame[0] = m_adsrs[0].Frame(0);
    m_frame[1] = m_adsrs[0].Frame(1);
    for (std::vector<CEnvelope>::iterator it = m_adsrs.begin()++; it != m_adsrs.end(); ++it) {
        valid = it->Generate(m_duration); 
        m_frame[0] += it->Frame(0);
        m_frame[1] += it->Frame(1);
    }
    m_time += GetSamplePeriod();
    return valid;
}

void CAdditiveSynth::SetNote(CNote* note)
{
  
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    note->Node()->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    
    for (int i = 0; i < len; i++)
    {
        CComPtr<IXMLDOMNode> attrib;
        attributes->get_item(i, &attrib);

        CComBSTR name;
        attrib->get_nodeName(&name);

  
        CComVariant value;
        attrib->get_nodeValue(&value);

        if (name == "duration")
        {
            value.ChangeType(VT_R8);
            double duration = value.dblVal * m_secperbeat;
            SetDuration(duration);
        }
        else if (name == "note")
        {
            SetFreq(NoteToFrequency(value.bstrVal));
        }

        // define harmonics
        else if (name == "harmonics")
        {
            std::wstring amplitudes = L"", temp;
            amplitudes = value.bstrVal;
            std::vector<std::wstring> parts;
            std::wstringstream wss(amplitudes);
            while (std::getline(wss, temp, L' '))
                parts.push_back(temp);
            SetAmplitude(parts);
        }


    }

}