#pragma once

//���j���[�ɂ�����I�����ȒP�ɂ���
class CMenuSelecter
{
private:
	int m_cur;
	int m_max;

public:
	//�ő�l�Ə����ʒu
	CMenuSelecter(int context_max, int current) :m_max(context_max), m_cur(current){
		if (this->m_cur > m_max)this->m_cur = m_max;
	}
	//1���ڑO��
	void prev();
	//1���ڌ��
	void next();
	//���݂̈ʒu���擾(0�`�ő�l)
	int get()const;
};

