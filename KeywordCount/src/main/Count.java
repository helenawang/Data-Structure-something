package main;

import java.util.List;

public class Count {
	public static int[] count(List<String> words, String[] keywords) {
		long start = System.currentTimeMillis();
		int[] results = new int[keywords.length];
		int cur = 0;//游标
		for(String keyword: keywords) {
			for(String word: words) {//这样与用迭代器的差别？
				if(word.equals(keyword)) {
					results[cur]++;
				}
			}
			cur++;
		}
		long end = System.currentTimeMillis();
		System.out.println("统计完成， 用时 " + (int)(end - start) + " ms");
		return results;
	}
	public static void main(String[] args) {
		
	}
}
