#pragma once

//メニューにおける選択を簡単にする
class CMenuSelecter
{
private:
	int m_cur;
	int m_max;

public:
	//最大値と初期位置
	CMenuSelecter(int context_max, int current) :m_max(context_max), m_cur(current){
		if (this->m_cur > m_max)this->m_cur = m_max;
	}
	//1項目前へ
	void prev();
	//1項目後へ
	void next();
	//現在の位置を取得(0～最大値)
	int get()const;
};

