//// **************************************************************************************
// Name: Milan Haruyama
// Date: 28 March 2021
//
// CS 225, Section 02, Surface-To-Air Saviors: Tower Defense
//
// This is the code for the game's Player Missile sprite.
// Credit to Lee Stemkoski for giving me some inspiration from his Asteroid JavaFX game.
// **************************************************************************************

import javafx.scene.paint.Color;

public class PlayerMissileSprite extends Sprite {
	private double angle, mouseX, mouseY, velocity = 2400;
	private double impactDamage = 50;
	private boolean explode = false;

	public PlayerMissileSprite(double xLoc, double mouseX, double mouseY, double angle) {
		super(7.5, 30, xLoc, 615, 1, Color.LIGHTGOLDENRODYELLOW);
		this.angle = angle;
		this.mouseX = mouseX;
		this.mouseY = mouseY;
	}

	public void move(double time) {
		setX(getX() + (velocity) * time * Math.cos(angle));
		setY(getY() - (velocity) * time * Math.sin(angle));
		setY(getY() + 0.5 * getHeight() * time);
		setRotate(90 - Math.toDegrees(angle));
		if (angle <= 0.5 * Math.PI) {
			if (getX() >= mouseX && getY() <= mouseY) {
				explode = true;
			}

		} else if (angle >= 0.5 * Math.PI) {
			if (getX() <= mouseX && getY() <= mouseY) {
				explode = true;
			}
		} else if (angle == 0.5 * Math.PI) {
			if (getX() == mouseX && getY() <= mouseY) {
				explode = true;
			}
		}
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

}