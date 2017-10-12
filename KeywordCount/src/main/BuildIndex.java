package main;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import model.ACA; 

public class BuildIndex {
	static String[] keywords;
	static int time_ms = 0;
	/**
	 * 默认实现
	 * @param filename
	 * @return
	 */
	public static String[] buildIndexFromFile(String filename) {
		return buildArray(filename);
	}
	
	public static String[] buildArray(String filename) {
		long start = System.currentTimeMillis();
		String contents;
		try {
			contents = new String(Files.readAllBytes(Paths.get(filename)), StandardCharsets.UTF_8);
			keywords = contents.split("\\s+");//难道我用不是回车符？？从github上粘下来后有问题了
//			System.out.println(keywords.length);
//			for(String keyword: keywords) {
//				System.out.println(keyword);
//			}
		} catch (IOException e) {
			System.err.println("read file [" + filename + "] fail!");
			e.printStackTrace();
		}
		long end = System.currentTimeMillis();
		time_ms = (int)(end - start);
		System.out.println("建立索引完成，用时 " + time_ms + " ms");
		return keywords;
	}
	/**
	 * ACA自动机实现索引
	 * @param filename
	 * @return
	 */
	public static ACA buildACA(String filename) {
		long start = System.currentTimeMillis();
		String contents;
		try {
			contents = new String(Files.readAllBytes(Paths.get(filename)), StandardCharsets.UTF_8);
			keywords = contents.split("\\s+");//难道我用不是回车符？？从github上粘下来后有问题了
//			System.out.println(keywords.length);
//			for(String keyword: keywords) {
//				System.out.println(keyword);
//			}
		} catch (IOException e) {
			System.err.println("read file [" + filename + "] fail!");
			e.printStackTrace();
		}
		long end = System.currentTimeMillis();
		ACA aca = new ACA();
		aca.buildGoto(keywords);
		aca.buildFailure();
		time_ms = (int)(end - start);
		System.out.println("建立索引完成，用时 " + time_ms + " ms");
		return aca;
	}
	public static void main(String[] args) {
		String filename = "data/keywords.txt";
		ACA aca = BuildIndex.buildACA(filename);
		int[] results = aca.match("structuresizeof", keywords.length);
		for(int i=0; i<keywords.length; i++) {
			System.out.println(keywords[i] + " : " + results[i]);
		}
	}

}
