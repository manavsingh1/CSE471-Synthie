#pragma once
#include "CEffect.h"
#include <vector>
class CChorus :
	public CEffect
{
public:
	CChorus();
	~CChorus();
	void ProcessStream(double*, int);
	void XmlLoad(IXMLDOMNode*, std::wstring&);
private:
	bool chorus;
	double chorus_delay;
	double chorus_wet;
	double chorus_dry;
	int m_wrloc;
	std::vector<double> chorus_queue_0;
	std::vector<double> chorus_queue_1;
};
