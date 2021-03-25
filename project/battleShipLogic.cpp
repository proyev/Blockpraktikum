#include"battleShipLogic.hpp"
#include <iostream>
// FUNCTIONS-----------------------------------------------------------------------------------------------------
void Print2Darray(Player* player)
{
	std::cout << "\n" << std::endl;
	for (size_t i = 0; i < player->Parameters->FieldSizeX;i++)
	{
		for (size_t j = 0; j < player->Parameters->FieldSizeY;j++)
		{
			std::cout << player->_BoardOwn[j][i].first << "\t" << std::flush;
		};
		std::cout << "\n" << std::endl;
	};
}

//chech if the path between 2 coordinates is corresponding to the selected ship size and if all the path has the same status(HIT,MISS,WATER...)
bool CheckPath(const uint8_t& size, 
	Support::coordinates & begin_field, 
	Support::Orientation& orientation, 
	std::vector<std::vector<BoardCase>> board_own,
	Support::coordinates &block_coor_1, 
	Support::coordinates& block_coor_2)
{
	for (size_t i = 0; i < size;i++)
	{
		if (orientation == Support::VERTICAL)
		{
			if (((begin_field.X >= board_own.size()) || (begin_field.Y + i >= board_own[i].size())))
				return false;
			if((board_own[begin_field.X][begin_field.Y + i].first != Support::WATER))
				return false;
			if (i == size-1)
			{
				block_coor_1.X = begin_field.X - 1;
				block_coor_1.Y = begin_field.Y - 1;
				if (block_coor_1.X < 0)
					block_coor_1.X++;
				if (block_coor_1.Y < 0)
					block_coor_1.Y++;
				if (block_coor_1.X >= board_own.size())
					block_coor_1.X--;
				if (block_coor_1.Y >= board_own[i].size())
					block_coor_1.Y--;
				block_coor_2.X = begin_field.X  + 1;
				block_coor_2.Y = begin_field.Y+ i + 1;
				if (block_coor_2.X >= board_own.size())
					block_coor_2.X--;
				if (block_coor_2.Y >= board_own[i].size())
					block_coor_2.Y--;
				if (block_coor_2.X < 0)
					block_coor_2.X++;
				if (block_coor_2.Y < 0)
					block_coor_2.Y++;
			}
		}
			
		else if (orientation == Support::HORIZONTAL)
		{
			if((begin_field.X + i >= board_own.size()) || (begin_field.Y >= board_own[i].size()))
				return false;
			if (((board_own[begin_field.X + i][begin_field.Y].first != Support::WATER)))
				return false;
			if (i == size-1)
			{
				block_coor_1.X = begin_field.X - 1;
				block_coor_1.Y = begin_field.Y - 1;
				if (block_coor_1.X < 0)
					block_coor_1.X++;
				if (block_coor_1.Y < 0)
					block_coor_1.Y++;
				if (block_coor_1.X >= board_own.size())
					block_coor_1.X--;
				if (block_coor_1.Y >= board_own[i].size())
					block_coor_1.Y--;
				block_coor_2.X =begin_field.X + i+1;
				block_coor_2.Y = begin_field.Y+1;
				if (block_coor_2.X >= board_own.size())
					block_coor_2.X--;
				if (block_coor_2.Y >= board_own[i].size())
					block_coor_2.Y--;
				if (block_coor_2.X < 0)
					block_coor_2.X++;
				if (block_coor_2.Y < 0)
					block_coor_2.Y++;
			}
		}
		
				 
	}
	return true;
}

void ShipPlacement(const uint8_t& size, 
	Support::Orientation &	orientation,
	Support::coordinates& ShipCoordinatesBegin, 
	std::vector<std::shared_ptr<Ship>>& ships_vec, 
	std::vector<std::vector<BoardCase>>& board_own)
{
	
	std::shared_ptr<Ship> ship_shared_ptr;
	//store the ship in the vector of player's ships and get its pointer
	ship_shared_ptr = AddShip(ships_vec, size, ShipCoordinatesBegin, orientation);

	if (orientation== Support::VERTICAL)
	{
		//fill cases in the board with ship
		for (size_t i = 0; i < size; i++)
		{
			board_own[ShipCoordinatesBegin.X][(ShipCoordinatesBegin.Y + i)].first = Support::SHIP;
			board_own[ShipCoordinatesBegin.X][(ShipCoordinatesBegin.Y + i)].second = ship_shared_ptr;
		}
	}
	
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			board_own[ShipCoordinatesBegin.X + i][ShipCoordinatesBegin.Y].first = Support::SHIP;
			board_own[ShipCoordinatesBegin.X + i][ShipCoordinatesBegin.Y].second = ship_shared_ptr;
		}

	}
}

std::shared_ptr<Ship> AddShip(std::vector<std::shared_ptr<Ship>>& ships_vec, 
	const uint8_t& size, 
	Support::coordinates& begin_coordination, 
	Support::Orientation& orientation)
{
	std::shared_ptr<Ship> ship{ std::make_shared<Ship>(size, begin_coordination, orientation) };
	ships_vec.push_back(ship);
	return ship;
}

// METHODS CLASS SHIP----------------------------------------------------------------------------------------------------
Ship::Ship(const uint8_t& ShipSize, Support::coordinates& begin_coordination, Support::Orientation& orientation)
{
	_ShipSize=ShipSize; 
	_ShipHealth=ShipSize;
	_ShipCoordinatesVector.reserve(2);
	for (size_t i = 0;i < ShipSize; i++)
	{
		if (orientation == Support::VERTICAL)
			_ShipCoordinatesVector.emplace_back(begin_coordination.X, (begin_coordination.Y + i));
		else
			_ShipCoordinatesVector.emplace_back((begin_coordination.X + i), begin_coordination.Y);

	}
}
void Ship::Decrement_ShipHealth() { _ShipHealth--; }
Ship::~Ship() {}

// METHODS CLASS PLAYER-----------------------------------------------------------------------------------------------------
Player::Player()
{
	for (size_t i = 0;i < Parameters->FieldSizeX;i++)
	{
		std::vector<BoardCase>temp1;
		std::vector< Support::FIELD_STATUS>temp2;
		for (size_t j = 0;j < Parameters->FieldSizeY;j++)
		{
			temp1.emplace_back(Support::WATER, nullptr);
			temp2.emplace_back(Support::WATER);
		}
		_BoardOwn.push_back(temp1);
		_BoardEnemy.push_back(temp2);
	}
	_PlayerMaxHealth = 30;
	_CurrentHealth = 30;
	_EnemyHealth = 30;
	_Target = Support::coordinates(0,0);
	_AttackResultEnemy=Support::MISS;
	_AttackResultPlayer = Support::MISS;
}
void Player::UpdateEnemy()
{
	if (_AttackResultPlayer == Support::HIT|| _AttackResultPlayer == Support::HIT_AND_SUNK || _AttackResultPlayer == Support::HIT_AND_SUNK_PLAYER)
	{
		_EnemyHealth--;
		_BoardEnemy[_Target.X][_Target.Y] = Support::HIT;
	}
}
bool Player::UpdatePlayer(std::vector<Support::coordinates> &sunk_ship_base)
{
	bool temp = false;
    _AttackResultEnemy = Support::MISS;
	if (_BoardOwn[_AttackEnemy.X][_AttackEnemy.Y].first == Support::SHIP)
	{
		_BoardOwn[_AttackEnemy.X][_AttackEnemy.Y].first = Support::HIT;
		_BoardOwn[_AttackEnemy.X][_AttackEnemy.Y].second->Decrement_ShipHealth();
		_CurrentHealth--;
		_AttackResultEnemy = Support::HIT;
		//check if the health of the hitted ship =0 and decide if it sink or not
		if (_BoardOwn[_AttackEnemy.X][_AttackEnemy.Y].second->_ShipHealth == 0)
		{
			_AttackResultEnemy = Support::HIT_AND_SUNK;
			sunk_ship_base = _BoardOwn[_AttackEnemy.X][_AttackEnemy.Y].second->_ShipCoordinatesVector;
			temp = true;
		}
		//if the player runs out of current health then player lose
		if (_CurrentHealth == 0)
		{
			_AttackResultEnemy = Support::HIT_AND_SUNK_PLAYER;
			sunk_ship_base = _BoardOwn[_AttackEnemy.X][_AttackEnemy.Y].second->_ShipCoordinatesVector;
			temp = true;
		}
	}
	return temp;
}
bool Player::CheckAndPlaceShip(Support::coordinates& block_coor_1, Support::coordinates& block_coor_2)
{
	uint8_t size = Parameters->SizeSelected;
	Support::Orientation orientation = Parameters->orientation;
	Support::coordinates begin_field = Parameters->CoordinatesSelected;
	if (CheckPath(size, begin_field, orientation, _BoardOwn, block_coor_1, block_coor_2) == true)
	{
		ShipPlacement(size, orientation, begin_field, _Ships, _BoardOwn);
		return true;
	}
	return false;
}
//Slots----------------------------------------------------------------------------------------------------------------------
void Player::SetSelectedShipSlot(int ship_size)
{
	Parameters->SizeSelected = ship_size;
    emit BlockingSurfaceSig(Parameters->Block1.X, Parameters->Block1.Y, Parameters->Block2.X, Parameters->Block2.Y);
}
void Player::SetOrientationSlot(char orientation)
{
	if(orientation == 'h')
	Parameters->orientation = Support::HORIZONTAL;
	else if (orientation == 'v')
	Parameters->orientation = Support::VERTICAL;
}
void Player::SetPlacingBeginCoordinatesSlot(int coord_begin_X, int coord_begin_Y)
{
    char orientation;
    if (Parameters->orientation == Support::HORIZONTAL){
        orientation = 'h';
    }else{
        orientation = 'v';
    }
    int size = Parameters->SizeSelected;
	Parameters->CoordinatesSelected.X = coord_begin_X;
	Parameters->CoordinatesSelected.Y = coord_begin_Y;

    if (CheckAndPlaceShip(Parameters->Block1, Parameters->Block2) == true)
    {
        emit DrawShipSig(coord_begin_X, coord_begin_Y,orientation,size);
    }
	else
        {emit ShipPlaceValidationSig(false);}

}
void Player::SetTargetSlot(int target_X, int target_Y)
{
	_Target.X = target_X;
	_Target.Y = target_Y;
}

void Player::PlayerAttackResultSlot(Support::FIELD_STATUS result, std::vector<Support::coordinates> ship_coordinates)
{
	_AttackResultPlayer = result;
	if (result == Support::MISS)
		emit PlayerAttackResultSig(_Target.X, _Target.Y, 'm');
	if (result == Support::HIT)
		emit PlayerAttackResultSig(_Target.X, _Target.Y, 'h');
	if (result == Support::HIT_AND_SUNK || result == Support::HIT_AND_SUNK_PLAYER)
	{
		emit PlayerAttackResultSig(_Target.X, _Target.Y, 'h');
		emit SunkShip(ship_coordinates.size());
	}
}

void Player::EnemyAttackSlot(Support::coordinates enemy_target)
{
	_AttackEnemy = enemy_target;
	char result_enemy;
	std::vector<Support::coordinates> sunk_ship_coordinates;
    if (UpdatePlayer(sunk_ship_coordinates) == true)

    {
        emit EnemyAttackResultSig(_AttackResultEnemy, sunk_ship_coordinates);
        switch (_AttackResultEnemy)
        {
        case Support::HIT:result_enemy = 'h';
            break;
        case Support::MISS:result_enemy = 'm';
            break;
        case Support::HIT_AND_SUNK:result_enemy = 'h';
            break;
        case Support::HIT_AND_SUNK_PLAYER:result_enemy = 'h';
            break;
        default:result_enemy = '0';
            break;
        }
        emit EnemyAttackResultGUISig(_AttackEnemy.X, _AttackEnemy.Y, result_enemy);
    }
    else
    {
        switch (_AttackResultEnemy)
        {
        case Support::HIT:result_enemy = 'h';
            break;
        case Support::MISS:result_enemy = 'm';
            break;
        case Support::HIT_AND_SUNK:result_enemy = 'h';
            break;
        case Support::HIT_AND_SUNK_PLAYER:result_enemy = 'h';
            break;
        default:result_enemy = '0';
            break;
        }
        emit EnemyAttackResultSig(_AttackResultEnemy, sunk_ship_coordinates);
        emit EnemyAttackResultGUISig(_AttackEnemy.X, _AttackEnemy.Y, result_enemy);
    }

}

