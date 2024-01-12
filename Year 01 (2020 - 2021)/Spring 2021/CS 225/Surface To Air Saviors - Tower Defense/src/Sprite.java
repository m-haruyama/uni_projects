// ***************************************************************
// Name: Milan Haruyama
// Date: 28 March 2021
//
// CS 225, Section 02, Surface-To-Air Saviors: Tower Defense
//
// This is the code for the game's Sprite class.
// Credit to Lee Stemkoski for giving me some inspiration from his Asteroid JavaFX game.
// ***************************************************************

import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

public class Sprite extends Rectangle {
	protected double HP;

	public Sprite(double width, double height, double xPos, double yPos, int HP, Color color) {
		this.setHeight(height);
		this.setWidth(width);
		this.setX(xPos);
		this.setY(yPos);
		this.setFill(color);
		this.HP = HP;
	}

	// Handles collision of sprites.
	public boolean overlap(Sprite other) {
		boolean overlap = true;
		
		//if any of these conditions are true, the two sprites are not overlapping
		if (this.getX() + this.getWidth() < other.getX() || 
				other.getX() + other.getWidth() < this.getX() ||
				this.getY() + this.getHeight() < other.getY() || 
				other.getY() + other.getHeight() < this.getY() ) {
			overlap = false;
		}
		return overlap;
	}
	
	public void takeDamage(double damage) {
		this.HP -= damage;
	}

	public boolean destroyed() {
		boolean destroyed = false;
		if (HP <= 0) {
			destroyed = true;
		}
		return destroyed;
	}

	public double getHP() {
		return HP;
	}

}