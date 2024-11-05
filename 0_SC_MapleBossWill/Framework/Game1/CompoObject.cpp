#include "stdafx.h"

CompoObject::CompoObject()
{
	_components = *new std::unordered_map<std::type_index, Component*>();
}

CompoObject::~CompoObject()
{
	for (auto& _component : _components)
	{
		SafeDelete(_component.second);
	}
}

void CompoObject::Update()
{
	if (!isVisible)
	{
		return;
	}

	GameObject::Update();

	for (auto& _component : _components)
	{
		if (!_component.second->enable)
		{
			continue;
		}

		_component.second->Update();
	}
}

void CompoObject::Render()
{
	if (!isVisible)
	{
		return;
	}

	GameObject::Render();

	for (auto& _component : _components)
	{
		if (!_component.second->enable)
		{
			continue;
		}

		_component.second->Render();
	}
}