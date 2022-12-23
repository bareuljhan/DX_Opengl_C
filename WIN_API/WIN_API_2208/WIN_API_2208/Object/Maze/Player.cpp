#include "framework.h"
#include "Player.h"

Player::Player(shared_ptr<Maze> maze)
:_maze(maze)
{
	_pos = _maze->GetStartPos();
	_maze->GetBlock(_pos)->SetType(Block::Type::PLAYER);


	_discovered = vector<vector<bool>>(25, vector<bool>(25, false));
	_parent = vector<vector<Vector2>>(25, vector<Vector2>(25, { -1,-1 }));
	BFS(_pos, _maze->GetEndPos());

	//_visited = vector<vector<bool>>(25, vector<bool>(25, false));
	// vector<Vector2> tempPath;
	// tempPath.reserve(300);
	//DFS(_pos, _maze->GetEndPos(), tempPath);

	////backTracking 
	//for (auto& pos : tempPath)
	//{
	//	_path.push_back(pos);
	//	if (pos == _maze->GetEndPos())
	//		break;
	//}
	// 
	// RightHand();
}

Player::~Player()
{
}

void Player::Update()
{
	if (_pathIndex >= _path.size())
		return;

	_time += 0.2f;

	if (_time > 1.0f)
	{
		_time = 0.0f;
		_pos = _path[_pathIndex];

		if (_pathIndex != 0)
		{
			Vector2 temp = _path[_pathIndex - 1];
			_maze->GetBlock(temp)->SetType(Block::Type::FOOT_PRINT);
		}

		_pathIndex++;
	}
	_maze->GetBlock(_pos)->SetType(Block::Type::PLAYER);
}

void Player::RightHand()
{
	Vector2 pos = _pos;
	_path.push_back(pos);
	Vector2 endPos = _maze->GetEndPos();
	_dir = Dir::DIR_UP;

	Vector2 frontPos[4] =
	{
		Vector2 {0, -1},	// UP		0
		Vector2 {-1, 0},	// LEFT		1
		Vector2 {0, 1},		// DOWN		2
		Vector2 {1, 0}		// RIGHT	3
	};

	while (pos != endPos)
	{
		// 현재 바라보는 방향 기준으로 오른쪽으로 갈 수 있는지 확인
		int newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		Vector2 oldDirVector2 = frontPos[_dir]; // 기존 방향
		Vector2 newDirVector2 = frontPos[newDir]; // 순환구조로 방향찾기 -> 새로운 방향

		if (CanGo(pos + newDirVector2))
		{
			_dir = static_cast<Dir>(newDir);
			pos += newDirVector2; // 방향 전환
			_path.push_back(pos);
		}

		// 현재 바라보는 방향 기준으로 전진할 수 있는지 확인
		else if (CanGo(pos + oldDirVector2))
		{
			pos += oldDirVector2;
			_path.push_back(pos);
		}

		// 오른쪽, 앞이 다 막혀있다면 왼쪽으로 회전
		else
		{
			_dir = static_cast<Dir>((_dir + 1 + DIR_COUNT) % DIR_COUNT);
		}
	}

	// Stack
	stack<Vector2> s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
		{
			s.pop();
		}
		else
			s.push(_path[i]);
	}
	s.push(_path.back());
	_path.clear();
	while (true)
	{
		if (s.empty() == true)
			break;
		_path.push_back(s.top());
		s.pop();
	}
	std::reverse(_path.begin(), _path.end());
	
}

void Player::DFS(Vector2 pos, Vector2 end, vector<Vector2> &tempPath)
{
	tempPath.push_back(pos);
	_maze->GetBlock(pos)->SetType(Block::Type::SEARCH_PRINT);
	_visited[pos.y][pos.x] = true;

	if (pos == end)
	{
		return;
	}
	Vector2 frontPos[4] =
	{
		Vector2 {0, 1},		// DOWN		2
		Vector2 {1, 0},		// RIGHT	3
		Vector2 {0, -1},	// UP		0
		Vector2 {-1, 0}		// LEFT		1
	};


	for (int i = 0; i < 4; i++)
	{
		Vector2 there = pos + frontPos[i];
		if (CanGo(there) == false)
			continue;
		if (_visited[there.y][there.x] == true)
			continue;
		DFS(there, end, tempPath);
	}

}

void Player::BFS(Vector2 pos, Vector2 end)
{
	queue<Vector2> q;

	q.push(pos);
	_path.push_back(pos);
	_discovered[pos.y][pos.x] = true;
	_parent[pos.y][pos.x] = pos;

	if (pos == end)
	{
		return;
	}

	Vector2 frontPos[4] =
	{
		Vector2 {0, 1},		// DOWN		2
		Vector2 {1, 0},		// RIGHT	3
		Vector2 {0, -1},	// UP		0
		Vector2 {-1, 0}		// LEFT		1
	};

	while (true)
	{
		if (q.empty() == true)
			break;

		Vector2 here = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			Vector2 there = pos + frontPos[i];
			if (_discovered[there.y][there.x] == true)
				continue;
			if (CanGo(there) == false)
				continue;
			if (here == there)
				continue;


			q.push(there);
			_discovered[there.y][there.x] = true;
			_parent[there.y][there.x] = here;
		}

	}
}

bool Player::CanGo(Vector2 pos)
{
	if (_maze->GetBlock(pos)->GetType() == Block::Type::DISABLE)
		return false;
	return true;
}
