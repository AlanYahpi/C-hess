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
	bool able; 			//alpha
	short int color;
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

struct rules {
	bool castleR;
	bool castleL;
};


#define textureCount 6

#define pawn 0
#define knight 1
#define bishop 2
#define tower 3
#define queen 4
#define king 5


#define white 0
#define black 1

#define maxPosibleMoves 59

#define gotten 1
#define gottenByMe 2
#define notGotten 0



int onBoard(chessCords piece){
	if (
			piece.x <= 'h' && piece.x >= 'a'
			&&
			piece.y <= '8' && piece.y >= '1'
			){
		return true;
	} else {
		return false;
	}
}

int relativeCordGottenByMe(piece * piecesG,int originPieceIndex, int relativeX, int relativeY, short color){
	short pieceGotten = 0;
	for (int i = 0; i < totalPieces; i++){
		if (
				(piecesG[i].position.x == (piecesG[originPieceIndex].position.x + relativeX) )
				&&
				(piecesG[i].position.y == (piecesG[originPieceIndex].position.y + relativeY) )
				&&
				(i != originPieceIndex)
				&& 
				(piecesG[i].color == color)
				){
			pieceGotten = true;
			break;
		}
	}
	return pieceGotten;
}


int relativeCordGotten(piece * piecesG,int originPieceIndex, int relativeX, int relativeY){
	short piecesOnIt = 0;
	short relativeColor = -1;
	for (int i = 0; i < totalPieces; i++){
		if (
				(piecesG[i].position.x == (piecesG[originPieceIndex].position.x + relativeX) )
				&&
				(piecesG[i].position.y == (piecesG[originPieceIndex].position.y + relativeY) )
				&&
				(i != originPieceIndex)
				){
			piecesOnIt = true;
			relativeColor = piecesG[i].color;
		}
	}
	if (!piecesOnIt) return notGotten;
	if (piecesG[originPieceIndex].color == relativeColor) return gottenByMe;
	else return gotten;
}

short int positionGotten (chessCords askedPosition, piece * piecesG){
	for (int i = 0; i < totalPieces; i++){
		if (
				askedPosition.x == piecesG[i].position.x
				&&
				askedPosition.y == piecesG[i].position.y
				){
			return true;
		}
	}
		return false;
}

int linearMovementEvaluation(short directionX, short directionY, int indexInit, piece * piecesG, int selectedPiece, chessCords * posibleMoves){
	chessCords checkPlace = piecesG[selectedPiece].position;
	short placeGotten = false;
	int i = indexInit;

	while (onBoard(checkPlace) && !placeGotten){
		checkPlace.x += directionX;
		checkPlace.y += directionY;

		posibleMoves[i] = checkPlace;
		i++;
		placeGotten = positionGotten(checkPlace, piecesG);
	}
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
			pieceToPlace->color = white;
			break;
		case black:
			absoluteLine = 8 - relativeLine;
			pieceToPlace->color = black;
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

int getPosibleMoves(piece * piecesG, int selectedPiece, chessCords * posibleMoves,struct rules * gameRules){

	int i = 0;
	char initialPawnPos;
	short int colorMultiplier;
	short int pawnEatable = 0;
	int frontPawn = 0;
	chessCords checkPlace = {'a', '1'};
	short int placeGotten = false;

	if (selectedPiece >= 0){
		switch (piecesG[selectedPiece].type){
			case pawn:

				//invert direction of pawns movement
				if (piecesG[selectedPiece].color == white){
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
							relativeCordGotten(
								piecesG,selectedPiece, 0, 1*colorMultiplier)

					   ){
						frontPawn = true;
					}

					//diagonal moves
					if (
							relativeCordGotten(
								piecesG, selectedPiece, 1, 1*colorMultiplier) == 1
					   ){
						posibleMoves[0] = (chessCords)
							{(char) (piecesG[selectedPiece].position.x + 1 ), 
							(char) (piecesG[selectedPiece].position.y + (1*colorMultiplier))};
						pawnEatable++;
					} 
					if (
							relativeCordGotten(
								piecesG, selectedPiece, -1, 1*colorMultiplier) == 1
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
					if (piecesG[selectedPiece].position.y == initialPawnPos
							&& 
							!relativeCordGotten(piecesG, selectedPiece, 0, 2)){
						posibleMoves[3] = 
							(chessCords) {
								piecesG[selectedPiece].position.x,
								(char) (piecesG[selectedPiece].position.y + (2*colorMultiplier)),
							};
				}


				}
				break;
			case tower:

				//index init is the initial index for the posile moves array, it is based on the maximus posible moves that can exist
				linearMovementEvaluation(1, 0, 0, piecesG, selectedPiece, posibleMoves);
				linearMovementEvaluation(-1, 0, 8, piecesG, selectedPiece, posibleMoves);
				linearMovementEvaluation(0, 1, 16, piecesG, selectedPiece, posibleMoves);
				linearMovementEvaluation(0, -1, 24, piecesG, selectedPiece, posibleMoves);
				break;
			case queen:
				linearMovementEvaluation(1, 0, 0, piecesG, selectedPiece, posibleMoves);
				linearMovementEvaluation(-1, 0, 8, piecesG, selectedPiece, posibleMoves);
				linearMovementEvaluation(0, 1, 16, piecesG, selectedPiece, posibleMoves);
				linearMovementEvaluation(0, -1, 24, piecesG, selectedPiece, posibleMoves);

				linearMovementEvaluation(1, 1, 31, piecesG, selectedPiece, posibleMoves);
				linearMovementEvaluation(-1, 1, 38, piecesG, selectedPiece, posibleMoves);
				linearMovementEvaluation(-1, -1, 45, piecesG, selectedPiece, posibleMoves);
				linearMovementEvaluation(1, -1, 52, piecesG, selectedPiece, posibleMoves);
				break;
			case bishop:
				linearMovementEvaluation(1, 1, 31, piecesG, selectedPiece, posibleMoves);
				linearMovementEvaluation(-1, 1, 38, piecesG, selectedPiece, posibleMoves);
				linearMovementEvaluation(-1, -1, 45, piecesG, selectedPiece, posibleMoves);
				linearMovementEvaluation(1, -1, 52, piecesG, selectedPiece, posibleMoves);
				break;
			case knight:
					posibleMoves[0] = (chessCords) {(char) (piecesG[selectedPiece].position.x + 2),
													(char) (piecesG[selectedPiece].position.y + 1)};
					posibleMoves[1] = (chessCords) {(char) (piecesG[selectedPiece].position.x + 2),
													(char) (piecesG[selectedPiece].position.y - 1)};
					posibleMoves[2] = (chessCords) {(char) (piecesG[selectedPiece].position.x - 2),
													(char) (piecesG[selectedPiece].position.y + 1)};
					posibleMoves[3] = (chessCords) {(char) (piecesG[selectedPiece].position.x - 2),
													(char) (piecesG[selectedPiece].position.y - 1)};
					posibleMoves[4] = (chessCords) {(char) (piecesG[selectedPiece].position.x + 1),
													(char) (piecesG[selectedPiece].position.y + 2)};
					posibleMoves[5] = (chessCords) {(char) (piecesG[selectedPiece].position.x - 1),
													(char) (piecesG[selectedPiece].position.y + 2)};
					posibleMoves[6] = (chessCords) {(char) (piecesG[selectedPiece].position.x + 1),
													(char) (piecesG[selectedPiece].position.y - 2)};
					posibleMoves[7] = (chessCords) {(char) (piecesG[selectedPiece].position.x - 1),
													(char) (piecesG[selectedPiece].position.y - 2)};
				break;
			case king:
					//Regular
					posibleMoves[0] = (chessCords) {(char) (piecesG[selectedPiece].position.x + 1),
													(char) (piecesG[selectedPiece].position.y + 0)};
					posibleMoves[1] = (chessCords) {(char) (piecesG[selectedPiece].position.x + 1),
													(char) (piecesG[selectedPiece].position.y + 1)};
					posibleMoves[2] = (chessCords) {(char) (piecesG[selectedPiece].position.x + 0),
													(char) (piecesG[selectedPiece].position.y + 1)};
					posibleMoves[3] = (chessCords) {(char) (piecesG[selectedPiece].position.x - 1),
													(char) (piecesG[selectedPiece].position.y + 0)};
					posibleMoves[4] = (chessCords) {(char) (piecesG[selectedPiece].position.x - 1),
													(char) (piecesG[selectedPiece].position.y - 1)};
					posibleMoves[5] = (chessCords) {(char) (piecesG[selectedPiece].position.x + 0),
													(char) (piecesG[selectedPiece].position.y - 1)};
					posibleMoves[6] = (chessCords) {(char) (piecesG[selectedPiece].position.x + 1),
													(char) (piecesG[selectedPiece].position.y - 1)};
					posibleMoves[7] = (chessCords) {(char) (piecesG[selectedPiece].position.x - 1),
													(char) (piecesG[selectedPiece].position.y + 1)};
					if (gameRules[piecesG[selectedPiece].color].castleR 
							&&
							!(relativeCordGotten(piecesG,selectedPiece, 2, 0))
							&&
							!(relativeCordGotten(piecesG,selectedPiece, 1, 0))
							){
						posibleMoves[8] = (chessCords) {(char) (piecesG[selectedPiece].position.x + 2),
														(char) (piecesG[selectedPiece].position.y)};
					}
					if (gameRules[piecesG[selectedPiece].color].castleL
							&&
							!(relativeCordGotten(piecesG,selectedPiece, -2, 0))
							&&
							!(relativeCordGotten(piecesG,selectedPiece, -1, 0))
							){
						posibleMoves[9] = (chessCords) {(char) (piecesG[selectedPiece].position.x - 2),
														(char) (piecesG[selectedPiece].position.y)};
					}

					break;


		}
	}
	else {
		for (int i = 0; i < maxPosibleMoves; i++){
			posibleMoves[i] = (chessCords) {0,0};
		}
	}

	printf("Piece %i\n", selectedPiece);

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
			if (posibleMoves[i].x > 0){
				//printf("Posible move at %c%c\n", posibleMoves[i].x, posibleMoves[i].y);

			}
		}
	}
	return 0;
}


int movePieces(piece * piecesG, int * selectedPiece, chessCords * posibleMoves, struct rules * gameRules){
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

		if (*selectedPiece >= 0){
			chessCords mouseCords = mouseToChess();

			for(int i = 0; i < maxPosibleMoves; i++){
				if ((mouseCords.x == posibleMoves[i].x) && (mouseCords.y == posibleMoves[i].y) ){

					for(int j = 0; j < totalPieces; j++){
						if ((mouseCords.x == piecesG[j].position.x) && (mouseCords.y == piecesG[j].position.y) && (j != *selectedPiece)){
							piecesG[j].able = false;
							break;
							//piecesG[*selectedPiece].position = mouseCords;

						}
					}
					switch (piecesG[*selectedPiece].type) {
						case king:

							//The posibleMoves index is where is gonna be located the posible castleing square

							if ((mouseCords.x == posibleMoves[8].x) /*Right castle*/ && (mouseCords.y == posibleMoves[8].y) ){
								//piece 17 is the white rook, piece 17+2 is the black one. piecesG[x].color is 0 or 1.
								piecesG[17+(2*piecesG[*selectedPiece].color)].position.x = 'f';
							}
							
							if ((mouseCords.x == posibleMoves[9].x) /*Right castle*/ && (mouseCords.y == posibleMoves[9].y) ){
								//piece 16 is the white rook, piece 16+2 is the black one. piecesG[x].color is 0 or 1.
								piecesG[16+(2*piecesG[*selectedPiece].color)].position.x = 'd';
							}

								gameRules[piecesG[*selectedPiece].color].castleR = false;
								gameRules[piecesG[*selectedPiece].color].castleL = false;
							break;
						case tower:

							if (piecesG[*selectedPiece].position.y != '1') { gameRules[piecesG[*selectedPiece].color].castleL = false; gameRules[piecesG[*selectedPiece].color].castleR = false; break;}


							if (piecesG[*selectedPiece].position.x != 'h') {
								gameRules[piecesG[*selectedPiece].color].castleR = false;
							} else if (piecesG->position.x != 'a') {
								gameRules[piecesG[*selectedPiece].color].castleL = false;
							}
							break;
					}
					piecesG[*selectedPiece].position = mouseCords;
				}
			}

			//piecesG[*selectedPiece].position = mouseCords;  //temp

			printf("Pawn x: %c\nPawn y: %c\n\n", piecesG[*selectedPiece].position.x,
					piecesG[*selectedPiece].position.y);
			*selectedPiece = -1;
		} else {
			chessCords mouseCords = mouseToChess();
			printf("x: %c\ny: %c\n", mouseCords.x, mouseCords.y);
			for (int i = 0; i < totalPieces; i++){
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
		if(piecesG[i].able){
			DrawTextureEx(*piecesG[i].texture,
					(Vector2){
						(float) (chessToMath(piecesG[i].position.x, 1) ) - 
							(float)(piecesG[i].texture->width*textureScale/2),
						(float) (chessToMath(piecesG[i].position.y, 2) ) -
							(float)(piecesG[i].texture->height*textureScale/2)
						},
					0, textureScale, 
					(Color){255,255,255, 255 });
		} else {
			piecesG[i].position.x = -10;
		}
	}



	return 0;
}


#endif
