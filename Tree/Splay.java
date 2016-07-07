package algorithm;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Splay {
	class Node{
		int val;//节点的兴趣值
		long totalVal;//子树的总兴趣值
		int num;//子树的节点数
		int lazy;
		
		int k;//id 互异的关键码
		Node l, r;
		Node p;
		Node(){
			k = 0;
			p = l = r = null;
			val = 0;
			totalVal = 0;
			lazy = 0;
			num = 0;
		}
		Node(int kk, Node pp, int v){
			k = kk;
			p = pp;
			val = v;
			l = r = null;
			num = 0;
			totalVal = 0;
			lazy = 0;
		}
		void update(){//重新统计子树信息，不递归，假定孩子已统计好
			num = 1;//自身
			totalVal = val;
			if(l != null){
				num += l.num;
				totalVal += l.totalVal;
			}
			if(r != null){
				num += r.num;
				totalVal += r.totalVal;
			}
		}
		void mark(int delta){//delta值加到此节点上，打lazy标记，不下放
			lazy += delta;
			totalVal += num*delta;
			val += delta;
		}
		void send(){//向孩子传递，一层
			//System.out.println(k + " lazy is " + lazy);
			if(l != null) l.mark(lazy);
			if(r != null) r.mark(lazy);
			lazy = 0;
			update();//更新当前节点的统计值，是否有必要？num不变，totalVal在打lazy标记时已更新，val不变
		}
	}
	
	Node root;
	Node _hot;
	Splay(){
		root = _hot = null;
	}
	Splay(int k){
		root = new Node(k, null, 0);
		_hot = root;
	}
	void zig(Node cur){
		if(cur == null) return ;
		//System.out.println("zig "+cur.k);
		Node v = cur.l;
		if(v == null) return ;
		Node g = cur.p;
		
		v.send();
		cur.send();
		
		v.p = g;
		if(g != null){
			if(cur == g.l) g.l = v;
			else g.r = v;
		}
		
		cur.l = v.r;
		if(cur.l != null) cur.l.p = cur;
		
		cur.p = v;
		v.r = cur;
		if(cur == root) root = v;
		
		v.update();
		cur.update();
	}
	void zag(Node cur){
		if(cur == null) return ;
		//System.out.println("zag "+cur.k);
		Node v = cur.r;
		if(v == null) return ;
		Node g = cur.p;
		
		v.send();
		cur.send();
		
		v.p = g;
		if(g != null){
			if(cur == g.l) g.l = v;
			else g.r = v;
		}
		
		cur.r = v.l;
		if(cur.r != null) cur.r.p = cur;
		
		cur.p = v;
		v.l = cur;
		if(cur == root) root = v;
		
		v.update();
		cur.update();
	}
	void splay(Node x, Node f){
		if(x == null) return ;
		//System.out.println("splay " + x.k);
		while(x.p != f){
			Node p = x.p;
			if(p.p == f){
				if(x == p.l){
					zig(p);
				}
				else{
					zag(p);
				}
			}else{
				Node g = p.p;
				if(g.l == p){
					if(p.l == x){
						zig(g); zig(p);
					}else{
						zag(p); zig(g);
					}
				}else{
					if(p.l == x){
						zig(p); zag(g);
					}else{
						zag(g); zag(p);
					}
				}
			}
		}
	}
	Node search(Node cur, int k){
		if(cur == null) return _hot;
		if(cur.k == k){
			splay(cur, null);
			return cur;
		}
		_hot = cur;
		if(k < cur.k) return search(cur.l, k);
		else return search(cur.r, k);
	}
	Node insert(Node cur, int k, int val){
		if(cur == null){
			cur = new Node(k, _hot, val);
			if(k < _hot.k) _hot.l = cur;
			else _hot.r = cur;
			_hot = cur;
			cur.update();
			//System.out.println("find place");
			splay(cur, null);
			//System.out.println(cur.k + " created");
			return cur;
		}
		_hot = cur;
		cur.send();
		if(k < cur.k) return insert(cur.l, k, val);
		else return insert(cur.r, k, val);
	}
	Node prev(int k){
		//System.out.println("search "+k);
		splay(search(root, k), null);
		Node cur = root.l;
		if(cur == null) return null;
		while(cur.r != null) cur = cur.r;
		return cur;
	}
	Node succ(int k){
		//System.out.println("search "+k);
		splay(search(root, k), null);
		Node cur = root.r;
		if(cur == null) return null;
		while(cur.l != null) cur = cur.l;
		return cur;
	}
	void splayInterval(int a, int b){
		//端点不存在则插入兴趣值为0的虚拟节点
		Node pa = search(root, a);
		if(pa.k != a) pa = insert(pa, a, 0);
		Node pb = search(root, b);
		if(pb.k != b) pb = insert(pb, b, 0);
		
		Node p = prev(a);
		Node s = succ(b);
		
		//System.out.println("prev="+p.k + " succ=" +s.k);
		
		splay(p, null);
		splay(s, p);
		Node q = s.l;
		_hot = q;
		//System.out.println("root of sub tree = " + _hot.k);
	}
	void deleteInterval(int a, int b){
		splayInterval(a, b);
		//释放子树空间
		_hot.p.l = null;
		_hot.p.update();
		//System.out.println("num of " + _hot.p.k + "=" +_hot.p.num);
		root.update();
		_hot = root;
	}
	long queryInterval(int a, int b){
		splayInterval(a, b);
		return _hot.totalVal;
	}
	void updateInterval(int a, int b, int d){
		splayInterval(a, b);
		//System.out.println("mark " + _hot.k);
		_hot.mark(d);
	}
	static final int MIN_K = 0;
	static final int MAX_K = 1000000005;
	public static void main(String[] args) throws FileNotFoundException {
		Splay mySplay = new Splay(MIN_K);
		mySplay.insert(mySplay.root, MAX_K, 0);
		
		File filename = new File("hiho105.txt");
		Scanner in = new Scanner(filename);
		int n = in.nextInt();
		//System.out.println(n);
		String c;
		int k, a, b;
		int val, d;
		for(int i=0; i<n; i++){
			c = in.next();
			//System.out.println(c);
			switch(c){
				case "I"://单点插入
					k = in.nextInt();
					val = in.nextInt();
					mySplay.insert(mySplay.root, k, val);
					break;
				case "Q"://区间查询
					a = in.nextInt(); b = in.nextInt();
					System.out.println(mySplay.queryInterval(a, b));
					break;
				case "M":
					a = in.nextInt(); b = in.nextInt(); d = in.nextInt();
					mySplay.updateInterval(a, b, d);
					break;
				case "D":
					a = in.nextInt(); b = in.nextInt();
					mySplay.deleteInterval(a, b);
					break;
				default: break;
			}
		}
	}
}