#pragma once
class Player
{
public:
	Player(shared_ptr<Maze> maze);
	~Player();

	void Update();

	void RightHand();
	void DFS(Vector2 pos, Vector2 end, vector<Vector2> &tempPath);
	void BFS(Vector2 pos, Vector2 end);
	bool CanGo(Vector2 pos);



private:
	Vector2 _pos = { 0, 0 };

	vector<Vector2> _path;
	int _pathIndex = 0;
	float _time = 0.0f;

	shared_ptr<Maze> _maze;
	Dir _dir = Dir::DIR_UP;

	// DFS
	vector<vector<bool>> _visited;
	
	// BFS
	vector<vector<bool>> _discovered;
	vector<vector<Vector2>> _parent;
};

