#include "DxLib.h"
#include <cassert>
#include "game.h"
#include "player.h"

namespace
{
	//�L�����N�^�[�A�j���[�V����1�R�}������̃t���[����
	constexpr int kAnimeChangeFrame = 8;
}
Player::Player()
{
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	m_animeNo = 0;
}

Player::~Player()
{
	
}

void Player::init()
{
	m_pos.x = Game::kScreenWidth / 2 - kGraphicSizeX / 2;
	m_pos.y = Game::kScreenHeight / 2 - kGraphicSizeY / 2;
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_animeNo = 0;
	m_animeFrame = 0;
	m_animeDirection = 0;
}

void Player::update()
{

	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	bool isKey = false;					//�L�[��������Ă���Ԃ����A�j���[�V������\��
	if (padState & PAD_INPUT_UP)		//��9-11
	{
		m_animeDirection = 3;
		isKey = true;
	}
	if (padState & PAD_INPUT_DOWN)		//��0-2
	{
		m_animeDirection = 0;
		isKey = true;
	}
	if (padState & PAD_INPUT_LEFT)		//��3-5
	{
		m_animeDirection = 1;
		isKey = true;
	}
	if (padState & PAD_INPUT_RIGHT)		//�E6-8
	{
		m_animeDirection = 2;
		isKey = true;
	}

	//�L�����N�^�[�̃A�j���[�V����
	if(isKey) m_animeFrame++;

	if (m_animeFrame >= kGraphicDivX * kAnimeChangeFrame)
	{
		m_animeFrame = 0;
	}

	int tempAnime = m_animeFrame / kAnimeChangeFrame;
	m_animeNo = m_animeDirection * kGraphicDivX + tempAnime;		//�����ꂽ�L�[�ɂ���ăA�j���[�V������ω�����
	

	
}

void Player::draw()
{
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[m_animeNo], true);
}