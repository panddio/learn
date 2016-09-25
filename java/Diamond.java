public class Diamond {
	public static void main(String[] args) {
		printHollowRhombus(11);
	}
	
	public static void printHollowRhombus(int size) {
		int i, j;
		
		if(size % 2 == 0)
			size++;
		
		for(i = 0; i < (size/2 + 1); i++) {
			for(j = size/2 + 1; j > i +1; j--) {
				System.out.print(" ");
			}
			for(j = 0; j < 2 * i + 1; j++) {
				if(j == 0 || j == 2 * i)
					System.out.print("*");
				else
					System.out.print(" ");
			}
			System.out.println("");
		}
		
		for(i = size/2 + 1; i < size; i++) {
			for(j = 0; j < i - size/2; j++) {
				System.out.print(" ");
			}
			for(j = 0; j < 2 * size - 1 - 2 * i; j++) {
				if(j == 0 || j == 2 * (size - i - 1))
					System.out.print("*");
				else
					System.out.print(" ");
			}
			System.out.println("");
		}
	}
}