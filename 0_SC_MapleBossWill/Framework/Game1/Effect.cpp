#include "stdafx.h"

Effect::Effect()
{
	_effectAnimPool = *new vector<Animation>(5);
	for (auto& _effectAnim : this->_effectAnimPool)
	{
		_effectAnim.enable = false;
		_effectAnim.isLoop = false;
	}
}

void Effect::PlayEffect(Vector2 _playPosition, vector<ObImage*>* _effectImages)
{
	Animation* _animation = nullptr;

	for (auto& _effectAnim : this->_effectAnimPool)
	{
		if (!_effectAnim.enable)
		{
			_effectAnim.enable = true;
			_animation = &_effectAnim;
			break;
		}
	}

	if (_animation == nullptr)
	{
		_animation = new Animation();
		_animation->enable = true;
		_animation->isLoop = false;

		this->_effectAnimPool.push_back(*_animation);
	}

	for (auto& _image : *_effectImages)
	{
		_image->SetWorldPos(_playPosition);
	}

	_animation->SetAnimation(_effectImages);
}

void Effect::Update()
{
	for (auto& _effectAnim : this->_effectAnimPool)
	{
		if (_effectAnim.enable)
		{
			if (_effectAnim.IsOver())
			{
				_effectAnim.enable = false;
			}
			else
			{
				_effectAnim.Update();
			}
		}
	}
}

void Effect::Render()
{
	for (auto& _effectAnim : this->_effectAnimPool)
	{
		if (_effectAnim.enable)
		{
			_effectAnim.Render();
		}
	}
}