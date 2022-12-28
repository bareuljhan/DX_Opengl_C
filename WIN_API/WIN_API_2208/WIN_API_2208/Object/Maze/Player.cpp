#include "framework.h"
#include "Player.h"

Player::Player(shared_ptr<Maze> maze)
:_maze(maze)
{
	Init();
}

Player::~Player()
{
}

void Player::Init()
{
	_pos = _maze->GetStartPos();
	_maze->GetBlock(_pos)->SetType(Block::Type::PLAYER);


	_discovered = vector<vector<bool>>(25, vector<bool>(25, false));
	_parent = vector<vector<Vector2>>(25, vector<Vector2>(25, Vector2(-1, -1)));
	//BFS(_pos, _maze->GetEndPos());
	//Dijikstra(_pos, _maze->GetEndPos());
	AStar(_pos, _maze->GetEndPos());
}

void Player::Update()
{
	if (_pathIndex >= _path.size())
	{
		_maze->CreateMaze();
		_pathIndex = 0;
		_path.clear();
		Init();
		return;
	}

	_time += 0.4f;

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

void Player::BFS(Vector2 start, Vector2 end)
{
	Vector2 frontPos[4] =
	{
		Vector2 {0, 1},		// DOWN		2
		Vector2 {1, 0},		// RIGHT	3
		Vector2 {0, -1},	// UP		0
		Vector2 {-1, 0}		// LEFT		1
	};
	queue<Vector2> q;

	q.push(start);
	_discovered[start.y][start.x] = true;
	_parent[start.y][start.x] = start;


	while (true)
	{
		if (q.empty() == true)
			break;

		Vector2 here = q.front();
		q.pop();

		if (here == end)
			break;

		for (int i = 0; i < 4; i++)
		{
			Vector2 there = here + frontPos[i];
			if (_discovered[there.y][there.x] == true)
				continue;
			if (CanGo(there) == false)
				continue;
			if (here == there)
				continue;

			_maze->GetBlock(there)->SetType(Block::Type::SEARCH_PRINT);
			q.push(there);
			_discovered[there.y][there.x] = true;
			_parent[there.y][there.x] = here;
		}
	}

	Vector2 pos = end;
	_path.push_back(pos);
	while (true)
	{
		_path.push_back(_parent[pos.y][pos.x]);
		pos = _parent[pos.y][pos.x];

		if (pos == start)
			break;
	}

	std::reverse(_path.begin(), _path.end());
}

void Player::Dijikstra(Vector2 start, Vector2 end)
{
	Vector2 frontPos[8] =
	{
		Vector2 {0, 1},		// DOWN		2
		Vector2 {1, 0},		// RIGHT	3
		Vector2 {0, -1},	// UP		0
		Vector2 {-1, 0},	// LEFT		1

		Vector2 {1, 1},		// RIGHT_DOWN	2
		Vector2 {-1, 1},	// LEFT_DOWN	3
		Vector2 {1, -1},	// RIGHT_UP		0
		Vector2 {-1, -1}	// LEFT_UP		1
	};
	priority_queue<Vertex_Dijikstra, vector<Vertex_Dijikstra>, greater<Vertex_Dijikstra>> pq;
	vector<vector<float>> best = vector<vector<float>>(25, vector<float>(25,100000.0f));

	Vertex_Dijikstra startV;
	startV.pos = start;
	startV.g = 0;
	pq.push(startV);
	best[start.y][start.x] = 0;
	_discovered[start.y][start.x] = true;
	_parent[start.y][start.x] = start;


	while (true)
	{
		if (pq.empty() == true)
			break;

		Vector2 here = pq.top().pos;
		float cost = pq.top().g;
		pq.pop();

		if (here == end)
			break;

		if (best[here.y][here.x] < cost)
			continue;

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here + frontPos[i];
			if (CanGo(there) == false)
				continue;
			if (here == there)
				continue;

			float distance = (there - here).Length();
			float nextCost = 0.0f;
			if (i < 4)
				nextCost = 1 + best[here.y][here.x];
			else
				nextCost = 1.4 + best[here.y][here.x];

			if (best[there.y][there.x] <= nextCost)
				continue;

			_maze->GetBlock(there)->SetType(Block::Type::SEARCH_PRINT);
			Vertex_Dijikstra thereV;
			thereV.pos = there;
			thereV.g = nextCost;
			best[there.y][there.x] = nextCost;
			pq.push(thereV);
			_discovered[there.y][there.x] = true;
			_parent[there.y][there.x] = here;
		}
	}

	Vector2 pos = _parent[end.y][end.x];
	_path.push_back(end);
	while (true)
	{
		_path.push_back(pos);
		pos = _parent[pos.y][pos.x];

		if (pos == start)
		{
			_path.push_back(start);
			break;
		}
	}

	std::reverse(_path.begin(), _path.end());
}

void Player::AStar(Vector2 start, Vector2 end)
{
	Vector2 frontPos[8] =
	{
		Vector2 {0, 1},		// DOWN		2
		Vector2 {1, 0},		// RIGHT	3
		Vector2 {0, -1},	// UP		0
		Vector2 {-1, 0},	// LEFT		1

		Vector2 {1, 1},		// RIGHT_DOWN	2
		Vector2 {-1, 1},	// LEFT_DOWN	3
		Vector2 {1, -1},	// RIGHT_UP		0
		Vector2 {-1, -1}	// LEFT_UP		1
	};

	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
	vector<vector<float>> best = vector<vector<float>>(25, vector<float>(25, 100000.0f));

	Vertex startV;

	startV.pos = start;
	startV.g = 0;
	startV.h = start.Manhattan(end);
	startV.f = startV.g + startV.h;

	pq.push(startV);
	best[start.y][start.x] = startV.h;
	_discovered[start.y][start.x] = true;
	_parent[start.y][start.x] = start;
	while (true)
	{
		if (pq.empty() == true)
			break;

		// Vector2 here = q.front();
		Vector2 here = pq.top().pos;
		float g = pq.top().g;
		float h = pq.top().h;
		float f = g + h;
		pq.pop();

		if (best[here.y][here.x] < f)
			continue;
		if (here == end)
			break;

		for (int i = 0; i < 8; i++)
		{

			Vector2 there = here + frontPos[i];

			if (CanGo(there) == false)
				continue;

			float nextG = 0.0f;
			float nextH = there.Manhattan(end);
			float nextF = nextG + nextH;
			if (i < 4)
			{
				nextG = g + 1.0f;
				nextF += nextG;
			}
			else
			{
				nextG = g + 1.4f;
				nextF += nextG;
			}

			if (nextF >= best[there.y][there.x])
				continue;

			Vertex v;
			v.pos = there;
			v.g = nextG;
			v.h = nextH;
			v.f = nextF;
			pq.push(v);
			_discovered[there.y][there.x] = true;
			best[there.y][there.x] = nextG + nextH;

			_maze->GetBlock(there)->SetType(Block::Type::SEARCH_PRINT);
			_parent[there.y][there.x] = here;
		}
	}

	Vector2 pos = _parent[end.y][end.x];
	_path.push_back(end);
	while (true)
	{
		_path.push_back(pos);
		pos = _parent[pos.y][pos.x];

		if (pos == start)
		{
			_path.push_back(start);
			break;
		}
	}

	std::reverse(_path.begin(), _path.end());

}

bool Player::CanGo(Vector2 pos)
{
	if (_maze->GetBlock(pos)->GetType() == Block::Type::DISABLE)
		return false;
	return true;
}
