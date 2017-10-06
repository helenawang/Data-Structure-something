package main;

import java.util.List;

public class Main {
	//程序入口
	public static void main(String[] args) {
		String sourcefile = "data/merge.c";
		String keywordsfile = "data/keywords.txt";
		//预处理源程序文本
		List<String> words = Preprocess.preprocessFile(sourcefile);
//		for(String word: words) {
//			System.out.println(word);
//		}
		
		//建立关键字查找结构
		String[] keywords = BuildIndex.buildIndexFromFile(keywordsfile);
//		for(String keyword: keywords) {
//			System.out.println(keyword);
//		}
		
		//计数
		int[] results = Count.count(words, keywords);
		for(int i=0; i<keywords.length; i++) {
			System.out.println(keywords[i] + ": " + results[i]);
		}
	}

}
