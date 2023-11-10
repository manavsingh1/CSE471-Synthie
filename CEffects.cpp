#include "pch.h"
#include "CEffects.h"
#include "CFlanging.h"
#include "CReverb.h"

CEffects::CEffects() {
}

CEffects::~CEffects() {
}

void CEffects::XmlLoad(IXMLDOMNode* xml, std::wstring& effect) {

    CComPtr<IXMLDOMNamedNodeMap> attributes;
    xml->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    if (effect == L"chorus") {
        CChorus* chorus = new CChorus();
        chorus->SetSampleRate(sample_rate);
        chorus->XmlLoad(xml, effect);
        effects.push_back(chorus);
    }
    else if (effect == L"flanging") {
        CFlanging* flange = new CFlanging();
        flange->SetSampleRate(sample_rate);
        flange->XmlLoad(xml, effect);
        effects.push_back(flange);
    }
    else if (effect == L"reverbation") {
        CReverb* reverbe = new CReverb();
        reverbe->SetSampleRate(sample_rate);
        reverbe->XmlLoad(xml, effect);
        effects.push_back(reverbe);
    }
}

void CEffects::ProcessStream(double* in_frame, int channels) {
    for (std::vector<CEffect*>::iterator it = effects.begin(); it != effects.end(); ++it) {
        (*it)->ProcessStream(in_frame, channels);
    }
}

void CEffects::empty() {
    effects.clear();
}