<?php

session_start();

function loggedCheck(){
  if (isset($_SESSION['id'])) {
    header('Location: home.php');
  }
}

function unloggedCheck(){
  if (!isset($_SESSION['id'])) {
    session_unset();
    session_destroy();
    header('Location: index.php');
  }
}
?>
