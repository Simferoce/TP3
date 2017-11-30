#pragma once
#include "IObservateur.h"
class IObservateurJoueur :
	public IObservateur
{
public:
	IObservateurJoueur();
	~IObservateurJoueur();
	void notifier(Sujet* sujet);
};

