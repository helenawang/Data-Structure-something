package util;

import java.io.*;
import java.nio.charset.*;
import java.util.*;

import common.*;

/**
 * @function 预处理源程序（去除空白符、注释、字符串常量）
 * @author helena
 *
 */
public class FilterSource {
	Scanner scanner;
	Source src;
	List<String> ls;
	public FilterSource(String filename) throws Exception{
		//先不考虑合并目录下的所有文件问题，先假定都在一个文件中
		src = new Source(filename);
		scanner = new Scanner(new InputStreamReader(new FileInputStream(filename), StandardCharsets.UTF_8));
		loadToList();
	}
	public void loadToList() throws Exception{
		ls = src.ls;//这一步在设计上似乎有缺陷
		System.out.println("****开始按空白符切分，载入数组****");
		long n = 0;
		while(scanner.hasNext()){
			ls.add(scanner.next());
			n++;
		}
		System.out.println("****载入结束共读入 " + n + "个单词****");
		writeList("data/output/deleteSpace.txt");
	}
	
	//把当前的单词list输出到文件
	public void writeList(String filename){
		PrintWriter out;
		try {
			out = new PrintWriter(filename);
			for(String str: ls){
				out.println(str);
			}
			out.close();
			System.out.println("共 " + ls.size() + " 个单词，写入 " + filename);
		} catch (FileNotFoundException e) {
			System.out.println(filename + "文件不存在");
		}
	}
	
	public void filterComment(){
		filterLabel("/*", "*/");
		System.err.println("****comment deleted****");
	}
	
	//过滤掉标签内的内容
	private int filterLabel(String prefix, String suffix){
		int cnt = 0;
		//自动机
		int state = 1;
		Iterator<String> it = ls.iterator();
		String str;
		while(it.hasNext()){
			str = it.next();
			if(state == 1){//在标签外
				if(str.startsWith(prefix)){//遇到开始标签
					cnt++;//计数
					state = 2;
					it.remove();
				}else ;
			}else{//在标签内
				if(str.endsWith(suffix)){//遇到结束标签
					state = 1;
					it.remove();
				}else it.remove();//删除标签内的内容
			}
		}
		return cnt;
	}
	
	public void filterConstantString(){//过滤字符串常量，完全照搬过滤注释的方法
		int cnt = filterLabel("\"", "\"");
		System.err.println("****constant string deleted, total + " + cnt + " segments****");
	}
	public void filterByLength(){//根据长度过滤，主要是括号、标点、过长的变量名和表达式。这一步是否应该计入统计阶段？
		Iterator<String> it = ls.iterator();
		while(it.hasNext()){
			String str = it.next();
			if(str.length() < 2 || str.length() > 8) it.remove();
		}
		System.err.println("****filtered by length****");
	}
	public void filterAll() throws Exception{
		filterComment();
		writeList("data/output/deleteComment.txt");
		filterConstantString();
		writeList("data/output/deleteConstantString.txt");
		filterByLength();
		writeList("data/output/filterByLength.txt");
	}
	public static void main(String[] args) throws Exception {
		FilterSource fs = new FilterSource("data/test.c");
		fs.filterAll();
	}
}
