//
// Created by Phillip Schuster on 24.03.15.
//

#ifndef _TEENSYCMAKE_ANIMATOR_H_
#define _TEENSYCMAKE_ANIMATOR_H_

#include "Animation.h"

class AnimatorClass
{
public:
	AnimatorClass();
	Animation* getAnimationSlot();

	void update();

private:
	Animation _animationSlots[10];
};

extern AnimatorClass Animator;


#endif //_TEENSYCMAKE_ANIMATOR_H_
