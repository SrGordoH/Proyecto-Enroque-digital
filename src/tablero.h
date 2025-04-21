#pragma once

class Tablero
{
public: 
	double center_x{ }, center_y{}, dist{1}, ancho_casillas{};
	int num_casillas{ 5 }; //num_casillas NxN
	void Draw();
    void DrawGrid();
	void DrawCell(int i, int j);
};
