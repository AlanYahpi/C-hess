#include <raylib.h>
#include <stdio.h>

#include "include.h"
#include "pieces.h"

int main (){

	InitWindow(screenW, screenH, "chess bc i am bored");
	SetTargetFPS(60);



	piece piecesG[totalPieces];
	Texture2D whiteTextures[textureCount];
	Texture2D blackTextures[textureCount];
	int selectedPiece = -1;
	chessCords posibleMoves[maxPosibleMoves];

	initPieces(piecesG, whiteTextures, blackTextures);

	while (!WindowShouldClose()) {
		movePieces(piecesG, &selectedPiece);
		getPosibleMoves(piecesG, selectedPiece, posibleMoves);


		BeginDrawing();
		ClearBackground( (Color) {0,0,0,255} );

		boardDraw();
		drawPieces(piecesG);
		drawPosibleMoves(piecesG, selectedPiece, posibleMoves);
		//getPlaces();

		EndDrawing();


		/*
		if (selectedPiece >= 0){
			printf("Pawn x: %c\nPawn y: %c\n", piecesG[selectedPiece].position.x, 
					piecesG[selectedPiece].position.y);
		}*/

	}

	CloseWindow();
	return 0;
	
}
