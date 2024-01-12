// **************************************************************************************
// Name: Milan Haruyama
// Date: 28 March 2021
//
// CS 225, Section 02, Surface-To-Air Saviors: Tower Defense
//
// This is the code for the game's play pane.
// The play pane will handle the animations of the gameplay.
// Credit to Lee Stemkoski for giving me some inspiration from his Asteroid JavaFX game.
// Link to sounds used: https://opengameart.org/content/512-sound-effects-8-bit-style
// **************************************************************************************

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Arrays;
import javafx.animation.AnimationTimer;
import javafx.event.EventHandler;
import javafx.scene.Cursor;
import javafx.scene.control.Label;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.media.AudioClip;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.TextAlignment;

public class PlayPane extends Pane {
	private AnimationTimer gameTimer;
	private ArrayList<String> keyPressedList = new ArrayList<String>();
	private ArrayList<String> keyJustPressedList = new ArrayList<String>();
	private ArrayList<MissileSprite> missileSpriteList = new ArrayList<MissileSprite>();
	private ArrayList<PlayerMissileSprite> pMissileSpriteList = new ArrayList<PlayerMissileSprite>();
	private ArrayList<BarracksSprite> barracksList = new ArrayList<BarracksSprite>();
	private ArrayList<MissileSiloSprite> siloList = new ArrayList<MissileSiloSprite>();
	private File highScores = new File("High_Scores.txt");
	private Label lblCountdown, lblXP;
	private Rectangle ground;
	private double[] siloCooldown = new double[3];
	private double mouseX, mouseY, mouseAngle;
	private float countdown = 5, timeElapsed = 0;
	private int[] scores = new int[6];
	private int wave = 0, XP = 0;

	public PlayPane() {
		setStyle("-fx-background-color: rgb(45, 45, 100);");
		setWidth(1280);
		setHeight(720);
		setCursor(Cursor.CROSSHAIR);
		createCountdownLabel();
		createXPLabel();
		createGround();
		createMissileSilos();
		createBarracks();
		for (int i = 0; i < 3; i++) {
			siloCooldown[i] = 0.8;
		}

		this.setOnMouseMoved(new EventHandler<MouseEvent>() {
			@Override
			public void handle(MouseEvent event) {
				mouseX = event.getX();
				mouseY = event.getY();
			}
		});

		this.setOnKeyPressed((KeyEvent event) -> {
			String keyName = event.getCode().toString();
			if (!keyPressedList.contains(keyName)) {
				keyPressedList.add(keyName);
				keyJustPressedList.add(keyName);
			}

		});

		this.setOnKeyReleased((KeyEvent event) -> {
			String keyName = event.getCode().toString();
			if (keyPressedList.contains(keyName)) {
				keyPressedList.remove(keyName);
			}
		});

		AudioClip missileExplosion = new AudioClip(new File("sfx_exp_short_hard9.wav").toURI().toString());
		AudioClip pMissileExplosion = new AudioClip(new File("sfx_exp_short_hard10.wav").toURI().toString());
		AudioClip towerExplosion = new AudioClip(new File("sfx_sounds_impact9.wav").toURI().toString());
		gameTimer = new AnimationTimer() {
			public void handle(long nanotime) {

				switch ((int) countdown) {
				case 0:
					createCountdownAnimation(countdown, 1);
					break;
				case 1:
					createCountdownAnimation(countdown, 2);
					break;
				case 2:
					createCountdownAnimation(countdown, 3);
					break;

				}

				if (countdown > 0) {
					countdown -= (1 / 50.0);
					System.out.println(countdown);
				}

				// when the countdown ends, run the pixar animation magic lol
				if (countdown < 0) {
					lblCountdown.setVisible(false);
					// first wave of missiles
					if (timeElapsed == 0) {
						createMissile(10, 0);
						wave++;
					}
					// all other waves of missiles
					if (timeElapsed >= 10 * wave && (int) timeElapsed % wave == 0) {
						createMissile(20, wave);
						wave++;
					}

					if (keyJustPressedList.contains("DIGIT1") && siloCooldown[0] >= 0.25
							&& !siloList.get(0).destroyed()) {
						createPMissile(0);
					}

					if (keyJustPressedList.contains("DIGIT2") && siloCooldown[1] >= 0.25
							&& !siloList.get(1).destroyed()) {
						createPMissile(1);

					}

					if (keyJustPressedList.contains("DIGIT3") && siloCooldown[2] >= 0.25
							&& !siloList.get(2).destroyed()) {
						createPMissile(2);
					}

					for (int i = 0; i < 3; i++) {
						if (siloCooldown[i] < 0.25) {
							siloCooldown[i] += (1 / 50.0);
						}
					}

					for (MissileSprite missileSprite : missileSpriteList) {
						missileSprite.move(1 / 50.0);
					}

					for (PlayerMissileSprite pMissileSprite : pMissileSpriteList) {
						pMissileSprite.move(1 / 50.0);
					}

					// checks collisions for p-missiles
					try {
						for (PlayerMissileSprite pMissileSprite : pMissileSpriteList) {

							// if a p-missile collides with a missile
							for (MissileSprite missileSprite : missileSpriteList) {
								if (pMissileSprite.overlap(missileSprite)) {
									pMissileSprite.explode();
									missileSprite.takeDamage(pMissileSprite.getImpactDamage());
									XP += 100;
									lblXP.setText("XP: " + XP);
								}
							}

							// when a p-missile explodes
							if (pMissileSprite.getExplode()) {
								pMissileExplosion.play(0.05);
								pMissileSpriteList.remove(pMissileSprite);
								getChildren().remove(pMissileSprite);
							}

							// when a p-missile goes out of bounds
							if ((pMissileSprite.getX() < -30 && pMissileSprite.getY() < -30)
									|| (pMissileSprite.getX() > 750 && pMissileSprite.getY() < -30)) {
								pMissileSpriteList.remove(pMissileSprite);
								getChildren().remove(pMissileSprite);
							}
						}

					} catch (Exception e) {
						// possible exception: the p-missile does not exist
						// possible exception: the missile does not exist
					}

					// checks collision for missiles
					try {
						for (MissileSprite missileSprite : missileSpriteList) {

							// perform any checks if a missile is at or above Y = 600
							if (missileSprite.getY() >= 600) {
								try {

									// if a missile collides with a barracks
									for (BarracksSprite barracks : barracksList) {
										if (missileSprite.overlap(barracks)) {
											missileSprite.explode();
											missileExplosion.play(0.10);
											barracks.takeDamage(missileSprite.getImpactDamage());
										}
									}

									// if a missile collides with a missile silo
									for (MissileSiloSprite silos : siloList) {
										if (missileSprite.overlap(silos)) {
											missileSprite.explode();
											missileExplosion.play(0.10);
											silos.takeDamage(missileSprite.getImpactDamage());
										}
									}

								} catch (Exception e) {
									// possible exception: one of all of the barracks no longer exist
									// possible exception: one or all of the missile silos no longer exist
								}
							}

							// if a missile collides with the ground, make it explode and delete the sprite
							if (missileSprite.getY() + missileSprite.getHeight() >= 660) {
								missileSprite.explode();
								missileExplosion.play(0.10);
							}

							// if a missile explodes or is destroyed by the player, delete the sprite
							if (missileSprite.getExplode() || missileSprite.getHP() <= 0) {
								missileSpriteList.remove(missileSprite);
								getChildren().remove(missileSprite);
							}
						}
					} catch (Exception e) {

					}

					// checks if any barracks is destroyed
					try {
						for (BarracksSprite barracks : barracksList) {
							// only checks if a barracks is destroyed if its HP is below 200
							if (barracks.getHP() < 200) {
								if (barracks.destroyed() && getChildren().contains(barracks)) {
									getChildren().remove(barracks);
									towerExplosion.play(0.25);
								}
							}
						}

						for (MissileSiloSprite silos : siloList) {
							if (silos.getHP() < 150) {
								if (silos.destroyed() && getChildren().contains(silos)) {
									getChildren().remove(silos);
									towerExplosion.play(0.25);
								}
							}
						}

					} catch (Exception e) {
						// possible exception: one or all of the barracks no longer exist
						// possible exception: one or all of the silos no longer exist
					}

					// if all of the barracks and/or all of the silos are destroyed, end the game
					if (!getChildren().contains(barracksList.get(0)) && !getChildren().contains(barracksList.get(1))
							&& !getChildren().contains(barracksList.get(2))
							&& !getChildren().contains(barracksList.get(3))
							|| (!getChildren().contains(siloList.get(0)) && !getChildren().contains(siloList.get(1))
									&& !getChildren().contains(siloList.get(2)))) {
						gameTimer.stop();
						createEndGamePrompt();
					}
					keyJustPressedList.clear();
					timeElapsed += (1 / 50.0);

					System.out.println(timeElapsed + "\n");
				}
			}
		};
		gameTimer.start();

	}

	public void createCountdownLabel() {
		lblCountdown = new Label();
		lblCountdown.setFont(new Font("Arial", 50));
		lblCountdown.setMaxSize(30, 60);
		lblCountdown.setTextFill(Color.WHITE);
		lblCountdown.setTextAlignment(TextAlignment.CENTER);
		lblCountdown.setTranslateX(625);
		lblCountdown.setTranslateY(330);
		getChildren().add(lblCountdown);
	}

	public void createCountdownAnimation(double countdown, int i) {
		AudioClip blip = new AudioClip(new File("sfx_sounds_Blip9.wav").toURI().toString());
		lblCountdown.setText(Integer.toString((int) countdown + 1));
		if (countdown <= i && countdown >= i - 0.20) {
			blip.play(0.05);
		}
	}

	public void createXPLabel() {
		lblXP = new Label("XP: " + XP);
		lblXP.setFont(new Font("Arial", 50));
		lblXP.setMinSize(1000, 60);
		lblXP.setTextFill(Color.WHITE);
		lblXP.setTranslateX(20);
		lblXP.setTranslateY(20);
		getChildren().add(lblXP);
	}

	public void createGround() {
		ground = new Rectangle(0, 660, 1280, 60);
		ground.setFill(Color.rgb(140, 140, 110));
		getChildren().addAll(ground);
	}

	public void createBarracks() {
		for (int i = 0; i < 4; i++) {
			BarracksSprite barracks = new BarracksSprite(130 + i * 300);
			barracksList.add(barracks);
			getChildren().add(barracks);
		}
	}

	public void createMissileSilos() {
		for (int i = 0; i < 3; i++) {
			MissileSiloSprite silo = new MissileSiloSprite(0 + i * 600);
			siloList.add(silo);
			getChildren().add(silo);
		}
	}

	public void createMissile(int missileCount, int speedIncreaseFactor) {
		AudioClip missileAlarm = new AudioClip(new File("sfx_alarm_loop3.wav").toURI().toString());
		missileAlarm.play(0.20);
		int speed = speedIncreaseFactor;
		if (speedIncreaseFactor > 5) {
			speed = 5;
		}
		for (int i = 0; i < missileCount; i++) {
			MissileSprite missileSprite = new MissileSprite(randomFrom(20, 1260));
			missileSprite.setVelocity(missileSprite.getVelocity() + speed * 30);
			missileSpriteList.add(missileSprite);
			getChildren().add(missileSprite);
		}

	}

	public void createPMissile(int i) {
		MissileSiloSprite silos = siloList.get(i);
		if (mouseY > 560) {
			mouseY = 560;
		}
		mouseAngle = Math.atan2(silos.getY() - mouseY, mouseX - silos.getX() - 35);
		PlayerMissileSprite pMissileSprite = new PlayerMissileSprite(silos.getX() + 35, mouseX, mouseY, mouseAngle);
		pMissileSpriteList.add(pMissileSprite);
		getChildren().add(pMissileSprite);
		siloCooldown[i] = 0.00;
		String soundFile = "sfx_wpn_cannon4.wav";
		AudioClip siloExplosion = new AudioClip(new File(soundFile).toURI().toString());
		siloExplosion.play(0.10);
	}

	public void createGameOverLabel() {
		Label lblGameOver = new Label("GAME OVER!");
		lblGameOver.setFont(new Font("Arial", 100));
		lblGameOver.setMaxSize(650, 150);
		lblGameOver.setTextAlignment(TextAlignment.CENTER);
		lblGameOver.setTextFill(Color.WHITE);
		lblGameOver.setTranslateX(315);
		lblGameOver.setTranslateY(20);
		getChildren().add(lblGameOver);
	}

	public void createHighScoresLabel() {
		readHighScores();
		writeHighScores();
		Label lblHighScores = new Label("High Scores: \n" + Integer.toString(scores[5]) + "\n"
				+ Integer.toString(scores[4]) + "\n" + Integer.toString(scores[3]) + "\n" + Integer.toString(scores[2])
				+ "\n" + Integer.toString(scores[1]) + "\n");
		lblHighScores.setFont(new Font("Arial", 50));
		lblHighScores.setMaxSize(400, 300);
		lblHighScores.setTextAlignment(TextAlignment.CENTER);
		lblHighScores.setTextFill(Color.WHITE);
		lblHighScores.setTranslateX(440);
		lblHighScores.setTranslateY(200);
		getChildren().add(lblHighScores);
	}

	public void readHighScores() {
		try {
			FileReader fr = new FileReader(highScores);
			BufferedReader br = new BufferedReader(fr);
			String line;
			for (int i = 0; i < scores.length - 1; i++) {
				try {
					line = br.readLine();
					scores[i] = Integer.parseInt(line);
				} catch (Exception e) {
					// possible exception: there aren't any lines to read
					scores[i] = 0;
				}
			}
			scores[5] = XP;
			br.close();
		} catch (Exception e) {

		}
	}

	public void writeHighScores() {
		Arrays.sort(scores);
		try {
			FileWriter fw = new FileWriter(highScores);
			BufferedWriter bw = new BufferedWriter(fw);
			try {
				for (int i = 5; i > 0; i--) {
					bw.write(Integer.toString(scores[i]));
					bw.newLine();
				}
			} catch (Exception e) {

			}
			bw.close();
		} catch (Exception e) {

		}
	}

	public void createEndGamePrompt() {
		createGameOverLabel();
		createHighScoresLabel();
	}

	public double randomFrom(int low, int high) {
		// RNG
		int randNum = 0;
		randNum = (int) (Math.random() * (high - low) + low);
		return randNum;
	}

}