#pragma once
class CompoObject;

class Component
{
public:
	Component();
	virtual ~Component() {}

	CompoObject* gameObject;

	bool enable;

	virtual void Update() {}
	virtual void Render() {}
};