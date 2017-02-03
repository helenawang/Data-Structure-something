package util;

import java.util.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import common.*;

/**
 * @function 构建关键字的查找结构
 * @author helena
 *
 */
public class BuildKeywords {
	int num;
	ArrayList<String> keywords;//循秩访问，按读入顺序做内部编号0-31
	public int getNum() {
		return num;
	}
	public HashMap<Long, Keyword> map;//这是最终使用的查找结构,key为计算得到的指纹，value为这个keyword的信息
	BuildKeywords(String filename) throws IOException{
		num = 0;
		map = new HashMap<Long, Keyword>();
		keywords = new ArrayList<String>();
		BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(filename), StandardCharsets.UTF_8));
		
		//文件内容格式：一行一个关键字。故逐行读取
		String line;
		while((line = br.readLine()) != null){
			Keyword keyword = new Keyword(line, num);
			map.put(keyword.getFingerPrint(), keyword);
			keywords.add(line);
			++num;
		}
		br.close();
		System.out.println("totally " + num + " keywords");
	}
	public static void main(String[] args) throws IOException {
		BuildKeywords bk = new BuildKeywords("data/keywords.txt");
	}
}
