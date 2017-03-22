package Translate;

public interface IDictionary {

  public void change_reverse();

  public boolean is_reverse();

  public abstract void dict_add(String spa, String ing);
  
  public abstract String dict_search(String word, boolean is_reverse);

  public abstract void dict_dump_file(IDictionary dict, String filename);

  public abstract IDictionary dict_from_file(IDictionary dict, String filename); 
}
