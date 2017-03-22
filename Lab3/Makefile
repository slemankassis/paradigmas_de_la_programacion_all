OCC = ocamlc
OCO = ocamlopt 

all: clean cons compile

alld : clean cons compiledebug

.PHONY : src/%.mli
	  $(OCC) -c $<

compile :
	cd src; $(OCC) -c *.mli; $(OCO) -o juego cartas.ml jugador.ml ronda.ml main.ml; mv *.cmi ../bin/; mv *.cmx ../bin; mv *.o ../bin; mv juego ../bin/; cd ../bin/; ./juego

compiledebug :
	cd src; $(OCC) -g -c *.mli; $(OCO) -g -o juego cartas.ml jugador.ml ronda.ml main.ml; export OCAMLRUNPARAM=b; mv *.cmi ../bin/; mv *.cmx ../bin; mv *.o ../bin; mv juego ../bin/; cd ../bin/; ocamldebug juego

.PHONY : clean
clean :
	rm -f *~ *# *.byte .#*; rm -f bin/*.cmx bin/*.cmi bin/*.o; rm -rf bin

.PHONY : cons
cons :
	mkdir bin
