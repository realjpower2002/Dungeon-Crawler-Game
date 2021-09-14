#include<iostream>
#include<random>
#include<cstdlib>
#include<time.h>

using namespace std;

const int rowsInMatrix = 20;
const int columnsInMatrix = 7;

void printMatrix(int array[rowsInMatrix][columnsInMatrix], int rows, int columns);

void populateMatrixWithRooms(int array[rowsInMatrix][columnsInMatrix], int rows, int columns);

//determines whether a '1' tile should convert another adjacent tile to a '1'
void convertTiles(int array[rowsInMatrix][columnsInMatrix], int tileRow, int tileColumn, int originRow, int originColumn);

int dungeonIsGood(int array[rowsInMatrix][columnsInMatrix]);

int main() {
	srand(time(NULL));
	int array[rowsInMatrix][columnsInMatrix];

	for (int r = 0; r < rowsInMatrix; r++) {
		for (int c = 0; c < columnsInMatrix; c++) {
			array[r][c] = 0;
		}
	}



	printMatrix(array, rowsInMatrix, columnsInMatrix);

	cout << endl;

	array[rowsInMatrix-1][columnsInMatrix / 2] = 1;

	int dungeonGood = 0;

	convertTiles(array, rowsInMatrix-1, columnsInMatrix/2, rowsInMatrix, columnsInMatrix/2);

	dungeonGood = dungeonIsGood(array);

	cout << endl << "Is dungeon good:" << dungeonGood << endl;

	while ((dungeonGood!=1)) {
		cout << endl << "Is dungeon good:" << dungeonGood << endl;

		for (int r = 0; r < rowsInMatrix; r++) {
			for (int c = 0; c < columnsInMatrix; c++) {
				array[r][c] = 0;
			}
		}
		array[rowsInMatrix-1][columnsInMatrix / 2] = 1;
		convertTiles(array, rowsInMatrix - 1, columnsInMatrix / 2, rowsInMatrix, columnsInMatrix / 2);
		dungeonGood = dungeonIsGood(array);
	}

	//array[rowsInMatrix - 1][columnsInMatrix / 2] = 1;
	//array[rowsInMatrix - 1][columnsInMatrix / 2 - 1] = 2;

	printMatrix(array, rowsInMatrix, columnsInMatrix);

	//cout << "is 2 left of 1 : " << (15 / 2 - 1) - (15 / 2) << "\n";

	return 0;
}

void printMatrix(int array[rowsInMatrix][columnsInMatrix], int rows, int columns) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			cout << "" << array[r][c] << " ";
		}
		cout << "\n";
	}
}

void populateMatrixWithRooms(int array[rowsInMatrix][columnsInMatrix], int rows, int columns) {

}

//takes in the index of the tile that will convert tiles adjacent to
//it, contains the 'origin' of the tile (the location of the tile that
//made the new tile) as well as the array to be populated by the tile
// 
//I want it to go in a direction opposite to where it originated from
//use recursion to have velocity information
//20% chance for a tile to make a tile in 1 direction, 10% chance to make 
//tiles in two directions, 3% chance to make tiles in three directions
//
//This function assumes standard mathematical notation for matrices
void convertTiles(int array[rowsInMatrix][columnsInMatrix], int tileRow, int tileColumn, int originRow, int originColumn) {
	int isOriginAboveTile = tileRow - originRow; //if the origin is below the new tile, returns -1, if it is same, returns 0
	int isOriginLeftOfTile = originColumn-tileColumn; //if the origin is to the right of the new tile, returns -1, if it is same, returns 0

	if (rand() % 1000 < 200) { //20% chance for 1 room to generate to the left of the tile (with the origin behind)
		//
		//handles cases where origin is to the top or bottom of the tile first 
		//(origin cant be both in a different column and different row to tile)
		if (isOriginLeftOfTile == 0) {
			if (isOriginAboveTile == 1 && tileColumn != columnsInMatrix - 1) {
				array[tileRow][tileColumn + 1] = 1;
				convertTiles(array, tileRow, tileColumn + 1, originRow + 1, originColumn);
			}
			if (isOriginAboveTile == -1 && tileColumn != 0) {
				array[tileRow][tileColumn - 1] = 1;
				convertTiles(array, tileRow, tileColumn - 1, originRow - 1, originColumn);
			}
		}
		//
		//handles cases where origin is to the left or right of the tile second
		else {
			if (isOriginLeftOfTile == 1 && tileRow != 0) {
				array[tileRow - 1][tileColumn] = 1;
				convertTiles(array, tileRow - 1, tileColumn, originRow, originColumn + 1);
			}
			if (isOriginLeftOfTile == -1 && tileRow != (rowsInMatrix - 1)) {
				array[tileRow + 1][tileColumn] = 1;
				convertTiles(array, tileRow + 1, tileColumn, originRow, originColumn - 1);
			}
		}
	}

	if (rand() % 1000 < 200) { //20% chance for 1 room to generate to the right of the tile (with the origin behind)
		//
		//handles cases where origin is to the top or bottom of the tile first 
		//(origin cant be both in a different column and different row to tile)
		if (isOriginLeftOfTile == 0) {
			if (isOriginAboveTile == 1 && tileColumn != 0) {
				array[tileRow][tileColumn - 1] = 1;
				convertTiles(array, tileRow, tileColumn - 1, originRow + 1, originColumn);
			}
			if (isOriginAboveTile == -1 && tileColumn != columnsInMatrix - 1)
				array[tileRow][tileColumn + 1] = 1;
			convertTiles(array, tileRow, tileColumn + 1, originRow - 1, originColumn);
		}
	}
	//
	//handles cases where origin is to the left or right of the tile second
	else {
		if (isOriginLeftOfTile == 1 && tileRow != rowsInMatrix - 1) {
			array[tileRow + 1][tileColumn] = 1;
			convertTiles(array, tileRow + 1, tileColumn, originRow, originColumn + 1);
		}
		if (isOriginLeftOfTile == -1 && tileRow != 0) {
			array[tileRow - 1][tileColumn] = 1;
			convertTiles(array, tileRow - 1, tileColumn, originRow, originColumn - 1);
		}
	}

	if (rand() % 1000 < 870) {  //20% chance for 1 rooms to generate in the front of the tile (with the origin behind)
		//
		//handles cases where origin is to the top or bottom of the tile first 
		//(origin cant be both in a different column and different row to tile)
		if (isOriginLeftOfTile == 0) {
			if (isOriginAboveTile == 1 && tileRow != rowsInMatrix - 1) {
				array[tileRow + 1][tileColumn] = 1;
				convertTiles(array, tileRow + 1, tileColumn, originRow + 1, originColumn);
			}
			if (isOriginAboveTile == -1 && tileRow != 0) {
				array[tileRow - 1][tileColumn] = 1;
				convertTiles(array, tileRow - 1, tileColumn, originRow - 1, originColumn);
			}
		}
		//
		//handles cases where origin is to the left or right of the tile second
		else {
			if (isOriginLeftOfTile == 1 && tileColumn != columnsInMatrix - 1) {
				array[tileRow][tileColumn + 1] = 1;
				convertTiles(array, tileRow, tileColumn + 1, originRow, originColumn + 1);
			}
			if (isOriginLeftOfTile == -1 && tileColumn != 0) {
				array[tileRow][tileColumn - 1] = 1;
				convertTiles(array, tileRow, tileColumn - 1, originRow, originColumn - 1);
			}
		}
	}
}

int dungeonIsGood(int array[rowsInMatrix][columnsInMatrix]) {
	int howManyIs = 0;
	for (int i = 0; i < rowsInMatrix; i++) {
		for (int j = 0; j < columnsInMatrix; j++) {
			if (array[i][j] == 1) {
				howManyIs++;
			}
		}
	}
	cout << endl << howManyIs << " " << ((rowsInMatrix * columnsInMatrix) / 5) << " " << (bool)(howManyIs > ((rowsInMatrix * columnsInMatrix) / 5)) << endl << endl;

	if (howManyIs > ((rowsInMatrix * columnsInMatrix) / 5)) {
		return 1;
	}
	return 0;
}