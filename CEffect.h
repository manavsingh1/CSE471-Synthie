#pragma once
#include <string>
class CEffect
{
public:
	CEffect();
	~CEffect();
	virtual void ProcessStream(double*, int) = 0;
	virtual void XmlLoad(IXMLDOMNode*, std::wstring&) = 0;
	void SetSampleRate(double s) { sample_rate = s; };

public:
	double sample_rate;
};