//// **************************************************************************************
// Name: Milan Haruyama
// Date: 28 March 2021
//
// CS 225, Section 02, Surface-To-Air Saviors: Tower Defense
//
// This is the code for the game's Missile sprite.
// Credit to Lee Stemkoski for giving me some inspiration from his Asteroid JavaFX game.
// **************************************************************************************

import javafx.scene.paint.Color;

public class MissileSprite extends Sprite {
	private double angle = 0.5 * Math.PI, velocity = 90;
	private double impactDamage = 50;
	private boolean explode = false;

	public MissileSprite(double xLoc) {
		super(5, 20, xLoc, 0, 1, Color.YELLOW);
	}

	public void move(double time) {
		setX(getX() + velocity * time * Math.cos(angle));
		setY(getY() + velocity * time * Math.sin(angle));
	}

	public void explode() {
		explode = true;
	}
	
	public boolean getExplode() {
		return explode;
	}

	public double getImpactDamage() {
		return impactDamage;
	}
	
	public double getVelocity() {
		return velocity;
	}
	
	public void setVelocity(double velocity) {
		this.velocity = velocity;
	}
}