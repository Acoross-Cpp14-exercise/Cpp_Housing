#ifndef _HOUSE_WorldObject_H_
#define _HOUSE_WorldObject_H_

#include <memory>

#include "Npc.h"
#include "House_entity.h"

////////////////////////////////////////////
// CHouseWorldObject

/*
	House 를 관리하는 NPC 가 아니라,
	인게임 상에 '집' 으로 보이는 NPC 이다.
	
	[기능]
	* 클라 상에서 집 모양 메쉬를 가지고 있다.
	* 대화를 통해 연결된 House inzone 으로 들어갈 수 있다.
*/
class CHouseNpc : public CNpc
{
public:

private:
	const int m_nSID;	// 내 instance id
	int m_nOwnerSID;

	CHouseEntitySP m_spHouseEntity;
};
typedef std::shared_ptr<CHouseNpc> CHouseNpcSP;

#endif //_HOUSE_WorldObject_H_