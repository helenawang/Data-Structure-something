package main;

import java.util.List;

import model.ACA;

public class Count {
	static int time_ms = 0;
	/**
	 * 默认实现
	 * @param words
	 * @param keywords
	 * @return
	 */
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
		time_ms = (int)(end - start);
		System.out.println("统计完成， 用时 " + time_ms + " ms");
		return results;
	}
	public static int[] countUsingACA(List<String> words, String[] keywords, ACA aca) {
		long start = System.currentTimeMillis();
		int[] results = new int[keywords.length];
		for(int i=0; i<keywords.length; i++) {
			results[i] = 0;
		}
		for(String word: words) {
//			System.out.println("matching text " + word);
			int[] partial_result = aca.match(word, keywords.length);
			for(int i=0; i<keywords.length; i++) {
				results[i] += partial_result[i];
			}
		}
		long end = System.currentTimeMillis();
		time_ms = (int)(end - start);
		System.out.println("统计完成， 用时 " + time_ms + " ms");
		return results;
	}
	public static void main(String[] args) {
		
	}
}
