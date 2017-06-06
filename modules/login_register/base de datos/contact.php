<?php include 'sessionlogin.php'; unloggedCheck();?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Home</title>
    <link rel="stylesheet" href="css/stylehome.css">
  </head>
  <body>
  <ul>
    <li><a href="home.php">Home</a></li>
    <li><a href="news.php">News</a></li>
    <li><a  class="active" href="contact.php">Contact</a></li>
    <li style="float:right; color: white;">Hi <?php echo $_SESSION['name']; ?>. <a href="modify.php">Settings</a><a href="logout.php" class="button">Logout</a></li>
  </ul><br><br><br>

  <div style="font-size: 32px; text-align: center;">Contact the admin lol.</div>

  </body>
</html
