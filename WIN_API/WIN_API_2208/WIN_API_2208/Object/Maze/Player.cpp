#include "framework.h"
#include "Player.h"

Player::Player(shared_ptr<Maze> maze)
:_maze(maze)
{
	_pos = _maze->GetStartPos();
	_maze->GetBlock(_pos)->SetType(Block::Type::PLAYER);


	_discovered = vector<vector<bool>>(25, vector<bool>(25, false));
	_parent = vector<vector<Vector2>>(25, vector<Vector2>(25, Vector2(-1,-1)));
	BFS(_pos, _maze->GetEndPos());
	//Dijikstra(_pos, _maze->GetEndPos());
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
		// ���� �ٶ󺸴� ���� �������� ���������� �� �� �ִ��� Ȯ��
		int newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		Vector2 oldDirVector2 = frontPos[_dir]; // ���� ����
		Vector2 newDirVector2 = frontPos[newDir]; // ��ȯ������ ����ã�� -> ���ο� ����

		if (CanGo(pos + newDirVector2))
		{
			_dir = static_cast<Dir>(newDir);
			pos += newDirVector2; // ���� ��ȯ
			_path.push_back(pos);
		}

		// ���� �ٶ󺸴� ���� �������� ������ �� �ִ��� Ȯ��
		else if (CanGo(pos + oldDirVector2))
		{
			pos += oldDirVector2;
			_path.push_back(pos);
		}

		// ������, ���� �� �����ִٸ� �������� ȸ��
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
	Vector2 frontPos[4] =
	{
		Vector2 {0, 1},		// DOWN		2
		Vector2 {1, 0},		// RIGHT	3
		Vector2 {0, -1},	// UP		0
		Vector2 {-1, 0}		// LEFT		1
	};
	queue<Vector2> q;

	q.push(pos);
	_discovered[pos.y][pos.x] = true;
	_parent[pos.y][pos.x] = pos;


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

	Vector2 finder = end;
	_path.push_back(finder);
	while (true)
	{
		_path.push_back(_parent[finder.y][finder.x]);
		finder = _parent[finder.y][finder.x];

		if (finder == pos)
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
			float nextCost = 1 + best[here.y][here.x];

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

	Vector2 finder = _parent[end.y][end.x];
	_path.push_back(end);
	while (true)
	{
		_path.push_back(finder);
		finder = _parent[finder.y][finder.x];

		if (finder == start)
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
