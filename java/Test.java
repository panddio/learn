/*
public class Test {
	void max(int a , int b) {
		System.out.println( a > b ? a : b );
	}
	
	void max(short a , short b) {
		System.out.println("short");
		System.out.println( a > b ? a : b );
	}
	
	void max(float a, float b) {
		System.out.println( a > b ? a : b );
	}
	
	public static void main(String[] args) {
		Test t = new Test();
		t.max(3, 4);
		//short a = 3;
		//short b = 4;
		t.max((short)3, (short)4);
	}
}*/
public class Test {
	public static void main(String[] args) {
		
		int i,j;
		int a[][]={{1,2},{3,4,5},{6},{7,8,9,0,}};
		String s[][];
		s = new String[3][];
		s[0] = new String[2];
		s[1] = new String[3];
		s[2] = new String[4];
		
		for(i=0;i < a.length;i++) {
			for(j=0; j < a[i].length;j++) {
				System.out.print("a["+i+"]["+j+"] = "+a[i][j]+"  ");
			}
			System.out.println();
		}
		
		for(i=0;i < s.length;i++) {
			for(j=0; j < s[i].length;j++) {
				s[i][j] = new String("我的位置是："+i+","+j+"  ");
			}
		}

		for(i=0;i < s.length;i++) {
			for(j=0; j < s[i].length;j++) {
				System.out.print(s[i][j]+"  ");
			}
			System.out.println();
		}
	}
}