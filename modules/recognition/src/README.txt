1º Obviamente, instalar opencv. Recomiendo usar el método del cmake que sale en la página oficial para ello.
enlace: http://docs.opencv.org/3.2.0/d7/d9f/tutorial_linux_install.html

2º En cualquier carpeta tener los archivos recognizer.cpp, CMakeLists.txt y la imagen usada. Podemos hacerlo en la misma del github donde están pero creo que es preferible no hacerlo porque se generan archivos especificos para cada ordenador

3º Escribimos "cmake ." en la linea de comandos para que nos genere el Makefile

4º Para generar o actualizar el ejecutable del cpp hacemos "make"



======Cosas a tener en cuenta======
	- La imagen que se usa está definida dentro del cpp(convendría que se pase como argumento de entrada)
	- El cmake genera el makefile para el archivo que esté definido en CMakeLists.txt(en este caso recognizer.cpp)
