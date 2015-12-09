#ifndef _NPC_H_
#define _NPC_H_

#include <memory>

class CInventory
{};

class CNpc
{
public:
	void AsyncSpawn();
	void AsyncDespawn();
	void Die();
	void Talk();
	void AsyncMove();
	void GotDamageBy();
	void EnterWorld();
	void LeaveWorld();

private:
	int m_nNpcType;
	int m_nNpcScriptID;

	bool m_bAlive;
	bool m_bActive;
	bool m_bHide;

	int m_nMasterID;

	int x, y, z;
	int rotation;
	int HP;

	CInventory m_Inventory;
};
std::shared_ptr<CNpc> CNpcSP;

#endif //_NPC_H_