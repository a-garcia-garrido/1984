<?php include 'sessionlogin.php'; unloggedCheck(); ?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>News</title>
    <link rel="stylesheet" type="text/css" href="css/style.css">
    <link rel="stylesheet" href="css/stylehome.css">
    <link rel="stylesheet" type="text/css" href="css/stylenews.css">
  </head>
  <body>
  <div>
  <ul>
    <li><a href="home.php">Home</a></li>
    <li><a class="active" href="news.php">News</a></li>
    <li><a href="contact.php">Contact</a></li>
    <li style="float:right; color: white;">Hi <?php echo $_SESSION['name']; ?>. <a href="modify.php">Settings</a><a href="logout.php" class="button">Logout</a></li>
  </ul><br><br><br>
  </div>

  <div id="alert" class="alert">
    <div class="background"></div>
    <div class="content">
      <div class="text-alert"><span id="alertMessage">Error: default message</span></div>
      <div class="button-alert"><a id="buttonAccept" class="button" onclick="closeError();">Accept</a></div>
    </div>
  </div>

  <div class="main-container" style="font-size: 32px; text-align: center;">
  <br>
    <div class="write-container">
      <img src="<?php echo $_GET['image']?>" alt="recogniced">
      <div class="">
        <?php
          $fichero = file_get_contents('./gente.txt', FILE_USE_INCLUDE_PATH);
          echo $fichero;
        ?>
      </div>
    </div>

  </div>
  </body>
</html>
