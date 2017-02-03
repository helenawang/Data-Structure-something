package common;

public class Keyword {
	public final static int RADIX = 27;//26个小写字母+1个下划线，构成字符表
	private String string;//关键字的字面值
	private int id;//内部编号
	public int getId() {
		return id;
	}
	private long fingerPrint;//指纹
	
	public String getString() {
		return string;
	}
	public long getFingerPrint() {
		return fingerPrint;
	}
	public Keyword(){
		this("", 0);
	}
	public Keyword(String str, int id){
		string = str;
		fingerPrint = calFingerPrint();
		this.id = id;
	}
	public long calFingerPrint(){//目前的实现策略是当作一个27进制的数来算
		long rs = 0;
		for(int i = 0; i < string.length(); i++){
			rs *= RADIX;
			rs += string.charAt(i) - 'a';
		}
		return rs;
	}
	public static void main(String[] args) {
		Keyword keyword = new Keyword("if", 1);
		System.out.println("the fingerPrint of " + keyword.getString() + "is " + keyword.getFingerPrint());
	}
}
