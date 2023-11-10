#pragma once
#include "CAudioNode.h"

class CEnvelope :
	public CAudioNode
{
public:
	double attack_ratio;
	double release_ratio;
	double decay_ratio;
	double time;
	double sustain_level;
	CAudioNode* source;

public:
	CEnvelope();
	~CEnvelope() {};
	void SetSource(CAudioNode* source);
	void Start();
	bool Generate(double duration);
	bool Generate();
};
