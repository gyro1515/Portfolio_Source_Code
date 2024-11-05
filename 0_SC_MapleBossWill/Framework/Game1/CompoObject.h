#pragma once
class CompoObject :public GameObject
{
private:
	std::unordered_map<std::type_index, Component*> _components;

public:
	CompoObject();
	virtual ~CompoObject();

	template<typename _T>
	_T* AddComponent()
	{
		_T* _component = new _T;

		this->_components[std::type_index(typeid(*_component))] = _component;

		_component->gameObject = this;

		return _component;
	}

	template<typename _T>
	_T* GetComponent()
	{
		auto it = this->_components.find(std::type_index(typeid(_T)));

		if (it != this->_components.end())
		{
			return dynamic_cast<_T*>(it->second); // 90¹øÂ°ÁÙ
		}

		return nullptr;
	}

	virtual void Update() override;
	virtual void Render() override;
};
