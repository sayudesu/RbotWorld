#pragma once
#include <vector>
#include <memory>

class Animation;
class Field
{
public:
	Field();
	virtual ~Field();

	void Init();
	void End();
	void Update();
	void Draw();

	// ƒ‚ƒfƒ‹ƒnƒ“ƒhƒ‹‚ÌŽæ“¾
	int GetModelHandle()const;
	int GetColFrameIndex()const;
private:
	std::vector<std::shared_ptr<Animation>> m_pModel;
};

