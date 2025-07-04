#pragma once
class Stand
{
public:
	vector<ObImage*> stand;

public:
	Stand();
	~Stand();
	void Update();
	void LateUpdate();
	void Render();
};

