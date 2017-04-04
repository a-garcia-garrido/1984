<?php
$con = mysql_connect('localhost','root','123')
or die('Could not connect to the server!');
mysql_select_db('web')
or die('Could not select a database.');
$nombre=$_POST['name'];
$email=$_POST['email'];
$pass=$_POST['pw'];

$sql = "SELECT nombre FROM usuario WHERE email='$email'";
$usuarios =  mysql_query($sql) or die('A error occured: ' . mysql_error());
if (mysql_num_rows($usuarios) == 1) {
  header('Location: index.php?error=register#alert');
} else {
  $sql = "INSERT INTO usuario (nombre, email, pass) VALUES('$nombre', '$email', '$pass')";
  $usuarios =  mysql_query($sql) or die('A error occured: ' . mysql_error());
  header('Location: index.php?success=register#alert');
}

?>
