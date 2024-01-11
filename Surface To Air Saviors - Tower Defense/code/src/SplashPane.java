// ***************************************************************
// Name: Milan Haruyama
// Date: 28 March 2021
//
// CS 225, Section 02, Surface-To-Air Saviors: Tower Defense
//
// This is the code for the game's splash pane.
// ***************************************************************

import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;
import javafx.scene.text.Font;

public class SplashPane extends Pane {
	private Button btGoToPlayPane;
	private Label info;

	public SplashPane() {
		setWidth(1280);
		setHeight(720);
	}

	public void setInfoLabel(Label newLabel) {
		info = newLabel;
		info.setText("Welcome to Surface-To-Air Saviors: Tower Defense! \n"
				+ "You are in command of a military base's defenses, three missile silos. It is up to you to defend the four barracks on base from \n"
				+ "an endless onslaught of enemy airstrikes for as long as you can. \n\n"
				+ "Each missile silo is controlled via the '1', '2', and '3' keys, and are aimed with your crosshair. \n\n"
				+ "If your towers get destroyed, they're gone for good, so make sure you protect them! \n\n"
				+ "The game ends when all of your barracks or silos are destroyed. \n\n"
				+ "Your XP will be based off of how many missiles you destroy, so destroy as many as you can! \n\n"
				+ "Godspeed, Commander!");
		info.setFont(new Font("Arial", 20));
		info.setStyle("-fx-text-fill: white;");
		info.setMaxSize(1200, 320);
		info.setTranslateX(40);
		info.setTranslateY(40);
		getChildren().add(info);
	}

	public void setbtGoToPlayPane(Button btNewButton) {
		btGoToPlayPane = btNewButton;
		btGoToPlayPane.setStyle("-fx-background-radius: 160;" + "-fx-background-color: red;"
				+ "-fx-background-insets: 0px;" + "-fx-padding: 0px;");
		btGoToPlayPane.setText("LAUNCH");
		btGoToPlayPane.setFont(new Font("Arial", 60));
		btGoToPlayPane.setMinSize(320, 320);
		btGoToPlayPane.setTranslateX(480);
		btGoToPlayPane.setTranslateY(360);
		getChildren().add(btGoToPlayPane);
	}

}
