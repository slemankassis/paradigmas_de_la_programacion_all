package Translate;
 
import java.io.IOException;
import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.GnuParser;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;

public class MainTranslate {

  static public void main(String[] args) throws IOException, ParseException {

    String inputfile = null;
    String dictfile = null;
    String outfile = null;
    String dict_ignore_file = null;

    DictArrayList dict_AL = null;
    DictLinkedList dict_LL = null;
    DictArrayList dict_temp_AL = null;
    DictLinkedList dict_temp_LL = null;

    IDictionary dict = null;
    IDictionary dict_temp = null;
    
    CommandLineParser parser = null;
    CommandLine cmdline = null;

    Options options = new Options();

    options.addOption("i", "input",     true,  "input file");
    options.addOption("m", "implementation", true, "implementation changes");
    options.addOption("d", "dict",      true,  "dict file");
    options.addOption("o", "out",       true,  "out file");
    options.addOption("g", "ignore",    true,  "dict ignore file");
    options.addOption("r", "reverse",   false, "reverse traduction");
    options.addOption("h", "help",      false, "help program");
    
    String helpmessage = ""
                + "   -i FILE | --input=FILE      : Documento de entrada. (Requerido)\n" 
                + "   -d FILE | --dictionary=FILE : Diccionario de traducción.\n" 
                + "   -g FILE | --ignored=FILE    : Diccionario de palabras ignoradas.\n" 
                + "   -o FILE | --output=FILE     : Archivo de salida.\n" 
                + "   -r      | --reverse         : Dirección de la traducción.\n"
                + "   -m 0 o 1| --implementation  : Cambia la implementacion a usar del"
                + " diccionario. (Requerido)\n";

    try {
      parser = new GnuParser();
      cmdline = parser.parse(options, args);

      ListIgnore dict_ignore = new ListIgnore();
      ListIgnore dict_ig_temp = new ListIgnore();

      if (cmdline.hasOption("m") && ("0".equals(cmdline.getOptionValue("m")) || 
                "1".equals(cmdline.getOptionValue("m")) )) {

        if ("0".equals(cmdline.getOptionValue("m"))) {
          dict_AL = new DictArrayList();
          dict_temp = new DictArrayList();
        } else {
          dict_LL = new DictLinkedList();
          dict_temp = new DictLinkedList();
        }
      } else {
        throw new org.apache.commons.cli.ParseException(
            "           El argumento debe ser 0 o 1 -m ARG");
      }
      
      if (cmdline.hasOption("i")) {
        inputfile = cmdline.getOptionValue("i");
      } else {
        throw new org.apache.commons.cli.ParseException(
            "           El archivo input es requerido -i ARG");
      }
      
      if (cmdline.hasOption("h")) {
        System.out.print(helpmessage);
        return;
      }

      if (cmdline.hasOption("d")) {
        dictfile = cmdline.getOptionValue("d");
      } else {
        dictfile = "dict.txt";
      }

      if (cmdline.hasOption("o")) {
        outfile = cmdline.getOptionValue("o");
      } else {
        outfile = "outsystem.txt";
      }

      if (cmdline.hasOption("g")) {
        dict_ignore_file = cmdline.getOptionValue("g");
      } else {
        dict_ignore_file = "ListIgnore.txt";
      }

      if (cmdline.hasOption("-r")) {
        if ("0".equals(cmdline.getOptionValue("m"))) {
          dict_AL.change_reverse();
        } else if ("1".equals(cmdline.getOptionValue("m"))) {
          dict_LL.change_reverse();
        } 
      }

      dict_ignore = (ListIgnore) dict_ignore.dict_from_file(dict_ignore,
                                        dict_ignore_file);
      
      if ("0".equals(cmdline.getOptionValue("m"))) {
        dict = dict_AL.dict_from_file(dict_AL, dictfile);
      } else if ("1".equals(cmdline.getOptionValue("m"))) {
        dict = dict_LL.dict_from_file(dict_LL, dictfile);
      }
      
      Translate.Translate(dict, dict_temp, dict_ignore, dict_ig_temp,
                        inputfile, outfile);

      dict.dict_dump_file(dict, dictfile);
      dict_ignore.dict_dump_file(dict_ignore, dict_ignore_file);

    } catch (ParseException ex) {
      System.out.println(ex.getMessage());
      System.out.print(helpmessage);

    } catch (java.lang.NumberFormatException ex) {
      System.out.print(helpmessage);
    }
  }
}