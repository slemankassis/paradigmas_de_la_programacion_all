package Translate;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class DictArrayList implements IDictionary {
    
  public ArrayList<Pair> Dict = new ArrayList<Pair>();

  boolean reverse;

  @Override
  public void change_reverse() {
    this.reverse = !this.reverse;
  }

  @Override
  public boolean is_reverse() {
    return reverse;
  }
  
  @Override
  public void dict_add(String spa, String ing) {

    Pair pair = new Pair(spa, ing);

    if (!Dict.isEmpty()) {

      if (!Dict.contains(pair)) {

        Dict.add(pair);
      }
    } else {
      Dict.add(pair);
    }   

  }
    
  @Override
  public String dict_search(String word, boolean is_reverse) {

    int size = Dict.size();
    String result = null;

    for (int iter = 0;iter < size;iter++) {
      if (!(is_reverse)) {
        if (((Dict.get(iter)).getSpa()).equals(word)) {
          result = Dict.get(iter).getIng();
          break;
        }

      } else {
        if (((Dict.get(iter)).getIng()).equals(word)) {
          result = Dict.get(iter).getSpa();
          break;
        }
      }
    }
    return result;
  }

  @Override
  public void dict_dump_file(IDictionary dict, String filename) {

    int size = Dict.size();
    String spa = null;
    String ing = null;
    FileWriter file = null;
    PrintWriter pw = null;

    try {

      file = new FileWriter(filename);
      pw = new PrintWriter(file);

      for (int iter = 0;iter < size;iter++) {
        spa = (Dict.get(iter)).getSpa();
        ing = (Dict.get(iter)).getIng();

        pw.println(spa + "," + ing);

      } 

    } catch (Exception excep) {
      excep.printStackTrace();
    } finally {
      try {
        if (null != file) {
          file.close();
        }
      } catch (Exception excep2) {
        excep2.printStackTrace();
      }
    }
  }

  @Override
  public IDictionary dict_from_file (IDictionary NewDict, String filename) {

    File file = null;
    FileReader fr = null;
    BufferedReader br = null;

    String buffstring = null;
    String spa = null;
    String ing = null;
    StringTokenizer token;

    file = new File(filename);

    if (file.exists()) {

      try {

        fr = new FileReader(file);
        br = new BufferedReader(fr);

        while ((buffstring = br.readLine()) != null ) {
          token = new StringTokenizer(buffstring, ",");

          spa = token.nextToken();
          ing = token.nextToken();

          NewDict.dict_add(spa, ing);

        }
      } catch (Exception e) {
      } finally {
        try {
          if (null != fr) {
            fr.close();
          }
        } catch (Exception e2) {
          e2.printStackTrace();
        }
      }
    } else {
      try {
        file.createNewFile();
        System.out.printf("\n\nIniciando diccionario principal vacio \n");
      } catch (IOException ex) {

      }
    }
    return NewDict;
  }
}    
