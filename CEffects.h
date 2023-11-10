#pragma once
#include <string>
#include <vector>
#include "CEffect.h"
#include "CChorus.h"

class CEffects
{
public:
	CEffects();
	~CEffects();
	void ProcessStream(double*, int);
	void XmlLoad(IXMLDOMNode*, std::wstring&);
	void SetSampleRate(double s) { sample_rate = s; };
	void empty();

private:
	double sample_rate;

	std::vector<CEffect*> effects;
};
