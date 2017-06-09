<?php include 'sessionlogin.php'; unloggedCheck();?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Home</title>
    <link rel="stylesheet" type="text/css" href="css/style.css">
    <link rel="stylesheet" href="css/stylehome.css">
    <link rel="stylesheet" type="text/css" href="css/stylenews.css">
  </head>
  <body>
  <ul>
    <li><a class="active" href="home.php">Home</a></li>
    <li><a href="news.php">Recognizer</a></li>
    <li><a href="contact.php">Contact</a></li>
    <li style="float:right; color: white;">Hi <?php echo $_SESSION['name']; ?>. <a href="modify.php">Settings</a><a href="logout.php" class="button">Logout</a></li>
  </ul><br><br><br>

  <div class="main-container" style="font-size: 32px; text-align: center;">
    <br>
    <div class="write-container">
      This is the home page for the recognicer project of Oscar, Victor, Antonio, Andres, Jesus.
      The actual funcion of this page is to be used like a image uploader.
    </div>
  </div>
  </body>
</html>
