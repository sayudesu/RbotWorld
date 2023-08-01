#include "Sound.h"
#include <DxLib.h>
#include <vector>

namespace
{
	// �T�E���h�n���h��
	std::vector<int>	m_soundHandle;

	// �T�E���h�t�@�C����
	const char* const kFileName[Sound::SoundId_Num] =
	{
		// BGM
		"Data/Sound/Bgm/Title.mp3",
		"Data/Sound/Bgm/Main.ogg",
		// SE
		"Data/Sound/SE/coin.wav",
		"Data/Sound/SE/Jump.mp3",
		"Data/Sound/SE/Run.mp3",
	};
}

namespace Sound
{
	void load()
	{
		// �T�E���h�f�[�^�̓ǂݍ���
		for (auto& fileName : kFileName)
		{
			int handle = LoadSoundMem(fileName);
			m_soundHandle.push_back(handle);
		}
	}
	void unload()
	{
		// �T�E���h�f�[�^�̉��
		for (auto& handle : m_soundHandle)
		{
			DeleteSoundMem(handle);
			handle = -1;
		}
	}

	// BGM�̍Đ�
	void startBgm(SoundId id, int volume)
	{
		PlaySoundMem(m_soundHandle[id], DX_PLAYTYPE_BACK, true);
		setVolume(id, volume);
	}
	void stopBgm(SoundId id)
	{
		StopSoundMem(m_soundHandle[id]);
	}

	// ���ʉ��̍Đ�
	void play(SoundId id)
	{
		PlaySoundMem(m_soundHandle[id], DX_PLAYTYPE_BACK, true);
	}

	// ���ʐݒ�	0~255
	void setVolume(SoundId id, int volume)
	{
		ChangeVolumeSoundMem(volume, m_soundHandle[id]);
	}
}
