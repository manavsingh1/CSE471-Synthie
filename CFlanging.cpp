
#include "pch.h"
#include "CFlanging.h"


CFlanging::CFlanging() {
    flanging = false;
    flanging_delay = 0.0;
    flanging_wet = 0.0;
    flanging_dry = 0.0;
    flanging_level = 0.0;
    flanging_queue_0.resize(100000);
    flanging_queue_1.resize(100000);
    output_queue_0.resize(100000);
    output_queue_1.resize(100000);
    m_wrloc = 0;
}

CFlanging::~CFlanging() {

}


void CFlanging::XmlLoad(IXMLDOMNode* xml, std::wstring& effect) {

    CComPtr<IXMLDOMNamedNodeMap> attributes;
    xml->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    if (effect == L"flanging") {
        flanging = true;
       
        for (int i = 0; i < len; i++)
        {
           
            CComPtr<IXMLDOMNode> attrib;
            attributes->get_item(i, &attrib);

            CComBSTR name;
            attrib->get_nodeName(&name);
 
            CComVariant value;
            attrib->get_nodeValue(&value);

            if (name == "delay")
            {
                flanging_delay = std::stod(value.bstrVal);
            }
            else if (name == "wet")
            {
                flanging_wet = std::stod(value.bstrVal);
            }
            else if (name == "dry")
            {
                flanging_dry = std::stod(value.bstrVal);
            }
            else if (name == "level") {
                flanging_level = std::stod(value.bstrVal);
            }
        }
    }
}

void CFlanging::ProcessStream(double* in_frame, int channels) {
    double original[2] = { in_frame[0], in_frame[1] };

    assert(flanging & channels == 2);

    m_wrloc = (m_wrloc + 1) % 100000;
    flanging_queue_0[m_wrloc] = in_frame[0];
    flanging_queue_1[m_wrloc] = in_frame[1];


    int length = int((flanging_delay * sample_rate + 0.5)) * 2;
    int rdloc = (m_wrloc + 100000 - length) % 100000;

    in_frame[0] = (in_frame[0] / 3 + (output_queue_0[rdloc] * flanging_level) / 3 +
        flanging_queue_0[rdloc] / 3) * flanging_wet / (1 + 1 / 3 * flanging_level) + original[0] * flanging_dry;
    in_frame[1] = (in_frame[1] / 3 + (output_queue_1[rdloc] * flanging_level) / 3 +
        flanging_queue_1[rdloc] / 3) * flanging_wet / (1 + 1 / 3 * flanging_level) + original[1] * flanging_dry;

    output_queue_0[m_wrloc] = in_frame[0];
    output_queue_1[m_wrloc] = in_frame[1];
}