#ifndef _HOUSE_WorldObject_H_
#define _HOUSE_WorldObject_H_

#include <memory>

#include "Npc.h"
#include "House_entity.h"

////////////////////////////////////////////
// CHouseWorldObject

/*
	House �� �����ϴ� NPC �� �ƴ϶�,
	�ΰ��� �� '��' ���� ���̴� NPC �̴�.
	
	[���]
	* Ŭ�� �󿡼� �� ��� �޽��� ������ �ִ�.
	* ��ȭ�� ���� ����� House inzone ���� �� �� �ִ�.
*/
class CHouseNpc : public CNpc
{
public:

private:
	const int m_nSID;	// �� instance id
	int m_nOwnerSID;

	CHouseEntitySP m_spHouseEntity;
};
typedef std::shared_ptr<CHouseNpc> CHouseNpcSP;

#endif //_HOUSE_WorldObject_H_