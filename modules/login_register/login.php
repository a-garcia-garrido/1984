<?php
session_start();
$con = mysql_connect('localhost','root','123')
    or die('Could not connect to the server!');
mysql_select_db('web')
    or die('Could not select a database.');
$email=$_POST['email'];
$pass=$_POST['pw'];

$sql = "SELECT id_us, nombre FROM usuario WHERE email='$email' AND pass='$pass'";
$usuarios =  mysql_query($sql) or die('A error occured: ' . mysql_error());
if (mysql_num_rows($usuarios) == 1) {
  $row = mysql_fetch_assoc($usuarios);
  $_SESSION['id'] = $row['id_us'];
  $_SESSION['name'] = $row['nombre'];
  header('Location: home.php');
} else {
  header('Location: index.php?error=login#alert');
}

?>
