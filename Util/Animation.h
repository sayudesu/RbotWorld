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
	// 位置を取得する
	void SetPos(Vec3 pos);
	// サイズを取得する
	void SetSize(VECTOR size);
	
	bool GetAnimeTime() { return m_isAnimTime; }

private:
	int m_modelHandle;// モデルハンドル

	float m_playTime;

	int m_attachIndex, m_totalTime;

	int m_saveAnimNo;

	bool m_isAnimTime;
};

