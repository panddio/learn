public class TestVar {
	
	static int j;
	
	public void m() {
		int i = 1;
		System.out.println(i);
	}
	
	public static void main(String[] args) {
		int i = 0; 
		System.out.println(i);
		System.out.println(j);
		
		TestVar T = new TestVar();
		T.m();
		
		boolean b = true;
		if(b) {
			int c = 1;
			System.out.println("b is true");
		}
		
		//System.out.println(c);
		
		long longNum1 = 8888888888888L;
	}
}