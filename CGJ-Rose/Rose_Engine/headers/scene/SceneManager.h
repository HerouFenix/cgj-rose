#ifndef SCENE_MANAGER
#define SCENE_MANAGER

// SCENE MANAGER CLASS HEADER
/// Class used to abstract the creation and management of shapes
#include<iostream>
#include <vector> 

#include "../shapes/Tetromino.h"

class SceneManager {
private:
	std::vector<Tetromino> sceneShapes;
	int currentSize = 0;
public:
	// FUNCTION DECLARATIONS
	/********************************************/ /**
	* Creates a new Scene Manager
	***********************************************/
	SceneManager();

	/********************************************/ /**
	* Returns the current scene's shapes
	* @return The Tetromino vector with all current shapes
	***********************************************/
	std::vector<Tetromino> getPieces();

	/********************************************/ /**
	* Returns the current number of shapes
	* @return The number of shapes added
	***********************************************/
	int getSize();

	/********************************************/ /**
	* Returns the piece stored in the specified index
	* @param index - The index of the piece
	* @return piece - The piece
	***********************************************/
	Tetromino getPieceAt(int index);

	/********************************************/ /**
	* Creates and adds a new L piece
	* @param colour - An int array containing information on R,G,B,A. Values should range from 0 to 255.
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	* @return The index of the newly created L piece 
	***********************************************/
	int createLPiece(float colour[4], Vector4 center = Vector4());

	/********************************************/ /**
	* Creates and adds a new L piece
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	* @return The index of the newly created L piece
	***********************************************/
	int createLPiece(Vector4 center = Vector4());

	/********************************************/ /**
	* Creates and adds a new RL piece
	* @param colour - An int array containing information on R,G,B,A. Values should range from 0 to 255.
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	* @return The index of the the newly created RL piece
	***********************************************/
	int createRLPiece(float colour[4], Vector4 center = Vector4());

	/********************************************/ /**
	* Creates and adds a new L piece
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	* @return The index of the newly created L piece
	***********************************************/
	int createRLPiece(Vector4 center = Vector4());

	/********************************************/ /**
	* Creates and adds a new L piece
	* @param colour - An int array containing information on R,G,B,A. Values should range from 0 to 255.
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	* @return The newly created I piece
	***********************************************/
	int createIPiece(float colour[4], Vector4 center = Vector4());

	/********************************************/ /**
	* Creates and adds a new L piece
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	* @return The newly created I piece
	***********************************************/
	int createIPiece(Vector4 center = Vector4());

	/********************************************/ /**
	* Creates and adds a new L piece
	* @param colour - An int array containing information on R,G,B,A. Values should range from 0 to 255.
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	* @return The index of the the newly created SQ piece
	***********************************************/
	int createSQPiece(float colour[4], Vector4 center = Vector4());

	/********************************************/ /**
	* Creates and adds a new L piece
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	* @return The index of the the newly created SQ piece
	***********************************************/
	int createSQPiece(Vector4 center = Vector4());

	/********************************************/ /**
	* Creates and adds a new T piece
	* @param colour - An int array containing information on R,G,B,A. Values should range from 0 to 255.
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	* @return The index of the the newly created T piece
	***********************************************/
	int createTPiece(float colour[4], Vector4 center = Vector4());

	/********************************************/ /**
	* Creates and adds a new T piece
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	* @return The index of the the newly created T piece
	***********************************************/
	int createTPiece(Vector4 center = Vector4());

	/********************************************/ /**
	* Creates and adds a new S piece
	* @param colour - An int array containing information on R,G,B,A. Values should range from 0 to 255.
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	* @return The index of the the newly created S piece
	***********************************************/
	int createSPiece(float colour[4], Vector4 center = Vector4());

	/********************************************/ /**
	* Creates and adds a new S piece
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	* @return The index of the the newly created S piece
	***********************************************/
	int createSPiece(Vector4 center = Vector4());

	/********************************************/ /**
	* Creates and adds a new RS piece
	* @param colour - An int array containing information on R,G,B,A. Values should range from 0 to 255.
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	* @return The index of the the newly created RS piece
	***********************************************/
	int createRSPiece(float colour[4], Vector4 center = Vector4());

	/********************************************/ /**
	* Creates and adds a new RS piece
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	* @return The index of the the newly created RS piece
	***********************************************/
	int createRSPiece(Vector4 center = Vector4());

	/********************************************/ /**
	* Creates and adds a new DEBUG piece
	* @return The index of the the newly created RS piece
	***********************************************/
	int createDebugPiece();

	/********************************************/ /**
	* Transforms a piece at a given index
	* @param The index of the the index of the piece
	* @param The transformation matrix
	***********************************************/
	void transformPiece(int index, Matrix4 mat);

	/********************************************/ /**
	* Deletes all shapes in the current scene
	* @param The index of the the index of the piece
	* @param The transformation matrix
	***********************************************/
	void clearScene();

};

#endif