package Translate;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class ListIgnore {

  public ArrayList<String> dict_ignore = new ArrayList<String>();

  boolean reverse;

  public void change_reverse() {
    this.reverse = !this.reverse;
  }

  public boolean is_reverse() {
    return reverse;
  }
  public void dict_add(String word, String ing) {

    if (!dict_ignore.isEmpty()) {

      if (!dict_ignore.contains(word)) {

        dict_ignore.add(word);
      }
    } else {
      dict_ignore.add(word);
    }
  }

  public boolean dict_search(String word, boolean is_reverse) {

    int size = dict_ignore.size();
    boolean result = false;

    for (int iter = 0;iter < size;iter++) {

      if ((dict_ignore.get(iter)).equals(word)) {
        result = true;
        break;
      }

    }

    return result;
  }

  public void dict_dump_file(ListIgnore dict, String filename) {
    int size = dict_ignore.size();
    String word = null;
    FileWriter file = null;
    PrintWriter pw = null;

    try {

      file = new FileWriter(filename);
      pw = new PrintWriter(file);

      for (int iter = 0;iter < size;iter++) {
        word = dict_ignore.get(iter);

        pw.write(word + ",");

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

  public ListIgnore dict_from_file(ListIgnore NewDict, String filename) {
    File file = null;
    FileReader fr = null;
    BufferedReader br = null;

    String buffstring = null;
    String word = null;
    StringTokenizer token;

    file = new File(filename);

    if (file.exists()) {

      try {

        fr = new FileReader(file);
        br = new BufferedReader(fr);

        while ((buffstring = br.readLine()) != null ) {
          token = new StringTokenizer(buffstring, ",");
          while (token.hasMoreTokens()) {
            word = token.nextToken();

            NewDict.dict_add(word, null);
          }

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
        System.out.printf("\n\nIniciando lista de palabras en vacio \n");
      } catch (IOException ex) {

      }
    }
    return NewDict;
  }
}