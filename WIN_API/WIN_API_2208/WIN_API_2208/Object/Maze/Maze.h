#pragma once
class Maze
{
public:
	Maze();
	~Maze();

	void Update();
	void Render(HDC hdc);

	void CreateMaze();

private:
	const UINT _poolCountX = 25;
	const UINT _poolCountY = 25;

	vector<shared_ptr<Block>> _blocks;
	shared_ptr<Block> _blockMatrix[25][25] = { nullptr };

};

