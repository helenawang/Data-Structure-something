package main;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;

/**
 * 预处理，源程序到词表
 * @author helena
 * 2017-fall
 */
public class Preprocess {
	static String delimiters = "\\s+";//分隔符：应为一个或多个空格、TAB、回车；看来\s包括了回车和TAB?

	/**
	 * 预处理对外接口，从源程序到过滤后的词表
	 * @param filename
	 * @return
	 */
	public static List<String> preprocessFile(String filename) {
		List<String> words = null;
		try {
			//从文件读入所有字符到一个String（太长的文本--有30MB多，会内存溢出吧，改成流式的更合适）
			String contents = new String(Files.readAllBytes(Paths.get(filename)), StandardCharsets.UTF_8);
//			System.out.println("读入源程序--------------------");
//			System.out.println(contents);
			
			//去除单行注释
			String contentsDeleteSC = deleteSingleLineComment(contents);
//			System.out.println("去除单行注释后---------------------");
//			System.out.println(contentsDeleteSC);
			
			//去除/*形式的注释
			String contentsDeleteComment = deleteComment(contentsDeleteSC);
//			System.out.println("去除/**/注释后---------------------");
//			System.out.println(contentsDeleteComment);
			
			//去除字符串常量
			String contentsDeleteStringConstant = deleteStringConstant(contentsDeleteComment);
//			System.out.println("去除字符串常量后---------------------");
//			System.out.println(contentsDeleteStringConstant);
			
			//去除标点，用空格替换
			String contentsDeletePunctuation = deletePunctuation(contentsDeleteStringConstant);
//			System.out.println("去除标点后-------------------------");
//			System.out.println(contentsDeletePunctuation);
			
			//按空白符切分成词链表
			words = Arrays.asList(contentsDeletePunctuation.split(delimiters));
//			for(String word: words) {
//				System.out.println(word);
//			}
		} catch (IOException e) {
			System.err.println("read file [" + filename + "] fail!");
			e.printStackTrace();
		}
		return words;
	}
	
	public static void preprocess() {
		
	}
	
	/**
	 * 去除单行注释-DFA实现
	 * @param 源程序String
	 * @return 替换单行注释为回车后的源程序String
	 */
	private static String deleteSingleLineComment(String contents) {
		StringBuilder stringBuilder = new StringBuilder();//result
		int state = 0;//初始在状态0
		char[] charArray = contents.toCharArray();
		for(char c: charArray) {
			//有限自动机
			switch(state) {
			case 0: 
				if(c == '/') {//可能构成单行注释
					state = 1;//注意这里没保留单斜杠，在状态1时再按情况决定是否追加
				}else {//非单行注释内容，保留
					stringBuilder.append(c);
				}
				break;
			case 1:
				if(c == '/') {//双斜杠，构成单行注释
					state = 2;
				}else {//单斜杠，未构成单行注释
					state = 0;
					stringBuilder.append('/');//把上个没保留的单斜杠加进来
					stringBuilder.append(c);//非单行注释内容，保留
				}
				break;
			case 2:
				if(c == '\n') {//抵达单行注释结尾，保留一个\n
					state = 0;
					stringBuilder.append(c);
				}else {//单行注释内容，不保留
					
				}
				break;
			}
		}
		return stringBuilder.toString();
	}
	
	/**
	 * 去除标点符号
	 * @param words
	 */
	private static String deletePunctuation(String contents) {
		StringBuilder stringBuilder = new StringBuilder();
		char[] charArray = contents.toCharArray();
		for(char c: charArray) {
			int asc = (int)c;
			if(asc >= 33 && asc <= 47
			|| asc >= 58 && asc <= 64
			|| asc >= 91 && asc <= 96) {
				stringBuilder.append(' ');
			}else {
				stringBuilder.append(c);
			}
		}
		return stringBuilder.toString();
	}
	
	/**
	 * 去除/* 形式的注释
	 * @前提：已去除//的单行注释
	 * @param contents
	 * @return
	 */
	private static String deleteComment(String contents) {
		StringBuilder stringBuilder = new StringBuilder();
		int state = 0;
		char[] charArray = contents.toCharArray();
		for(char c: charArray) {
			switch(state) {
			case 0:
				if(c == '/') {
					state = 1;
				}else {//处于注释外，保留
					stringBuilder.append(c);
				}
				break;
			case 1:
				if(c == '*') {//进入注释
					state = 2;
				}else {//处于注释外，保留
					state = 0;
					stringBuilder.append(c);
				}
				break;
			case 2:
				if(c == '*') {
					state = 3;
				}else {//处于注释内，不保留
					
				}
				break;
			case 3:
				if(c == '/') {//一段完整的注释结束
					state = 0;
				}else {//处于注释内，不保留
					state = 2;
				}
				break;
			}
		}
		return stringBuilder.toString();
	}
	
	/**
	 * 去除字符串常量
	 * @param contents
	 * @return
	 */
	private static String deleteStringConstant(String contents) {
		StringBuilder stringBuilder = new StringBuilder();
		int state = 0;
		char[] charArray = contents.toCharArray();
		for(char c: charArray) {
			switch(state) {
			case 0:
				if(c == '\"') {//进入字符串常量
					state = 1;
				}else {//在字符串常量外部
					stringBuilder.append(c);
				}
				break;
			case 1:
				if(c == '\"') {//结束字符串常量
					state = 0;
				}else {//在字符串常量内部
					
				}
				break;
			}
		}
		return stringBuilder.toString();
	}
	
	/**
	 * 单元测试
	 * @param args
	 */
	public static void main(String[] args) {
		String filename = "data/source.c";
		Preprocess.preprocessFile(filename);
	}
}
