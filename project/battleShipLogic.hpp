#ifndef __HEADER__
#define __HEADER__

#include<iostream>
#include<utility>
#include<vector>
#include<string>
#include<memory>
#include<QObject>



//--------------------------------------------------------------------------------------------------
class Support
{
public:
	struct coordinates
	{
		int X, Y;
		coordinates(int x, int y) :Y(y), X(x) {}
		coordinates() = default;
	};
    enum FIELD_STATUS: char{ WATER, SHIP, HIT=0x01, MISS=0x00, HIT_AND_SUNK=0x02, HIT_AND_SUNK_PLAYER=0x03, NONVALID=0x20, NOTYOURTURN=0x10, OUTOFBOUNDS=0x11 };
//    enum FIELD_STATUS: char{MISSED=0x00,
//    HIT=0x01,
//    DESTROYED=0x02,
//    GAMEOVER=0x03,
//    NOTYOURTURN=0x10,
//    OUTOFBOUNDS=0x11,
//    INVALID=0x20};
	enum Orientation { HORIZONTAL, VERTICAL };
	enum ShipType { SCHLACHTSCHIFF, KREUZER,ZERSTOERER,UBOOT };
};

struct ParametersAndSelections
{
	ParametersAndSelections() :
		FieldSizeX(10), FieldSizeY(10), SizeSelected(0), CoordinatesSelected(0, 0), orientation(Support::HORIZONTAL) {}
	ParametersAndSelections(uint8_t a, uint8_t b) :
		FieldSizeX(a), FieldSizeY(b), SizeSelected(0), CoordinatesSelected(0, 0), orientation(Support::HORIZONTAL) {}

	const uint8_t FieldSizeX, FieldSizeY;
	uint8_t SizeSelected;
	Support::coordinates Block2 = { 0, 0};
	Support::coordinates Block1= { 0, 0 };
	Support::coordinates CoordinatesSelected;
	Support::Orientation orientation;

};


class Ship {

public:
	Ship(const uint8_t& ShipSize, Support::coordinates& begin_coordination,Support::Orientation& orientation);
	~Ship();
	void Decrement_ShipHealth();

	uint8_t _ShipSize;
	uint8_t _ShipHealth;
	std::vector<Support::coordinates> _ShipCoordinatesVector;
};
//--------------------------------------------------------------------------------------------------
typedef std::pair < Support::FIELD_STATUS, std::shared_ptr<Ship> >  BoardCase;
//--------------------------------------------------------------------------------------------------
class Player :public QObject	
{
	Q_OBJECT
public:
	Player();
	~Player() {  };

	bool CheckAndPlaceShip(Support::coordinates& block_coor_1, Support::coordinates& block_coor_2);

	//get coordinates of attaked field by the enemy, check if it is a HIT and updates the health, ships's healths and the board of the local player  
	//and updates the result of the enemy attack
	bool UpdatePlayer(std::vector<Support::coordinates>& sunk_ship_base);

	//get coordinates of attaked field by the player(_Target) and feedback by the enemy about the result of the attack and updates the health, and the board of the enemy  
	//and updates the result of the player attack(_AttackResultPlayer)
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
	
public slots:
	void SetSelectedShipSlot(int ship_size);//GUI
	void SetOrientationSlot(char orientation);//GUI
	void SetPlacingBeginCoordinatesSlot(int coord_begin_X, int coord_begin_Y);
	void SetTargetSlot(int target_X, int target_Y);
	void PlayerAttackResultSlot(Support::FIELD_STATUS result, std::vector<Support::coordinates> ship_coordinates = {});
	void EnemyAttackSlot(Support::coordinates enemy_target);

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
//    void EnemyAttackResultGUISig(char result);
	void EnemyAttackResultSig(Support::FIELD_STATUS result, std::vector<Support::coordinates> sunkShip = {});
	void PlayerAttackResultSig(int x, int y, char result);//'H' or'M'
	void SunkShip(int lengthOfSunkShip);
};

void ShipPlacement(const uint8_t& size,
	Support::Orientation& orientation,
	Support::coordinates& ShipCoordinatesBegin,
	std::vector<std::shared_ptr<Ship>>& ships_vec,
	std::vector<std::vector<BoardCase>>& board_own);

std::shared_ptr<Ship> AddShip(std::vector<std::shared_ptr<Ship>>& ships_vec,
	const uint8_t& size,
	Support::coordinates& begin_coordination,
	Support::Orientation& orientation);



bool CheckPath(const uint8_t& size,
	Support::coordinates& begin_field,
	Support::Orientation& orientation,
	std::vector<std::vector<BoardCase>> board_own,
	Support::coordinates& block_coor_1,
	Support::coordinates& block_coor_2);


//--------------------------------------------------------------------------------------------------
void Print2Darray(Player *player);


#endif 
