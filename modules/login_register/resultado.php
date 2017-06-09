<?php include 'sessionlogin.php'; unloggedCheck(); ?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Recognicer</title>
    <link rel="stylesheet" type="text/css" href="css/style.css">
    <link rel="stylesheet" href="css/stylehome.css">
    <link rel="stylesheet" type="text/css" href="css/stylenews.css">
  </head>
  <body>
  <div>
  <ul>
    <li><a href="home.php">Home</a></li>
    <li><a class="active" href="news.php">Recongnizer</a></li>
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
      <div>Esta persona es:
        <?php
          $myfile = fopen("/home/tester/1984/modules/recognition/src/name.txt", "r") or die("Unable to open file!");
          echo fread($myfile,filesize("/home/tester/1984/modules/recognition/src/name.txt"));
          fclose($myfile);
        ?>
      </div>
        <img src="<?php echo $_GET['image']?>" alt="recogniced">
    </div>

  </div>
  </body>
</html>
