CREATE TABLE usuario(
  id_us INT PRIMARY KEY AUTO_INCREMENT,
  nombre VARCHAR(20),
  email VARCHAR(30) UNIQUE,
  pass VARCHAR(16)
);

CREATE TABLE comentario(
  id_com INT PRIMARY KEY AUTO_INCREMENT,
  id_us INT,
  titulo varchar(40),
  texto text(500),
  fechaCreacion DATETIME,
  CONSTRAINT fk_usarioComentario FOREIGN KEY (id_us) REFERENCES usuario (id_us)
);

CREATE TABLE respuestas(
  id_res INT PRIMARY KEY AUTO_INCREMENT,
  id_pdr INT,
  texto text (500),
  fechaPublica DATETIME,
  autor varchar(20),
  CONSTRAINT fk_ComentarioRespuestas FOREIGN KEY (id_pdr) REFERENCES comentario (id_com)
)
