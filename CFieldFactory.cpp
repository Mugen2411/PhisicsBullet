#include "CFieldFactory.h"
#include "CField_Grass.h"

std::shared_ptr<CField> CFieldFactory::create(unsigned int x, unsigned int y, std::string name, std::vector<double> params)
{
	//�����ɖ��O�ƃp�����[�^���g����CField�𐶐����鏈�����S���S���Ə����Ă���
	if (name == "Field_Grass")return std::make_shared<CField_Grass>("field_grass", CVector(x*32+16, y*32+16));
}
