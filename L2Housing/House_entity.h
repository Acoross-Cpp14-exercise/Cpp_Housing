#ifndef _HOUSE_DATA_H_
#define _HOUSE_DATA_H_

#include <memory>
#include <unordered_map>
#include <functional>

class CFurniture
{
};
typedef std::shared_ptr<CFurniture> CFurnitureSP;



//////////////////////////////////////
// CHouseData
/*
house script 에 정의된 house type 별 const 정보.
*/
class CHouseDefine
{
public:
	CHouseDefine(int nHouseTypeID,
		int nNPCTypeID,
		int nInzoneTypeID)
		:
		m_nHouseTypeID(nHouseTypeID),
		m_nNPCTypeID(nNPCTypeID),
		m_nInzoneTypeID(nInzoneTypeID)
	{
	}

	CHouseDefine(CHouseDefine& rhs) = default;
	CHouseDefine(CHouseDefine&& rhs) = default;

private:
	const int m_nHouseTypeID;
	const int m_nNPCTypeID;
	const int m_nInzoneTypeID;
};

////////////////////////////////////////////
// CHouseInstance
class CHouseInstance
{
public:
	// 일시적인 값. 
	enum State
	{
		INZONE_OPENING,
		INZONE_OPENED,
		INZONE_CLOSING,
		INZONE_CLOSED
	};
public:
	void AsyncOpenHouseInzone();
	void AsyncCloseHouseInzone();

private:
	int m_nInzoneSID;
	int m_nOwnerSID;
	std::list<int> m_list_HouseNpcID;
};


////////////////////////////////////////////
// CHouseEntity
class CHouseEntity;
typedef std::shared_ptr<CHouseEntity> CHouseEntitySP;

class CHouseEntity
{
public:
	typedef std::function<void(CHouseEntitySP& createdHouseEntity)> house_create_callback_t;

	CHouseEntity(CHouseDefine& houseDefine)
		: m_HouseDefine(houseDefine)
	{
	}

	//// spHouseData 로부터 생성되어 spHouseData 를 소유하는 CHouseInst instance 를 만든다.
	//static std::unique_ptr<CHouseInstance> Instantiate(CHouseEntitySP& spHouseData);
	
// DB load and save
public:
	void RequestSaveDB();
	void AsyncLoadFromDB(house_create_callback_t callback);

	enum State
	{
		NOT_INITIALIZED,
		LOADING,
		LOADED,
	};

// keydata: Entity 생성 시 결정되고 바뀌지 않음. identity = unique key 와도 같다. const.
// DB 에서도 key value.
private:
	const CHouseDefine m_HouseDefine;
	int m_nHouseDBID;
	int m_nOwnerDBID;

// 이 entity 의 변하는 값. house 안의 가구들, NPC 들, 아이템 들 등.
// DB 저장 됨.
private:
	std::unordered_map<int, CFurnitureSP> m_map_spFurniture;

// instence: world 에 instantiated 인 상태에만 valid.
	// 상대적으로 일시적인 상태가 저장됨. (여러 SID 등)
private:
	std::unique_ptr<CHouseInstance> m_upHouseInstance;
};


//////////////////////////////////////////////////////
// CHouseEntityDB
class CHouseEntityDB
{
public:
	typedef std::function<void(CHouseEntitySP& createdHouseEntity)> house_create_callback_t;

	// Singleton
	static CHouseEntityDB& Inst()
	{
		static CHouseEntityDB inst;
		return inst;
	}

public:
	// call this when program start.
	void AsyncLoadAllHouseEntityFromDB();

	// make new house
	CHouseEntitySP MakeNewHouse();

	// request make new house to CacheD,
	// get reply from db, and Call callback functoin.
	void AsyncMakeNewHouse(int ownerDBID, int entityTypeID, house_create_callback_t callback);
	
	// return house entity by DBID
	// if not loaded, return null sp
	CHouseEntitySP GetHouseEntity(int houseEntityDBID);

	// try load house.
	// If house is not loaded, load house from CacheD asynchronously, 
	// get reply from db, and Call callback functoin.
	void AsyncGetHouseEntity(int houseEntityDBID, house_create_callback_t callback);

private:
	std::unordered_map<int, CHouseEntitySP> m_map_spHouseEntity;

private:
	CHouseEntityDB()
	{}
};

#endif //_HOUSE_DATA_H