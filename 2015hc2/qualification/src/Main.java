import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;


public class Main {

	public static void main(String[] args) {
		int shipPos = -1;
		int invI = 0;
		int[] invaders = new int[500];
		//Input
		try(BufferedReader reader = new BufferedReader(new FileReader("generated70.txt"))){
			do {
				String line = reader.readLine();
				int i = line.length() - 1;
				while(i >= 0){
					if(line.charAt(i) == 'v'){
						invaders[invI++] = i;
						break;
					}
					if(line.charAt(i) == 'A'){
						shipPos = i;
						break;
					}
					--i;
				}
			} while(shipPos < 0);
		} catch (IOException e) {
			e.printStackTrace();
		}
		//Process & Output
		while(invI > 0){
			int diff = invaders[--invI] - shipPos;
			System.out.print(
				//Number
				(Math.abs(diff) > 0 ? Math.abs(diff) : "") +
				//Left/Right
				(diff > 0 ? "r" : (diff < 0 ? "l" : "")) +
				//Shoot
				"s");
			shipPos = invaders[invI];
		}
	}

}
