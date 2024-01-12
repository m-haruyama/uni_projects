// **************************************************************************************
// Name: Milan Haruyama
// Date: 28 March 2021
//
// CS 225, Section 02, Surface-To-Air Saviors: Tower Defense
//
// This is the code for the game's Missile Silo sprite
// Credit to Lee Stemkoski for giving me some inspiration from his Asteroid JavaFX game.
// **************************************************************************************

import javafx.scene.paint.Color;

public class MissileSiloSprite extends Sprite {

	public MissileSiloSprite(double xLoc) {
		super(80, 48, xLoc, 640, 150, Color.rgb(160, 160, 160));
	}

}