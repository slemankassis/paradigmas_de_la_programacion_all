package Translate;

import java.io.IOException;
import java.io.FileOutputStream;
import java.io.FileInputStream;

public class Translate {
    
  public static void Translate(IDictionary dict, IDictionary temp,
                                ListIgnore ignore, ListIgnore ignore_temp,
                            String input, String out) throws IOException {

    TryChar tc = new TryChar();
    OptionUser option = new OptionUser();

    boolean flagmayus = false;
    int iter = 0;
    int charForFile = 0;

    String word = "";
    String translate = "";
    FileInputStream file = null;
    FileOutputStream FileOut = null;

    try {
      file = new FileInputStream(input);

      FileOut = new FileOutputStream(out);

      charForFile = file.read();
      while (charForFile != -1) {

        iter++;
        while (charForFile != -1 && tc.ValidChar((char)charForFile)) {

          if (tc.is_mayus((char) charForFile)) {
            if (1 != iter) {
              flagmayus = true;
              iter--;
            }
            charForFile = tc.change_mayus_minus((char) charForFile);
          }

          word += (char) charForFile;
          charForFile = file.read();
        }
        if (!word.isEmpty()) {
          translate = dict.dict_search(word, dict.is_reverse());
          if (translate == null) {
            translate = temp.dict_search(word, dict.is_reverse());
            if (translate == null) {
              if (ignore_temp.dict_search(word, dict.is_reverse()) || 
                  ignore.dict_search(word, dict.is_reverse())
              ) {
                translate = word;
              } else {
                translate = option.word_user(dict, temp, ignore, ignore_temp, word);

              }
            }
          }
        }
        if (flagmayus) {
          translate = tc.change_mayus_minus(translate.charAt(0)) + 
                  translate.substring(1);
          flagmayus = false;
        }

        FileOut.write(translate.getBytes());
        FileOut.write(((char) charForFile));

        word = "";
        translate = "";
        charForFile = file.read();

      }

    } catch (Exception e) {
      e.printStackTrace();

    } finally {
      try {
        if (null != FileOut) {
          FileOut.close();
        }

      } catch (Exception e2) {
        e2.printStackTrace();
      }
    }
  }    
}
