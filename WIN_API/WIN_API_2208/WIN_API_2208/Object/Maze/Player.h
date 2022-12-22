#pragma once
class Player
{
public:
	Player(shared_ptr<Maze> maze);
	~Player();

	void Update();

	void RightHand();
	bool CanGo(Vector2 pos);
private:
	Vector2 _pos = { 0, 0 };

	vector<Vector2> _path;
	int _pathIndex = 0;
	float _time = 0.0f;

	shared_ptr<Maze> _maze;
	Dir _dir = Dir::DIR_UP;

};

