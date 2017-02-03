package common;

import java.util.*;

public class Source {
	String filename;
	public List<String> ls;
	public List<String> getLs() {
		return ls;
	}
	public Source(){
		this("");
	}
	public Source(String filename){
		this.filename = filename;
		ls = new LinkedList<String>();
	}
}
