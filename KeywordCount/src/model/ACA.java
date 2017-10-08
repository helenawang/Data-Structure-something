package model;

import java.util.*;

/**
 * Aho-Corasick Automation, referring to Aho & Corasick's paper
 * @author helena wang
 *
 */
public class ACA {
	private static int FAILURE = -1;
	private static int MAX_STATE = 256;
	private static char[] SIGMA;
	{//fill sigma
		SIGMA = new char[26];
		for(int i=0; i<26; i++) {
			SIGMA[i] = (char) ((int)'a' + i);
		}
	}
	private int[][] gotoArray;
	{//init root node (state 0)
		gotoArray = new int[MAX_STATE][];//预留这么多状态节点
		gotoArray[0] = new int[SIGMA.length];//留出虚拟节点的存储空间
		for(int i=0; i<26; i++) {//全部初始化为failure
			gotoArray[0][i] = FAILURE;
		}
	}
	private List<List<Integer>> outputArrayIndex = new ArrayList<List<Integer>>();//这个直接记录关键字所在的秩，方便统计
	{
		for(int i=0; i<MAX_STATE; i++) {//开辟所有状态的list的空间
			outputArrayIndex.add(new ArrayList<Integer>());
		}
	}
	private List<List<String>> outputArray = new ArrayList<List<String>>();//Java不支持泛型数组，这里用二维的arraylist代替
	{
		for(int i=0; i<MAX_STATE; i++) {//开辟所有状态的list的空间
			outputArray.add(new ArrayList<String>());
		}
	}
	private int[] failureArray;
	{
		failureArray = new int[MAX_STATE];
	}
	private int[] failureArrayGeneral;
	private int goTo(int state, char a) {
		return gotoArray[state][getCharIndex(a)];
	}
	private int failure(int state) {
		return failureArray[state];
	}
	private List<String> output(int state) {
		return outputArray.get(state);
	}
	private List<Integer> outputIndex(int state) {
		return outputArrayIndex.get(state);
	}
	private int falureGeneral(int state) {
		return failureArrayGeneral[state];
	}
	private Queue<Integer> queue;//构建failure表使用
	/**
	 * 对外调用接口，匹配
	 * @param x 长文本
	 * @param n 关键字的个数
	 */
	public int[] match(String x, int n) {
		int[] results = new int[n];
		for(int i=0; i<n; i++) {
			results[i] = 0;
		}
		int state = 0;
		for(int i=0; i<x.length(); i++) {
			char a = x.charAt(i);
			while(goTo(state, a) == FAILURE) {//沿失败链回溯
				state = failure(state);
			}
			state = goTo(state, a);//状态转换成功
			List<String> hits = output(state);
			List<Integer> hitsIndex = outputIndex(state);
			if(hits != null && hits.size() > 0) {//命中了关键字
				int cnt = hits.size();
//				System.out.println("got " + cnt + " hits");
				for(int j=0; j<cnt; j++) {
//					System.out.println(hits.get(j));
//					System.out.println(hitsIndex.get(j));
					results[hitsIndex.get(j)]++;//累加
				}
			}
		}
		return results;
	}
	/**
	 * 构建goto表
	 * 照着论文写的，还不是很理解
	 * @param keywords
	 */
	public void buildGoto(String[] keywords) {
		int new_state = 0;//假设这个keyword从new_state开始产生新节点(状态)
		int k = keywords.length;
		for(int i=0; i<k; i++) {//insert all k keywords
//			System.out.println("entering keyword " + keywords[i]);
			new_state = enterKeyword(i, keywords[i], new_state);
		}
		for(int i=0; i<SIGMA.length; i++) {//state 0添加自环
			char a = SIGMA[i];
			if(goTo(0, a) == FAILURE) {
				gotoArray[0][getCharIndex(a)] = 0;
			}
		}
	}
	/**
	 * 添加关键字一个
	 * 照着论文写的，还不是很理解
	 * @param keyword
	 * @param new_state 新状态的起始值，即指针末尾
	 */
	private int enterKeyword(int index, String keyword, int new_state) {
		int state = 0, j = 0;//注意论文中字符串下标是从1开始的！
		char a = keyword.charAt(j);
		while(goTo(state, a) != FAILURE) {//有公共前缀
//			System.out.println("公共前缀字符 " + a);
			state = goTo(state, a);
			j++;
			a = keyword.charAt(j);
		}
		for(int p=j; p<keyword.length(); p++) {
			a = keyword.charAt(p);
//			System.out.println("新字符 " + a);
			new_state++;
			gotoArray[state][getCharIndex(a)] = new_state;//从state节点上长出new_state节点
//			System.out.println("goto(" + state + ", " + a + ") = " + goTo(state, a));
			createNodes(new_state);//预留下一批子节点的空间
			state = new_state;
		}
		outputArray.get(state).add(keyword);
		outputArrayIndex.get(state).add(index);
		return new_state;//再把指针的值回传
	}
	/**
	 * 构建failure表和output表
	 * 照着论文写的，还不是很理解
	 */
	public void buildFailure() {
		queue = new LinkedList<Integer>();//链表实现的队列
		for(int i=0; i<SIGMA.length; i++) {//init depth 1 states' failure array
			char a = SIGMA[i];
			int s = goTo(0, a);
			if(s != 0) {
				queue.offer(s);
				failureArray[s] = 0;
			}
		}
		while(!queue.isEmpty()) {//BFS
			int r = queue.poll();
			for(int i=0; i<SIGMA.length; i++) {
				char a = SIGMA[i];
				int s = goTo(r, a);
				if(s != FAILURE) {
					queue.offer(s);
					int state = failure(r);
					while(goTo(state, a) == FAILURE) {//和匹配过程是雷同的
						state = failure(state);
					}
					failureArray[s] = goTo(state, a);
					outputArray.get(s).addAll(output(failure(s)));
					outputArrayIndex.get(s).addAll(outputIndex(failure(s)));//同时维护一个字符串list和一个整型list
				}
			}
		}
	}
	/**
	 * 对failure表的优化，去除多余比较
	 * 论文中没有以伪码形式给出算法，先不实现这个了
	 */
	private void buildFailureGeneral() {
		
	}
	/**
	 * 把字母a-z映射到整数0-25
	 * @param a
	 * @return
	 */
	private int getCharIndex(char a) {
		return (int)(a - 'a');
	}
	/**
	 * 为state的子节点预留空间
	 * @param state
	 */
	private void createNodes(int state) {
		gotoArray[state] = new int[SIGMA.length];//留出虚拟节点的存储空间
		for(int i=0; i<26; i++) {//全部初始化为failure
			gotoArray[state][i] = FAILURE;
		}
	}
	public void printFailureTable() {
		for(int i=0; i<MAX_STATE; i++) {
			System.out.println("f(" + i + ") = " + failure(i));
		}
	}
	public void printGotoTable() {
		for(int i=0; i<MAX_STATE; i++) {
			for(int j=0; j<SIGMA.length; j++) {
				System.out.println("goto(" + i + ", " + SIGMA[j] + ") = " + goTo(i, SIGMA[j]));
			}
		}
	}
	public static void main(String[] args) {
		String[] keywords = { "he", "she", "his", "hers" };
		ACA aca = new ACA();
		aca.buildGoto(keywords);
		aca.buildFailure();
//		System.out.println("goto table---------------------");
//		aca.printGotoTable();
//		System.out.println("failure table------------------");
//		aca.printFailureTable();
		System.out.println("matching results------------------");
		int[] results = aca.match("ushers", keywords.length);
		for(int i=0; i<keywords.length; i++) {
			System.out.println(keywords[i] + " : " + results[i]);
		}
	}

}
