package main;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;

public class BuildIndex {
	static String[] keywords;
	public static String[] buildIndexFromFile(String filename) {
		return buildArray(filename);
	}
	
	private static String[] buildArray(String filename) {
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
		System.out.println("建立索引完成，用时 " + (int)(end - start) + " ms");
		return keywords;
	}
	public static void main(String[] args) {
		String filename = "data/keywords.txt";
		BuildIndex.buildIndexFromFile(filename);
	}

}
