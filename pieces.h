#ifndef PIECES_H
#define PIECES_H

#include <string.h>
#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>
#include "include.h"

#define pawnsNumber 8
#define totalPieces 32

#define textureScale 1.5

typedef struct chessCords {
	char x;
	char y;
} chessCords;
typedef struct piece {
	chessCords position;
	int able; 			//alpha
	char color;
	Texture2D * texture;
	int type;
	/* k 	knight
	 * p 	Pawn
	 * t 	tower
	 * b 	bishop
	 * q 	queen
	 * c 	king
	 */
} piece;


#define textureCount 6

#define pawn 0
#define knight 1
#define bishop 2
#define tower 3
#define queen 4
#define king 5


#define white 0
#define black 1

#define maxPosibleMoves 27


int relativeCordGotten(piece * piecesG,int originPieceIndex, int relativeX, int relativeY){
	int piecesOnIt = 0;
	for (int i = 0; i < totalPieces; i++){
		if (
				(piecesG[i].position.x == (piecesG[originPieceIndex].position.x + relativeX) )
				&&
				(piecesG[i].position.y == (piecesG[originPieceIndex].position.y + relativeY) )
				&&
				(i != originPieceIndex)
				){
			piecesOnIt++;
		}
	}
	return piecesOnIt;
}

int generatePiece 
		(int color, int relativeLine, char column, int pieceType,
		 Texture2D * colorTextures,  piece * pieceToPlace){
		
	unsigned int absoluteLine = 0;

	 //relative line 0 = cordinate y 1/8
	if (absoluteLine > 8) {printf("Relative line out of boundaries. %i > 8.\n", absoluteLine); return 1;}
	 
	switch (color){
		case white:
			absoluteLine = 1 + relativeLine;
			pieceToPlace->color = 'w';
			break;
		case black:
			absoluteLine = 8 - relativeLine;
			pieceToPlace->color = 'b';
			break;
	}


	//placing
	pieceToPlace->position = (chessCords) {column, (char)(absoluteLine + 48) };

	pieceToPlace->able = true;
	pieceToPlace->type = pieceType;
	pieceToPlace->texture = &colorTextures[pieceType];


	printf("Placed piece on %c%c, able = %i\n", pieceToPlace->position.x, pieceToPlace->position.y, pieceToPlace->able);

	return 0;
}


int initPieces(piece * piecesG, Texture2D * whiteTextures, Texture2D * blackTextures){

	whiteTextures[pawn] = LoadTexture("resources/Wpawn.png");
	blackTextures[pawn] = LoadTexture("resources/Bpawn.png");
	whiteTextures[knight] = LoadTexture("resources/Wknight.png");
	blackTextures[knight] = LoadTexture("resources/Bknight.png");
	whiteTextures[bishop] = LoadTexture("resources/Wbishop.png");
	blackTextures[bishop] = LoadTexture("resources/Bbishop.png");
	whiteTextures[tower] = LoadTexture("resources/Wrook.png");
	blackTextures[tower] = LoadTexture("resources/Brook.png");

	whiteTextures[queen] = LoadTexture("resources/Wqueen.png");
	blackTextures[queen] = LoadTexture("resources/Bqueen.png");


	whiteTextures[king] = LoadTexture("resources/Wking.png");
	blackTextures[king] = LoadTexture("resources/Bking.png");

	
	int i = 0;
	for (; i < pawnsNumber; i++){
		generatePiece(white,
				1, ('a' + i), pawn, whiteTextures, &piecesG[i]);
		generatePiece(black,
				1, ('a' + i), pawn, blackTextures, &piecesG[i+8]);
		printf("i : %i\ni + 8: %i\n\n", i, i+8);
	}
	//Towers
	i += 8;
	printf("Towers starts at i : %i\n", i);

	generatePiece(white, 0, 'a', tower, whiteTextures, &piecesG[i++]);
	generatePiece(white, 0, 'h', tower, whiteTextures, &piecesG[i++]);
	generatePiece(black, 0, 'a', tower, blackTextures, &piecesG[i++]);
	generatePiece(black, 0, 'h', tower, blackTextures, &piecesG[i++]);
	printf("Last i: %i\n", i);

	//knight
	generatePiece(white, 0, 'b', knight, whiteTextures, &piecesG[i++]);
	generatePiece(white, 0, 'g', knight, whiteTextures, &piecesG[i++]);
	generatePiece(black, 0, 'b', knight, blackTextures, &piecesG[i++]);
	generatePiece(black, 0, 'g', knight, blackTextures, &piecesG[i++]);

	//bishop
	generatePiece(white, 0, 'c', bishop, whiteTextures, &piecesG[i++]);
	generatePiece(white, 0, 'f', bishop, whiteTextures, &piecesG[i++]);
	generatePiece(black, 0, 'c', bishop, blackTextures, &piecesG[i++]);
	generatePiece(black, 0, 'f', bishop, blackTextures, &piecesG[i++]);

	//queens
	generatePiece(white, 0, 'd', queen, whiteTextures, &piecesG[i++]);
	generatePiece(black, 0, 'd', queen, blackTextures, &piecesG[i++]);

	//kings
	generatePiece(white, 0, 'e', king, whiteTextures, &piecesG[i++]);
	generatePiece(black, 0, 'e', king, blackTextures, &piecesG[i]);

}

chessCords mouseToChess(){
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();

	chessCords cordinates;


	if (mouseX > 700) {cordinates.x = 'h';}
	else if (mouseX > 600) {cordinates.x = 'g';}
	else if (mouseX > 500) {cordinates.x = 'f';}
	else if (mouseX > 400) {cordinates.x = 'e';}
	else if (mouseX > 300) {cordinates.x = 'd';}
	else if (mouseX > 200) {cordinates.x = 'c';}
	else if (mouseX > 100) {cordinates.x = 'b';}
	else {cordinates.x = 'a';}

	if (mouseY > 700) {cordinates.y = '1';}
	else if (mouseY > 600) {cordinates.y = '2';}
	else if (mouseY > 500) {cordinates.y = '3';}
	else if (mouseY > 400) {cordinates.y = '4';}
	else if (mouseY > 300) {cordinates.y = '5';}
	else if (mouseY > 200) {cordinates.y = '6';}
	else if (mouseY > 100) {cordinates.y = '7';}
	else {cordinates.y = '8';}

	return cordinates;
}

int getPosibleMoves(piece * piecesG, int selectedPiece, chessCords * posibleMoves){

	int i = 0;
	char initialPawnPos;
	short int colorMultiplier;
	short int pawnEatable = 0;
	int frontPawn = 0;
	chessCords checkPlace = {'a', '1'};
	short int placeGotten;

	if (selectedPiece >= 0){
		switch (piecesG->type){
			case pawn:

				//invert direction of pawns movement
				if (piecesG[selectedPiece].color == 'w'){
					colorMultiplier = 1;
					initialPawnPos = '2';
				} else {
					colorMultiplier = -1;
					initialPawnPos = '7';
				}

			
				for (int j = 0; j < totalPieces; j++){
					//set posible moves
					//mov +1
					if (
							/*
							(piecesG[selectedPiece].position.y + (1*colorMultiplier) ) == piecesG[j].position.y 
							&&
    						piecesG[selectedPiece].position.x == piecesG[j].position.x 
							*/ 
							relativeCordGotten(
								piecesG,selectedPiece, 0, 1*colorMultiplier)

					   ){
						frontPawn = true;
					}

					if (
							/*
							(piecesG[selectedPiece].position.y + (1*colorMultiplier)) == piecesG[j].position.y
							&&
							 	(((piecesG[selectedPiece].position.x + 1) == piecesG[j].position.x)
									||
								 ((piecesG[selectedPiece].position.x - 1) == piecesG[j].position.x) )
							&&
							(piecesG[j].color != piecesG[selectedPiece].color)
							*/
							relativeCordGotten(
								piecesG, selectedPiece, 1, 1*colorMultiplier)
					   ){
						posibleMoves[0] = (chessCords)
							{(char) (piecesG[selectedPiece].position.x + 1 ), 
							(char) (piecesG[selectedPiece].position.y + (1*colorMultiplier))};
						pawnEatable++;
					} 
					if (
							relativeCordGotten(
								piecesG, selectedPiece, -1, 1*colorMultiplier)
							){
						posibleMoves[1] = (chessCords)
							{(char) (piecesG[selectedPiece].position.x + -1 ), 
							(char) (piecesG[selectedPiece].position.y + (1*colorMultiplier))};
						pawnEatable++;
					}

					

				}
				if (!frontPawn){
					posibleMoves[2] = 
						(chessCords) {
							piecesG[selectedPiece].position.x,
							(char)(piecesG[selectedPiece].position.y + (1*colorMultiplier)),
						};
					//if a pawn is on initial position
					if (piecesG[selectedPiece].position.y == initialPawnPos){
						posibleMoves[3] = 
							(chessCords) {
								piecesG[selectedPiece].position.x,
								(char) (piecesG[selectedPiece].position.y + (2*colorMultiplier)),
							};
				}


				}
				break;
			/*
			case tower:
				while (onBoard(checkPlace) && !placeGotten){

				}*/

		}
	}
	else {
		for (int i = 0; i < maxPosibleMoves; i++){
			posibleMoves[i] = (chessCords) {0,0};
		}
	}

	return 0;
}

int drawPosibleMoves( piece * piecesG, int selectedPiece, chessCords * posibleMoves){
	if (selectedPiece >= 0){
		for (int i = 0; i < maxPosibleMoves; i++){
			DrawCircle(
					chessToMath(posibleMoves[i].x, 1),
					chessToMath(posibleMoves[i].y, 2),
					20, 
					(Color){200,200,200,255});
		}
	}
	return 0;
}


int movePieces(piece * piecesG, int * selectedPiece){
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

		if (*selectedPiece >= 0){
			chessCords mouseCords = mouseToChess();

			piecesG[*selectedPiece].position = mouseCords;
			printf("Pawn x: %c\nPawn y: %c\n\n", piecesG[*selectedPiece].position.x,
					piecesG[*selectedPiece].position.y);
			*selectedPiece = -1;
		} else {
			chessCords mouseCords = mouseToChess();
			printf("x: %c\ny: %c\n", mouseCords.x, mouseCords.y);
			for (int i = 0; i < pawnsNumber*2; i++){
				if(piecesG[i].position.x == mouseCords.x &&
						piecesG[i].position.y == mouseCords.y){
					*selectedPiece = i;
				}
			}
		}
	}
	return 0;
}

int drawPieces(piece * piecesG){

	for (int i = 0; i < totalPieces; i++){
		DrawTextureEx(*piecesG[i].texture,
				(Vector2){
					(float) (chessToMath(piecesG[i].position.x, 1) ) - 
						(float)(piecesG[i].texture->width*textureScale/2),
					(float) (chessToMath(piecesG[i].position.y, 2) ) -
						(float)(piecesG[i].texture->height*textureScale/2)
					},
				0, textureScale, 
				(Color){255,255,255, (unsigned char) (255 * piecesG[i].able) });
	}



	return 0;
}


#endif
