package util;

import java.io.*;
/**
 * @function 预处理源程序
 * @author helena
 *
 */
public class Preprocess {
	public Preprocess() throws Exception{
		this("data/src.c", "data/src_preprocessed.txt");
	}
	public Preprocess(String inname, String outname) throws Exception{
		//从文件读入源程序
		FilterSource fs = new FilterSource(inname);
		System.out.println("***进行初步过滤***");
		fs.filterAll();//做初步过滤
		fs.writeList(outname);//过滤后的源程序写入文件
	}
	public static void main(String[] args) throws Exception {
		Preprocess preprocess = new Preprocess("data/src.c", "data/src_preprocessed.txt");
	}
}
