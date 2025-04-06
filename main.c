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

	struct rules gameRules[2] = {
		{1,1},
		{1,1}
	};

	initPieces(piecesG, whiteTextures, blackTextures);

	while (!WindowShouldClose()) {
		movePieces(piecesG, &selectedPiece, posibleMoves, gameRules);
		getPosibleMoves(piecesG, selectedPiece, posibleMoves, gameRules);


		BeginDrawing();
		ClearBackground( (Color) {0,0,0,255} );

		boardDraw();
		drawPieces(piecesG);
		drawPosibleMoves(piecesG, selectedPiece, posibleMoves);
		//getPlaces();

		EndDrawing();
/*
		printf("1:\tL %i, R %i\n", gameRules[1].castleL, gameRules[1].castleR);
		printf("2:\tL %i, R %i\n\n", gameRules[0].castleL, gameRules[0].castleR);
*/

		/*
		if (selectedPiece >= 0){
			printf("Pawn x: %c\nPawn y: %c\n", piecesG[selectedPiece].position.x, 
					piecesG[selectedPiece].position.y);
		}*/

	}

	CloseWindow();
	return 0;
	
}
