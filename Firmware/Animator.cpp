/*
 * Little Helper -- your best friend in your lab
 * http://www.appfruits.com/littlehelper
 * 
 * 2014-2015 Phillip Schuster (@appfruits)
 * http://www.appfruits.com
 */

#include "Animator.h"

AnimatorClass Animator;

AnimatorClass::AnimatorClass()
{

}

Animation* AnimatorClass::getAnimationSlot()
{
	for (uint8_t i=0;i<10;i++)
	{
		if (!_animationSlots[i].isActive())
		{
			_animationSlots[i].reset();
			return &_animationSlots[i];
		}
	}

	return NULL;
}

void AnimatorClass::update()
{
	for (uint8_t i=0;i<10;i++)
	{
		if (_animationSlots[i].isActive())
		{
			_animationSlots[i].update();
		}
	}
}