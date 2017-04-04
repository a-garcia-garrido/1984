<?php
session_start();
$con = mysql_connect('localhost','root','123')
    or die('Could not connect to the server!');
mysql_select_db('web')
    or die('Could not select a database.');
$opass=$_POST['opw'];
$pass=$_POST['pw'];
$id = $_SESSION['id'];

$sql = "SELECT pass FROM usuario WHERE id_us='$id' AND pass='$opass'";
$usuarios = mysql_query($sql) or die('A error occured: ' . mysql_error());
if (mysql_num_rows($usuarios) == 1) {
  $sql = "UPDATE usuario SET pass='$pass' WHERE id_us='$id'";
  $update = mysql_query($sql) or die('A error occured: ' . mysql_error());
  header('Location: modify.php?success=modified#alert');
} else {
  header('Location: modify.php?error=oldPassword#alert');
}
?>
