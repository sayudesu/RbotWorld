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
	// �e�L�X�g�p�̃N���X
	CreateText* m_pText;
	// 3D���f���\���p�N���X
	TitleDrawModeler* m_pDrawModeler;
	// 2D�V�F�[�_�[�p�N���X
	Shadow* m_pShadow;
	// �{�^�������p�N���X
	ButtonDrawer* m_pButtonDrawer;
	// �N���W�b�g�\�L�p�N���X
	CreditDrawer* m_pCreditDrawer;
	std::shared_ptr<FieldBase>m_pField;
};

