<?php include 'sessionlogin.php'; unloggedCheck();?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Change password</title>
    <link rel="stylesheet" href="css/style.css">
    <link rel="stylesheet" href="css/stylehome.css">
    <script>

    function validateFormModify(form) {
      var pw = form["pw"];
      var pw2 = form["pw2"];
      var opw = form["opw"];

      if(pw.value.length < 8 || pw.value.length > 16){
        errorMsg("passwordLength");
        return false;
      }

      if(pw.value != pw2.value){
        errorMsg("passwordMatch");
        return false;
      }
      //codigo para comprobar que la contraseña antigua (opw) es correcta
      return true;
    }

    function errorMsg(error) {
      switch(error) {
        case "passwordLength":
          document.getElementById("alert").style.display = "block";
          document.getElementById("alertMessage").innerHTML = "Password must be between 8 and 16 characters.";
          break;
        case "passwordMatch":
          document.getElementById("alert").style.display = "block";
          document.getElementById("alertMessage").innerHTML = "Password doesn´t match.";
          break;
        case "oldPassword":
          document.getElementById("alert").style.display = "block";
          document.getElementById("alertMessage").innerHTML = "Old password incorrect.";
          break;
      }
      return false;
    }
    function successMsg(success) {
      switch(success){
        case "modified":
          document.getElementById("alert").style.display = "block";
          document.getElementById("alertMessage").innerHTML = "Successly modified.";
          break;
      }
      return;
    }

    function closeError() {
      document.getElementById("alert").style.display = "none";
    }
  </script>
  </head>
  <body>
  <ul>
    <li><a href="home.php">Home</a></li>
    <li><a href="news.php">Recognicer</a></li>
    <li><a href="contact.php">Contact</a></li>
    <li style="float:right; color: white;">Hi <?php echo $_SESSION['name']; ?>. <a class="active" href="modify.php">Settings</a><a href="logout.php" class="button">Logout</a></li>
  </ul><br><br><br>
  <div class="login-page">
  <div id="alert" class="alert">
    <div class="background"></div>
    <div class="content">
      <div class="text-alert"><span id="alertMessage">Unexpected error.</span></div>
      <div class="button-alert"><a id="buttonAccept" class="button" onclick="closeError()">Accept</a></div>
    </div>
  </div>
  <div class="form">
    <form class="modify-form" method="POST" action="funcmodify.php" onsubmit="return validateFormModify(this)">
      <input type="text" placeholder="new password" name="pw" id="pw"/>
      <input type="text" placeholder="new password again" name="pw2" id="pw2">
      <input type="text" placeholder="old password" name="opw" id="opw"/>
      <button>modify</button>
    </form>
  </div>
</div>
    <script type="text/javascript">
      errorMsg("<?php echo $_GET['error'] ?>");
      successMsg("<?php echo $_GET['success'] ?>");
    </script>
  </body>
</html>
