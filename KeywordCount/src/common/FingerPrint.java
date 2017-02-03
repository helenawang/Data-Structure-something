package common;

public class FingerPrint {
	public static long getFingerPrint(String string){
		long rs = 0;
		for(int i = 0; i < string.length(); i++){
			rs *= Keyword.RADIX;
			rs += string.charAt(i) - 'a';
		}
		return rs;
	}
}
