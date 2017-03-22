
JC = javac
JVR = java -jar

name = Translate.jar

bin = bin/
cjar = jar -cvfm ../$(name) ../MANIFEST.MF Translate/MainTranslate Translate/*.class

sources = src/Translate/*.java
classes = $(sources:.java=.class)

all:
	$ mkdir -p bin
	$ javac -cp lib/*.jar $(sources) -d $(bin) 
	$ cd $(bin) && $(cjar)

clean:
	$(RM) -r $(bin)*
	$(RM) -r *.jar

