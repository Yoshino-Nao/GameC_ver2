#pragma once

#include "../Base/Base.h"

/// <summary>
/// �G���A�`�F���W�p����I�u�W�F�N�g
/// </summary>
class Event : public Base {
public:
	int m_type;					//�ړ���̃G���A�ԍ�

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="nextArea">�ړ���̃G���A�ԍ�</param>
	/// <param name="rect">�����蔻���`</param>
	/// <param name="nextplayerpos">�ړ���̃v���C���[�̈ʒu</param>
	Event(int type,const CRect& rect);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>

	~Event();
	
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	int GetEventNum();
};