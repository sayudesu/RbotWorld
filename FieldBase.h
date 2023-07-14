#pragma once
#include <vector>
#include <memory>

class Model;
class FieldBase
{
protected:
	struct LoadData
	{
		const char* fileName;
		int blockNumX;
		int blockNumY;
	};

public:
	FieldBase();
	virtual ~FieldBase();

	virtual void Init(LoadData data);
	
	virtual	void End();
	virtual void Update();
	virtual void Draw();

	void FirstModelLoad();
	void LoadFile(const char* fileName);
	void ModelLoad(int orgModel);
protected:
	LoadData m_data;
	int m_stageNum;
	std::vector<int>m_blockNum;
	std::vector<std::shared_ptr<Model>>m_pModel;
};

