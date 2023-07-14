#pragma once
class Model;
class TitleDrawModeler
{
public:
	TitleDrawModeler();
	virtual ~TitleDrawModeler();

	void Update();
	void Draw();

	// ゲームスタートと同時に右に移動させる
	void SetStartPos(bool move) { m_isMoveSelect = move; }

	bool GetSceneChange() { return m_isSceneChange; }
private:
	// モデルクラス
	Model* m_pModel;
	// モデルのY座標だけ
	float m_posY;
	// シーンが切り替わるかどうか
	bool m_isMoveSelect;
	// モデルが右まで移動しかたどうか
	bool m_isSceneChange;
};

