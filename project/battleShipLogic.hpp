#ifndef __HEADER__
#define __HEADER__

#include<iostream>
#include<utility>
#include<vector>
#include<string>
#include<memory>
#include<algorithm>
#include<QObject>



//--------------------------------------------------------------------------------------------------
/**
 * @brief Implements Enums(FIELD_STATUS, Orientation)  and a struct(coordinates)
 *
 * 
 **/
class Support

{
public:
	struct coordinates
	{
		int X, Y;
		coordinates(int x, int y) :Y(y), X(x) {}
		coordinates() = default;
	};
    enum FIELD_STATUS: char{ WATER, SHIP, HIT=0x01, 
							MISS=0x00, HIT_AND_SUNK=0x02, 
							HIT_AND_SUNK_PLAYER=0x03, 
							NONVALID=0x20, NOTYOURTURN=0x10, OUTOFBOUNDS=0x11 };
	enum Orientation { HORIZONTAL, VERTICAL };
	
};
//--------------------------------------------------------------------------------------------------
/**
 * @brief struct that stores Parameters, Selections and Blocked area coordinates 
 *
 **/
struct ParametersAndSelections
{
	ParametersAndSelections() :
		FieldSizeX(10), FieldSizeY(10), SizeSelected(0), CoordinatesSelected(0, 0), orientation(Support::HORIZONTAL) {
		BlockedCases.reserve(50);
	}
	ParametersAndSelections(uint8_t a, uint8_t b) :
		FieldSizeX(a), FieldSizeY(b), SizeSelected(0), CoordinatesSelected(0, 0), orientation(Support::HORIZONTAL) {
		BlockedCases.reserve(50);
	}

	const uint8_t FieldSizeX, FieldSizeY;
	uint8_t SizeSelected;
	Support::coordinates Block2 = { 0, 0};
	Support::coordinates Block1= { 0, 0 };
	Support::coordinates CoordinatesSelected;
	Support::Orientation orientation;
	std::vector<Support::coordinates> BlockedCases;
};
//--------------------------------------------------------------------------------------------------
/**
 * @brief Defines Ship
 *
 * Implements methods to Construct Ship ,to Decrement Ship's Health
 **/
class Ship {

public:
        /**
         * @purpose Instantiates Ship
		 * Calling Ship with parameters will Instantiates a Ship with a certain Size and the wholesome of the coordinates on which the ship is placed on the board,
         * @param[in] ShipSize Size of the Ship 
         * @param[in] begin_coordination Coordinates of the first case of the ship on the Board
		 * @param[in] orientation Orientation mode of the ship on the Board
         **/
	Ship(const uint8_t& ShipSize, Support::coordinates& begin_coordination,Support::Orientation& orientation);
	~Ship();
	/**
     * @purpose Decrements the Health of a certain ship,
     **/
	void Decrement_ShipHealth();

	uint8_t _ShipSize;
	uint8_t _ShipHealth;
	std::vector<Support::coordinates> _ShipCoordinatesVector;
};
//--------------------------------------------------------------------------------------------------
/**
 * @brief Defines a type of a Case of Board as a pair that contains FIELD_STATUS as first and a Shared-pointer as second(that points at a certain ship)
 *
 * 
 **/
typedef std::pair < Support::FIELD_STATUS, std::shared_ptr<Ship> >  BoardCase;
//--------------------------------------------------------------------------------------------------
/**
 * @brief Defines a player
 *Implements methods to 
 * 
 **/
class Player :public QObject	
{
	Q_OBJECT
public:
    /**
    * @purpose Instantiates Player
    **/
    Player();
	~Player() {  };
    /**
    * @purpose Checks the legality of a certain Ship's placement on board ,constructs a new Ship object and stores it in the player Class
	* and sets the surface around the ship that would be blocked after placing   
    * @param[in] block_coor_1 Coordinates of the point on the Left Top corner 
    * @param[in] block_coor_2 Coordinates of the point on the right Bottom corner 
    * @return Boolean that checks validity of the placement
	**/
	bool CheckAndPlaceShip(Support::coordinates& block_coor_1, Support::coordinates& block_coor_2);
    /**
    * @purpose Updates: Player's Health , the Result of the Enemy's Attack , And local player's Board
    * @param[in] sunk_ship_base Sunk Ship's Coordinates on Board
    * @return Boolean that checks the existence of a Sunk ship
    **/
	bool UpdatePlayer(std::vector<Support::coordinates>& sunk_ship_base);
    /**
    * @purpose Updates: Player's Attack Result on Board , Enemy's Health on local , And local Enemy's Board
    **/
	void UpdateEnemy();
	//player max health is the sum of the sizes(healthes) of his own ships
	uint8_t _PlayerMaxHealth;
	uint8_t _CurrentHealth;
	uint8_t _EnemyHealth;
	//coordinates on which the player wants to shoot(filled by the signal function from GUI)
	Support::coordinates _Target;
	Support::coordinates _AttackEnemy;
	//board of the local player. each case is of type pair [status of the field][shared pointer points to the ship if ther's a ship on this field] 
	std::vector<std::vector<BoardCase>> _BoardOwn;
	//board of the enemy each case gives information if it was hitted, missed or still not shooted by the local player
	std::vector<std::vector<Support::FIELD_STATUS>> _BoardEnemy;
	//result of the local player's attack (filled by signal from network function as feedback from enemy)
	Support::FIELD_STATUS _AttackResultPlayer;
	//result of the enemy's attack 
	Support::FIELD_STATUS _AttackResultEnemy;
	//vector stores the ships of the local player
	std::vector<std::shared_ptr<Ship>> _Ships;
	std::shared_ptr<ParametersAndSelections> Parameters{ new ParametersAndSelections() };
//------------------------------------------------------------------------------------------------------------------
	
public slots:
	void SetSelectedShipSlot(int ship_size);//GUI
	void SetOrientationSlot(char orientation);//GUI
	void SetPlacingBeginCoordinatesSlot(int coord_begin_X, int coord_begin_Y);

	void SetTargetSlot(int target_X, int target_Y);
//-----------------------------NW -> player --------------------------------------
	void PlayerAttackResultSlot(Support::FIELD_STATUS result, std::vector<Support::coordinates> ship_coordinates = {});
	void EnemyAttackSlot(Support::coordinates enemy_target);
//------------------------------------------------------------------------------------------------------------------

signals:
	void ShipPlaceValidationSig(bool validation = false);
	void DrawShipSig(int begin_coord_X,
		int begin_coord_Y,
		char orientation,
		uint8_t size);
	void BlockingSurfaceSig(int left_TopCorner_Point_X,
		int left_TopCorner_Point_Y,
		int right_BottomCorner_Point_X,
		int right_BottomCorner_Point_Y);
    void EnemyAttackResultGUISig(int x, int y, char result);
	void SunkShip(int lengthOfSunkShip);
    //----------------------------player -> NW ----------------------------------------
	void EnemyAttackResultSig(Support::FIELD_STATUS result, std::vector<Support::coordinates> sunkShip = {});
	void PlayerAttackResultSig(int x, int y, char result);//'H' or'M'
};
//------------------------------------------------------------------------------------------------------------------
/**
 * @purpose Creates a new Ship , Updates Player's Board After Placing a Ship  
* @param[in] size Ship's Size
* @param[in] orientation Orientation mode of the ship on the Board
* @param[in] ShipCoordinatesBegin Coordinates of the first case of the ship on the Board 
* @param[in] ships_vec Vector that contains All the Ships Placed by the player
* @param[in] board_own Local player's Board
 **/
void ShipPlacement(const uint8_t& size,
	Support::Orientation& orientation,
	Support::coordinates& ShipCoordinatesBegin,
	std::vector<std::shared_ptr<Ship>>& ships_vec,
	std::vector<std::vector<BoardCase>>& board_own);
//------------------------------------------------------------------------------------------------------------------
/**
 * @purpose Creates a new Ship , Updates Player's Board After Placing a Ship  
* @param[in] ships_vec Vector that contains All the Ships Placed by the player
* @param[in] size Ship's Size
* @param[in] begin_coordination Coordinates of the first case of the ship on the Board 
* @param[in] orientation Orientation mode of the ship on the Board
*  @return Pointer that points on the placed Ship  
 **/
std::shared_ptr<Ship> AddShip(std::vector<std::shared_ptr<Ship>>& ships_vec,
	const uint8_t& size,
	Support::coordinates& begin_coordination,
	Support::Orientation& orientation);

//------------------------------------------------------------------------------------------------------------------
/**
 * @purpose Creates a new Ship , Updates Player's Board After Placing a Ship  
* @param[in] ships_vec Vector that contains All the Ships Placed by the player
* @param[in] begin_field Coordinates of Ship's Begin 
* @param[in] orientation Orientation mode of the ship on the Board
* @param[in] board_own Local player's Board
* @param[in] block_coor_1 Coordinates of the point on the Left Top corner to be updated
* @param[in] block_coor_2 Coordinates of the point on the right Bottom corner to be updated
*  @return Boolean that checks validity of the placement
 **/
bool CheckPath(const uint8_t& size,
	Support::coordinates& begin_field,
	Support::Orientation& orientation,
	std::vector<std::vector<BoardCase>> board_own,
	Support::coordinates& block_coor_1,
	Support::coordinates& block_coor_2);

/**
 * @brief checks the existence of certain coordinates in a specific vector
 * @param vec vector of coordinates
 * @param item coordinates to find in the vector
 * @return boolean that confirms the existence of item in vec
*/
bool findCordInVec(const std::vector<Support::coordinates>& vec, const Support::coordinates& item);
//--------------------------------------------------------------------------------------------------
void Print2Darray(Player* player);

#endif 
