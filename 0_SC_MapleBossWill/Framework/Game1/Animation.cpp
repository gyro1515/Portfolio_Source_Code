#include "stdafx.h"

Animation::Animation()
{
	this->_animCount = 0;
	this->_time = 0.f;

	this->_animImages = new vector<ObImage*>();

	flipX = false;
	isLoop = false;
}

Animation::~Animation()
{
	for (auto& _image : *(this->_animImages))
	{
		SafeDelete(_image);
	}
}

bool Animation::IsOver()
{
	if (_animImages->size() == 0)
	{
		return false;
	}

	if (isLoop)
	{
		return false;
	}
	else
	{
		if (_animCount >= _animImages->size())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void Animation::Update()
{
	if (_time < 0.f || _time > 1.f)
	{
		_time = 0.f;
	}

	//cout << _animCount << endl;
	if (!isLoop && _animCount >= _animImages->size())
	{
		return;
	}

	while (true)
	{
		if (_time >= (*_animImages)[_animCount % _animImages->size()]->animInterval)
		{
			_time -= (*_animImages)[_animCount % _animImages->size()]->animInterval;

			_animCount++;
		}
		else
		{
			break;
		}
	}

	_renderingImage = *(*_animImages)[_animCount % _animImages->size()];

	_renderingImage.scale = Vector2(_renderingImage.imageSize.x, _renderingImage.imageSize.y);
	if (flipX)
	{
		_renderingImage.Update();
		_renderingImage.SetWorldPosX(-_renderingImage.GetWorldPos().x);
	}
	_renderingImage.reverseLR = flipX;
	if (gameObject != nullptr)	_renderingImage.SetParentRT(*gameObject);

	_renderingImage.Update();

	_time += DELTA;
}

void Animation::Render()
{
	_renderingImage.Render();
}

void Animation::Play()
{
	this->_animCount = 0;
	this->_time = 0.f;
}

void Animation::SetAnimation(vector<ObImage*>* _animImages)
{
	this->_animImages = _animImages;
	Play();
}