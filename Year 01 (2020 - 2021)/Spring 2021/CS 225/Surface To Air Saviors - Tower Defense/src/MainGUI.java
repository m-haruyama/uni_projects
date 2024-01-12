// ***************************************************************
// Name: Milan Haruyama
// Date: 28 March 2021
//
// CS 225, Section 02, Surface-To-Air Saviors: Tower Defense
//
// This is the code for the game's main GUI
// ***************************************************************

import java.io.File;

import javafx.application.Application;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;
import javafx.scene.media.AudioClip;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class MainGUI extends Application {
	private BorderPane topPane = new BorderPane();
	private SplashPane splashPane = new SplashPane();
	private PlayPane playPane;
	private Button btGoToStartPane = new Button();
	private Label startInfo = new Label();

	@Override
	public void start(Stage primaryStage) {
		topPane.setCenter(splashPane);
		splashPane.requestFocus();
		splashPane.setStyle("-fx-background-color: black;");
		splashPane.setInfoLabel(startInfo);
		btGoToStartPane.setOnAction(e -> startGame());
		splashPane.setbtGoToPlayPane(btGoToStartPane);
		Scene scene = new Scene(topPane, 1280, 720);
		primaryStage.setTitle("Surface-To-Air Saviors: Tower Defense");
		primaryStage.setResizable(false);
		primaryStage.setScene(scene);
		primaryStage.show();
	}

	public void startGame() {
		playPane = new PlayPane();
		topPane.setCenter(playPane);
		playPane.requestFocus();
		AudioClip startSound = new AudioClip(new File("sfx_lowhealth_alarmloop7.wav").toURI().toString());
		startSound.play(0.25);
	}

	public static void main(String[] args) {
		try {
			launch(args);
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			System.exit(0);
		}

	}

}
