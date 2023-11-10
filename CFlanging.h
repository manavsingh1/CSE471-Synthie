#pragma once
#include "CEffect.h"
#include <vector>

class CFlanging :
	public CEffect
{
public:
	CFlanging();
	~CFlanging();
	void ProcessStream(double*, int);
	void XmlLoad(IXMLDOMNode*, std::wstring&);
private:
	bool flanging;
	double flanging_delay;
	double flanging_wet;
	double flanging_dry;
	double flanging_level;
	int m_wrloc;
	std::vector<double> flanging_queue_0;
	std::vector<double> flanging_queue_1;
	std::vector<double> output_queue_0;
	std::vector<double> output_queue_1;
};
