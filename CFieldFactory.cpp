#include "CFieldFactory.h"
#include "CField_Grass.h"
#include "CField_IceFloor.h"

std::shared_ptr<CField> CFieldFactory::create(int x, int y, std::string name, std::vector<double> params)
{
	//�����ɖ��O�ƃp�����[�^���g����CField�𐶐����鏈�����S���S���Ə����Ă���
	if (name == "Field_Grass")return std::make_shared<CField_Grass>("Field_Grass", CVector(x, y));
	if (name == "Field_IceFloor")return std::make_shared<CField_IceFloor>("Field_IceFloor", CVector(x, y), params[0]);
}
