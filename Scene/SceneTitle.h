#pragma once
#include "SceneBase.h"
#include <vector>
#include <memory>
#include "../Util/Vec3.h"

class CreateText;
class TitleDrawModeler;
class FieldBase;
class Shadow;
class ButtonDrawer;
class CreditDrawer;

class SceneTitle:public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual void End();
	virtual SceneBase* Update() override;
	virtual void Draw();
private:
	// テキスト用のクラス
	CreateText* m_pText;
	// 3Dモデル表示用クラス
	TitleDrawModeler* m_pDrawModeler;
	// 2Dシェーダー用クラス
	Shadow* m_pShadow;
	// ボタン説明用クラス
	ButtonDrawer* m_pButtonDrawer;
	// クレジット表記用クラス
	CreditDrawer* m_pCreditDrawer;
	std::shared_ptr<FieldBase>m_pField;
};

