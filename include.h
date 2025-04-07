#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <raylib.h>

#define bool	_Bool
#define true	1
#define false	0

#define screenW 800
#define screenH 800

#define FRACBLOCK (screenH/8)

#define usrR 255
#define usrG 255
#define usrB 255

#define sqsize (screenH/8)

int charToInt(char character){
	return (character - 48);
}

int chessToMath(char pieceChessCord, int whichCord){
	//1 = X (letter)
	//2 = Y (numers)
	
	int buffer;
	
	if (whichCord == 1) {buffer = pieceChessCord - 96;} //letters
	else {
		int n = (pieceChessCord - 48);
		if (n > 4.5){
			buffer = n - ( (n - 4.5)*2 );
		} else {
			buffer = n + ( (4.5-n)*2 );
		}
	} 				//Numers

	int returnValue = (100*buffer - 50);
	//printf("Wichcord: %i\nbuffer: %i\nreturn: %i\n\n", 
	//		whichCord, buffer, returnValue);
	return returnValue;

}

int getPlaces(){

	char pieceChessX = 'e';
	char pieceChessY = '7';

	int pieceY, pieceX;
	//char chessx, chessy;

	DrawCircle(chessToMath(pieceChessX, 1),
			chessToMath(pieceChessY, 2), 
			25, (Color){255,0,0,255});


	/*
*/

	
	return 0;
}

int boardDraw(){
	int nx = 0, ny = 0;
	int sqnum = 1;
	Color sqColor;
	Color darkSquareColor = {173,113,235,255};
	Color lightSquareColor = {255,255,255,255};

	while (ny < screenH){
		while (nx < screenW) {
			if (sqnum % 2){
				sqColor = darkSquareColor;
			} else {
				sqColor = lightSquareColor;
			}
			DrawRectangle(nx, ny, 
					sqsize, sqsize, 
					sqColor);
			/*PLACE CEnter
			DrawCircle(nx + 50, ny + 50, 25, 
					(Color) {255,0,0,255});
					*/
			sqnum++;

			nx = nx + 100;
		}
		sqnum--;
		nx = 0;
		ny = ny + 100;
	}
	return 0;
}


#endif
