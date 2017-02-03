package util;

import java.io.*;
import java.nio.charset.StandardCharsets;

import common.FingerPrint;
import common.Keyword;

public class Count {
	int[] bucket;
	Count(){
		this(32);//C语言
	}
	Count(int size){
		bucket = new int[size];
	}
	public static void main(String[] args) throws Exception {
		//把关键字建成查找结构
		BuildKeywords bk = new BuildKeywords("data/keywords.txt");

		//开始对源程序的单词逐一判断、统计
		Count cnt = new Count(bk.getNum());
		
		//预处理源程序
		Preprocess preprocess = new Preprocess("data/merge/outside.c", "data/src_preprocessed.txt");
		
		//读入预处理后的源程序
		BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream("data/src_preprocessed.txt"), StandardCharsets.UTF_8));
		
		long start = System.currentTimeMillis();//开始计时
		//进行统计
		String str;
		while((str = br.readLine()) != null){
			long fingerPrint = FingerPrint.getFingerPrint(str);
			Keyword hit = bk.map.get(fingerPrint);
			if(hit != null){
				if(hit.getString().equals(str)){//精确命中
					//System.out.println("find a " + str);
					cnt.bucket[hit.getId()]++;
				}
			}
		}
		long end = System.currentTimeMillis();//结束计时
		System.out.println("统计用时 " + (end - start) + "ms");
		System.out.println("****统计结果****");
		//输出结果
		for(int i=0; i<cnt.bucket.length; i++){
			if(cnt.bucket[i] > 0){
				System.out.printf("%8s : %d\n", bk.keywords.get(i), cnt.bucket[i]);
			}
		}
	}
}
