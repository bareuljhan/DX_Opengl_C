#pragma once
class Maze
{
public:
	Maze();
	~Maze();

	void Update();
	void Render(HDC hdc);

	void CreateMaze();

	Vector2 GetStartPos() { return { 1,1 }; }
	Vector2 GetEndPos() { return Vector2((int)_poolCountX - 2, (int)_poolCountY - 2); }
	shared_ptr<Block> GetBlock(Vector2 pos) { return _blockMatrix[static_cast<UINT>(pos.y)][static_cast<UINT>(pos.x)]; }

private:
	const UINT _poolCountX = 25;
	const UINT _poolCountY = 25;

	vector<shared_ptr<Block>> _blocks;
	shared_ptr<Block> _blockMatrix[25][25] = { nullptr };
};