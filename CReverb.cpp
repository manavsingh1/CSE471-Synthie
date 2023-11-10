#include "pch.h"
#include "CReverb.h"

CReverb::CReverb() {
    reverbation_queue_0.resize(100000);
    reverbation_queue_1.resize(100000);
    output_queue_0.resize(100000);
    output_queue_1.resize(100000);
    m_wrloc = 0;
    reverbation_rate = 0;
    reverbation = false;
    reverbation_wet = 0.0;
    reverbation_dry = 0.0;
}

CReverb::~CReverb() {

}

void CReverb::XmlLoad(IXMLDOMNode* xml, std::wstring& effect) {
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    xml->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    if (effect == L"reverbation") {
        reverbation = true;
        for (int i = 0; i < len; i++)
        {
            
            CComPtr<IXMLDOMNode> attrib;
            attributes->get_item(i, &attrib);

            
            CComBSTR name;
            attrib->get_nodeName(&name);

            CComVariant value;
            attrib->get_nodeValue(&value);

            if (name == "rate")
            {
                reverbation_rate = std::stod(value.bstrVal);
            }
            else if (name == "wet")
            {
                reverbation_wet = std::stod(value.bstrVal);
            }
            else if (name == "dry")
            {
                reverbation_dry = std::stod(value.bstrVal);
            }
        }
    }
}

void CReverb::ProcessStream(double* in_frame, int channels) {
    assert(reverbation && channels == 2);
    double original[2] = { in_frame[0], in_frame[1] };
    m_wrloc = (m_wrloc + 1) % 100000;

    reverbation_queue_0[(m_wrloc)] = in_frame[0];
    reverbation_queue_1[(m_wrloc)] = in_frame[1];
    in_frame[0] = 0.0;
    in_frame[1] = 0.0;
    int factor = 1;
    for (int i = 1; i < 10; i++) {
        int rdloc = int(m_wrloc + 100000 - reverbation_rate * sample_rate * i) % 100000;
        in_frame[0] += reverbation_queue_0[rdloc] * 1 / (i + 1) * reverbation_wet;
        in_frame[1] += reverbation_queue_1[rdloc] * 1 / (i + 1) * reverbation_wet;
        factor += 1 / (i + 1);
    }

    in_frame[0] = in_frame[0] / factor + original[0] * reverbation_dry;
    in_frame[1] = in_frame[1] / factor + original[1] * reverbation_dry;

}