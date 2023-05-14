#pragma once
#include <DxLib.h>
#include "Util/Vec3.h"
class Animation
{
public:
	Animation(const char* modelName, Vec3 pos);
	Animation(const char* modelName);
	virtual ~Animation();

	void Init();
	void End();
	void Update(float angleX, float angleY, float angleZ, float animTime = 0.5f);
	void Draw();

	void SetAnimation(int animNo);

	void ChangeAnimation(int animNo, bool isLoop);
	// �ʒu���擾����
	void SetPos(Vec3 pos);
	// �T�C�Y���擾����
	void SetSize(VECTOR size);
	
	bool GetAnimeTime() { return m_isAnimTime; }

private:
	int m_modelHandle;// ���f���n���h��

	float m_playTime;

	int m_attachIndex, m_totalTime;

	int m_saveAnimNo;

	bool m_isAnimTime;
};

