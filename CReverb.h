#pragma once
#include "CEffect.h"
#include <vector>
class CReverb :
    public CEffect
{
public:
	CReverb();
	~CReverb();
	void ProcessStream(double*, int);
	void XmlLoad(IXMLDOMNode*, std::wstring&);
private:
	bool reverbation;
	int m_wrloc;
	double reverbation_rate;
	double reverbation_dry;
	double reverbation_wet;
	std::vector<double> reverbation_queue_0;
	std::vector<double> reverbation_queue_1;
	std::vector<double> output_queue_0;
	std::vector<double> output_queue_1;
};

