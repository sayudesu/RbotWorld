#pragma once
class Model;
class DrawTitleModel
{
public:
	DrawTitleModel();
	virtual ~DrawTitleModel();

	void Update();
	void Draw();
private:
	Model* m_pModel;
};

